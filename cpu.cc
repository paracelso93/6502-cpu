#include "cpu.hh"
#include "tokens.hh"
#include <cstdlib>
#include <cstring>
#include <iostream>

CPU::CPU(u16 cycles) : pc(0), sp(255), cycles(cycles) {
    memset(memory, 0, MAX_MEM);
}

void CPU::reset() {
    sp = 255;
    X = Y = ACC = 0;
    flags = 0;
    cycles = 0;
    pc |= memory[0xFFFC];
    pc |= memory[0xFFFD] << 8;
    std::cout << std::hex << pc << std::endl;
}

u16 CPU::get_stack_address(u8 ptr) {
    return STACK_START + ptr;
}

u8 CPU::fetch() {
    return memory[pc ++];
}

void CPU::parse(u8 instruction) {
    
    switch (instruction) {
        case LDA_IM: {
            u8 val = fetch();
            cycles += 2;
            ACC = memory[val];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_Z: {
            u8 val = fetch();
            cycles += 3;
            ACC = memory[val];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            //std::cout << std::hex << total << std::endl;
            ACC = memory[(u8)(total & 0x00FF)];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            ACC = memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + X;
            if ((total & 0xFF) < X) cycles++;
            ACC = memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + Y;
            if ((total & 0xFF) < Y) cycles++;
            ACC = memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_IND_X: {
            u8 val = fetch();
            cycles += 6;
            u8 address = val + X;
            u16 final = ((u16)memory[address] | ((u16)memory[address + 1] << 8));
            ACC = memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDA_IND_Y: {
            cycles += 5;
            u16 val = fetch();
            u16 address = ((u16)memory[val] | ((u16)memory[val + 1] << 8));
            u16 final = address + Y;
            if ((final & 0xFF) < Y) cycles++;
            ACC = memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;


        
        case LDX_IM: {
            u8 val = fetch();
            cycles += 2;
            X = memory[val];
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDX_Z: {
            u8 val = fetch();
            cycles += 3;
            X = memory[val];
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDX_Z_Y: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + Y;
            //std::cout << std::hex << total << std::endl;
            X = memory[(u8)(total & 0x00FF)];
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDX_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            X = memory[total];
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDX_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + Y;
            if ((total & 0xFF) < Y) cycles++;
            X = memory[total];
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;



        case LDY_IM: {
            u8 val = fetch();
            cycles += 2;
            Y = memory[val];
            if (Y == 0) flags |= FLAG_ZERO;
            if ((Y & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDY_Z: {
            u8 val = fetch();
            cycles += 3;
            Y = memory[val];
            if (Y == 0) flags |= FLAG_ZERO;
            if ((Y & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDY_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            //std::cout << std::hex << total << std::endl;
            Y = memory[(u8)(total & 0x00FF)];
            if (Y == 0) flags |= FLAG_ZERO;
            if ((Y & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDY_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            Y = memory[total];
            if (Y == 0) flags |= FLAG_ZERO;
            if ((Y & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case LDY_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + X;
            if ((total & 0xFF) < X) cycles++;
            Y = memory[total];
            if (Y == 0) flags |= FLAG_ZERO;
            if ((Y & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;



        case STA_Z: {
            u8 val = fetch();
            cycles += 3;
            memory[val] = ACC;
        } break;
        case STA_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            //std::cout << std::hex << total << std::endl;
            memory[(u8)(total & 0x00FF)] = ACC;
        } break;
        case STA_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            memory[total] = ACC;
        } break;
        case STA_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 5;
            u16 total = (val1 | (val2 << 8)) + X;
            memory[total] = ACC;
        } break;
        case STA_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 5;
            u16 total = (val1 | (val2 << 8)) + Y;
            memory[total] = ACC;
        } break;
        case STA_IND_X: {
            u8 val = fetch();
            cycles += 6;
            u8 address = val + X;
            u16 final = ((u16)memory[address] | ((u16)memory[address + 1] << 8));
            memory[final] = ACC;
        } break;
        case STA_IND_Y: {
            cycles += 6;
            u16 val = fetch();
            u16 address = ((u16)memory[val] | ((u16)memory[val + 1] << 8));
            u16 final = address + Y;
            memory[final] = ACC;
        } break;


        case STX_Z: {
            u8 val = fetch();
            cycles += 3;
            memory[val] = X;
        } break;
        case STX_Z_Y: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + Y;
            //std::cout << std::hex << total << std::endl;
            memory[(u8)(total & 0x00FF)] = X;
        } break;
        case STX_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            memory[total] = X;
        } break;


        case STY_Z: {
            u8 val = fetch();
            cycles += 3;
            memory[val] = Y;
        } break;
        case STY_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + Y;
            //std::cout << std::hex << total << std::endl;
            memory[(u8)(total & 0x00FF)] = Y;
        } break;
        case STY_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            memory[total] = Y;
        } break;


        case TAX: {
            X = ACC;
            cycles += 2;
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case TAY: {
            Y = ACC;
            cycles += 2;
            if (Y == 0) flags |= FLAG_ZERO;
            if ((Y & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case TSX: {
            X = sp;
            cycles += 2;
            if (X == 0) flags |= FLAG_ZERO;
            if ((X & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case TXA: {
            ACC = X;
            cycles += 2;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case TXS: {
            sp = X;
            cycles += 2;
        } break;
        case TYA: {
            ACC = Y;
            cycles += 2;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;

        
        case PHA: {
            memory[sp++] = ACC;
            cycles += 3;
        } break;
        case PHP: {
            memory[sp++] = flags;
            cycles += 3;
        } break;
        case PLA: {
            ACC = memory[--sp];
            cycles += 4;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case PLP: {
            flags = memory[--sp];
            cycles += 4;
        } break;


        case AND_IM: {
            u8 value = fetch();
            cycles += 2;
            ACC &= value;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_Z: {
            u8 val = fetch();
            cycles += 3;
            ACC &= memory[val];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            //std::cout << std::hex << total << std::endl;
            ACC &= memory[(u8)(total & 0x00FF)];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            ACC &= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + X;
            if ((total & 0xFF) < X) cycles++;
            ACC &= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + Y;
            if ((total & 0xFF) < Y) cycles++;
            ACC &= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_IND_X: {
            u8 val = fetch();
            cycles += 6;
            u8 address = val + X;
            u16 final = ((u16)memory[address] | ((u16)memory[address + 1] << 8));
            ACC &= memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case AND_IND_Y: {
            cycles += 5;
            u16 val = fetch();
            u16 address = ((u16)memory[val] | ((u16)memory[val + 1] << 8));
            u16 final = address + Y;
            if ((final & 0xFF) < Y) cycles++;
            ACC &= memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;



        case EOR_IM: {
            u8 value = fetch();
            cycles += 2;
            ACC ^= value;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_Z: {
            u8 val = fetch();
            cycles += 3;
            ACC ^= memory[val];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            //std::cout << std::hex << total << std::endl;
            ACC ^= memory[(u8)(total & 0x00FF)];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            ACC ^= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + X;
            if ((total & 0xFF) < X) cycles++;
            ACC ^= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + Y;
            if ((total & 0xFF) < Y) cycles++;
            ACC ^= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_IND_X: {
            u8 val = fetch();
            cycles += 6;
            u8 address = val + X;
            u16 final = ((u16)memory[address] | ((u16)memory[address + 1] << 8));
            ACC ^= memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case EOR_IND_Y: {
            cycles += 5;
            u16 val = fetch();
            u16 address = ((u16)memory[val] | ((u16)memory[val + 1] << 8));
            u16 final = address + Y;
            if ((final & 0xFF) < Y) cycles++;
            ACC ^= memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;


        case ORA_IM: {
            u8 value = fetch();
            cycles += 2;
            ACC |= value;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_Z: {
            u8 val = fetch();
            cycles += 3;
            ACC |= memory[val];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            //std::cout << std::hex << total << std::endl;
            ACC |= memory[(u8)(total & 0x00FF)];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            ACC |= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + X;
            if ((total & 0xFF) < X) cycles++;
            ACC |= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + Y;
            if ((total & 0xFF) < Y) cycles++;
            ACC |= memory[total];
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_IND_X: {
            u8 val = fetch();
            cycles += 6;
            u8 address = val + X;
            u16 final = ((u16)memory[address] | ((u16)memory[address + 1] << 8));
            ACC |= memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ORA_IND_Y: {
            cycles += 5;
            u16 val = fetch();
            u16 address = ((u16)memory[val] | ((u16)memory[val + 1] << 8));
            u16 final = address + Y;
            if ((final & 0xFF) < Y) cycles++;
            ACC |= memory[final];

            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;


        case BIT_Z: {
            u8 val = fetch();
            u8 result = val & ACC;
            if (result == 0) flags |= FLAG_ZERO;
            if ((result & 0b01000000) != 0) flags |= FLAG_OVERFLOW;
            if ((result & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case BIT_ABS: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            u8 result = memory[total] & ACC;
            if (result == 0) flags |= FLAG_ZERO;
            if ((result & 0b01000000) != 0) flags |= FLAG_OVERFLOW;
            if ((result & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;


        case ADC_IM: {
            u8 value = fetch();
            cycles += 2;
            u8 temp = ACC;
            u16 result = (u16)ACC + (u16)value;
            ACC = (u8)(result & 0xFF);
            std::cout << (i16)temp << "," << (i16)value << "," << (i16)ACC << std::endl;
            if (positive(temp) && positive(value) && !positive(ACC)) {
                flags |= FLAG_OVERFLOW;
                std::cout << "OBAMA" << std::endl;
            }
            if (!positive(temp) && !positive(value) && positive(ACC)) flags |= FLAG_OVERFLOW;
            
            if (ACC < ((u16)value + temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_Z: {
            u8 val = fetch();
            cycles += 3;
            u8 temp = ACC;
            u16 result = (u16)ACC + (u16)memory[val];
            ACC = (u8)(result & 0xFF);
            if ((i8)temp > 0 && (i8)memory[val] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[val] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[val] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_Z_X: {
            u8 val = fetch();
            cycles += 4;
            u16 total = val + X;
            u8 temp = ACC;
            //std::cout << std::hex << total << std::endl;
            ACC += memory[(u8)(total & 0xFF)];
            if ((i8)temp > 0 && (i8)memory[(u8)(total & 0xFF)] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[(u8)(total & 0xFF)] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[(u8)(total & 0xFF)] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_ABS: {

            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8));
            u8 temp = ACC;
            ACC += memory[total];
            
            if ((i8)temp > 0 && (i8)memory[total] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[total] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[total] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_ABS_X: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + X;
            if ((total & 0xFF) < X) cycles++;
            u8 temp = ACC;
            ACC += memory[total];
            if ((i8)temp > 0 && (i8)memory[total] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[total] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[total] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_ABS_Y: {
            u16 val1 = fetch();
            u16 val2 = fetch();
            cycles += 4;
            u16 total = (val1 | (val2 << 8)) + Y;
            if ((total & 0xFF) < Y) cycles++;
            u8 temp = ACC;
            ACC += memory[total];
            if ((i8)temp > 0 && (i8)memory[total] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[total] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[total] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_IND_X: {
            u8 val = fetch();
            cycles += 6;
            u8 address = val + X;
            u16 final = ((u16)memory[address] | ((u16)memory[address + 1] << 8));
            u8 temp = ACC;
            ACC += memory[final];
            if ((i8)temp > 0 && (i8)memory[final] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[final] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[final] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;
        case ADC_IND_Y: {
            cycles += 5;
            u16 val = fetch();
            u16 address = ((u16)memory[val] | ((u16)memory[val + 1] << 8));
            u16 final = address + Y;
            if ((final & 0xFF) < Y) cycles++;
            u8 temp = ACC;
            ACC += memory[final];

            if ((i8)temp > 0 && (i8)memory[final] > 0 && (i8)ACC < 0) flags |= FLAG_OVERFLOW;
            if ((i8)temp < 0 && (i8)memory[final] < 0 && (i8)ACC > 0) flags |= FLAG_OVERFLOW;
            
            if ((u16)ACC < ((u16)memory[final] + (u16)temp)) flags |= FLAG_CARRY;
            if (ACC == 0) flags |= FLAG_ZERO;
            if ((ACC & 0b10000000) != 0) flags |= FLAG_NEGATIVE;
        } break;

        default: std::cerr << "Unhandled instruction: " << std::hex << instruction << std::endl;
    }
}