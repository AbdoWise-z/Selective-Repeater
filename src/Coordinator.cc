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

#include "Coordinator.h"
#include "common.h"
#include <regex>
#include <cstdio>

Define_Module(Coordinator);

void Coordinator::initialize()
{
    auto content = readFileAsString("../inputs/coordinator.txt");
    std::regex pattern(R"(\b(\d+)\b\s+\b(\d+)\b)");
    std::smatch match;

    if (!std::regex_search(content, match, pattern)) {
        EV << "Coodinator.txt contains invalid data." << "\n";
    }

    auto node = std::stoi(match[1].str());
    auto time = std::stoi(match[2].str());

    auto* msg = new cMessage();

    if (node == 0){
        msg->setName("control0");
    } else {
        msg->setName("control1");
    }

    EV << "START_TIME=" << time << ", START_NODE=" << node << std::endl;

    //
    // clear previous run log file
    //

    std::remove(pPar("LOG_FILE").stringValue());

    scheduleAt(time, msg);
}

void Coordinator::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()){
        std::string n = msg->getName();
        msg->setName("Start");
        send(msg, n.c_str());
    }
}
