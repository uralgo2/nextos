//
// Created by uralg on 09.04.2023.
//

#ifndef NEXTOS_GDT_H
#define NEXTOS_GDT_H
#include "types.h"
struct gdt_entry_struct
{
    uint16 limit_low;           // Младшие 16 битов граничного значения limit.
    uint16 base_low;            // Младшие 16 битов адресной базы.
    uint8  base_middle;         // Следующие 8 битов адресной базы.
    uint8  access;              // Флаги доступа, определяющие в каком кольце можно использовать этот сегмент.
    uint8  granularity;
    uint8  base_high;           // Последние 8 битов адресной базы.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
    uint16 limit;               // Верхние 16 битов всех предельных значений селектора.
    uint32 base;                // Адрес первой структуры gdt_entry_t.
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

struct idt_entry_struct
{
    uint16 base_lo;             // Младшие 16 битов адреса, куда происходи переход в случае возникновения прерывания.
    uint16 sel;                 // Переключатель сегмента ядра.
    uint8  always0;             // Это значение всегда должно быть нулевым.
    uint8  flags;               // More flags. See documentation.
    uint16 base_hi;             // Старшие 16 битов адреса, куда происходи переход.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// Структура, описывающая указатель на массив обработчиков прерываний.
// Этот формат подходит для загрузки с помощью 'lidt'.
struct idt_ptr_struct
{
    uint16 limit;
    uint32 base;                // Адрес первого элемента нашего массива idt_entry_t.
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

void initialize_descriptor_tables();
typedef struct registers {
    uint32 ds;                  // Переключатель сегмента данных
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Помещает в стек значения регистров с помощью  pusha.
    uint32 int_no, err_code;    // Номер прерывания и код ошибки (если он предоставляется)
    uint32 eip, cs, eflags, useresp, ss; // Значения автоматически помещаются процессором в стек.
}__attribute__((packed)) registers_t;
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
#endif //NEXTOS_GDT_H
