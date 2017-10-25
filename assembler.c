#include <stdio.h>

int f(char t[]) {
  if (strcmp(t, "al") == 0) return 0;
  if (strcmp(t, "cl") == 0) return 1;
  if (strcmp(t, "dl") == 0) return 2;
  if (strcmp(t, "bl") == 0) return 3;
  if (strcmp(t, "ah") == 0) return 4;
  if (strcmp(t, "ch") == 0) return 5;
  if (strcmp(t, "dh") == 0) return 6;
  if (strcmp(t, "bh") == 0) return 7;
  if (strcmp(t, "ax") == 0) return 8;
  if (strcmp(t, "cx") == 0) return 9;
  if (strcmp(t, "dx") == 0) return 10;
  if (strcmp(t, "bx") == 0) return 11;
  if (strcmp(t, "sp") == 0) return 12;
  if (strcmp(t, "bp") == 0) return 13;
  if (strcmp(t, "si") == 0) return 14;
  if (strcmp(t, "di") == 0) return 15;
  return 200;
}

int main(void) {
  int sy[200];
  char t[10], u[10], v[10]; int i, g;
  for (i = 0; i < 200; i++)
    sy[i] = -1;
  i = 0;
  printf(".model small\n");
  printf(".code\n");
  do {
    scanf("%s", t);
    if (t[1] == ':') sy[t[0]] = i;
    if (strcmp(t, "int") == 0) {
      scanf("%d", &g);
      i = i+2;
      printf("db 205\n");
      printf("db %d\n", g);
    }
    if (strcmp(t, "jc") == 0) {
      scanf("%s", u);
      i = i+2;
      printf("db 114\n");
      printf("db %d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "jmp") == 0) {
      scanf("%s", u);
      i = i+2;
      printf("db 235\n");
      printf("db %d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "jl") == 0) {
      scanf("%s", u);
      i = i+2;
      printf("db 124\n");
      printf("db %d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "add") == 0) {
      scanf("%s%s", u, v);
      if (v[0] >= '0' && v[0] <= '9') {
        i = i+3;
        printf("db 128\n");
        printf("db %d\n", 192 + f(u));
        printf("db %d\n", atoi(v));
      } else {
        i = i+2;
        printf("db 2\n");
        printf("db %d\n", 192 + f(u)*8 + f(v));
      }
    }
    if (strcmp(t, "cmp") == 0) {
      scanf("%s%s", u, v);
      if (v[0] >= '0' && v[0] <= '9') {
        i = i+3;
        printf("db 128\n");
        printf("db %d\n", 248 + f(u));
        printf("db %d\n", atoi(v));
      } else {
        i = i+2;
        printf("db 58\n");
        printf("db %d\n", 192 + f(u)*8 + f(v));
      }
    }
    if (strcmp(t, "mov") == 0) {
      scanf("%s%s", u, v);
      if (f(u) < 8) {
        i = i+2;
        if (f(v) < 200) {
          printf("db 138\n");
          printf("db %d\n", 192 + 8*f(u) + f(v));
        } else {
          printf("db %d\n", 176 + f(u));
          printf("db %d\n", atoi(v));
        }
      } else {
        if (f(v) < 200) {
          i = i+2;
          printf("db 139\n");
          printf("db %d\n", 192 + 8*(f(u)-8) + f(v)-8);
        } else {
          i = i+3;
          printf("db %d\n", 184 + f(u)-8);
          printf("db %d\n", (atoi(v) % 256));
          printf("db %d\n", (atoi(v) / 256));
        }
      }
    }
  } while (strcmp(t, "end") != 0);
  printf("end\n");
  return 0;
}
