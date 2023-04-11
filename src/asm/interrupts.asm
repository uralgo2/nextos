extern _isr_handler
%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
  global _isr%1     ; %1 доступ к первому параметру.
  _isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  global _isr%1
  _isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
; Это наша общая часть ISR. Она сохраняет состояние процессора, настраивает
; сегменты на использование в режиме ядра, вызывает обработчик отказов, написанный на C
; и, наконец, восстанавливает состояние стека.
isr_common_stub:
   pusha                    ; Помещает в стек содержимое регистров edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Младшие 16 битов регистра eax = ds.
   push eax                 ; Сохранение дескриптора сегмента данных

   mov ax, 0x10  ; Загрузка сегмента данных ядра
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call _isr_handler

   pop eax        ; Перезагрузка оригинального дескриптора сегмента данных
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa                     ; Выталкиваем из стека значения edi,esi,ebp...
   add esp, 8     ; Очищаем из стека код ошибки, помещаем в стек номер ISR
   sti
   iret           ; Выталки