.data # 全局数据段
# data...

.text # 代码段
.global _start # 程序入口
_start:
  int $0x0
