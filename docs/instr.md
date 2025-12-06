
# ISA Definition and Documentation

Instructions that the Cute Engine can execute and what they do.


## Engine Control


### instrExitEngine

Operands: [4 Bytes] | Pops: 0 | Loads: 0

The operand is the return code, 0 for success.
Ends the Engine process, killing all states. 


### instrExit

Operands: [4 Bytes] | Pops: 0 | Loads: 0

The operand is the return code, 0 for success.
Lighter version of ExitEngine, just ends the current state. For the Engine to end properly, the program should end with this instruction. 


### instrOut

Operands: [4 bytes] | Pops: 0 | Loads: 0

Prints the contents of the last atom. The operand is the type specifier. This is for testing purposes.

+ 0 : raw binary digits
+ 1 : raw bytes in hex format (use this for memory addresses too)
+ 2 : i32
+ 3 : i64
+ 4 : u32
+ 5 : u64
+ 6 : f32
+ 7 : f64

### instrDump

Operands: [4 bytes] | Pops: 0 | Loads: 0

Used to dump engine info. The operand is the level/type of dump. Used for debugging.

+ 0 : Function dump. Displays: Function ID, args passed, number of locals and value of each local.
+ 1 : Function Stack dump: Displays: The function traceback, their IDs and args passed.
+ 2 : execution stack dump. Displays: execution stack size and its contents.
+ 3 : State dump. Displays: Complete information about the state, including traceback and content of the execution stack.
+ 4 : Engine dump. Displays: Information about all active states, the file being run and general info.

### instrPopAtom

Operands: [None] | Pops: 1 | Loads: 0

Pops an atom from the Execution Stack.

### instrDupAtom

Operands: [None] | Pops: 0 | Loads: 1

Duplicates the last atom and pushes it back on the Execution Stack.

### instrNull

Operands: [None] | Pops: 0 | Loads: 0

Does nothing and the engine skips over it. Should be used as place holder by the compiler.

### instrModCall

Operands: [4 bytes , 4 Bytes] | Pops: variable | Loads: variable

Calls a virtual function inside the engine. The first operand is the module ID and the second operand is the function ID. The engine automatically passes the amount of arguments the module function takes. Whether the module function returns anything will be defined in header files for the compiler.


## Constant Loading


### instrLoadCoI32
### instrLoadCoI64
### instrLoadCoF32
### instrLoadCoF64

Operands: [4/8 bytes] | Pops: 0 | Loads: 1

Loads the specific type into the ExeStack. The numeral is encoded into the bytecode. I decided not to use constant pools for numerals since they will almost be the same size (4 bytes) as the indexes used to refer to the constant pool.

### instrLoadConst

Operands: [4 bytes] | Pops: 0 | Loads: 1

Constants are loaded as individual Constant structs and kept in memory. The reference to the constant is loaded. Note that these Constant structs would be mostly used by engine modules and not by the engine itself.

The operand is the constant index.

Some constant types that will be put into the pool are: ConstString(count specfied), ConstArray(count and item size specified). The ConstArray will mostly be used for primitives.

Arrays of complex types like containers will be assigned iteratively in the bytecode. Same for maps.



## Memory Operations


### instrLoadI32
### instrLoadI64
### instrLoadF32
### instrLoadF64

Operands: [4 bytes] | Pops: 0 | Loads: 1

Takes an index and loads the local atom at that index to the execution stack.

### instrGLoadI32
### instrGLoadI64
### instrGLoadF32
### instrGLoadF64

Operands: [4 bytes] | Pops: 0 | Loads: 1

Same principle but globally.

### instrStoreI32
### instrStoreI64
### instrStoreF32
### instrStoreF64

Operands: [4 bytes] | Pops: 1 | Loads: 0

Takes an index and stores the top atom on the execution stack to the local at that index.
Same prinicple applies, only I64 is enough since its just byte copying but other types are kept for consistency.

### instrGStoreI32
### instrGStoreI64
### instrGStoreF32
### instrGStoreF64

Operands: [4 bytes] | Pops: 1 | Loads: 0

Same but globally.

### instrCopyI32
### instrCopyI64
### instrCopyF32
### instrCopyF64

Operands: [4 bytes, 4 bytes] | Pops: 0 | Loads: 0

Copies an atom from one location to another. The first operand is the source while the second is the destination.
No global version of these exist since it seems like a rare case.
If global copying is ever needed, just do:
```python
instrGLoadI64  src
instrGStoreI64 dest
```

> More memory operations exist in the Containers section.

## Arithmetic Operations


### instrAddI32
### instrAddI64
### instrAddF32
### instrAddF64

Operands: [None] | Pops: 2 | Loads: 1

Adds the last two atoms and pushes the result back. 

### instrSubI32
### instrSubI64
### instrSubF32
### instrSubF64

Operands: [None] | Pops: 2 | Loads: 1

Subtracts  the last two atoms and pushes the result back. The atom that was pushed first will be the first operand in the subtraction.

### instrMulI32
### instrMulI64
### instrMulF32
### instrMulF64

Operands: [None] | Pops: 2 | Loads: 1

Multiplies the last two atoms and pushes the result back. 

### instrDivI32
### instrDivI64
### instrDivF32
### instrDivF64

Operands: [None] | Pops: 2 | Loads: 1

Divides the last two atoms and pushes the result back. The atom that was pushed first is the dividend and the one which was pushed later is divisor. 

### instrDivU32
### instrDivU64

Operands: [None] | Pops: 2 | Loads: 1

Unsigned division for I32 and I64, same principle.


### instrModI32
### instrModU32
### instrModI64
### instrModU64

Operands: [None] | Pops: 2 | Loads: 1

Modulo operation. The first atom to be pushed onto the execution stack is the divisor while the second atom is the divisor. Signed Mod has the same sign as the dividend.


## Logical Operations


### instrLogicAnd
### instrLogicOr
### instrLogicNot
### instrLogicXor

Operands: [None] | Pops: 2 | Loads: 1

Logical comparison between the last two atoms. Does the logic operation on the whole 64 bits.


## Bitwise operations


### instrBitAnd
### instrBitOr
### instrBitNot
### instrBitXor

Operands: [None] | Pops: 2 | Loads: 1

Bitwise comparison between the last two atoms. Does the bitwise operation on the whole 64 bits. The first-to-be-pushed atom is the one on which the bitwise is applied and the second is the amount

### instrBitLShift
### instrBitRShift
### instrBitRaShift

### instrBitRShift32
### instrBitRaShift32

Operands: [None] | Pops: 2 | Loads: 1

Shift operations, operate on the whole 64 bits. The first-to-be-pushed atom is the one on which the bitwise is applied and the second is the amount by which the bits are shifted. Ra means arithmetic shift.

32 bit variants for R Shift also exists.


## Comparison Operations


### instrCmpI32
### instrCmpI64
### instrCmpF32
### instrCmpF64

Operands: [None] | Pops: 2 | Loads: 1

Takes two atoms and does an arithmetic comparison. Same principle applies for placement. 

If first atom is greater than the second, pushes 1.
If it is less, pushes -1.
If they are equal push 0.

These outputs are pushed at i64

### instrCmp2BoolEq
### instrCmp2BoolNe
### instrCmp2BoolLt
### instrCmp2BoolLe
### instrCmp2BoolGt
### instrCmp2BoolGe

Operands: [None] | Pops: 1 | Loads: 1

Takes the result of Cmp instruction and outputs 0(false)/1(true) depending upon the condition.


## Type Conversions


### instrF32I32
### instrI32F32
### instrI64F64
### instrF64I64

Operands: [None] | Pops: 1 | Loads: 1

Converts from int to float and float to int.

### instrF32F64
### instrF64F32
### instrI32I64
### instrI64I32

Operands: [None] | Pops: 1 | Loads: 1

Converts between sizes. 


## Control Flow


### instrJmp
### instrJmpTrue
### instrJmpFalse

Operands: [4 bytes] | Pops: 0/1/1 | Loads: 0

Jumps to a given instruction address. It is based on offsets so the maximum jumping limit is +/- 2 billion or so. 
JmpTrue/JmpFalse take the last atom and jump if it is true/false respectively.

### instrFuncCall

Operands: [4 bytes] | Pops: variable | Loads: variable

Takes a function ID and calls it. Some points to note:

+ Each function call has its own set of locals defined in the function table.
+ The number of arguments it accepts should be less than the local memory count.
+ The engine automatically passes and assigns the arguments. If n is the number of arguments a function accepts, then the engine pops the last n atoms from the execution stack and assigns them to the locals in the order in which they were pushed.

Example,

```python
func(x, y) [...];
func(1, 2);

# Byte code would be:

LoadCoI32 1
LoadCoI32 2
FuncCall  func_id

# 2 gets assigned to y and 1 gets assigned to x automatically.
```

### instrReturn

Operands: [None] | Pops: 0 | Loads: 0

Stops the function and returns back to the previous function and continues execution. Since there is a single ExeStack, if the function needs to return something, it just loads it before returning and it will be on top of the stack for the caller.


## Container Operations

### instrConNew

Operands: [4 bytes] | Pops: 0 | Loads: 1

Allocates a new container with the specified size. Operand indicates the number of atoms the container will have. It loads its reference onto the execution stack. 

### instrConDel

Operands: [None] | Pops: 1 | Loads: 0

Pops the last stored atom as a container and frees it. The container manager will check if the reference actually exists within its heap and will raise an error if the free is invalid.

### instrConStore

Operands: [4 bytes] | Pops: 1 | Loads: 0

Stores the last atom in the execution stack as a container. Since the engine is type agnostic, any atom can be stored as a container type and the functionality of this instruction is the same the Store instructions discussed before. The only difference is container manager hook that handles container life-times.

Operand is the local atom at which this operand is stored.

### instrConGStore

Operands: [4 bytes] | Pops: 1 | Loads: 0

Same as the normal except stores the container in the global scope.

### instrConLoad

Operands: [4 bytes] | Pops: 0 | Loads: 1

Loads the atom at the n index onto the stack as a container. n is the operand provided.

### instrConGLoad

Operands: [4 bytes] | Pops: 0 | Loads: 1

Same as the normal except loads the container in the global scope.

### instrConCopy

Operands: [4 bytes, 4 bytes] | Pops: 0 | Loads: 0

Copies the container from one atom to another. 1st operand is the source while the other is the destination.
This only copies the reference, it is still the same container.

### isntrConClone

Operands: [None] | Pops: 1 | Loads: 1

Pops the last pushed atom as a container and pushes back a completely new container with the same fields, all copied. Note that this does not do a deep copy since the engine does not know about types. 

### instrConAccLoad

Operands: [4 Bytes] | Pops: 1 | Loads: 1

Acc means access.

Pops the last atom from execution stack as a container and loads it's Nth atom to the stack. N is the operand provided.

An example so it makes sense:

```python
container.field 
```
This would be written as:
```python
instrConLoad     container_location
instrConAccLoad  field_location_inside_the_container
```
This will load field onto the stack. Note that this is not a reference to field but is actually its value.

### instrConAccStore

Operands: [4 Bytes] | Pops: 2 | Loads: 1

The last loaded atom onto the stack is taken as the container atom and the first loaded atom will be stored at the nth atom of the container. Operand is the n.

An example so it makes sense:

```python
container.field = 10
```
This would be written as:
```python
instrLoadCoI32   10
instrConLoad     container_location
instrConAccStore field_location_inside_the_container
```
   
### instrConInc

Operands: [None] | Pops: 1 | Loads: 0

Increments the container reference count by one.

### instrConDec

Operands: [None] | Pops: 1 | Loads: 0

decrements the container reference count by one.


