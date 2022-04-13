BOOT_SECT = 0x07c0            # 宏定义
    .code16                    # 将这个汇编代码编译成16位程序
    .section .text            # 这是代码段的内容
    .global _start            # 在目标文件中导出_start符号
_start:
    jmp $BOOT_SECT, $go        # 跳转到0x07c0段
go:
    mov %cs, %ax            # 初始化ds/es段寄存器
    mov %ax, %ds
    mov %ax, %es




    mov $0x0003, %ax        # 调用BIOS 10H功能号设定显卡模式
    int $0x10
    mov $0x1301, %ax        # 调用BIOS 10H功能号显式字符串。
    mov $0x0007, %bx
    mov msg_len, %cx
    mov $0x0000, %dx
    mov $msg, %bp
    int $0x10
cpu_hlt:                    # 停止CPU
    hlt
    jmp cpu_hlt




msg:                        # 字符串内容
    .ascii "Hello, world!"
msg_len:                    # 字符串长度
    .word .-msg




    .org 510                # 启动扇区标志
    .word 0xAA55
