#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "Usage: mycat file.txt\n");
    return EXIT_FAILURE;
  }

  FILE *fs = fopen(argv[1], "r");

  if (fs == NULL) {

    fprintf(stderr, "Error: file could not be found.");
    return EXIT_FAILURE;
  }

  char buffer[5000];

  while (fgets(buffer, sizeof buffer, fs)) {
    printf("%s", buffer);
  }

  fclose(fs);
}
