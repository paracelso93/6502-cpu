#include "cpu.hh"
#include "tokens.hh"
#include <iostream>
#include <bitset>

int main() {
    CPU cpu(100);
    cpu.memory[0xFFFC] = (u8)0x00;
    cpu.memory[0xFFFD] = (u8)0x20;

    cpu.reset();
    cpu.memory[0x2000] = ADC_IM;
    cpu.ACC = 0b11111111;
    cpu.memory[0x2001] = 0b01111111;
    

    cpu.parse(cpu.fetch());
    std::cout << std::hex << (u16)cpu.ACC << std::endl;
    std::cout << std::dec << std::bitset<8>(cpu.flags) << std::endl;
    return 0;
}