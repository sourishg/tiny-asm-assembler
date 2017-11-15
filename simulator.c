#include <stdio.h>

int main(int argc, char const *argv[])
{
  int i = 0, cy = 1, x, y, z, p, q, r[8], a[10000], pc = 0;
  char t[10], c;
  for (i = 0; i < 1000; i++) {
    scanf("%d", &a[i]);
    if (a[i] == -1)
      break;
  }
  while (1) {
    x = a[pc++];
    if (x > 175 && x < 184) {
      y = a[pc++];
      z = x % 8;
      if (z >= 4) {
        r[z-4] = 256 * y;
      } else {
        r[z] = y;
      }
    }
    if (x >= 184 && x <= 191) {
      y = a[pc++];
      z = a[pc++];
      r[x % 8] = z * 256 + y;
    }
    if (x == 138) {
      y = a[pc++];
      p = y % 64 / 8;
      q = y % 8;
      r[p] = r[q];
    }
    if (x == 139) {
      y = a[pc++];
      p = y % 64 / 8;
      q = y % 8;
      r[p] = r[q];
    }
    if (x == 205 && r[0]/256 == 2) {
      y = a[pc++];
      printf("%c", r[2]%256);
      fflush(stdout);
      sleep(1);
    }
    if (x == 205 && r[0]/256 == 76) {
      y = a[pc++];
      break;
    }
    if (x == 205 && r[0]/256 == 1) {
      y = a[pc++];
      do {
        c = getchar();
      } while (c < 20);
      r[0] = c;
    }
    if (x == 128) {
      y = a[pc++];
      z = a[pc++];
      p = y % 8;
      q = r[p];
      if (y > 191 && y < 200) {
        r[p] += z;
        if (r[p] >= 256) {
          r[p] -= 256;
          cy = 1;
        } else {
          cy = 0;
        }
      }
      if (y > 247) {
        if (q < z)
          cy = 1;
        else
          cy = 0;
      }
    }
    if (x == 114) {
      y = a[pc++];
      if (cy == 1)
        pc = pc + y;
    }
  }	
  return 0;
}