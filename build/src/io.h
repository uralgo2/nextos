//
// Created by uralg on 09.04.2023.
//

#ifndef NEXTOS_IO_H
#define NEXTOS_IO_H

#include "types.h"
#include "asm.h"

enum COLORS {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_PURPLE,
    COLOR_BROWN,
    COLOR_GRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_PURPLE,
    COLOR_YELLOW,
    COLOR_WHITE,
};

void initialize_io();

void clear();

void print_str(const char* str);
void print_c(char ch);
void print_i(int32 num, uint8 base);
void print_u(uint32 num, uint8 base);
void print_hex(uint32 num);
void print_dec(int32 num);

void println_str(const char* str);
void println_c(char ch);
void println_i(int32 num, uint8 base);
void println_u(uint32 num, uint8 base);
void println_hex(uint32 num);
void println_dec(int32 num);
void println();

void set_color(uint8 bg, uint8 fg);
uint8 get_color();
void panic(const char* msg);
#endif //NEXTOS_IO_H
