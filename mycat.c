#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 5000

int main(int argc, char **argv) {

  char buffer[BUFFER_SIZE];
  if (argc < 2) {
    fprintf(stderr, "Usage: mycat file.txt\n");
    return EXIT_FAILURE;
  }

  if (argc == 4 && strcmp(argv[2], ">") == 0) {
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[3], "w");

    if (inputFile == NULL) {
      fprintf(stderr, "Error: file or files could not be created sorry.");
      fclose(outputFile);
      fclose(inputFile);
      return EXIT_FAILURE;
    }
    if (outputFile == NULL) {
      fprintf(stderr, "Error: file or files could not be created sorry.");
      fclose(outputFile);
      fclose(inputFile);
      return EXIT_FAILURE;
    }
    while (fgets(buffer, sizeof buffer, inputFile)) {
      fprintf(outputFile, "%s", buffer);
    }
    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
  }

  else if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      FILE *fs = fopen(argv[i], "r");

      if (fs == NULL) {
        fprintf(stderr, "Error: %s file could not be found.", argv[i]);
        return EXIT_FAILURE;
      }

      while (fgets(buffer, sizeof buffer, fs)) {
        printf("%s", buffer);
      }
      fclose(fs);
    }
    return EXIT_SUCCESS;
  }

  else {
    fprintf(stderr, "Usage: mycat file.txt\n");
    return EXIT_FAILURE;
  }
}
