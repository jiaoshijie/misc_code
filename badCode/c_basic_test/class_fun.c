#include <stdio.h>
#include <string.h>

typedef struct class_f
{
  int age;
  char s[8];
  void (*init)(int *i, char *s);
  void (*print_jie)(int age, char *s);
  void (*print_age)(int age);
  void (*print_s)(char *s);
}Class_f;

void d_init(int *i, char *s)
{
  *i = 10;
  strcpy(s, "sex");
}

void d_print_jie(int age, char *s)
{
  printf("jie: %d, %s\n", age, s);
}

void d_print_age(int age)
{
  printf("age: %d\n", age);
}

void d_print_s(char *s)
{
  printf("s: %s\n", s);
}

Class_f use = {
  .init = d_init,
  .print_jie = d_print_jie,
  .print_age = d_print_age,
  .print_s = d_print_s
};

int main(void)
{
  use.init(&use.age, use.s);
  use.print_jie(use.age, use.s);
  use.print_age(use.age);
  use.print_s(use.s);

  return 0;
}
