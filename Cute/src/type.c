#include "CuteTypes.h"


// cute_Int

inline cute_Int
cute_Int__create__0(int64_t c)
{
    return (cute_Int) {.val = c};
}

inline cute_Int
cute_Int__create__1(cute_Int c)
{
    return (cute_Int) {.val = c.val};
}

inline cute_Int
cute_Int__create__2(cute_UInt c)
{
    return (cute_Int) {.val = (int64_t) c.val};
}

inline cute_Int
cute_Int__create__3(cute_Float c)
{
    return (cute_Int) {.val = (int64_t) c.val};
}

inline cute_Int
cute_Int__create__4(cute_Bool c)
{
    return (cute_Int) {.val = c.val ? 1 : 0};
}

inline cute_Int
cute_Int__create__5(cute_Byte c)
{
    return (cute_Int) {.val = c.val};
}

inline int64_t
cute_Int__val(cute_Int i)
{
    return i.val;
}



// cute_UInt

inline cute_UInt
cute_UInt__create__0(uint64_t c)
{
    return (cute_UInt) {.val = c};
}

inline cute_UInt
cute_UInt__create__1(cute_UInt c)
{
    return (cute_UInt) {.val = c.val};
}

inline cute_UInt
cute_UInt__create__2(cute_Int c)
{
    return (cute_UInt) {.val = (uint64_t) c.val};
}

inline uint64_t
cute_UInt__val(cute_UInt i)
{
    return i.val;
}


// cute_Float

inline cute_Float
cute_Float__create__0(double c)
{
    return (cute_Float) {.val = c};
}

inline cute_Float
cute_Float__create__1(cute_Float c)
{
    return (cute_Float) {.val = c.val};
}

inline cute_Float
cute_Float__create__2(cute_Int c)
{
    return (cute_Float) {.val = (double) c.val};
}

inline double
cute_Float__val(cute_Float f)
{
    return f.val;
}


// cute_Bool

inline cute_Bool
cute_Bool__create__0(uint8_t c)
{
    return (cute_Bool) {.val = c};
}

inline cute_Bool
cute_Bool__create__1(cute_Bool c)
{
    return (cute_Bool) {.val = c.val};
}

inline cute_Bool
cute_Bool__create__2(cute_Int c)
{
    return (cute_Bool) {.val = c.val == 0 ? 0 : 1};
}

inline cute_Bool
cute_Bool__create__3(cute_UInt c)
{
    return (cute_Bool) {.val = c.val == 0 ? 0 : 1};
}

inline cute_Bool
cute_Bool__create__4(cute_Byte c)
{
    return (cute_Bool) {.val = c.val == 0 ? 0 : 1};
}

inline uint64_t
cute_Bool__val(cute_Bool b)
{
    return b.val;
}


// cute_Byte

inline cute_Byte
cute_Byte__create__0(uint8_t c)
{
    return (cute_Byte) {.val = c};
}

inline cute_Byte
cute_Byte__create__1(cute_Byte c)
{
    return (cute_Byte) {.val = c.val};
}

