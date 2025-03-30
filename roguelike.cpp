#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

#define TAM 30

void tirarCursorDaTela(){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
        
}

// ====================== Mapa ======================
void criaMapa(int mapa[TAM][TAM]){
    for (int i=0;i<TAM;i++){
        for (int j=0;j<TAM;j++){
            if (i==TAM-TAM or j==TAM-TAM or j==TAM-1 or i ==TAM-1){
                mapa[i][j] = 1;
            } else{
                mapa[i][j] = 0;
            }
        }   
    }
}

void desenharMapa(bool revelaMapa[TAM][TAM], int mapa[TAM][TAM], int x, int y, int ix, int iy){
    for (int i=0;i<TAM;i++){
        for (int j=0;j<TAM;j++){
            if (i > x-5 && i < x+5 && j > y-5 && j < y+5){
                revelaMapa[i][j] = true;
            }

            if (i == x && j == y){
                cout<<char(36)<<char(36);
            } else if(i == ix && j == iy){
                cout<<char(37)<<char(37);
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
}

void hud(int vida){
    cout<<"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout<<"Vida: "<<vida<<endl;
    cout<<"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

}

// ====================== Movimento ======================
void movimentoInimigo(int &ix, int &iy){
    int movimento = rand() % 4 + 1;
    switch (movimento){
        case 1: ix<39 ? ix++ : ix; break;
        case 2: iy<39 ? iy++ : iy; break;
        case 3: ix>0 ? ix-- : ix; break;
        case 4: iy>0 ? iy-- : iy; break;
    }
}

void movimentoJogador(int mapa[TAM][TAM], int &x, int &y, int &vida, int ix, int iy){
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
        if (x == ix and y == iy){
            vida--;
        }
        if (mapa[novo_x][novo_y] == 0) {
            x = novo_x;
            y = novo_y;
        }
    }
}


// ====================== Main ======================
int main()
{
    srand(time(NULL));
    tirarCursorDaTela();
    short int CX=0, CY=0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;      

    int x=1, y=1, ix = 10, iy = 10, vida = 3;
    // int yProjetil = -1, xProjetil = -1;
    bool revelaMapa[TAM][TAM] = {false};
    int mapa[TAM][TAM];
    criaMapa(mapa);

    while(vida> 0){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        
        movimentoInimigo(ix, iy);
        desenharMapa(revelaMapa, mapa, x, y, ix, iy);
        hud(vida);        
        movimentoJogador(mapa, x, y, vida, ix, iy);
        
    }

    return 0;
}