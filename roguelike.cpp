#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string>
using namespace std;

// === Importações de cabeçalhos ===
#include "menu.h"
#include "mapa.h"

#define TAM 30

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

struct Item {
    string nome;
    int dano;
};

struct Inimigo {
    Ser_vivo inimigo;
};

struct Jogador {
    Ser_vivo jogador;
    Item arma;
};

void atirarDireita(int mapa[TAM][TAM], int x, int y, Inimigo &inimigo) {
    for (int i = y + 1; i < TAM; i++) {
        // Parar se encontrar parede
        if (mapa[x][i] == 1) break;

        // Mostrar o projétil
        COORD coord = { (SHORT)(i * 2), (SHORT)x };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "->";
        Sleep(50);

        // Verifica se atingiu o inimigo
        if (inimigo.inimigo.posicao.x == x && inimigo.inimigo.posicao.y == i) {
            inimigo.inimigo.vida -= 1;
            break;
        }

        // Limpa o rastro
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "  ";
    }
}

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
void movimentoInimigo(int &x, int &y) {
    int mov = rand() % 4;
    switch (mov) {
        case 0: if (x < TAM - 2) x++; break;
        case 1: if (y < TAM - 2) y++; break;
        case 2: if (x > 1) x--; break;
        case 3: if (y > 1) y--; break;
    }
}

void movimentoJogador(int mapa[TAM][TAM], int &x, int &y, int &vida, int ix, int iy, Inimigo &inimigo) {
    if (_kbhit()) {
        char tecla = _getch();
        int novo_x = x, novo_y = y;

        switch (tecla) {
            case 72: case 'w': novo_x--; break;
            case 80: case 's': novo_x++; break;
            case 75: case 'a': novo_y--; break;
            case 77: case 'd': novo_y++; break;
        }

        if (tecla == ' ') {
            atirarDireita(mapa, x, y, inimigo);
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

    Jogador jogador {{{1,1}, 3, 0, 1}, {"pistola", 3}};
    Inimigo inimigo {{{10,10}, 5, 3, 1}};
    resetarRevelarMapa(revelarMapa);
    criarMapa(mapa);

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
                        // Reinicia tanto o jogador como o inimigo
                        jogador = {{{1,1}, 3, 0, 1}, {"pistola", 3}};
                        inimigo = {{{10,10}, 5, 3, 1}};
                        resetarRevelarMapa(revelarMapa);

                        while (jogador.jogador.vida > 0) {
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                            movimentoInimigo(inimigo.inimigo.posicao.x, inimigo.inimigo.posicao.y);
                            desenharMapa(revelarMapa, mapa,
                                         jogador.jogador.posicao.x, jogador.jogador.posicao.y,
                                         inimigo.inimigo.posicao.x, inimigo.inimigo.posicao.y);
                            hud(jogador.jogador.vida);
                            movimentoJogador(mapa,
                                             jogador.jogador.posicao.x, jogador.jogador.posicao.y,
                                             jogador.jogador.vida,
                                             inimigo.inimigo.posicao.x, inimigo.inimigo.posicao.y,
                                             inimigo);
                        }
                        break;
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
