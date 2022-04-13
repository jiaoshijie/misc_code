#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int getint(char **date)
{
  char str[5] = "";
  int i;
  for (i = 0; i < strlen(*date); i++)
  {
    if((*date)[i] >= 48 && (*date)[i] <= 57)
      str[i] = (*date)[i];
    else
      break;
  }
  str[i] = '\0';
  while((*date)[i] < 48 || (*date)[i] > 57)
    i++;

  *date = &((*date)[i]);

  return atoi(str);
}

time_t strtotm(char *date)
{
  struct tm stm;
  // 2019年10月22日 星期二 0:0:23
  stm.tm_year = getint(&date) - 1900;
  stm.tm_mon = getint(&date) - 1;
  stm.tm_mday = getint(&date);
  stm.tm_hour = getint(&date);
  stm.tm_min = getint(&date);
  stm.tm_sec = getint(&date);
  stm.tm_isdst = 0;

  return mktime(&stm);
}

time_t strtotm_en(char *date)
{
  struct tm stm;
  // 10/22/2019 Tuesday 0:0:17
  stm.tm_mon = getint(&date) - 1;
  stm.tm_mday = getint(&date);
  stm.tm_year = getint(&date) - 1900;
  stm.tm_hour = getint(&date);
  stm.tm_min = getint(&date);
  stm.tm_sec = getint(&date);
  stm.tm_isdst = 0;
  
  return mktime(&stm);

}

int main(int argc, char *argv[])
{
  char *date = "2019年10月22日 星期二 0:51:38";
  printf("%ld\n", strtotm(date));

  return 0;
}
