#include <stdio.h>
#include <stdlib.h>

#define COLOR_BASE 0 // 0 or 60

int main(void)
{

  /** 使用终端8颜色
   * \033[%d;%ldm
   * %d 范围在40~47 100~107是背景色 40黑 41红 42绿 43黄 44蓝 45紫 46青 47灰
   * %d 范围在30~37 90~97是前景色 30黑 31红 32绿 33黄 34蓝 35紫 36青 37灰
   * %ld 设置样式, 范围在0~9分别为不同的样式 0无样式 1加粗 2减细 3斜体 4下划线 5闪烁 6闪烁 7背景色 8不显示 9删除线
   * */

  /** 使用256色
   * 格式: \033[38;5;%dm
   * %d 范围0~255 代表不同的颜色
   * */


  // 背景色
 // for(int i = 40 + COLOR_BASE; i < 48 + COLOR_BASE; i++)
 //   printf("\033[%d;1m color\n", i);

  // 前景色
  // for(int i = 30 + COLOR_BASE; i < 38 + COLOR_BASE; i++)
  //   printf("\033[%d;1m color\n", i);

  // 样式
  // for(int i = 0; i < 10; i++)
  //   printf("\033[32;%dm color\n\033[0m", i);

  // 256色
  // for(int i = 0; i < 256; i++)
  // {
  //   printf("\033[38;5;%dm color=%d\n", i, i);
  // }

  return 0;
}
