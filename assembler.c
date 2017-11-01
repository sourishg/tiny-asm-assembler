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
  int sy[200], fjump[200], mcodes[200];
  char t[10], u[10], v[10]; int i, g;
  for (i = 0; i < 200; i++) {
    sy[i] = -1;
    fjump[i] = -1;
  }
  i = 0;
  int j = 0;
  printf(".model small\n");
  printf(".code\n");
  do {
    scanf("%s", t);
    if (t[1] == ':') {
      if (fjump[t[0]] != -1) {
        mcodes[fjump[t[0]]] = i - fjump[t[0]] - 1;
      }
      sy[t[0]] = i;
    }
    if (strcmp(t, "int") == 0) {
      scanf("%d", &g);
      i = i+2;
      mcodes[j++] = 205;
      mcodes[j++] = g;
      //printf("db 205\n");
      //printf("db %d\n", g);
    }
    if (strcmp(t, "jc") == 0) {
      scanf("%s", u);
      i = i+2;
      mcodes[j++] = 114;
      if (sy[u[0]] == -1) {
        fjump[u[0]] = j++;
      } else {
        mcodes[j++] = sy[u[0]] - i;
      }
      //printf("db 114\n");
      //printf("db %d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "jmp") == 0) {
      scanf("%s", u);
      i = i+2;
      mcodes[j++] = 235;
      mcodes[j++] = sy[u[0]] - i;
      //printf("db 235\n");
      //printf("db %d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "jl") == 0) {
      scanf("%s", u);
      i = i+2;
      mcodes[j++] = 124;
      mcodes[j++] = sy[u[0]] - i;
      //printf("db 124\n");
      //printf("db %d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "add") == 0) {
      scanf("%s%s", u, v);
      if (v[0] >= '0' && v[0] <= '9') {
        i = i+3;
        mcodes[j++] = 128;
        mcodes[j++] = 192 + f(u);
        mcodes[j++] = atoi(v);
        //printf("db 128\n");
        //printf("db %d\n", 192 + f(u));
        //printf("db %d\n", atoi(v));
      } else {
        i = i+2;
        mcodes[j++] = 2;
        mcodes[j++] = 192 + f(u)*8 + f(v);
        //printf("db 2\n");
        //printf("db %d\n", 192 + f(u)*8 + f(v));
      }
    }
    if (strcmp(t, "cmp") == 0) {
      scanf("%s%s", u, v);
      if (v[0] >= '0' && v[0] <= '9') {
        i = i+3;
        mcodes[j++] = 128;
        mcodes[j++] = 248 + f(u);
        mcodes[j++] = atoi(v);
        //printf("db 128\n");
        //printf("db %d\n", 248 + f(u));
        //printf("db %d\n", atoi(v));
      } else {
        i = i+2;
        mcodes[j++] = 58;
        mcodes[j++] = 192 + f(u)*8 + f(v);
        //printf("db 58\n");
        //printf("db %d\n", 192 + f(u)*8 + f(v));
      }
    }
    if (strcmp(t, "mov") == 0) {
      scanf("%s%s", u, v);
      if (f(u) < 8) {
        i = i+2;
        if (f(v) < 200) {
          mcodes[j++] = 138;
          mcodes[j++] = 192 + f(u)*8 + f(v);
          //printf("db 138\n");
          //printf("db %d\n", 192 + 8*f(u) + f(v));
        } else {
          mcodes[j++] = 176 + f(u);
          mcodes[j++] = atoi(v);
          //printf("db %d\n", 176 + f(u));
          //printf("db %d\n", atoi(v));
        }
      } else {
        if (f(v) < 200) {
          i = i+2;
          mcodes[j++] = 139;
          mcodes[j++] = 192 + (f(u)-8)*8 + f(v)-8;
          //printf("db 139\n");
          //printf("db %d\n", 192 + 8*(f(u)-8) + f(v)-8);
        } else {
          i = i+3;
          mcodes[j++] = 184 + f(u)-8;
          mcodes[j++] = (atoi(v) % 256);
          mcodes[j++] = (atoi(v) / 256);
          //printf("db %d\n", 184 + f(u)-8);
          //printf("db %d\n", (atoi(v) % 256));
          //printf("db %d\n", (atoi(v) / 256));
        }
      }
    }
  } while (strcmp(t, "end") != 0);
  for (int k = 0; k < j; k++)
    printf("db %d\n", mcodes[k]);
  printf("end\n");
  return 0;
}
