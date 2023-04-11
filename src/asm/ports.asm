global _writePort8
global _writePort16
global _writePort32
global _readPort8
global _readPort16
global _readPort32
_writePort8:
    mov edx, [esp + 4] 
    mov eax, [esp + 8] 

    out dx, al 

    ret

_writePort16:
    mov edx, [esp + 4] 
    mov eax, [esp + 8] 

    out dx, ax ; пишем в порт

    ret

_writePort32:
    mov edx, [esp + 4] 
    mov eax, [esp + 8] 

    out dx, eax ; пишем в порт

    ret

_readPort8:
    mov edx, [esp + 4] 

    in al, dx ; читаем из порта

    ret

_readPort16:
    mov edx, [esp + 4] ; берем из стека номер порта

    in ax, dx ; читаем из порта

    ret

_readPort32:
    mov edx, [esp + 4]  ; берем из стека номер порта

    in eax, dx ; читаем из порта

    ret