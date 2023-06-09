//
// Created by uralg on 09.04.2023.
//
#include "dtables.h"

extern void load_gdt(uint32);
extern void load_idt(uint32);
extern void reload_segments();

static void init_gdt();
static void gdt_set_gate(int32,uint32,uint32,uint8,uint8);
static void init_idt();
static void idt_set_gate(uint8,uint32,uint16,uint8);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void initialize_descriptor_tables()
{
    init_gdt();
    init_idt();
}

static void init_gdt()
{
    gdt_ptr.limit = sizeof(gdt_entries) - 1;
    gdt_ptr.base  = (uint32)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    load_gdt((uint32)&gdt_ptr);
    reload_segments();
}

static void gdt_set_gate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}
static void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (uint32)&idt_entries;

    uint64* tmp = (uint64*)idt_entries;
    for(int i = 0; i < 256; ++i){
        tmp[i] = 0;
    }

    idt_set_gate( 0, (uint32)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uint32)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uint32)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (uint32)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (uint32)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (uint32)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (uint32)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (uint32)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (uint32)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (uint32)isr9 , 0x08, 0x8E);
    idt_set_gate( 10, (uint32)isr10 , 0x08, 0x8E);
    idt_set_gate( 11, (uint32)isr11 , 0x08, 0x8E);
    idt_set_gate( 12, (uint32)isr12 , 0x08, 0x8E);
    idt_set_gate( 13, (uint32)isr13 , 0x08, 0x8E);
    idt_set_gate( 14, (uint32)isr14 , 0x08, 0x8E);
    idt_set_gate( 15, (uint32)isr15 , 0x08, 0x8E);
    idt_set_gate( 16, (uint32)isr16 , 0x08, 0x8E);
    idt_set_gate( 17, (uint32)isr17 , 0x08, 0x8E);
    idt_set_gate( 18, (uint32)isr18 , 0x08, 0x8E);
    idt_set_gate( 19, (uint32)isr19 , 0x08, 0x8E);
    idt_set_gate( 20, (uint32)isr20 , 0x08, 0x8E);
    idt_set_gate( 21, (uint32)isr21 , 0x08, 0x8E);
    idt_set_gate( 22, (uint32)isr22 , 0x08, 0x8E);
    idt_set_gate( 23, (uint32)isr23 , 0x08, 0x8E);
    idt_set_gate( 24, (uint32)isr24 , 0x08, 0x8E);
    idt_set_gate( 25, (uint32)isr25 , 0x08, 0x8E);
    idt_set_gate( 26, (uint32)isr26 , 0x08, 0x8E);
    idt_set_gate( 27, (uint32)isr27 , 0x08, 0x8E);
    idt_set_gate( 28, (uint32)isr28 , 0x08, 0x8E);
    idt_set_gate( 29, (uint32)isr29 , 0x08, 0x8E);
    idt_set_gate( 30, (uint32)isr30 , 0x08, 0x8E);
    idt_set_gate(31, (uint32)isr31, 0x08, 0x8E);

    load_idt((uint32)&idt_ptr);

    //asm_sti();

}

static void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    // Мы должны раскомментировать приведенную ниже операцию OR в случае, если нужен пользовательский режим.
    // Эта операция устанавливает уровень привилегий, используемый шлюзом прерываний, равным 3.
    idt_entries[num].flags   = flags /* | 0x60 */;
}
void isr_handler(registers_t regs)
{
    print_str("recieved interrupt: ");
    println_dec(regs.int_no);
}