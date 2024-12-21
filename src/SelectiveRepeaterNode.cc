//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "SelectiveRepeaterNode.h"
#include "common.h"
#include "byte_utils.h"
#include "crc.h"

Define_Module(SelectiveRepeaterNode);


static inline bool inCircular(int p, int start, int end, int mod){
    if (end > start) {
        return p >= start && p < end;
    }
    return (p >= start && p < mod) || (p < end);
}

void SelectiveRepeaterNode::_start_as_sender() {
    auto input_file_name = "../inputs/input" + std::to_string(_node_id) + ".txt";
    auto lines = readFileLines(input_file_name);
    msgQueue.clear();

    for (const auto& packet : lines){
        auto flags = packet.substr(0, 4); //1111 some text here
        auto message = packet.substr(5, packet.length() - 5);
        std::cout << "Flags=" << flags << ", Message=" << message << std::endl;
        auto* frame = new RawFrame_Base();

        auto payload = to_bit_stream(
            performByteStuffing(
                message,
                pPar("FLAG_BYTE").stringValue()[0],
                pPar("ESCAPE_BYTE").stringValue()[0]
            )
         );

        frame->setM_payload(
            payload.c_str()
        );

        frame->setM_Trailer(calculateCRC(payload, pPar("CRC_GENERATOR").stringValue()).c_str());
        frame->setM_Type(2);     // DATA
        frame->setM_header(0);   // will be set later
        frame->setM_Target(-1);  // useless

        FrameWithFlags fwf{};
        fwf.frame = frame;
        fwf.flags = flags;

        msgQueue.push_back(fwf);
    }

    std::cout << "Added: " << msgQueue.size() << " to the queue." << std::endl;

    _send_next_message();
}

void SelectiveRepeaterNode::_send_next_message() {
    if (processTimer->isScheduled()) {
        return; // already processing a packet
    }

    if (processSchedular.size() != 0) {
        // EV << "_send_next_message() called while process queue wasn't empty." << std::endl;
        // start processing the next one
        scheduleAfter(pPar("PT").doubleValue() , processTimer);
        return;
    }

    int WS = pPar("WS").intValue();
    if (senderWindow.size() >= WS || msgQueue.size() == 0) {
        return; // we can't send any more messages
    }


    auto next = msgQueue[0];
    msgQueue.erase(msgQueue.begin());

    // EV << "Sending: " << reverseByteStuffing(from_bit_stream(next.frame->getM_payload()), pPar("ESCAPE_BYTE").stringValue()[0] ) << std::endl;
    _log << "At time [" << simTime() << "], Node[" << _node_id << "] , Introducing channel error with code =[" << next.flags << "]." << std::endl;
    EV << "At time [" << simTime() << "], Node[" << _node_id << "] , Introducing channel error with code =[" << next.flags << "]." << std::endl;

    bool is_modified   = next.flags[0] == '1';
    bool is_lost       = next.flags[1] == '1';
    bool is_duplicated = next.flags[2] == '1';
    bool is_delayed    = next.flags[3] == '1';

    SenderWindowEntry ent {};
    ent.original_frame = next.frame;
    ent.sq_num = (last_sent_sq++) % (pPar("SN").intValue() + 1);

    std::string timer_name = "Timer-";
    timer_name += std::to_string(ent.sq_num);
    ent.timer = new cMessage(timer_name.c_str());

    senderWindow.push_back(ent);

    // now process the errors
    std::vector<RawFrame_Base*> frames;
    frames.push_back(next.frame->dup());

    if (is_duplicated) {
        frames.push_back(next.frame->dup());
    }

    if (is_modified) {
        for (auto& frame: frames) {
            std::string payload = frame->getM_payload();
            int _bit = int(uniform(0, payload.size()));
            payload[_bit] = payload[_bit] == '1' ? '0' : '1'; // flip it
            frame->setM_payload(payload.c_str());
            frame->setModified_bit(_bit);
        }
    }

    for (int i = 0;i < frames.size();i++) {
        auto& frame = frames[i];
        frame->setM_header(senderWindow.back().sq_num);
        frame->setDup_index(is_duplicated + i);
        frame->setChannel_delay(is_delayed ? pPar("ED").doubleValue() : 0.0);
        frame->setIs_lost(is_lost);
    }


    ProcessResult result;
    result.associated_timer = ent.timer;
    result.frames = frames;
    processSchedular.push_back(result);
    scheduleAfter(pPar("PT").doubleValue() , processTimer);
}


void SelectiveRepeaterNode::initialize()
{
    auto name = getName();
    auto len = strlen(name);
    _node_id = name[len - 1] == '0' ? 0 : 1;

    for (int i = 0;i < pPar("WS").intValue();i++) { // allocate the receiver window
        ReceiverWindowEntry ent{};
        ent.recieved = false;
        ent.frame = nullptr;
        receiverWindow.push_back(ent);
    }

    nack_sent = false;
    // ackTimer = new cMessage("ack_timer");
    processTimer = new cMessage("process_timer");

    _log.open(pPar("LOG_FILE").stringValue(), std::ios::app);
}


void SelectiveRepeaterNode::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        auto frame = dynamic_cast<Frame_Base*>(msg);
        auto rawFrame = dynamic_cast<RawFrame_Base*>(msg);

        if (frame) {
            // redirect message .. now send
            send(msg, "out");
            // EV <<"Node[" << _node_id << "] Frame: "<< frame->getM_header() << ", " << frame->getM_Target() << " is out" << std::endl;
            if (frame->getM_payload() != nullptr) {
                std::string p = frame->getM_payload();
                if (p.size() > 16){ // at least 2 flags
                    // EV << "\t" << reverseByteStuffing(from_bit_stream(frame->getM_payload()), pPar("ESCAPE_BYTE").stringValue()[0] ) << std::endl;
                }
            }
        }
        else if (rawFrame) {
            if (rawFrame->getM_Type() == 2) { // data
                _log << "At time ["
                     << (simTime())
                     << "], Node[" << _node_id
                     << "] [sent] frame with seq_num=["
                     << rawFrame->getM_header()
                     << "] and payload=["
                     << from_bit_stream(rawFrame->getM_payload())
                     << "] and trailer=["
                     << rawFrame->getM_Trailer()
                     << "] , Modified ["
                     << (rawFrame->getModified_bit())
                     << "] , Lost ["
                     << (rawFrame->getIs_lost() ? "Yes" : "No")
                     << "], Duplicate ["
                     << (rawFrame->getDup_index())
                     << "], Delay ["
                     << (rawFrame->getChannel_delay())
                     << "]"
                     << std::endl;

                EV << "At time ["
                   << (simTime())
                   << "], Node[" << _node_id
                   << "] [sent] frame with seq_num=["
                   << rawFrame->getM_header()
                   << "] and payload=["
                   << from_bit_stream(rawFrame->getM_payload())
                   << "] and trailer=["
                   << rawFrame->getM_Trailer()
                   << "] , Modified ["
                   << (rawFrame->getModified_bit())
                   << "] , Lost ["
                   << (rawFrame->getIs_lost() ? "Yes" : "No")
                   << "], Duplicate ["
                   << (rawFrame->getDup_index())
                   << "], Delay ["
                   << (rawFrame->getChannel_delay())
                   << "]"
                   << std::endl;

                // construct the real frame
                auto f = new Frame_Base();
                f->setM_Target(rawFrame->getM_Target());
                f->setM_header(rawFrame->getM_header());
                f->setM_payload(rawFrame->getM_payload());
                f->setM_Type(rawFrame->getM_Type());
                f->setM_Trailer(rawFrame->getM_Trailer());

                if (!rawFrame->getIs_lost()){
                    scheduleAfter(rawFrame->getChannel_delay() + pPar("TD").doubleValue(), f);
                }
            } else { // ACK-NACK
                auto lb = pPar("LP").doubleValue();
                volatile double rand = uniform(0, 1);
                bool drop = rand < lb;

                if (!drop){
                    auto f = new Frame_Base();
                    f->setM_Type(rawFrame->getM_Type());
                    f->setM_Target(rawFrame->getM_Target());
                    scheduleAfter(pPar("TD").doubleValue(), f);
                    // EV << "Receiver: Sending " << (f->getM_Type() == 1 ? "ACK" : "NACK") << "-" << f->getM_Target() << std::endl;
                }
                _log << "At time["
                        << simTime()
                        << "], Node["
                        << _node_id
                        << "] Sending ["
                        << (rawFrame->getM_Type() == 1 ? "ACK" : "NACK")
                        << "] with number ["
                        << rawFrame->getM_Target()
                        << "] , loss ["
                        << (drop ? "Yes" : "No")
                        << "]" << std::endl;

                EV << "At time["
                   << simTime()
                   << "], Node["
                   << _node_id
                   << "] Sending ["
                   << (rawFrame->getM_Type() == 1 ? "ACK" : "NACK")
                   << "] with number ["
                   << rawFrame->getM_Target()
                   << "] , loss ["
                   << (drop ? "Yes" : "No")
                   << "]" << std::endl;
            }
        }
        else if (strcmp(msg->getName(), "process_timer") == 0) {
            // successful process
            auto result = processSchedular[0];
            processSchedular.erase(processSchedular.begin());

            for (auto pf : result.frames) {
                // send the frames on the virtual channel (self message)
                scheduleAfter(pf->getDup_index() != 0 ? (pf->getDup_index() - 1) * pPar("DD").doubleValue() : 0, pf);
            }

            if (result.associated_timer != nullptr){
                // if this should set a timer .. then set it
                scheduleAfter(pPar("TO").doubleValue(), result.associated_timer);
            }

            _send_next_message();
        }
        else if (strcmp(msg->getName(), "ack_timer") == 0) {
            // not mentioned in the project document ..
//            auto f = new RawFrame_Base();
//            f->setM_Type(1);
//            f->setM_Target(expected_recv_sq);
//            f->setIs_lost(true);
//            scheduleAfter(pPar("PT").doubleValue(), f);
        }
        else {
            //timer
            for (auto& ent : senderWindow) {
                if (ent.timer == msg) {
                    // re-send

                    if (processTimer->isScheduled()) {
                        // roll-back last frame we were processing
//                        EV << "Rolled Back: "
//                           << ( processSchedular.front().frames[0]->getM_Type() == 2 ?
//                                   reverseByteStuffing(from_bit_stream(processSchedular.front().frames[0]->getM_payload()), pPar("ESCAPE_BYTE").stringValue()[0] )
//                                   : (processSchedular.front().frames[0]->getM_Type() == 0 ? "NACK" : "ACK") )
//                           << std::endl;
                        cancelEvent(processTimer);
                    }

//                    EV << "Timeout on: " << ent.sq_num << std::endl;
                    auto f = new RawFrame_Base();
                    f->setM_Target(ent.original_frame->getM_Target());
                    f->setM_header(ent.sq_num);
                    f->setM_payload(ent.original_frame->getM_payload());
                    f->setM_Type(ent.original_frame->getM_Type());
                    f->setM_Trailer(ent.original_frame->getM_Trailer());

                    _log << "Time out event at time [" << simTime() << "], at Node["
                         << _node_id << "] for frame with seq_num=[" << ent.sq_num << "]\n";
                    EV << "Time out event at time [" << simTime() << "], at Node["
                       << _node_id << "] for frame with seq_num=[" << ent.sq_num << "]\n";

                    ProcessResult result;
                    result.frames.push_back(f);
                    result.associated_timer = ent.timer;
                    processSchedular.insert(processSchedular.begin(), result);
                    scheduleAfter(0.001 + pPar("PT").doubleValue(), processTimer);
                    break;
                }
            }
        }
        return;
    }

    if (strcmp(msg->getArrivalGate()->getBaseName(), "control") == 0) {
        // process coordinator message
        // the only message would be "START"
        // so start processing packets from input file :)
        _start_as_sender();
    } else {

        auto* frame = dynamic_cast<Frame_Base*>(msg);
        if (!frame) {
            throw std::runtime_error("somehow got something other than a frame in receiving logic");
        }

        if (frame->getM_Type() == 2) { // DATA
            // Receiver code
            // check if we can receive it
            auto sq = frame->getM_header();
//            EV << "Received Data At: " << simTime() << std::endl;

            auto window_start = window_recv_start_sq;
            auto window_end   = (window_recv_start_sq + pPar("WS").intValue()) % (pPar("SN").intValue() + 1);
//            EV << "Receiver Window: " << window_start << " -> " << window_end << std::endl;

            std::string payload = frame->getM_payload();
            std::string crc     = frame->getM_Trailer();

            if (!inCircular(sq, window_start, window_end, pPar("SN").intValue() + 1)) {
                // frame is outside of the window, drop
                // EV << "Receiver: Packet dropped (out of window)" << std::endl;
            } else {
                if (evaluateCRC(payload + crc, pPar("CRC_GENERATOR").stringValue())) {
                    // EV << "Receiver: CRC OK [" << sq << "] \"" << reverseByteStuffing(from_bit_stream(frame->getM_payload()), pPar("ESCAPE_BYTE").stringValue()[0] ) << "\"" << std::endl;
                    // valid packet
                    if (inCircular(sq, window_start, window_end, pPar("SN").intValue() + 1)) {
                        if (sq != expected_recv_sq && nack_sent){
                            auto f = new RawFrame_Base(); // send ACK if a NACK has already been sent and the packet is out of order
                            f->setM_Type(1);
                            f->setM_Target(expected_recv_sq);
                            scheduleAfter(pPar("PT").doubleValue(), f);
                            // EV << "Receiver: Sending ACK (out of order)" << std::endl;
                        }

                        if (sq != expected_recv_sq && !nack_sent) {
                            nack_sent = true; // send a NACK
                            auto f = new RawFrame_Base();
                            f->setM_Type(0);
                            f->setM_Target(expected_recv_sq);
                            scheduleAfter(pPar("PT").doubleValue(), f);
                            // EV << "Receiver: Sending NACK (out of order)" << std::endl;
                        }

                        // EV << "Receiver: Packet in the Receive Window" << std::endl;
                        auto& rs = receiverWindow[sq % pPar("WS").intValue()];
                        if (!rs.recieved) {
                            rs.frame = frame;
                            rs.recieved = true;
                            auto is_expected = receiverWindow[expected_recv_sq % pPar("WS").intValue()].recieved;
                            int move_count = 0;
                            while (receiverWindow[expected_recv_sq % pPar("WS").intValue()].recieved) {
                                // TO Network layer
                                nack_sent = false;
                                auto& curr = receiverWindow[expected_recv_sq % pPar("WS").intValue()];
                                curr.recieved = false;
                                auto original = from_bit_stream(curr.frame->getM_payload());

                                _log << "Uploading payload=["
                                        << reverseByteStuffing(original, pPar("ESCAPE_BYTE").stringValue()[0])
                                        << "] and seq_num=["
                                        << curr.frame->getM_header()
                                        << "] to the network layer" << std::endl;

                                EV << "Uploading payload=["
                                     << reverseByteStuffing(original, pPar("ESCAPE_BYTE").stringValue()[0])
                                     << "] and seq_num=["
                                     << curr.frame->getM_header()
                                     << "] to the network layer" << std::endl;

                                expected_recv_sq = (expected_recv_sq + 1) % (pPar("SN").intValue() + 1);
                                move_count ++;
                            }
                            // EV << "Moving Receiver Window: " << move_count << std::endl;
                            window_recv_start_sq = expected_recv_sq;
                            if (is_expected){
                                auto f = new RawFrame_Base();
                                f->setM_Type(1); // ACK
                                f->setM_Target(expected_recv_sq);
                                scheduleAfter(pPar("PT").doubleValue(), f);
                            } else {
                                // EV << "Out of order" << std::endl;
                            }
                        } else {
                            // EV << "Receiver: Packet dropped (already exists)" << std::endl;
                        }
                    } else {
                        // EV << "Receiver: Packet dropped (out of window)" << std::endl;
                    }
                } else {
                    // EV << "Receiver: CRC ERROR [" << sq << "]" << std::endl;
                }
            }

//            else {
//                EV << "Receiver: CRC ERROR [" << sq << "]" << std::endl;
//                // checksum (CRC) error
//                if (!nack_sent && sq == expected_recv_sq) { // if no nack was sent. send NACK
//                    nack_sent = true; // send a nack
//                    auto f = new RawFrame_Base();
//                    f->setM_Type(0);
//                    f->setM_Target(expected_recv_sq);
//                    scheduleAfter(pPar("PT").doubleValue(), f);
//                    EV << "Receiver: Sending NACK (CRC)" << std::endl;
//                }
//            }
        } else { // ACK-NACK
            // EV << "Received [ACK/NACK]: " << frame->getM_Target() << std::endl;
            auto target = frame->getM_Target() - 1;
            if (target < 0){
                target += pPar("SN").intValue() + 1;
            }

            if (frame->getM_Type() == 0) {
                // NACK
                // re-send the expected frame
                auto it = senderWindow.begin();
                while (it != senderWindow.end()) {
                    if (it->sq_num == frame->getM_Target()) {
                        // EV << "Re-sending NACK Packet" << std::endl;

                        if (processTimer->isScheduled()) {
                            // roll-back last frame we were processing
//                            EV << "Rolled Back: "
//                               << ( processSchedular.front().frames[0]->getM_Type() == 2 ?
//                                       reverseByteStuffing(from_bit_stream(processSchedular.front().frames[0]->getM_payload()), pPar("ESCAPE_BYTE").stringValue()[0] )
//                                    : (processSchedular.front().frames[0]->getM_Type() == 0 ? "NACK" : "ACK") )
//                               << std::endl;

                            cancelEvent(processTimer);
//                            cancelEvent(senderWindow.back().timer);
//                            senderWindow.pop_back();
//                            last_sent_sq--;
//                            if (last_sent_sq < 0){
//                                last_sent_sq += pPar("SN").intValue();
//                            }
//                            msgQueue.insert(msgQueue.begin(), currentFrame);
                        }

                        auto f = new RawFrame_Base();
                        f->setM_Target(it->original_frame->getM_Target());
                        f->setM_header(it->sq_num);
                        f->setM_payload(it->original_frame->getM_payload());
                        f->setM_Type(it->original_frame->getM_Type());
                        f->setM_Trailer(it->original_frame->getM_Trailer());

                        cancelEvent(it->timer);

                        ProcessResult result;
                        result.frames.push_back(f);
                        result.associated_timer = nullptr;
                        processSchedular.insert(processSchedular.begin(), result);
                        scheduleAfter(0.001 + pPar("PT").doubleValue(), processTimer);
                        break;
                    }
                    ++it;
                }
            }

            // clear received frames
            auto it = senderWindow.begin();
            while (it != senderWindow.end()) {
                if (it->sq_num == target) break;
                ++it;
            }

            if (it != senderWindow.end()) {
                int i = 0;
                auto break_sq = it->sq_num;
                while (senderWindow.size()){
                    auto sq = senderWindow[0].sq_num;
                    cancelEvent(senderWindow[0].timer);
                    senderWindow.erase(senderWindow.begin());
                    i++;
                    if (sq == break_sq){
                       break;
                    }
                }
                // EV << "Moving Sender Window: " << i << std::endl;
                _send_next_message();
            }
        }
    }
}
