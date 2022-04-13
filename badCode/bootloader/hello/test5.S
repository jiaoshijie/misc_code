.text
.global _start
_start:
  movb  $0x97, %al
  subb  $0x98, %al
  int $0x80
