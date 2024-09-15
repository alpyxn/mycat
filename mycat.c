#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 5000

// Color definitions.
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void read_or_highlight(char *buffer) {
  if (buffer[0] == '#' && buffer[1] != '#'){
    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, buffer);
    return;
  }
  else if (buffer[0] == '#' && buffer[1] == '#' && buffer[2] != '#'){
    printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, buffer);
    return;
  }
  else if (buffer[0] == '#' && buffer[1] == '#' && buffer[2] == '#' && buffer[3] != '#') {
    printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, buffer);
    return;
  }
  else if(buffer[0] == '/' && buffer[1] == '/' && buffer[2] != '/'){
    printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, buffer);
    return;
  }

  // Look for double quotes ""
  int quote_found = 0;
  for (int i = 0; i < strlen(buffer); i++) {
    if(buffer[i] == '"'){
      quote_found = !quote_found;
      if(quote_found){
        printf(ANSI_COLOR_YELLOW "%c", buffer[i]);
      }
      else{
        printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET,buffer[i]);
      }
    }
    else{
      if(quote_found){
        printf(ANSI_COLOR_YELLOW "%c", buffer[i]);
      }
      else{
        printf("%c",buffer[i]);
      }
    }
  }
   
  printf(ANSI_COLOR_RESET);
}

int main(int argc, char **argv) {

  char buffer[BUFFER_SIZE];
  if (argc < 2) {
    fprintf(stderr, "Usage: mycat file.txt\n");
    return EXIT_FAILURE;
  }

  
  else if (argc >= 2) {
    int nohl = 0;

    if(strcmp(argv[argc-1],"--nohl") == 0 && argc != 2){
      for(int i = 1; i<argc-1;i++){
        FILE *fs = fopen(argv[i],"r");
        if(fs == NULL){
          fprintf(stderr, "Error: %s file could not be found.\n", argv[i]);
          return EXIT_FAILURE;
        }
        while(fgets(buffer, sizeof buffer,fs)){
          printf("%s",buffer);
        }
      }
    }

    else{
      for (int i = 1; i < argc; i++) {
        FILE *fs = fopen(argv[i], "r");

        if (fs == NULL) {
          fprintf(stderr, "Error: %s file could not be found.\n", argv[i]);
          return EXIT_FAILURE;
        }

        while (fgets(buffer, sizeof buffer, fs)) {
          if(isatty(STDOUT_FILENO))
            read_or_highlight(buffer);
          else
            printf("%s",buffer);
        }
        fclose(fs);
      }
    }
    
    return EXIT_SUCCESS;
  }

  else {
    fprintf(stderr, "Usage: mycat file.txt\n");
    return EXIT_FAILURE;
  }
}
