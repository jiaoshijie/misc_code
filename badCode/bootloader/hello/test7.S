.data
array:
  .byte 1, 8, 2, 8, 9, 6, 8, 9, 8, 10, 7, 8
len:
  .byte . - array

.text
.global _start
_start:
  movb  $0, %al       # 记录等于8的个数
  movb  $8, %ah
  movb  (len), %cl    # array数组长度
  movb  $0, %dl       # 记录遍历的个数
  movb  (array), %bl

lop:
  cmp  %bl, %ah
  jne   s
  addb  $1, %al

s:
  addb  $1, %dl
  movl  $array, %ebx
  addb  %dl, %bl
  movb  (%ebx), %bl
  cmp   %cl, %dl
  jne   lop

ret
