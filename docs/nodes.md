
## Node System for the Compiler

The node system is common between the parser, analyzer and other components of the compiler. 

## 1- Object Nodes

Represent a construct inside the compiler. 

### 1.1- Root Program

Represents the entire program to be compiled. Is a collection of source nodes.

### 1.2- Source 

And each source file can contain its own functions, enums, container defs and what not. The compiler automatically isolates them. The root program node contains a global map of these source file nodes that can be used by the compiler to namespace the different files.

Each source file will have a map of defined functions:

### 1.3- Function Node

Each function node will have:

+ A name
+ A list of parameter types
+ Map of local variables including the arguments
+ An array of  which indicate the function body

This is end of the program heirarchy for now. Now for the unit nodes which make up everything.



## 2- Statement Nodes

These are statement nodes that do something special and are not evaluated normally.

### 2.1- Declaration
Contains a type identifier and name identifier, the analyzer handles these types.

### 2.2- Assign
Indicates an assign operation between two nodes.

### 2.3- Expression
Holds a node of the expression type. Only here so standalone expressions can execute as statements too. Also used by assign.



### 3- Expression 

Represents an expression.

#### 3.1- Int 
Basically stores an int in string form which is assigned to a real int by the analyzer.

#### 3.2- Float 
Same as Int Node but for float types.

#### 3.3- Binary Operation 
Used to show binary operations, has two child nodes which should be an expression node.

#### 3.4- Identifier
Contains an identifier which might be interpreted by the compiler differently depending upon the context

#### 3.5- Function Call
Indicates a function call. Contains the name of the function and arguments passed.
