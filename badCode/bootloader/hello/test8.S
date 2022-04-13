.data
msg:
  .byte 8, 9, 10, 2, 3, 7, 9, 11, 12, 8
len:
  .byte . - msg

.text
.global _start
_start:
  # movl  msg, %ebx movl  (msg), %ecx
  # movl  $msg, %eax
  # 初始化数据
  movb  $8, %ah # 用来放置比较的8
  movb  $0, %al # 用来统计大于8的个数
  movb  $0, %cl # 用来记录遍历的次数
  movb  len, %ch #用来表示数组的长度
  movl  msg, %ebx

lop:
# cmp指令不允许使用立即数
  cmp   %bl, %ah
  jns s # 如果ah > bl则不跳转
  addb  $1, %al

s:
  addb  $1, %cl
  movl  $msg, %ebx
  addb  %cl, %bl
  movl  (%ebx), %ebx
  cmp   %cl, %ch
  jne    lop


ret
