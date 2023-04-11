bits 32
global _load_gdt    ; Позволяет коду на C обращаться gdt_flush().
global _reload_segments
global _load_idt

_load_idt:
   mov eax, [esp+4]  ; Берет указатель на IDT, передаваемый в качестве параметра.
   lidt [eax]        ; Загружает указатель IDT.
   ret
_load_gdt:
    mov eax, [esp + 4]  ; Берет указатель на таблицу GDT, переданную в качестве параметра.
    lgdt [eax]        ; Загружает новый указатель GDT
    ret

_reload_segments:
mov ax, 0x10      ; 0x10 является смещением, находящимся в таблице GDT и указываемым на наш сегмент данных
                    ;mov ds, ax        ; Загрузка переключателей всех сегментов данных
                    ;mov es, ax
                    ;mov fs, ax
                    ;mov gs, ax
                    ;mov ss, ax
   ;jmp 0x08:.reload
.reload:  ; 0x08 является смещением на наш сегмент кода: Длинный переход!

   ret
