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

#ifndef __SELECTIVE_REPEAT_SELECTIVEREPEATERNODE_H_
#define __SELECTIVE_REPEAT_SELECTIVEREPEATERNODE_H_

#include <omnetpp.h>
#include <fstream>

#include "Frame_m.h"
#include "RawFrame_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */


struct FrameWithFlags {
    std::string flags;
    RawFrame_Base* frame;
};

struct SenderWindowEntry{
    RawFrame_Base* original_frame;
    cMessage* timer; // ack timer
    int sq_num;
};

struct ReceiverWindowEntry{
    Frame_Base* frame;
    bool recieved;
};

class SelectiveRepeaterNode : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
  private:
    int _node_id;
    std::ofstream _log;

    std::vector<FrameWithFlags> msgQueue;      // messages from the input file
    FrameWithFlags currentFrame;
    std::vector<ReceiverWindowEntry> receiverWindow;
    std::vector<SenderWindowEntry> senderWindow;
    int last_sent_sq     = 0;
    int expected_recv_sq = 0;
    int window_recv_start_sq = 0;
    bool nack_sent = false;
    cMessage* ackTimer;
    cMessage* processTimer;
    std::vector<RawFrame_Base*> processedFrames;

    void _start_as_sender();
    void _send_next_message();
};

#endif
