.text
.global _start
_start:
  movb  $0b10000001, %al
  addb  $0b1, %al
  int   $0x80
