#include "CuteTypes.h"


inline cute_Int
cute_Int__create__0(int64_t i)
{
    return (cute_Int) {.val = i};
}

inline cute_Int
cute_Int__create__1(cute_Float f)
{
    return (cute_Int) {.val = (int64_t) f.val};
}

inline int64_t
cute_Int__val(cute_Int self)
{
    return self.val;
}


inline cute_Float
cute_Float__create__0(double d)
{
    return (cute_Float) {.val = d};
}

inline cute_Float
cute_Float__create__1(cute_Int i)
{
    return (cute_Float) {.val = (double) i.val};
}

inline double
cute_Float__val(cute_Float self)
{
    return self.val;
}


// cute_Bool
inline cute_Bool
cute_Bool__create__0(cute_Int i)
{
    return (cute_Bool) {.val = i.val};
}


inline cute_Char
cute_Char__create__0(cute_Int i)
{
    return (cute_Char) {.val = i.val};
}
