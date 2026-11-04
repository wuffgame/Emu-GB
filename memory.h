#pragma once
#include <cstdint>
#include <vector>

class Memory {
public:
    Memory() : data(0x10000, 0) {} // 64KB filled by 0

    void loadRom(const std::vector<uint8_t>& rom) {
        for (size_t i = 0; i < rom.size() && i < 0x8000; i++)
            data[i] = rom[i]; //without MBC
    }

    uint8_t read(uint16_t addr) const { return data[addr]; }

    void write(uint16_t addr, uint8_t value) {
        if (addr < 0x8000) return; // ROM only readable
        data[addr] = value;
    }

private:
    std::vector<uint8_t> data;
};