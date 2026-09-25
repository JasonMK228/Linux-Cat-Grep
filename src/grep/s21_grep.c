#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
} flag_t;

void output(FILE *file, char *pattern, char *filenames, flag_t flags);
int title(char *text, int lineNumber, flag_t flags);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Ошибка! Неправильно введена команда запуска");
    return 1;
  }

  char *filenames[100];
  int fileNumbers = 0;
  char *pattern = NULL;
  flag_t flags = {0};

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-e") == 0) {
        if (i + 1 < argc) {
          flags.e = 1;
          pattern = argv[i + 1];
          i++;
        } else {
          printf("Ошибка! После -e должен быть шаблон");
          return 1;
        }
      } else if (strcmp(argv[i], "-i") == 0) {
        flags.i = 1;
      } else if (strcmp(argv[i], "-c") == 0) {
        flags.c = 1;
      } else if (strcmp(argv[i], "-n") == 0) {
        flags.n = 1;
      } else if (strcmp(argv[i], "-l") == 0) {
        flags.l = 1;
      } else if (strcmp(argv[i], "-v") == 0) {
        flags.v = 1;
      }
    } else if (pattern == NULL) {
      pattern = argv[i];
    } else {
      if (fileNumbers >= 100) {
        printf("Ошибка! Слишком много файлов");
        return 1;
      }
      filenames[fileNumbers] = argv[i];
      fileNumbers++;
    }
  }
  if (pattern == NULL) {
    printf("Ошибка! Неправильно введена команда запуска");
    return 1;
  }

  for (int i = 0; i < fileNumbers; i++) {
    FILE *file = fopen(filenames[i], "r");
    if (file == NULL) {
      printf("Ошибка в чтении файла");
      continue;
    }
    output(file, pattern, filenames[i], flags);
    fclose(file);
  }

  if (fileNumbers == 0) {
    output(stdin, pattern, "stdin", flags);
  }

  return 0;
}

void output(FILE *file, char *pattern, char *filenames, flag_t flags) {
  char text[MAX_LINE_LENGTH];
  int count = 0, lineNumber = 0, lineFlag = 0;

  int cflags = REG_EXTENDED;
  if (flags.i == 1) {
    cflags |= REG_ICASE;
  }
  regex_t regex;
  regcomp(&regex, pattern, cflags);

  while (fgets(text, sizeof(text), file)) {
    lineNumber++;
    if (regexec(&regex, text, 0, NULL, 0) == 0 && flags.i == 0 &&
        flags.v == 0) {
      count += title(text, lineNumber, flags);
      lineFlag = 1;
    } else if (flags.i == 1) {
      if ((regexec(&regex, text, 0, NULL, 0) == 0) && flags.v == 0) {
        count += title(text, lineNumber, flags);
        lineFlag = 1;
      } else if (flags.v == 1) {
        if (regexec(&regex, text, 0, NULL, 0) != 0) {
          count += title(text, lineNumber, flags);
          lineFlag = 1;
        }
      }
    } else if (flags.i == 0 && flags.v == 1) {
      if (regexec(&regex, text, 0, NULL, 0) != 0) {
        count += title(text, lineNumber, flags);
        lineFlag = 1;
      }
    }
  }
  if (flags.c == 1 && flags.l == 0) {
    printf("%i\n", count);
  }
  if (flags.l == 1 && flags.c == 0 && lineFlag == 1) {
    printf("%s\n", filenames);
  }
  regfree(&regex);
}

int title(char *text, int lineNumber, flag_t flags) {
  if (flags.n == 1 && flags.l == 0) {
    printf("%d:", lineNumber);
  }
  if (flags.c == 0 && flags.l == 0) {
    printf("%s", text);
  } else if (flags.c == 1 && flags.l == 0)
    return 1;
  return 0;
}
