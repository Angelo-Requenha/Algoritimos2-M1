#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string>
using namespace std;

// === Importações de cabeçalhos ===
#include "menu.h"
#include "mapa.h"

// === Structs ===
struct Posicao {
    int x, y;
};

struct Ser_vivo {
    Posicao posicao;
    int vida;
    int xp;
    int dano;
};

struct Boss {
    Ser_vivo boss;
};

struct Inimigo {
    Ser_vivo inimigo;
};

struct Jogador {
    Ser_vivo jogador;
};

struct Projetil {
    Posicao posicao;
    int dano;
    bool ativo;
    int dx, dy;
};


// === Funções utilitárias ===
void tirarCursorDaTela() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}

// === HUD ===
void hud(int vida) {
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout << "Vida: " << vida << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
}

// === Movimento ===
void movimentoInimigo(int &x, int &y, int mapa[TAM][TAM]) {
    int mov = rand() % 4;
    int novo_x = x, novo_y = y;

    switch (mov) {
        case 0: if (x < TAM - 2) novo_x++; break;
        case 1: if (y < TAM - 2) novo_y++; break;
        case 2: if (x > 1) novo_x--; break;
        case 3: if (y > 1) novo_y--; break;
    }

    if (mapa[novo_x][novo_y] == 0) {
        x = novo_x;
        y = novo_y;
    } 
}

void movimentoBoss(int &x, int &y) {
    int mov = rand() % 4;
    switch (mov) {
        case 0: if (x < TAM - 2) x++; break;
        case 1: if (y < TAM - 2) y++; break;
        case 2: if (x > 1) x--; break;
        case 3: if (y > 1) y--; break;
    }
}

void movimentoJogador(int mapa[TAM][TAM], int &x, int &y, int &vida, int ix, int iy, int &proj_x, int &proj_y, bool &proj_ativo, int &lado, int &proj_dx, int &proj_dy) {
    if (_kbhit()) {
        char tecla = _getch();
        int novo_x = x, novo_y = y;

        switch (tecla) {
            if (lado != 0){
                case 72: lado = 1; break;
                case 80: lado = 2; break;
                case 75: lado = 3; break;
                case 77: lado = 4; break;
            }
            case 'w': novo_x--; break;
            case 's': novo_x++; break;
            case 'a': novo_y--; break;
            case 'd': novo_y++; break;
            case 32:
                if (!proj_ativo) {
                    proj_x = x;
                    proj_y = y;
                    proj_ativo = true;

                    // Define direção do tiro
                    switch (lado) {
                        case 1: proj_dx = -1; proj_dy = 0; break; // cima
                        case 2: proj_dx = 1; proj_dy = 0; break;  // baixo
                        case 3: proj_dx = 0; proj_dy = -1; break; // esquerda
                        case 4: proj_dx = 0; proj_dy = 1; break;  // direita
                        default: proj_dx = 0; proj_dy = 0; break;
                    }
                }
                break;
        }

        if (ix == x && iy == y) {
            vida--;
        }

        if (vida <= 0) {
            system("cls");
            cout << "╔═════════════════════════════════╗\n";
            cout << "║    VOCÊ PERDEU, FIM DE JOGO!    ║\n";
            cout << "╚═════════════════════════════════╝\n";
            system("pause");
            return;
        }

        if (mapa[novo_x][novo_y] == 0) {
            x = novo_x;
            y = novo_y;
        }
    }
}

// === Função principal ===
int main() {
    SetConsoleOutputCP(65001); // UTF-8
    srand(time(NULL));
    tirarCursorDaTela();

    bool revelarMapa[TAM][TAM] = {};
    int mapa[TAM][TAM];
    int lado = 1;
    int fase = 1;

    // Definir: "Posição", "Vida", "XP", "Dano"
    Jogador jogador {{{1, 1}, 3, 0, 1}};
    Inimigo inimigo {{{8, 9}, 5, 3, 1}};
    Boss boss {{{20, 20}, 50, 100, 5}};
    Projetil projetil = {{-1, -1}, 1, false, 0, 0}; 

    // Menu
    COORD coord = {0, 0};
    int opcao = 0;
    bool rodando = true;
    const int totalOpcoes = 6;
    string opcoes[totalOpcoes] = {
        "Jogar                    ║",
        "Como jogar               ║",
        "Itens                    ║",
        "Sistema de Pontuações    ║",
        "Créditos                 ║",
        "Sair                     ║"
    };

    while (rodando) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        menu(opcao, opcoes, totalOpcoes);

        char tecla = _getch();
        switch (tecla) {
            case 72: case 'w': opcao = (opcao - 1 + totalOpcoes) % totalOpcoes; break;
            case 80: case 's': opcao = (opcao + 1) % totalOpcoes; break;
            case 13: // ENTER
                switch (opcao) {
                    case 0:
                        jogador = {{{1,1}, 3, 0, 1}};
                        inimigo = {{{10,10}, 5, 3, 1}};
                        resetarRevelarMapa(revelarMapa);
                        for (int i = 0; i < 3; i++) {
                            resetarRevelarMapa(revelarMapa);
                            criarMapa(mapa, i);
                            while (jogador.jogador.vida > 0) {
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                            
                                // Movimentação dos Inimigos
                                if (inimigo.inimigo.vida > 0) movimentoInimigo(inimigo.inimigo.posicao.x, inimigo.inimigo.posicao.y, mapa);
                                else {inimigo.inimigo.posicao.x = -1; inimigo.inimigo.posicao.y = -1;}
                                movimentoBoss(boss.boss.posicao.x, boss.boss.posicao.y);
                                
                                if (projetil.ativo && lado != 0) {
                                    projetil.posicao.x += projetil.dx;
                                    projetil.posicao.y += projetil.dy;  

                                    // Bate na parede
                                    if (mapa[projetil.posicao.x][projetil.posicao.y] == 1 || projetil.posicao.y >= TAM) {
                                        projetil.ativo = false;
                                        projetil.posicao.y = -1;
                                        projetil.posicao.x = -1;
                                    }

                                    // Bate no inimigo
                                    if (projetil.posicao.x == inimigo.inimigo.posicao.x &&
                                        projetil.posicao.y == inimigo.inimigo.posicao.y) {
                                        inimigo.inimigo.vida -= projetil.dano;
                                        projetil.ativo = false;
                                        projetil.posicao.y = -1;
                                        projetil.posicao.x = -1;
                                    }
                                }

                                desenharMapa(revelarMapa, mapa,
                                    jogador.jogador.posicao.x, jogador.jogador.posicao.y,
                                    inimigo.inimigo.posicao.x, inimigo.inimigo.posicao.y,
                                    boss.boss.posicao.x, boss.boss.posicao.y,
                                    projetil.posicao.x, projetil.posicao.y, lado);

                                movimentoJogador(mapa,
                                    jogador.jogador.posicao.x, jogador.jogador.posicao.y,
                                    jogador.jogador.vida,
                                    inimigo.inimigo.posicao.x, inimigo.inimigo.posicao.y,
                                    projetil.posicao.x, projetil.posicao.y, projetil.ativo, lado, projetil.dx, projetil.dy);
                                hud(jogador.jogador.vida);
                            }
                        }
                    case 1: comoJogar(); system("cls"); break;
                    case 2: itens(); system("cls"); break;
                    case 3: sistemaDePontuacao(); system("cls"); break;
                    case 4: creditos(); system("cls"); break;
                    case 5: rodando = false; break;
                }
                break;
        }
    }

    return 0;
}
