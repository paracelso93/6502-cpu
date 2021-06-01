#pragma once

enum Tokens {
    LDA_IM = 0xA9,
    /*
    A <- memory[immediate]
    */
    LDA_Z = 0xA5,
    /*
    A <- memory[immediate < 0xFF]
    */
    LDA_Z_X = 0xB5,
    /*
    A <- memory[immediate + X < 0xFF]
    */
    LDA_ABS = 0xAD,
    /*
    A <- memory[immediate | immediate2 << 8]
    */
    LDA_ABS_X = 0xBD,
    /*
    A <- memory[(immediate | immediate2 << 8) + X]
    */
    LDA_ABS_Y = 0xB9,
    /*
    A <- memory[(immediate | immediate2 << 8) + Y]
    */
    LDA_IND_X = 0xA1,
    /*
    ADDRESS = immediate + X
    A <- memory[memory[ADDRESS] | (memory[ADDRESS + 1] << 8)]
    */
    LDA_IND_Y = 0xB1,
    /*
    ADDRESS = memory[immediate] | (memory[immediate + 1] << 8)
    A <- memory[ADDRESS + Y]
    */



    LDX_IM = 0xA2,
    /*
    X <- memory[immediate]
    */
    LDX_Z = 0xA6,
    /*
    X <- memory[immediate < 0xFF]
    */
    LDX_Z_Y = 0xB6,
    /*
    X <- memory[immediate + Y < 0xFF]
    */
    LDX_ABS = 0xAE,
    /*
    X <- memory[immediate | immediate2 << 8]
    */
    LDX_ABS_Y = 0xBE,
    /*
    X <- memory[(immediate | immediate2 << 8) + Y]
    */



   LDY_IM = 0xA0,
    /*
    Y <- memory[immediate]
    */
    LDY_Z = 0xA4,
    /*
    Y <- memory[immediate < 0xFF]
    */
    LDY_Z_X = 0xB4,
    /*
    Y <- memory[immediate + X < 0xFF]
    */
    LDY_ABS = 0xAC,
    /*
    Y <- memory[immediate | immediate2 << 8]
    */
    LDY_ABS_X = 0xBC,
    /*
    Y <- memory[(immediate | immediate2 << 8) + X]
    */


    STA_Z = 0x85,
    /*
    A -> memory[immediate < 0xFF]
    */
    STA_Z_X = 0x95,
    /*
    A -> memory[immediate + X < 0xFF]
    */
    STA_ABS = 0x8D,
    /*
    A -> memory[immediate | immediate2 << 8]
    */
    STA_ABS_X = 0x9D,
    /*
    A -> memory[(immediate | immediate2 << 8) + X]
    */
    STA_ABS_Y = 0x99,
    /*
    A -> memory[(immediate | immediate2 << 8) + Y]
    */
    STA_IND_X = 0x81,
    /*
    ADDRESS = immediate + X
    A -> memory[memory[ADDRESS] | (memory[ADDRESS + 1] << 8)]
    */
    STA_IND_Y = 0x91,
    /*
    ADDRESS = memory[immediate] | (memory[immediate + 1] << 8)
    A -> memory[ADDRESS + Y]
    */


    STX_Z = 0x86,
    /*
    X -> memory[immediate < 0xFF]
    */
    STX_Z_Y = 0x96,
    /*
    X -> memory[immediate + Y < 0xFF]
    */
    STX_ABS = 0x8E,
    /*
    X -> memory[immediate | immediate2 << 8]
    */


    STY_Z = 0x84,
    /*
    Y -> memory[immediate < 0xFF]
    */
    STY_Z_X = 0x94,
    /*
    Y -> memory[immediate + X < 0xFF]
    */
    STY_ABS = 0x8C,
    /*
    Y -> memory[immediate | immediate2 << 8]
    */



    TAX = 0xAA,
    /*
    X <- A
    */
    TAY = 0xA8,
    /*
    Y <- A
    */
    TSX = 0xBA,
    /*
    X <- SP
    */
    TXA = 0x8A,
    /*
    A <- X
    */
    TXS = 0x9A,
    /*
    SP <- X
    */
    TYA = 0x98,
    /*
    A <- Y
    */


    PHA = 0x48,
    /*
    STACK <- A
    */
    PHP = 0x08,
    /*
    STACK <- FLAGS
    */
    PLA = 0x68,
    /*
    A <- STACK
    */
    PLP = 0x28,
    /*
    FLAGS <- STACK
    */

    AND_IM = 0x29,
    /*
    A <- A & immediate
    */
    AND_Z = 0x25,
    /*
    A <- A & memory[immediate < 256]
    */
    AND_Z_X = 0x35,
    /*
    A <- A & memory[immediate + X < 256]
    */
    AND_ABS = 0x2D,
    /*
    A <- A & memory[immediate | immediate2 << 8]
    */
    AND_ABS_X = 0x3D,
    /*
    A <- A & memory[(immediate | immediate2 << 8) + X]
    */
    AND_ABS_Y = 0x39,
    /*
    A <- A & memory[(immediate | immediate2 << 8) + Y]
    */
    AND_IND_X = 0x21,
    /*
    ADDRESS = immediate + X
    A <- A & memory[memory[ADDRESS] | memory[ADDRESS + 1] << 8]
    */
    AND_IND_Y = 0x31,
    /*
    ADDRESS = memory[immediate] | (memory[immediate + 1] << 8)
    A <- A & memory[ADDRESS + Y]
    */


    EOR_IM = 0x49,
    /*
    A <- A ^ immediate
    */
    EOR_Z = 0x45,
    /*
    A <- A ^ memory[immediate < 256]
    */
    EOR_Z_X = 0x55,
    /*
    A <- A ^ memory[immediate + X < 256]
    */
    EOR_ABS = 0x4D,
    /*
    A <- A ^ memory[immediate | immediate2 << 8]
    */
    EOR_ABS_X = 0x5D,
    /*
    A <- A ^ memory[(immediate | immediate2 << 8) + X]
    */
    EOR_ABS_Y = 0x59,
    /*
    A <- A ^ memory[(immediate | immediate2 << 8) + Y]
    */
    EOR_IND_X = 0x41,
    /*
    ADDRESS = immediate + X
    A <- A ^ memory[memory[ADDRESS] | memory[ADDRESS + 1] << 8]
    */
    EOR_IND_Y = 0x51,
    /*
    ADDRESS = memory[immediate] | (memory[immediate + 1] << 8)
    A <- A ^ memory[ADDRESS + Y]
    */


    ORA_IM = 0x09,
    /*
    A <- A | immediate
    */
    ORA_Z = 0x05,
    /*
    A <- A | memory[immediate < 256]
    */
    ORA_Z_X = 0x15,
    /*
    A <- A | memory[immediate + X < 256]
    */
    ORA_ABS = 0x0D,
    /*
    A <- A | memory[immediate | immediate2 << 8]
    */
    ORA_ABS_X = 0x1D,
    /*
    A <- A | memory[(immediate | immediate2 << 8) + X]
    */
    ORA_ABS_Y = 0x19,
    /*
    A <- A | memory[(immediate | immediate2 << 8) + Y]
    */
    ORA_IND_X = 0x01,
    /*
    ADDRESS = immediate + X
    A <- A | memory[memory[ADDRESS] | memory[ADDRESS + 1] << 8]
    */
    ORA_IND_Y = 0x11,
    /*
    ADDRESS = memory[immediate] | (memory[immediate + 1] << 8)
    A <- A | memory[ADDRESS + Y]
    */

    BIT_Z = 0x24,
    /*
    A & memory[immediate]
    */
    BIT_ABS = 0x2C,
    /*
    A & memory[immediate | immediate2 << 8]
    */


    ADC_IM = 0x69,
    /*
    A <- A + immediate
    */
    ADC_Z = 0x65,
    /*
    A <- A + memory[immediate < 256]
    */
    ADC_Z_X = 0x75,
    /*
    A <- A + memory[immediate + X < 256]
    */
    ADC_ABS = 0x6D,
    /*
    A <- A + memory[immediate | immediate2 << 8]
    */
    ADC_ABS_X = 0x7D,
    /*
    A <- A + memory[(immediate | immediate2 << 8) + X]
    */
    ADC_ABS_Y = 0x79,
    /*
    A <- A + memory[(immediate | immediate2 << 8) + Y]
    */
    ADC_IND_X = 0x61,
    /*
    ADDRESS = immediate + X
    A <- A + memory[memory[ADDRESS] | memory[ADDRESS + 1] << 8]
    */
    ADC_IND_Y = 0x71,
    /*
    ADDRESS = memory[immediate] | (memory[immediate + 1] << 8)
    A <- A + memory[ADDRESS + Y]
    */
};