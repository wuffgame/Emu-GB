#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include "cpu.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " hello-world.gb\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cout << "Cannot open file";
        return 1;
    }

    std::vector<uint8_t> rom(std::istreambuf_iterator<char>(file), {});

    std::cout << "Size of ROM: " << rom.size() << " bytes\n";

    std::cout << "Title: ";
    for (int i = 0x134; i <= 0x142; i++) {
        if (rom[i] != 0) std::cout << (char)rom[i];
    }
    std::cout << "\n";

    std::cout << "Cartridge type: 0x" << std::hex << (int)rom[0x147] << "\n";

    Memory mem;
    mem.loadRom(rom);
    Cpu cpu(mem);

    while (true) {
        cpu.step();
    }

    return 0;
}