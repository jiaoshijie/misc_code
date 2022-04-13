.text
.global _start
_start:
  movb  $0x7f, %al
  addb  0x5, %al
  int $0x80
