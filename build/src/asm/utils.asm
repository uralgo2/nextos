bits 32
global _asm_hlt
global _asm_cli
global _asm_sti

_asm_hlt:
    hlt
    jmp $
_asm_cli:
    cli
    ret
_asm_sti:
    sti
    ret