/*
    SE QUISER MUDAR O MAPA, ALTERA O ARQUIVO fase1.txt

    ALGUNS COMANDOS IMPORTANTES RAYLIB:

    *OBS*: QUALQUER COMANDO RELACIONADO A RAYLIB DEVE ESTAR ABAIXO DO InitWindow(900, 900, "Robo");

    Texture nome = LoadTexture("./imagem.png");
     -salva a imagem.png no variavel nome (exemplo).

    DrawTexture(nome, posição_largura, posição_altura, WHITE);
     -nome: é onde a imagem tá salva.
     -posição_largura: é a posição da tela em que quer imagem comece a ser desenhada, considerando a posição horizontal.
        Ex: caso a tela tenha a resolução 1280x720, a borda superior da tela é a posição 0 de largura e 0 de altura, e a inferior é a posição 1280 de largura e 720 de altura.
    -posição_altura: é a posição da tela em que quer imagem comece a ser desenhada, considerando a posição vertical.
    *OBS*: O COMANDO DrawTexture OU QUALQUER OUTRO QUE ENVOLVE DESENHAR ALGO NA TELA DEVE ESTAR ENTRE OS COMANDO BeginDrawing(); e EndDrawing();

     if(IsKeyDown(KEY_X)) -> X é a tecla que quer verificar se está sendo pressionada no momento. Tudo dentro do if só acontece se a tecla for pressionada.
*/

#include <iostream>
#include <fstream>
#include <raylib.h>
using namespace std;

#define TAM 30

void guardarMatriz(char mapa[TAM][TAM]){
    int i = 0;
    string salvar;
    ifstream arquivo("fase1.txt");
    while(getline(arquivo, salvar)){ //lê o arquivo até acabarem as linhas (a cada volta no while, é salvo na string "salvar" o conteúdo da linha atual).
        for(int j = 0; j < TAM; j++)
            mapa[i][j] = salvar[j]; //salva o caractere salvar[j] da linha atual em todas as colunas da linha.
        i++; //soma o k a cada fim do while para, na próxima volta, salvar os caracteres na linha seguinte da matriz mapa.
    }
}

void desenharCenario(Texture &cenario, float &posx, float &posy, char mapa[TAM][TAM]){
    DrawTexture(cenario, 0.f, 0.f, WHITE); //desenha o cenário.
    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++)
            if(mapa[i][j] == '1')
                DrawRectangle(j*TAM, i*TAM, TAM, TAM, GRAY); //desenha blocos cinza nas posições em que se tem '1' na matriz, criando paredes.
}

void moverRobo(float &posx, float &posy, float &novaposx, float &novaposy, float &velocidade, bool &andando, bool &virado_direita){
    novaposx = posx;
    novaposy = posy;

    if(IsKeyDown(KEY_A)){
        novaposx -= velocidade;
        andando = true;
        virado_direita = false; // o virado_direita falso significa que o robô não virou para a direita por último, então virou para a esquerda.
    }
    if(IsKeyDown(KEY_D)){
        novaposx += velocidade;
        andando = true;
        virado_direita = true; //ao desenhar o robô, ele vai ser desenhado virado para direita, pois foi o último lado pro qual ele andou.
    }
    if(IsKeyDown(KEY_W)){
        novaposy -= velocidade;
        andando = true;
    }
    if(IsKeyDown(KEY_S)){
        novaposy += velocidade;
        andando = true;
    }
}

void verificarColisoes(Texture robo_andando[], char mapa[TAM][TAM], float &posx, float &novaposx, float &posy, float &novaposy, bool &colisao){
    Rectangle celRobo = {novaposx, novaposy, (float)robo_andando[2].width, (float)robo_andando[2].height}; //cria uma célula retangular com as proporções do robô, para que assim possa verificar colisão entre retangulos mais a frente.
    //são usados robo_andando[2].width e height pois é nessa textura em que robô possui maior largura e altura, assim, evita que parte do robô fique em cima da parede quando forem desenhadas outras texturas dele.
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(mapa[i][j] == '1' || mapa[i][j] == '3'){ //verifica as partes em que o robô não pode andar sobre (diferente de 0).
                Rectangle celMapa = {j*(float)TAM, i*(float)TAM, (float)TAM, (float)TAM}; //cria uma célula para a parte do mapa em que o robô não pode andar sobre (paredes do cenário e desenhadas).
                if(CheckCollisionRecs(celMapa, celRobo)){ //verifica se a celula do robô e a celula do mapa em que não se pode andar sobre colidem.
                    colisao = true;
                    break; //quebra laço j.
                }
            }
        }
        if(colisao)
            break; //quebra o laço i.
    }
    
    if(!colisao){ //só permite que o robô ande se não houver colisão.
        posx = novaposx;
        posy = novaposy;
    }
}

void desenharRobo(Texture &robo_parado, Texture robo_andando[], bool &andando, bool &virado_direita, float &posx, float &novaposx, float &posy, float &novaposy, float &largura_robo, int &cont_mov, int &espera_mov){
    if(!andando || posx != novaposx || posy != novaposy || (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) || (IsKeyDown(KEY_W) && IsKeyDown(KEY_S))){ //verifica se não há nenhum movimento e se a posx/posy (onde o robô de fato vai ser desenhado) é diferente da novaposx/novaposy (posição para testar colisão), pois, se forem diferentes, quer dizer que o movimento não ocorreu, pois o posx/posy não foi atualizado para ser igual ao novaposx/novaposy. Verifica também se duas teclas de posições antagônicas estão sendo pressinadas ao mesmo tempo (robô não anda).
        if(virado_direita) //condição verdadeira caso o último movimento do robô tenha sido pra direita.
            largura_robo = robo_parado.width; //guardar a largura da imagem pra usar no retângulo origem.
        else //se o robô não se moveu por último pra direita, foi pra esquerda.
            largura_robo = -robo_parado.width; //a largura negativa significa que o eixo horizontal vai ser invertido (em vez do robo ficar virado pra direita, fica pra esquerda).

        Rectangle retangulo_origem = {0.f, 0.f, largura_robo, (float)robo_parado.height};
        //retângulo que serve para escolher a partir de que posição da imagem do robô ele vai começar a ser desenhado (0.f e 0.f é o inicio da imagem, pra desenhar ela toda) e também qual a largura e altura do desenho.
        Rectangle retangulo_destino = {posx, posy, (float)robo_parado.width, (float)robo_parado.height};
        //retângulo que serve para indicar em que posições o robo vai ser desenhado (posx e posy) e a largura e a altura que o desenho vai ocupar na tela (não pode usar o largura_robo no retangulo destino, só no origem, porque se a largura da textura for negativa, dá erro).

        DrawTexturePro(robo_parado, retangulo_origem, retangulo_destino, {0.f, 0.f}, 0.f, WHITE); //(qual imagem vai ser desenhada, os retangulos de origem e destino, posições do ponto de rotação, a rotação e WHITE por ser png).
    }
    else{ // se o robô não estiver parado, roda a animação dele andando.
        if(virado_direita)
            largura_robo = robo_andando[cont_mov].width;
        else
            largura_robo = -robo_andando[cont_mov].width;

        Rectangle retangulo_origem = {0.f, 0.f, largura_robo, (float)robo_andando[cont_mov].height};
        Rectangle retangulo_destino = {posx, posy, (float)robo_andando[cont_mov].width, (float)robo_andando[cont_mov].height};
        
        DrawTexturePro(robo_andando[cont_mov], retangulo_origem, retangulo_destino, {0.f, 0.f}, 0.f, WHITE);
    }
    
    espera_mov++;

    if(espera_mov == 30){ //se o espera_mov chegar a 30, ao entrar no if abaixo, o cont_mov viraria 6, e não há um robo_andando[6] para desenhar, então é a hora de resetar a animação.
        espera_mov = 0;
        cont_mov = 0;
    }
    
    if(espera_mov%5 == 0 && espera_mov != 0) //verificar se o espera_mov é um múltiplo de 5 (ou seja, a imagem de animação vai mudar a cada 5 voltas no while(!WindowShouldClose)).
        cont_mov++;
}

int main(){
    char mapa[TAM][TAM];
    int cont_mov = 0; //para verificar qual quadro da animação será impresso na tela (usado no desenharRobo).
    int espera_mov = 0; //para dar um tempo entre cada impressão de imagem do robô andando (animação não ser muito rápida) (usado no desenharRobo).
    float posx = 70.f, posy = 100.f, novaposx, novaposy, velocidade = 4.f;
    float largura_robo; //para quando criar o retângulo de origem do DrawTexturePro (usado no desenharRobo).
    bool colisao = false, andando = false, virado_direita = true;
    InitWindow(900, 900, "Robo");
    SetTargetFPS(60); //crava o FPS do jogo em 60, para o jogo sempre rodar em velocidade igual, independente da taxa de atualização do monitor.
    Texture cenario = LoadTexture("./cenario.png"); //textura com o cenário.
    Texture robo_parado = LoadTexture("./robo_parado.png"); //textura com o robô parado. 
    Texture robo_andando[6]; //abaixo, texturas com varios desenhos do robô, que depois serão usadas para fazer uma animação dele andando.
    robo_andando[0] = LoadTexture("./robo_andando1.png");
    robo_andando[1] = LoadTexture("./robo_andando2.png");
    robo_andando[2] = LoadTexture("./robo_andando3.png");
    robo_andando[3] = LoadTexture("./robo_andando4.png");
    robo_andando[4] = LoadTexture("./robo_andando5.png");
    robo_andando[5] = LoadTexture("./robo_andando6.png");

    guardarMatriz(mapa); //função para salvar a fase do txt na matriz.

    while(!WindowShouldClose()){
        BeginDrawing(); //inicia o modo desenho.
            ClearBackground(WHITE); //limpa o cenário a cada volta (impede que desenhos antigos do robô apareçam).
            
            desenharCenario(cenario, posx, posy, mapa); //função que desenha a textura do cenário e as paredes.
            moverRobo(posx, posy, novaposx, novaposy, velocidade, andando, virado_direita); //função que movimenta o robô (movimento só pode ocorrer (ou não) após a verificação de colisão na função abaixo).
            verificarColisoes(robo_andando, mapa, posx, novaposx, posy, novaposy, colisao); //função que verifica colisões entre o robô e o cenário/paredes.
            desenharRobo(robo_parado, robo_andando, andando, virado_direita, posx, novaposx, posy, novaposy, largura_robo, cont_mov, espera_mov); //função que desenha o robô e suas possíveis animações.
        EndDrawing(); //finaliza o modo desenho.
        colisao = false;
        andando = false;
    }
    CloseWindow();
    return 0;
}