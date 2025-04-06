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
   cout<< "╔═════ Como jogar? ═════╗\n";
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