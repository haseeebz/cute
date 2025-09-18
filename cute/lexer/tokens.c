#include "tokens.h"

void Token_print(Token* token, bool endline);
TokenStack* TokenStack_new(int capacity);
void TokenStack_del(TokenStack* stack);
void TokenStack_resize(TokenStack* stack, int capacity);
bool TokenStack_isEmpty(TokenStack* stack);
void TokenStack_push(TokenStack* stack, Token token);
Token TokenStack_pop(TokenStack* stack);