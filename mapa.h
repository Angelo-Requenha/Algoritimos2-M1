#ifndef MAPA_h
#define MAPA_h
using namespace std;

#define TAM 30

void criarMapa(int mapa[TAM][TAM], int fase);
bool verificarPortal(int mapa[TAM][TAM], int x, int y);
void desenharMapa(bool revelaMapa[TAM][TAM], int mapa[TAM][TAM], int x, int y, int ix, int iy, int bx, int by, int projetil_x, int projetil_y, int lado);
void resetarRevelarMapa(bool revelarMapa[TAM][TAM]);

#endif