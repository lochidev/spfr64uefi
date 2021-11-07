[bits 64]
LoadGDT:
    lgdt [rdi]      ; load GDT, rdi (1st argument) contains the gdt_ptr
    mov ax, 0x40    ; TSS segment is 0x40
    ltr ax          ; load TSS
    mov ax, 0x10    ; kernel data segment is 0x10
    mov ds, ax      ; load kernel data segment in data segment registers
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi        ; pop the return address
    mov rax, 0x08   ; kernel code segment is 0x08
    push rax       ; push the kernel code segment
    push rdi       ; push the return address again
    lretq           ; do a far return, like a normal return but
                    ; pop an extra argument of the stack
                    ; and load it into CS
EnableSCE:
    mov rcx, 0xc0000080 ; EFER MSR
    rdmsr               ; read current EFER
    or eax, 1           ; enable SCE bit
    wrmsr               ; write back new EFER
    mov rcx, 0xc0000081 ; STAR MSR
    rdmsr               ; read current STAR
    mov edx, 0x00180008 ; load up GDT segment bases 0x0 (kernel) and 0x18 (user)
    wrmsr               ; write back new STAR
    ret                 ; return back to C

ToUserSpace:
    mov rcx, rdi        ; first argument, new instruction pointer
    mov rsp, rsi        ; second argument, new stack pointer
    mov r11, 0x202     ; eflags
    o64 sysret;            ; to space!

GLOBAL ToUserSpace
GLOBAL EnableSCE
GLOBAL LoadGDT
GLOBAL load_gdt