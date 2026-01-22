#include "CuteTypes.h"
#include "types.hpp"



void CtTypes::initPrimitives()
{
    
    FunctionInfo* constructor;

    auto* int_container = new ContainerInfo();
    int_container->repr = CUTE_INT_TYPE;
    auto* uint_container = new ContainerInfo();
    uint_container->repr = CUTE_UINT_TYPE;
    auto* float_container = new ContainerInfo();
    float_container->repr = CUTE_FLOAT_TYPE;
    auto* bool_container = new ContainerInfo();
    bool_container->repr = CUTE_BOOL_TYPE;
    auto* byte_container = new ContainerInfo();
    byte_container->repr = CUTE_BYTE_TYPE;


    // int(int)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(int_container);
    int_container->constructors.push_back(constructor);

    // int(uint)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(uint_container);
    int_container->constructors.push_back(constructor);

    // int(float)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(float_container);
    int_container->constructors.push_back(constructor);

    // int(bool)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(bool_container);
    int_container->constructors.push_back(constructor);
    
    // int(byte)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(byte_container);
    int_container->constructors.push_back(constructor);



    // uint(uint)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(uint_container);
    uint_container->constructors.push_back(constructor);

    // uint(int)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(int_container);
    uint_container->constructors.push_back(constructor);



    // float(float)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(float_container);
    float_container->constructors.push_back(constructor);

    // float(int)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(int_container);
    float_container->constructors.push_back(constructor);



    // bool(bool)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(bool_container);
    bool_container->constructors.push_back(constructor);

    // bool(int)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(int_container);
    bool_container->constructors.push_back(constructor);

    // bool(uint)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(uint_container);
    bool_container->constructors.push_back(constructor);

    // bool(byte)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(byte_container);
    bool_container->constructors.push_back(constructor);



    // byte(byte)
    constructor = new FunctionInfo();
    constructor->parameters.push_back(byte_container);
    byte_container->constructors.push_back(constructor);


    CtTypes::primitives["int"] = int_container;
    CtTypes::primitives["uint"] = uint_container;
    CtTypes::primitives["float"] = float_container;
    CtTypes::primitives["bool"] = bool_container;
    CtTypes::primitives["byte"] = byte_container;
}



void CtScope::addSymbol(std::string s, CtTypes::Info* sym)
{
    this->symbols[s] = sym;
}

CtTypes::Info* CtScope::getSymbol(std::string s)
{
    if (this->symbols.contains(s))
    {
        return this->symbols[s];
    }
    else 
    {
        if (this->parent)
        {
            return this->parent->getSymbol(s);
        }
        else
        {
            return nullptr;
        }
    }
}