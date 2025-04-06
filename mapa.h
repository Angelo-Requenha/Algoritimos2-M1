#ifndef MAPA_h
#define MAPA_h
using namespace std;

#define TAM 30

void criarMapa(int mapa[TAM][TAM]);
void desenharMapa(bool revelaMapa[TAM][TAM], int mapa[TAM][TAM], int x, int y, int ix, int iy);
void resetarRevelarMapa(bool revelarMapa[TAM][TAM]);

#endif