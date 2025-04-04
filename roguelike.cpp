#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

// Importações
#include "menu.h"

#define TAM 30

void tirarCursorDaTela() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// ====================== Menu ======================
void menu(int opcao, const string opcoes[], int totalOpcoes) {
    cout << "╔═════ Dungeons and Binaries ═════╗\n";
    cout << "║                                 ║\n";
    // Exibe o menu com a seta
    for (int i = 0; i < totalOpcoes; i++) {
       if (i == opcao) {
          cout << "║      ► "; // Seta para indicar a seleção
       } else {
          cout << "║        ";
       }

       cout << opcoes[i] << "\n";
    }
    cout << "║                                 ║\n";
    cout << "╚═════════════════════════════════╝\n";
}

// ====================== Mapa ======================
void criarMapa(int mapa[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (i == TAM-TAM || j == TAM - TAM || j == TAM - 1 || i == TAM - 1) {
                mapa[i][j] = 1;
            } else{
                mapa[i][j] = 0;
            }
        }   
    }
}

void desenharMapa(bool revelaMapa[TAM][TAM], int mapa[TAM][TAM], int x, int y, int ix, int iy) {
    for (int i = 0; i < TAM; i++) {
        for (int j=0 ; j < TAM; j++) {
            if (i > x - 5 && i < x + 5 && j > y - 5 && j < y + 5) {
                revelaMapa[i][j] = true;
            }

            if (i == x && j == y) {
                cout<< char(36) << char(36); // Personagem
            } else if (i == ix && j == iy) {
                cout<< char(37) << char(37); // Inimigo
            } else if (revelaMapa[i][j] == false) {
                cout<< " -"; // Fog
            } else if (revelaMapa[i][j] == true) {
                if (mapa[i][j] == 0){
                    cout<<"  "; // Espaço vazio
                } else if(mapa[i][j] == 1) {
                    cout<< "█" << "█"; // Parede char(219)
                }
            }
        }
        cout<< endl;
    }
}

void hud(int vida) {
    cout<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout<< "Vida: " << vida << endl;
    cout<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
}

// ====================== Structs ======================

// struct Pontos {
//     int pontos;
// };

struct Posicao {
    int x, y;
};

struct Inimigo {
    int x, y; // Define a posição inicial do inimigo
    int vida;
};

// ====================== Movimento ======================
void movimentoInimigo(Inimigo &inimigo) {
    int movimento = rand() % 4 + 1;
    switch (movimento) {
        case 1: inimigo.x < 39 ? inimigo.x++ : inimigo.x; break;
        case 2: inimigo.y < 39 ? inimigo.y++ : inimigo.y; break;
        case 3: inimigo.x > 0 ? inimigo.x-- : inimigo.x; break;
        case 4: inimigo.y > 0 ? inimigo.y-- : inimigo.y; break;
    }
}

void movimentoJogador(int mapa[TAM][TAM], int &x, int &y, int &vida, Inimigo inimigo) {
    if (_kbhit()) {
        char tecla = _getch();
        int novo_x = x, novo_y = y;
        switch (tecla) {
            case 72: case 'w': novo_x--; break;
            case 80: case 's': novo_x++; break;
            case 75: case 'a': novo_y--; break;
            case 77: case 'd': novo_y++; break;
            // case 32: xProjetil = y; yProjetil = x;
        }
        if (x == inimigo.x && y == inimigo.y) {
            vida--;
        }
        if (vida == 0) {
            system("cls");
            cout<< "╔═════════════════════════════════╗\n";
            cout<< "║                                 ║\n";
            cout<< "║    VOCÊ PERDEU, FIM DE JOGO!    ║\n";
            cout<< "║                                 ║\n";
            cout<< "║              †▄▄▄               ║\n";
            cout<< "╚═════════════════════════════════╝\n";
            system("pause");
        }
        if (mapa[novo_x][novo_y] == 0) {
            x = novo_x;
            y = novo_y;
        }
    }
}

// ====================== Main ======================
int main() {
    SetConsoleOutputCP(65001); // Define o console para UTF-8
    srand(time(NULL));
    tirarCursorDaTela();

    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;      

    int x = 1, y = 1, ix = 10, iy = 10, vida = 3;
    // int yProjetil = -1, xProjetil = -1;
    bool revelarMapa[TAM][TAM] = {false};
    int mapa[TAM][TAM];

    // Opções do menu
    int opcao = 0; // Índice da opção selecionada
    bool rodando = true;
    const int totalOpcoes = 6;
    // Matriz de opções começando com o indice de 0
    string opcoes[totalOpcoes] = {
        "Jogar                    ║",
        "Como jogar               ║",
        "Itens                    ║",
        "Sistema de Pontuações    ║",
        "Créditos                 ║",
        "Sair                     ║"
    };
    
    string opcoesPause[totalOpcoes] = {
        "Continuar                ║",
    };
    
    criarMapa(mapa);

    // Posição inicial
    //Inimigo inimigo = {5, 5};
    Inimigo inimigoPosicao = {10, 10};

    while (rodando) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Não deixar o menu atualizar
        menu(opcao, opcoes, totalOpcoes); // Chama a função "menu"

        char menu = _getch();

        switch(menu) {
            case 72: 
                case 'w': opcao--;
                if (opcao == -1) { // Impede da seta do menu ultrapassar o limite de cima
                    opcao = 5;
                }
                break;
            case 80: 
                case 's': opcao++;
                if (opcao == 6) { // Impede da seta do menu ultrapassar o limite de baixo
                    opcao = 0;
                }
                break;
            case 13: {
                case 0: {
                    switch(opcao) {
                        case 0:
                            while(vida > 0) {
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Não deixa o jogo atualizar
                                movimentoInimigo(inimigoPosicao);
                                desenharMapa(revelarMapa, mapa, x, y, inimigoPosicao.x, inimigoPosicao.y);
                                hud(vida);
                                movimentoJogador(mapa, x, y, vida, inimigoPosicao);
                            }
                        case 1:
                            comoJogar();
                            system("cls");
                            break;
                        case 2:
                            itens();
                            system("cls");
                            break;
                        case 3:
                            sistemaDePontuacao();
                            system("cls");
                            break;
                        case 4:
                            creditos();
                            system("cls");
                            break;
                        case 5:
                            rodando = false;
                            break;
                    }
                }
            }
        }
    }

    return 0;
}
