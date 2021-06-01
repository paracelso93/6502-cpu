#pragma once

#include "defines.hh"

static constexpr u32 MAX_MEM = 0xFFFF;
static constexpr u32 STACK_START = 0x0100;

enum Flags: u8 {
    FLAG_CARRY = 0b00000001,
    FLAG_ZERO = 0b00000010,
    FLAG_INTERRUPT_DISABLE = 0b00000100,
    FLAG_DECIMAL = 0b00001000, // Decimal Mode
    FLAG_BREAK = 0b00010000,
    FLAG_OVERFLOW = 0b01000000,
    FLAG_NEGATIVE = 0b10000000,
};

class CPU {
public:
    u16 pc; // Program Counter
    u8 sp; // Stack Pointer
    u8 memory[MAX_MEM];

    /* REGISTER */
    u8 ACC = 0; // Accumulator
    u8 X = 0, Y = 0;
    
    u8 flags = 0;
    u16 cycles = 0;
    void reset();
    u8 fetch();
    u16 get_stack_address(u8 ptr);
    void parse(u8 instruction);
    CPU(u16 cycles);

    bool positive(u8 value) const {
        return !(value & 0b10000000);
    }
};