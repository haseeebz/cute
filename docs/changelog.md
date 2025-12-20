
# Changelog

Each version needs three sections:

+ Language
+ Stdlib
+ Compiler
+ Engine
+ Tooling

## v0.0.1

### Language
+ Int32 type supported.
+ Basic arithmetic operations supported. Operations include adding, subtracting, multiplying, dividing and modulus.
+ Variables supported.
+ Assignments (singular/multiple) supported. 

### Stdlib
+ No stdlib implemented yet.

### Compiler
+ **Language spec** defined.
+ **Tokenizer** capable of tokenizing special symbols, keywords, general words, integers and floating numbers. 
+ **Parser** which parses the entire file as function `main`. Parses declarations using `let`, and assignments. 
+ Parser uses Pratt Parsing to parse expressions.
+ **Emitter** which converts the node tree into bytecode directly.
+ No type checking or optimizations.

### Engine
+ Supports 103 instructions.
+ All instructions other than the container instructions implemented.
+ Supports functions, function locals and recursion.
+ No support for containers and no distinction (yet) between primitive variables and container variables at the engine level.

### Tooling
+ No tooling support.



## v0.0.2

### Language
+ Float32 type supported.
+ Type casting added and done using `{type} expression`
+ Added `Out` instruction for basic printing.

### Stdlib
+ No stdlib implemented yet.

### Compiler
+ **Analyzer** implemented with two functions, name resolution and type checking.
+ **Name Resolver** capable of informing about undefined variables and repeated declaration.
+ **Type checker** can check whether variables are assigned with the correct types and whether binary operations are valid.
+ **Errors** are now raised when any of the components fail.

### Engine
+ No improvement done to the engine.

### Tooling
+ No tooling support.


## v0.0.3

### Language
+ All 32-bit type variants removed for simplicity. They ended up taking the same amount of space in the engine as 64-bit variant so it seemed useless. 
+ Cute now supports three primitive types: int, uint, float.

### Stdlib
+ Nope

### Compiler 
+ `CtSpec` now defines the language's semantics. Stuff like binary operations and types.
+ Added better error messages.

### Engine
+ **MAJOR** engine changes.
+ Instruction set redefined to accomodate only 64-bit primitives.
+ Added the previosly missing `CmpU` instruction for unsigned ints.

### Tooling
+ What's that?