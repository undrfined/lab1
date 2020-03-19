#ifndef UTILS_H_
#define UTILS_H_

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_LEFT "╚"
#define BOTTOM_RIGHT "╝"
#define HORIZONTAL_STRAIGHT "═"
#define VERTICAL_STRAIGHT "║"
#define CROSS "╬"
#define T_BOTTOM "╦"
#define T_TOP "╩"
#define T_RIGHT "╠"
#define T_LEFT "╣"
#define STR_REPEAT(str, times) \
{ \
    for (int i = 0; i < times; ++i) \
        printf("%s", str); \
}

size_t split(const char* const string, const char* const delimiters, char*** const parts);
char* trim(const char* const string);

#endif
