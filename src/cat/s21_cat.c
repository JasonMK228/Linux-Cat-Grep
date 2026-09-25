#include <stdio.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int v;
  int T;
} flags_t;

int cat(FILE *file, char namefile[], flags_t flags);
int v(unsigned char c);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Ошибка! Неправильно введена команда запуска!");
    return 1;
  }

  flags_t flags = {0};
  char *filenames[100];
  int file_count = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strcmp(argv[i], "-b") == 0) {
        flags.b = 1;
      } else if (strcmp(argv[i], "-e") == 0) {
        flags.e = 1;
        flags.v = 1;
      } else if (strcmp(argv[i], "-E") == 0) {
        flags.E = 1;
      } else if (strcmp(argv[i], "-n") == 0) {
        flags.n = 1;
      } else if (strcmp(argv[i], "-s") == 0) {
        flags.s = 1;
      } else if (strcmp(argv[i], "-t") == 0) {
        flags.t = 1;
        flags.v = 1;
      } else if (strcmp(argv[i], "-T") == 0) {
        flags.T = 1;
      } else if (strcmp(argv[i], "-v") == 0) {
        flags.v = 1;
      } else {
        printf("Неизвестный флаг %s\n", argv[i]);
      }
    } else {
      if (file_count >= 100) {
        printf("Превышен лимит файлов!");
        return 1;
      }
      filenames[file_count++] = argv[i];
    }
  }

  if (file_count == 0) {
    cat(stdin, "stdin", flags);
  }

  for (int i = 0; i < file_count; i++) {
    FILE *file = fopen(filenames[i], "r");
    if (file != NULL) {
      cat(file, filenames[i], flags);
    } else {
      printf("Ошибка: не удалось открыть файл %s\n", filenames[i]);
    }
  }

  return 0;
}

int cat(FILE *file, char namefile[], flags_t flags) {
  if (file == NULL) {
    printf("Ошибка, не удалось открыть файл %s", namefile);
    return 1;
  }
  int count = 1;
  char text[1000];
  int block_empty = 0;
  while (fgets(text, 1000, file) != NULL) {
    if (flags.s == 1 && text[0] == '\n') {
      if (block_empty == 0) {
        block_empty = 1;
      } else
        continue;
    } else if (flags.s == 1 && text[0] != '\n') {
      block_empty = 0;
    }
    if (flags.b == 1) {
      if (text[0] != '\n' && text[0] != '\0') {
        printf("%6d\t", count);
        count++;
      }
    } else if (flags.n == 1) {
      printf("%6d\t", count);
      count++;
    }
    for (int i = 0; text[i] != '\0'; i++) {
      int func_v = 0;
      unsigned char c = text[i];

      if (c == '\n' && (flags.e == 1 || flags.E == 1)) printf("$");
      if (c == '\t' && (flags.t == 1 || flags.T == 1)) {
        printf("^I");
        continue;
      }
      if (flags.v == 1) {
        func_v = v(c);
      }
      if (func_v == 0 && flags.v == 1)
        putchar(c);
      else if (flags.v == 0)
        putchar(c);
    }
  }
  if (file != stdin) {
    fclose(file);
  }
  return 0;
}

int v(unsigned char c) {
  if (c < 32 && c != '\t' && c != '\n') {
    printf("^%c", c + 64);
    return 1;
  } else if (c == 127) {
    printf("^?");
    return 1;
  } else if (c > 127 && c < 160) {
    printf("M-^%c", c - 128 + 64);
    return 1;
  } else if (c >= 160) {
    printf("M-%c", c - 128);
    return 1;
  }
  return 0;
}