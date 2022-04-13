.text
.global _start
_start:
  movb  $0x20, %al
  movb  $0x30, %bl
  cmp   %al, %bl
  je    s
  addb  %bl, %al
  jmp   ok
s:
  addb  %al, %al
ok:
  ret
