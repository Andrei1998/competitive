#include "cgdzlib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int czy_zainicjalizowana = 0;
static int n, p[500001], licznik_f, licznik_g;

int inicjuj() {
  //freopen("gdz0.in", "r", stdin);
  int i;
  assert(czy_zainicjalizowana == 0);
  //scanf("%d", &n);
  n = 299364;
  for (i = 1; i <= n; ++i) {
    //scanf("%d", &p[i]);
    p[i] = i;
  }
  licznik_f = licznik_g = 0;
  czy_zainicjalizowana = 1;
  return n;
}

int f(int i, int j, int d) {
  assert(czy_zainicjalizowana == 1);
  assert(1 <= i && i <= n);
  assert(1 <= j && j <= n);
  assert(d > 0);
  licznik_f++;
  return (((p[i] - p[j]) % d) == 0);
}

int g(int i, int j) {
  assert(czy_zainicjalizowana == 1);
  assert(1 <= i && i <= n);
  assert(1 <= j && j <= n);
  licznik_g++;
  return (p[i] > p[j]);
}

void odpowiedz(int k) {
  assert(czy_zainicjalizowana == 1);
  assert(1 <= k && k <= n);
  printf((p[k] == 1) ? "OK.\n" : "ZLA ODPOWIEDZ.\n");
  printf("A intrebat pe g de %d ori.\n", licznik_g);
  exit(0);
}
