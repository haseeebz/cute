
#pragma once 

typedef enum
{
    instrHalt = 0x00,

    instrPushI = 0x01,

    instrAddI = 0x02,
    instrSubI = 0x03,
    instrDivI = 0x04,
    instrMulI = 0x05,

    instrEqI = 0x09,
    instrStation = 0x06,
    instrJump = 0x07,

    instrOutI = 0x08,
} Instr;