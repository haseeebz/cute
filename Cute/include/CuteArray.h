
#pragma once 

/*
Template file for standard implementation of CuteArray
*/


#define CUTE_ARRAY_DEF(NAME, TYPE, SIZE)                                   \
                                                                           \
typedef TYPE NAME##_item;                                                  \
                                                                           \
typedef struct {                                                           \
    TYPE items[SIZE];                                                      \
} NAME;                                                                    \
                                                                           \
int NAME##_get(NAME* array, size_t index, TYPE* item) {                    \
    if (index >= SIZE) {                                                   \
        return 0;                                                          \
    } else {                                                               \
        *item = array->items[index];                                       \
        return 1;                                                          \
    }                                                                      \
}                                                                          \
                                                                           \
int NAME##_set(NAME* array, size_t index, TYPE* item) {                    \
    if (index >= SIZE) {                                                   \
        return 0;                                                          \
    } else {                                                               \
        array->items[index] = *item;                                       \
        return 1;                                                          \
    }                                                                      \
}
