
#pragma once 

/*
Template file for standard implementation of CuteArray
*/

#include <stdlib.h>
#include "CuteContainer.h"


#define CUTE_DYARRAY_DEF(NAME, TYPE)                                        \
                                                                            \
typedef TYPE NAME##_item;                                                   \
                                                                            \
typedef struct {                                                            \
    cute_Container* header;                                                 \
    TYPE* items;                                                            \
    size_t size;                                                            \
    size_t capacity;                                                        \
} NAME;                                                                     \
                                                                            \
void NAME##_init(NAME* self, size_t cap) {                                  \
    self->items = malloc(sizeof(TYPE) * cap);                               \
    self->capacity = cap;                                                   \
    self->size = 0;                                                         \
}                                                                           \
                                                                            \
void NAME##_del(NAME* self) {                                               \
    if (self->items) {                                                      \
        free(self->items);                                                  \
    }                                                                       \
    self->items = NULL;                                                     \
    self->capacity = 0;                                                     \
    self->size = 0;                                                         \
}                                                                           \
                                                                            \
int NAME##_resize(NAME* self, size_t new_cap) {                             \
    int return_type;                                                        \
    size_t item_count;                                                      \
                                                                            \
    if (new_cap > self->size) {                                             \
        return_type = 1;                                                    \
        item_count = self->size;                                            \
    } else if (new_cap < self->size) {                                      \
        return_type = 0;                                                    \
        item_count = new_cap;                                               \
    } else {                                                                \
        return 1;                                                           \
    }                                                                       \
                                                                            \
    TYPE* items = malloc(sizeof(TYPE) * new_cap);                           \
    for (size_t i = 0; i < item_count; i++) {                               \
        items[i] = self->items[i];                                          \
    }                                                                       \
                                                                            \
    free(self->items);                                                      \
    self->items = items;                                                    \
    self->capacity = new_cap;                                               \
    self->size = item_count;                                                \
                                                                            \
    return return_type;                                                     \
}                                                                           \
                                                                            \
void NAME##_push(NAME* self, TYPE item) {                                   \
    if (self->size >= self->capacity) {                                     \
        NAME##_resize(self, self->capacity ? self->capacity * 2 : 1);       \
    }                                                                       \
    self->items[self->size++] = item;                                       \
}                                                                           \
                                                                            \
int NAME##_pop(NAME* self, TYPE* item) {                                    \
    if (self->size == 0) {                                                  \
        return 0;                                                           \
    }                                                                       \
    *item = self->items[--self->size];                                      \
    return 1;                                                               \
}                                                                           \
                                                                            \
int NAME##_set(NAME* self, size_t index, TYPE item) {                       \
    if (index >= self->size) {                                              \
        return 0;                                                           \
    }                                                                       \
    self->items[index] = item;                                              \
    return 1;                                                               \
}                                                                           \
                                                                            \
int NAME##_get(NAME* self, size_t index, TYPE* item) {                      \
    if (index >= self->size) {                                              \
        return 0;                                                           \
    }                                                                       \
    *item = self->items[index];                                             \
    return 1;                                                               \
}                                                                           \
                                                                            \
int NAME##_insert(NAME* self, size_t index, TYPE item) {                    \
    if (index > self->size) {                                               \
        return 0;                                                           \
    }                                                                       \
    if (self->size >= self->capacity) {                                     \
        NAME##_resize(self, self->capacity ? self->capacity * 2 : 1);       \
    }                                                                       \
    for (size_t i = self->size; i > index; i--) {                           \
        self->items[i] = self->items[i - 1];                                \
    }                                                                       \
    self->items[index] = item;                                              \
    self->size++;                                                           \
    return 1;                                                               \
}
