# TODO 没有搞定
.data # 全局数据段
msg:
  .string "Welcome to gas!"
str_len:
  .byte . - msg
gate:
  .string "000000000000000"

.text # 代码段
.global _start # 程序入口
_start:
  cld
  # movl $msg, %ds
  # movl $gate, %es
  movl $msg, %esi
  movl $gate, %edi
  movl (str_len), %ecx
  movsb

ret
