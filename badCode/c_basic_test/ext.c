#include <stdio.h>

#define s5(a)   Connect_##a##b // "##": 扩展a, 对于b则只是去掉了"##"
#define s(p)    #p // "#": 将p转换为字符串

void Connect_Testb(const char* p)
{
    printf("this is Connect Test:\n");
    printf("%s\n", p);
}

int main(void)
{
  s5(Test)("ext"); // Connect_Testb ad
  printf("%s\n", s(1234));
  return 0;
}
