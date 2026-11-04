#pragma once
#include <cstdint>
#include "memory.h"

class Cpu {
public:
    explicit Cpu(Memory& mem) : mem(mem) {}
    int step();

    uint16_t pc = 0x0100;
    uint16_t sp = 0xFFFE;

private:
    Memory& mem;

    uint8_t a = 0x01, f = 0xB0, b = 0x00, c = 0x13;
    uint8_t d = 0x00, e = 0xD8, h = 0x01, l = 0x4D;

    static constexpr uint8_t FLAG_Z = 0x80, FLAG_N = 0x40, FLAG_H = 0x20, FLAG_C = 0x10;

    void setFlag(uint8_t flag, bool on) {
        if (on) f |= flag; else f &= ~flag;
    }
    bool getFlag(uint8_t flag) const {return f & flag;}

    uint8_t fetch8() {return mem.read(pc++);}
    uint16_t fetch16() {uint8_t lo = fetch8(); uint8_t hi = fetch8(); return (hi << 8) | lo;}
};
