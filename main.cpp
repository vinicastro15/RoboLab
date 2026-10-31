/*
    ALGUNS COMANDOS IMPORTANTES RAYLIB:

    *OBS*: QUALQUER COMANDO RELACIONADO A RAYLIB DEVE ESTAR ABAIXO DO InitWindow(900, 900, "Robo");

    Texture nome = LoadTexture("./imagem.png");
     -salva a imagem.png no variavel nome (exemplo)

    DrawTexture(nome, posição_largura, posição_altura, WHITE);
     -nome: é onde a imagem tá salva
     -posição_largura: é a posição da tela em que quer imagem comece a ser desenhada, considerando a posição horizontal.
        Ex: caso a tela tenha a resolução 1280x720, a borda superior da tela é a posição 0 de largura e 0 de altura, e a inferior é a posição 1280 de largura e 720 de altura.
    -posição_altura: é a posição da tela em que quer imagem comece a ser desenhada, considerando a posição vertical.
    *OBS*: O COMANDO DrawTexture OU QUALQUER OUTRO QUE ENVOLVE DESENHAR ALGO NA TELA DEVE ESTAR ENTRE OS COMANDO BeginDrawing(); e EndDrawing();

     IsKeyDown(KEY_X) -> X é a tecla q quiser que esteja pressionada no momento
*/

#include <iostream>
#include <raylib.h>
using namespace std;

int main(){
    int TAM = 30;
    float posx = 80.f, posy = 200.f, novaposx, novaposy, velocidade = 4.f;
    int mapa[TAM][TAM] = {
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
    };
    bool colisao = false;
    InitWindow(900, 900, "Robo");
    SetTargetFPS(60); //crava o FPS do jogo em 60, para o jogo sempre roda em velodidade igual, independente da taxa de atualização do monitor.
    Texture cenario = LoadTexture("./cenario.png");
    Texture  robo = LoadTexture("./robo.png");
    while(!WindowShouldClose()){
        novaposx = posx;
        novaposy = posy;

        if(IsKeyDown(KEY_D))
            novaposx += velocidade;
        if(IsKeyDown(KEY_A))
            novaposx -= velocidade;
        if(IsKeyDown(KEY_W))
            novaposy -= velocidade;
        if(IsKeyDown(KEY_S))
            novaposy += velocidade;
        
        Rectangle celRobo = {novaposx, novaposy, (float)robo.width, (float)robo.height}; //cria uma celula com as proporções do robo, para que assim possa verificar colisão entre retangulos mais a frente.
        DrawTexture(cenario, 0.f, 0.f, WHITE);
        for(int i = 0; i < TAM; i++){
            for(int j = 0; j < TAM; j++){
                if(mapa[i][j] == 1 || mapa[i][j] == 3){ //verifica as partes em que o robo não pode andar sobre (diferente de 0).
                    Rectangle celMapa = {j*(float)TAM, i*(float)TAM, (float)TAM, (float)TAM}; //cria uma celula para a parte do mapa que deve haver colisão com o robo.
                    if(CheckCollisionRecs(celMapa, celRobo)){ //verifica se a celula do robo e a celula do mapa em que não se pode andar sobre colidem.
                        colisao = true;
                        break; //quebra laço j
                    }
                }
            }
            if(colisao)
                break; //quebra o laço i
        }
        
        if(!colisao){ //só permite que o robo ande se não houver tido uma colisão.
            posx = novaposx;
            posy = novaposy;
        }
        
        BeginDrawing(); //incia o modo desenho.
            for(int i = 0; i < TAM; i++)
                for(int j = 0; j < TAM; j++)
                    if(mapa[i][j] == 1)
                        DrawRectangle(j*TAM, i*TAM, TAM, TAM, GRAY); //desenha blocos cinza nas posições em que se tem 1 na matriz, fazem obstáculos.
            DrawTexture(robo, posx, posy, WHITE);
        EndDrawing(); //finaliza o modo desenho.
        colisao = false;
    }
    CloseWindow();
    return 0;
}
//PERMITIR QUE, AO COLIDIR COM ALGO, DE PRA USAR COMANDO PRA DESCER OU SUBIR + O DE ANDAR