#include "syntax.h"

#define JIE_CONSTP

#ifdef JIE_FUNPOINTER
int func(int x, int y) {
  printf("now the func is running, and x + y = %d\n", x + y);
  return x + y;
}

typedef int (*funcp)(int x, int y);

int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }
int mul(int x, int y) { return x * y; }

struct charandfunc {
  char funname[4];
  funcp pfun;
};
#endif

#ifdef JIE_CONSTP
  void changePointer(int * const nums) { /*nums = (int*)malloc(sizeof(int));*/ *nums = 1; }
#endif

int main(int argc, char * argv[]) {
#ifdef JIE_FUNPOINTER
  if (argc < 4) {
    printf("argv: funname argv1 argv2\n");
    exit(1);
  }
  struct charandfunc cf[3];
  strcpy(cf[0].funname, "add");
  strcpy(cf[1].funname, "sub");
  strcpy(cf[2].funname, "mul");
  cf[0].pfun = add;
  cf[1].pfun = sub;
  cf[2].pfun = mul;

  for (int i = 0; i < 3; i++) {
    if (strcmp(cf[i].funname, argv[1]) == 0) {
      int l1 = atoi(argv[2]);
      int l2 = atoi(argv[3]);
      printf("argv[2] = %d, argv[3] = %d, %s = %d\n", l1, l2, argv[1],
      cf[i].pfun(l1, l2)); return 0;
    }
  }
  printf("Invalid argv\n");
#endif

#ifdef JIE_STATIC
  printf("%d\n", sv);
#endif

#ifdef JIE_CONSTP
  int *nums = (int*)malloc(sizeof(int));
  *nums = 100;
  changePointer(nums);
  printf("nums = %d\n", *nums);
#endif
  return 0;
}
