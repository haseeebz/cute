#include "CuteLib.h"
#include "CuteString.h"


cute_String* 
cute_String_create(cute_I32 size);

cute_String* 
cute_String_create_with_string(char* string);

void 
cute_String_append(cute_String* self, char c);

void 
cute_String_extend(cute_String* self, cute_String* other);

void 
cute_String_insert(cute_String* self, cute_I32 index, char c);

void 
cute_String_pop(cute_String* self, cute_I32 index);

void 
cute_String_remove(cute_String* self, char c, cute_I32 count);

void 
cute_String_del(cute_String* self);
