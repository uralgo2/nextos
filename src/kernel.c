//
// Created by uralg on 14.08.2022.
//
#include "multiboot2.h"
#include "types.h"
#include "io.h"
#include "dtables.h"
#include "asm.h"
extern gdt_entry_t gdt_entries[5];
void ok(const char* str){
    uint8 color = get_color();
    set_color(COLOR_WHITE, COLOR_GREEN);
    println_str(str);
    set_color(color << 4, color & 0x0f);
}
void print_bytes(uint8* addr, uint32 size){
    for(int i = 0; i < size; i++){
        if(i != 0 && i % 8 == 0)
            println();
        print_u(addr[i], 16);
        print_c(' ');
    }
    println();
}
void kernel_startup(struct multiboot_info* mInfo, uint32 magic){
    initialize_io();
    clear();
    println_hex(magic);
    println_str("Hello World!");

    println_str("Initializing descriptors tables...");
    initialize_descriptor_tables();
    print_bytes((uint8*)&gdt_entries, sizeof (gdt_entries));
    //asm_sti();
    ok("Done!");

    panic("Unknown error!");
}