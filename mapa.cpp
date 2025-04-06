#include <iostream>
#include "mapa.h"
using namespace std;

#define TAM 30

void criarMapa(int mapa[TAM][TAM]) {
   for (int i = 0; i < TAM; i++) {
       for (int j = 0; j < TAM; j++) {
           mapa[i][j] = (i == 0 || j == 0 || i == TAM - 1 || j == TAM - 1) ? 1 : 0;
       }
   }
}

void desenharMapa(bool revelaMapa[TAM][TAM], int mapa[TAM][TAM], int x, int y, int ix, int iy) {
   for (int i = 0; i < TAM; i++) {
       for (int j = 0; j < TAM; j++) {
           if (i > x - 5 && i < x + 5 && j > y - 5 && j < y + 5) {
               revelaMapa[i][j] = true;
           }

           if (i == x && j == y) cout << "$$";
           else if (i == ix && j == iy) cout << "%%";
           else if (!revelaMapa[i][j]) cout << " -";
           else cout << (mapa[i][j] == 1 ? "██" : "  ");
       }
       cout << endl;
   }
}

void resetarRevelarMapa(bool revelarMapa[TAM][TAM]) {
   for (int i = 0; i < TAM; i++) {
       for (int j = 0; j < TAM; j++) {
           revelarMapa[i][j] = false;
       }
   }
}
