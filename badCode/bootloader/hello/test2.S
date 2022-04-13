.text
.global _start
_start:
code32: # TODO
  movl  $0x1, %eax
  orl   $0x2, %eax
  int   $0x80
