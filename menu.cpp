#include <iostream>
#include <windows.h>
#include <conio.h> // Para _getch() e kbhit()
using namespace std;

int main()
{
   SetConsoleOutputCP(65001); // Define o console para UTF-8

   /// ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
   // INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
   HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO cursorInfo;
   GetConsoleCursorInfo(out, &cursorInfo);
   cursorInfo.bVisible = false; // set the cursor visibility
   SetConsoleCursorInfo(out, &cursorInfo);
   // FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
   // INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
   short int CX = 0, CY = 0;
   COORD coord;
   coord.X = CX;
   coord.Y = CY;
   // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
   /// ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

   int opcao = 0; // Índice da opção selecionada
   bool rodando = true;
   const int totalOpcoes = 4;

   while (rodando)
   {
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

      cout << "╔═════ Dungeons and Binaries ═════╗\n";
      cout << "║                                 ║\n";
      string opcoes[totalOpcoes] = {"Jogar                    ║", "Como jogar               ║", "Créditos                 ║", "Sair                     ║"};

      // Exibe o menu com a seta
      for (int i = 0; i < totalOpcoes; i++)
      {
         if (i == opcao)
            cout << "║      ► "; // Seta para indicar a seleção
         else
            cout << "║        ";

         cout << opcoes[i] << "\n";
      }
      cout << "║                                 ║\n";
      cout << "╚═════════════════════════════════╝\n";

      // Captura a tecla pressionada
      char tecla = _getch();

      switch (tecla) {
      case 72: // Seta para cima
         opcao = (opcao - 1 + totalOpcoes) % totalOpcoes;
         break;
      case 80: // Seta para baixo
         opcao = (opcao + 1) % totalOpcoes;
         break;
      case 13:           // Enter
         if (opcao == 3) // Se for "Sair"
            rodando = false;
         else
            switch (opcao)
            {
            case 0:
               // Aqui você pode chamar a função do jogo
               cout << "Iniciando o jogo...\n";
               break;
            }

         system("pause"); // Espera uma tecla antes de continuar
         break;
      }
   }

   return 0;
}