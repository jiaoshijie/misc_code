#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t png_sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};

int main(int argc, char *argv[]) {
  (void)argc;
  char *program = *argv++;
  char *imgPath = *argv++;
  if (imgPath == NULL) {
    fprintf(stderr, "$%s [image path]\n", program);
    exit(1);
  }
  FILE *fp;
  fp = fopen(imgPath, "rb");
  if (fp == NULL) {
    perror("Error: ");
    exit(1);
  }

  uint8_t* file_contents = (uint8_t *)malloc(sizeof(uint8_t) * 8);
  fread(file_contents, sizeof(uint8_t) * 8, 1, fp);
  if (memcmp(file_contents, png_sig, sizeof(uint8_t) * 8)) {
    fprintf(stderr, "%s is not a valid png image.\n", imgPath);
    exit(1);
  }

  fclose(fp);
  return 0;
}
