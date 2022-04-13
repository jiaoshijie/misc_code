#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
  int lang = 0;
  if(argc != 1)
    lang = 1;

  time_t local_time = time(0);
  /* printf("%ld\n", local_time); */
  struct tm *ltm = localtime(&local_time);
  char week[7][4] = {"日", "一", "二", "三", "四", "五", "六"};
  char week_en[7][10] = {"Sunday", "Monday", "Tuesday", 
    "Wednesday", "Thusday", "Friday", "Saturday"};
  /** printf("%ld\n", local_time); */
  switch(lang)
  {
    case 0:
      printf("%d年%d月%d日 星期%s %d:%d:%d\n", ltm->tm_year + 1900,
       ltm->tm_mon + 1, ltm->tm_mday, week[ltm->tm_wday], ltm->tm_hour,
       ltm->tm_min, ltm->tm_sec);
    break;

    case 1:
      printf("%d/%d/%d %s %d:%d:%d\n", ltm->tm_mon + 1, ltm->tm_mday, 
          ltm->tm_year + 1900, week_en[ltm->tm_wday], ltm->tm_hour, 
          ltm->tm_min, ltm->tm_sec);
    break;
  }

  return 0;
}
