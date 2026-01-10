
/*
Template file for standard Cute Array.
*/


#define CUTE_ARRAY_DEF(NAME, TYPE, LEN) \
\
\
typedef TYPE NAME##_item; \
\
typedef struct { \
	TYPE items[LEN]; \
} NAME; \
\
\
int NAME##_get(NAME* array, size_t index, TYPE* item) { \
	if (index >= LEN || index < 0) {return 0;} \
	else {*item = array->items[index]; return 1;} \
} \
int NAME##_set(NAME* array, size_t index, TYPE* item) { \
	if (index >= LEN || index < 0) {return 0;} \
	else {array->items[index] = *item; return 1;} \
} 
