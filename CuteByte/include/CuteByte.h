
#pragma once
 

typedef enum
{
    instrHalt = 0x00, 
    // Causes the Engine to halt and pack up.

    instrPushConstI = 0x20,
    instrPushConstF = 0x22,
    // Pushes a constant value to the stack // Needs an index to the constant pool

    instrLoadI = 0x30,
    instrLoadF = 0x32,
    // Loads a value from the virtual memory // Needs an index

    instrStorI = 0x38,
    instrStorF = 0x39,
    // Stores the last pushed value to the virtual memory // Needs an index // will pop it from stack

    instrAddI = 0x40,
    instrSubI = 0x41,
    instrMulI = 0x42,
    instrDivI = 0x43,

    instrAddF = 0x44,
    instrSubF = 0x45,
    instrMulF = 0x46,
    instrDivF = 0x47,
    // Basic arithmetic operations

    instrItoF = 0x50,
    instrFtoI = 0x51,
    // Typecasts the last pushed value and pushes it back in

    instrOutI = 0x60,
    instrOutF = 0x61,
    // For debugging

    instrStation = 0x88,
    // Tells the engine to store the current pc at a given station // requires an index

    instrJmpE = 0x90, 
    // Pops the last two entries and jumps if they are equal
    
} CtInstr;