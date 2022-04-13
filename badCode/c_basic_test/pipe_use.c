#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
  pid_t pid;
  int ipipe[2];

  pipe(ipipe);
  pid = fork();

  if(pid == 0)
  {
    close(ipipe[1]);
    char buf[1024] = { 0 };
    uint nbytes = 0;
    nbytes = read(ipipe[0], buf, 1024);
    buf[nbytes] = 0;
    printf("I am a child process, and I got this messages is {%s}\n", buf);
  }
  else
  {
    close(ipipe[0]);
    char name[] = "Hello child process";
    write(ipipe[1], name, sizeof(name));
    close(ipipe[1]);
  }

  return 0;
}
