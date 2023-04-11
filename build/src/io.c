//
// Created by uralg on 09.04.2023.
//
#include "io.h"

#define COLUMNS 80
#define LINES 25
#define SCREENSIZE (COLUMNS*LINES)
#define COORD(x, y) ((COLUMNS * y + x)*2)
#define LINEAR(x) (x*2)

static char *video_memory = (char *) 0xb8000;
static char color = 0x0F;
static uint8 x = 0, y = 0;

void initialize_io() {

}

void clear() {
    x = 0;
    y = 0;

    for (int i = 0; i < LINEAR(SCREENSIZE); i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = color;
    }
}

void print_str(const char *str) {
    int i = 0;
    while (str[i] != 0) {
        print_c(str[i]);
        ++i;
    }
}

void print_c(char ch) {
    if (ch == '\n') {
        x = 0;
        y += 1;
    } else {
        video_memory[COORD(x, y)] = ch;
        video_memory[COORD(x, y) + 1] = color;
        x++;
        if (x >= COLUMNS) {
            x = 0;
            y += 1;
        }
    }
}

void print_i(int32 num, uint8 base) {
    int count = 0;
    char buffer[64];

    if(num < 0) {
        buffer[0] = '-';
        ++count;
    }

    do {
        int digit = num % base;
        buffer[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
    } while ((num /= base) != 0);

    buffer[count] = '\0';
    int i;

    for (i = 0; i < count / 2; ++i) {
        char symbol = buffer[i];
        buffer[i] = buffer[count - i - 1];
        buffer[count - i - 1] = symbol;
    }

    print_str(buffer);
}

void print_u(uint32 num, uint8 base){
    int count = 0;
    char buffer[64];

    do {
        int digit = num % base;
        buffer[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
    } while ((num /= base) != 0);

    buffer[count] = '\0';
    int i;

    for (i = 0; i < count / 2; ++i) {
        char symbol = buffer[i];
        buffer[i] = buffer[count - i - 1];
        buffer[count - i - 1] = symbol;
    }

    print_str(buffer);
}

void print_hex(uint32 num){
    print_str("0x");
    print_u(num, 16);
}

void print_dec(int32 num){
    print_i(num, 10);
}

void println_str(const char *str) {
    print_str(str);
    print_c('\n');
}

void println_c(char ch) {
    print_c(ch);
    print_c('\n');
}

void println_i(int32 num, uint8 base){
    print_i(num, base);
    print_c('\n');
}


void println_u(uint32 num, uint8 base){
    print_u(num, base);
    print_c('\n');
}

void println_hex(uint32 num){
    print_hex(num);
    print_c('\n');
}

void println_dec(int32 num){
    print_dec(num);
    print_c('\n');
}

void println() { print_c('\n'); }

void set_color(uint8 bg, uint8 fg) {
    color = (bg << 4) | fg;
}

uint8 get_color(){
    return color;
}

void panic(const char* msg){
    set_color(COLOR_WHITE, COLOR_RED);
    println_str(msg);
    asm_hlt();
}