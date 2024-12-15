#ifndef OPERATOR_H
#define OPERATOR_H

typedef enum
{
    false,
    true
} bool;

typedef enum
{
    OP_NONE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE
} OPERATOR;

typedef enum
{
    KEY_NONE,
    KEY_EQUAL,
    KEY_SQRT,
    KEY_INV,
    KEY_SQUARE,
    KEY_BACKSPACE,
    KEY_POS_NEG
} SPECIAL_KEY;

typedef struct
{
    int   button_id;
    char* text;
    int   row;
    int   col;
    int   width;
    int   height;
    int   key_id;
} BUTTON_ATTRIBUTES;

#endif /* OPERATOR_H */