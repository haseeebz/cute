#include "types.hpp"

void CtTypes::initPrimitives()
{
    
    FunctionInfo* constructor;

    auto* int_container = new ContainerInfo();
    auto* uint_container = new ContainerInfo();
    auto* float_container = new ContainerInfo();
    auto* bool_container = new ContainerInfo();
    auto* byte_container = new ContainerInfo();


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