.text
.global _start
_start:
code32:
  movl $0x1, %eax
  andl $0x0, %eax
  int $0x80
