.text
.globl start
.code16
start:
  ljmp $0x07c0, $code

code:
  mov %cs, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %ss

  mov $0x400, %sp
  call dispstr

loop0:
  jmp loop0

msg:
  .string "Booting......"
strlen:
  .word .-msg

dispstr:
  mov $msg, %bp
  mov (strlen), %cx
  mov $0x1301, %ax
  mov $0x000c, %bx
  mov $0x0, %dx
  int $0x10
  ret


.org 0x1fe, 0x90
.word 0xaa55
