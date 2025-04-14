#include <iostream>
#include "menu.h"
using namespace std;

void menu(int opcao, const string opcoes[], int totalOpcoes) {
   cout << "╔═════ Dungeons and Binaries ═════╗\n";
   cout << "║                                 ║\n";
   for (int i = 0; i < totalOpcoes; i++) {
       cout << "║" << (i == opcao ? "      ► " : "        ") << opcoes[i] << "\n";
   }
   cout << "║                                 ║\n";
   cout << "╚═════════════════════════════════╝\n";
}

void comoJogar() {
   system("cls");
   cout<< "╔════════════ Como jogar? ════════════╗\n";
   cout<< "║                                     ║\n";
   cout<< "║ Aperte: W,A,S,D para se mover       ║\n";
   cout<< "║ para cima ou para baixo.            ║\n";
   cout<< "║                                     ║\n";
   cout<< "║ Aperte a tecla 'Espaço' para atirar ║\n";
   cout<< "║                                     ║\n";
   cout<< "║ Use as setas do teclado ←↑→↓ para   ║\n";
   cout<< "║ virar o personagem                  ║\n";
   cout<< "║                                     ║\n";
   cout<< "║ Objetivo: Entre nos portais 'ØØ'    ║\n";
   cout<< "║ apertando a tecla 'e' do teclado    ║\n";
   cout<< "║ para avançar de nivel (matar os     ║\n";
   cout<< "║ inimigos é opcional) derrote o      ║\n";
   cout<< "║ Boss final para vencer o jogo       ║\n";
   cout<< "╚═════════════════════════════════════╝\n";
   system("pause");
}

void itens() {
   system("cls");
   cout<< "╔════════ Itens ════════╗\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "║                       ║\n";
   cout<< "╚═══════════════════════╝\n";
   system("pause");
}

void sistemaDePontuacao() {
   system("cls");
   cout<< "╔════════ Sistema de Pontuação ════════╗\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "║                                      ║\n";
   cout<< "╚══════════════════════════════════════╝\n";
   system("pause");
}

void creditos() {
   system("cls");
   cout<< "╔════════ Créditos ════════╗\n";
   cout<< "║                          ║\n";
   cout<< "║ - Angelo Miguel Requenha ║\n";
   cout<< "║ - Dinae Pfiffer          ║\n";
   cout<< "║ - Bruno de Queiróz       ║\n";
   cout<< "║                          ║\n";
   cout<< "║ Professor: Alex Rese     ║\n";
   cout<< "║ Feito em: DD/MM/AAAA     ║\n";
   cout<< "║                          ║\n";
   cout<< "╚══════════════════════════╝\n";
   system("pause");
}