#include "cpu.h"
#include <cstdlib>
#include <iostream>

int Cpu::step() {
    uint8_t opcode = fetch8();

    switch (opcode) {
        case 0x00:  // NOP
            return 4;

        case 0xC3:  // JP a16
            pc = fetch16();
            return 16;

        case 0x3E:  // LD A, n8
            a = fetch8();
            return 8;

        case 0xAF:  // XOR A
            a = 0;
            f = 0;
            setFlag(FLAG_Z, true);
            return 4;

        case 0x18: {  // JR e8
            int8_t offset = (int8_t)fetch8();
            pc += offset;
            return 12;
        }

        default:
            std::cout << "Unimplemented opcode 0x" << std::hex << (int)opcode << " at PC=0x" << (pc - 1) << "\n";
            std::exit(1);
    }
}
