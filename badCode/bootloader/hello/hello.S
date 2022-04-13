# hello.s
.data       # 数据段声明
  msg:
    .string "Hello world!\n" #要输出的字符串

  len = . - msg

.text       # 代码段声明

.global _start

_start:
  movl $len, %edx
  movl $msg, %ecx
  movl $1, %ebx
  movl $4, %eax
  int $0x80
  movl $0, %ebx
  movl $1, %eax
  int $0x80
