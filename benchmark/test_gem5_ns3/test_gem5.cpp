#include <iostream>
#include <vector>
#include <cstdlib>
#include "apis_c.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <ID>" << std::endl;
        return -1;
    }

    int idX = atoi(argv[1]);
    int idY = 0;
    std::cout << "Process " << idX << " started." << std::endl;

   
    uint8_t buf[8] = {0};
    *(uint32_t*)buf = 0xDEADBEEF;

    if (idX == 0) {
        std::cout << "Process 0: Sending data to Process 1..." << std::endl;
	std::cout << "Process0 实际发送 =  0x" << std::hex << *(unsigned int*)buf << std::dec << std::endl;        
        InterChiplet::sendMessage(1, 0, idX, idY, buf, 8);
      
        InterChiplet::receiveMessage(idX, idY, 1, 0, buf, 8);
        std::cout << "Process 0: Received back from 1: " << std::hex << *(uint32_t*)buf << std::dec << std::endl;

    } else if (idX == 1) {
        std::cout << "Process 1: Waiting for data from Process 0..." << std::endl;
        
        InterChiplet::receiveMessage(idX, idY, 0, 0, buf, 8);
        
        uint32_t real_data = *(uint32_t*)buf;
        std::cout << std::hex << std::uppercase;
        std::cout << "Process1 实际收到 = 0x" << real_data << std::dec << std::endl;

        *(uint32_t*)buf = 0xABCDEFFF; // 回传值
        std::cout << "Process 1: Sending ack to Process 0..." << std::endl;
        // ===== 【顺带改】回传也传buf+长度8 =====
        InterChiplet::sendMessage(0, 0, idX, idY, buf, 8);
    }

    std::cout << "Process " << idX << " finished." << std::endl;
    return 0;
}
