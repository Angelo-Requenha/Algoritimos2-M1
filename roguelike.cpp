#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define TAM 30

int main()
{
    srand(time(NULL));
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    bool revelaMapa[TAM][TAM] = {false};
    int mapa[TAM][TAM];

    for (int i=0;i<TAM;i++){
        for (int j=0;j<TAM;j++){
            if (i==TAM-TAM or j==TAM-TAM or j==TAM-1 or i ==TAM-1){
                mapa[i][j] = 1;
            } else{
                mapa[i][j] = 0;
            }
        }   
    }

    //Posicao inicial do personagem no console
    int x=1, y=1, ix = 10, iy = 10, vida = 3, movimento = 0;
    int yProjetil = -1, xProjetil = -1;
    
    while(vida> 0){
        ///Posiciona a escrita no inicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        movimento = rand() % 4 + 1;
        switch (movimento){
            case 1: ix<39 ? ix++ : ix; break;
            case 2: iy<39 ? iy++ : iy; break;
            case 3: ix>0 ? ix-- : ix; break;
            case 4: iy>0 ? iy-- : iy; break;
        }

        for (int i=0;i<TAM;i++){
            for (int j=0;j<TAM;j++){
                if (i > x-5 && i < x+5 && j > y-5 && j < y+5){
                    revelaMapa[i][j] = true;
                }

                if (xProjetil > 0 && xProjetil < 30){
                    xProjetil++;
                }

                if (i == x && j == y){
                    cout<<char(36)<<char(36);
                    
                } else if(i == ix && j == iy){
                    cout<<char(37)<<char(37);

                } else if(i == yProjetil and j == xProjetil){
                    cout<<char(22)<<char(22);

                } else if (revelaMapa[i][j]==false){
                    cout<<" -";

                } else if(revelaMapa[i][j]==true){
                    if (mapa[i][j] == 0){
                        cout<<"  ";
                    } else if(mapa[i][j]==1){
                        cout<<char(219)<<char(219);
                    }
                }
            }
            cout<<endl;
        }

        cout<<"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        cout<<"Vida: "<<vida<<endl;
        cout<<"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

        ///executa os movimentos
         if (_kbhit()) {
            char tecla = _getch();
            int novo_x = x, novo_y = y;
            
            switch (tecla) {
                case 72: case 'w': novo_x--; break;
                case 80: case 's': novo_x++; break;
                case 75: case 'a': novo_y--; break;
                case 77: case 'd': novo_y++; break;

                case 32: xProjetil = y; yProjetil = x;
            }
            
            if (x == ix and y == iy){
                vida--;
            }
            
            if (mapa[novo_x][novo_y] == 0) {
                x = novo_x;
                y = novo_y;
            }
        }
    } //fim do laco do jogo

    return 0;
} //fim main
