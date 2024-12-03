package selective_repeat;

@license(LGPL);

import ned.IdealChannel;


network Network
{
    parameters:
        int WS = default(4);
        int SN = default(7);
        double TO = default(10);
        double PT = default(0.5);
        double TD = default(1.0);
        double ED = default(4.0);
        double DD = default(0.1);
        double LP = default(0  );
        string CRC_GENERATOR = default("110101");
        
        string FLAG_BYTE = default("$");
        string ESCAPE_BYTE = default("/");
        
        string LOG_FILE = default("../output.txt");
    submodules:
        node0: SelectiveRepeaterNode {
            @display("p=32.307693,66.15385");
        }
        node1: SelectiveRepeaterNode {
            @display("p=273.07693,66.15385");
        }
        coordinator: Coordinator {
            @display("p=152.3077,109.230774");
        }
    connections:
        coordinator.control0 --> IdealChannel --> node0.control;
        coordinator.control1 --> IdealChannel --> node1.control;
        node1.out --> IdealChannel --> node0.in;
        node0.out --> IdealChannel --> node1.in;
}

