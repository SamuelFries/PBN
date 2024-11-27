#include "/opt/homebrew/include/SDL2/SDL.h"
#include "/opt/homebrew/include/SDL2/SDL_image.h"
#include <stdbool.h>
#include <stdio.h>
//gcc App.c -I SDL2\x86_64-w64-mingw32\include\SDL2 -L SDL2\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

int verificaColuna (int x);
int verificaLinha (int coluna, int matriz[6][7]);
void mostrarTabuleiro(int matriz[6][7]);
bool haVencedores(int matriz[6][7], int coluna, int linha);

int main(int argc, char** argv){
  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDL_Window* window = SDL_CreateWindow("Interface Gráfica usando SDL", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
  SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture * img = IMG_LoadTexture(renderer, "Tabuleiro.png"); 
  SDL_Texture * circleR = IMG_LoadTexture(renderer, "CRed.png"); 
  SDL_Texture * circleY = IMG_LoadTexture(renderer, "CYellow.png"); 

  //1, quando for a vez do jogador 1, e 2, quando for a vez do jogador 2  
  int jogador = 1;
  bool venceu = false;

  //matriz que representa o tabuleiro
  int matriz[6][7];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            matriz[i][j]=0;
        }
    }

  //interface tabuleiro
  SDL_Rect quad1, quad2, quad3; 
  //quad1 --> é relacionado ao tabuleiro
  quad1.x = 20;
  quad1.y = 20;
  quad1.w = 900;
  quad1.h = 610;


  //evento --> jogo
  while(true)
  {
    SDL_Event event;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, img, NULL, &quad1);
    SDL_SetRenderDrawColor(renderer, 127, 207, 240, 255); //altera cor de fundo
    
    while(SDL_PollEvent(&event)){
      //sair do jogo
      if( event.type == SDL_QUIT || venceu){
        exit(0);
      }

	    else if( event.type == SDL_MOUSEBUTTONDOWN)
      {
        int mouse_x = event.button.x;
        int mouse_y = event.button.y;
        
        int x, y;
        x = verificaColuna (mouse_x);
        printf("%d",x);
        y = verificaLinha (x, matriz);
        printf("%d",y);

        printf("\nColuna (0-6) %d escolhida pelo jogador %d", x, jogador);

        matriz[y][x] = jogador; 
        mostrarTabuleiro(matriz);
        
        jogador = (jogador == 1) ? 2 : 1;

        if (haVencedores(matriz, x, y)) {
            mostrarTabuleiro(matriz);
            printf("Parabéns! Jogador %d venceu!\n", jogador);
            venceu = true;
        }
      }
    }

    for (int i = 0; i < 6; ++i) 
    {
      for (int j = 0; j < 7; ++j) 
      {
        SDL_Rect posicaoPeca;
          //--> posição da imagem
          posicaoPeca.x = 25;
          posicaoPeca.y = 27;
          //--> achatar imagem
          posicaoPeca.w = 110;
          posicaoPeca.h = 85;
        if (matriz[i][j] == 1) 
        {
          posicaoPeca.x += 130*j;
          posicaoPeca.y += 102*i;
          SDL_RenderCopy(renderer, circleR, NULL, &posicaoPeca);
        } 
        else if (matriz[i][j] == 2) 
        {
          posicaoPeca.x += 130*j;
          posicaoPeca.y += 102*i;
          SDL_RenderCopy(renderer, circleY, NULL, &posicaoPeca);
        }
      }
    } 
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}


int verificaColuna (int x)
{
  if (x > 27 && x < 156) 
  {
    return 0;
  }    
  else if (x > 157 && x < 286)
  {
    return 1; 
  }
  else if (x > 287 && x < 416)
  {
    return 2;
  }
  else if (x > 417 && x < 546)
  {
    return 3;
  }
  else if (x > 547 && x < 676)
  {
    return 4;
  }
  else if (x > 677 && x < 806)
  {
    return 5;
  }
  else if (x > 807 && x < 937) //nao sei o limite do tabuleiro
  {
    return 6;
  }
  else
  {
    return -1;
  }
}

int verificaLinha (int coluna, int matriz[6][7]) 
{
    int linha = 5;
    while (linha >= 0) {
        if (matriz[linha][coluna] == 0) {
            return linha;
        }
        linha--;
    }
    return -1; // Retorno caso a coluna esteja cheia (embora o código principal já verifique isso)
}

//método para checar se o jogo funciona corretamente
void mostrarTabuleiro(int matriz[6][7]) {
    printf("\n");
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            printf("| ");
            switch (matriz[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("V");
                    break;
                case 2:
                    printf("A");
                    break;
            }
            printf(" ");
        }
        printf("|\n");
    }
    printf("+---------------------------+\n");
    printf("| 1   2   3   4   5   6   7 |\n\n");
}

bool haVencedores(int matriz[6][7], int coluna, int linha) {
    int peca = matriz[linha][coluna];
    if (peca == 0) {
        return false;
    }

    int count = 1;
    // Verifica na horizontal (direita e esquerda)
    for (int x = coluna + 1; x < 7 && matriz[linha][x] == peca; ++x) {
        ++count;
    }
    for (int x = coluna - 1; x >= 0 && matriz[linha][x] == peca; --x) {
        ++count;
    }
    if (count >= 4) {
        return true;
    }

    count = 1;
    // Verifica na vertical (baixo e cima)
    for (int y = linha + 1; y < 6 && matriz[y][coluna] == peca; ++y) {
        ++count;
    }
    for (int y = linha - 1; y >= 0 && matriz[y][coluna] == peca; --y) {
        ++count;
    }
    if (count >= 4) {
        return true;
    }

    count = 1;
    // Verifica na diagonal principal (/)
    for (int x = coluna + 1, y = linha + 1; x < 7 && y < 6 && matriz[y][x] == peca; ++x, ++y) {
        ++count;
    }
    for (int x = coluna - 1, y = linha - 1; x >= 0 && y >= 0 && matriz[y][x] == peca; --x, --y) {
        ++count;
    }
    if (count >= 4) {
        return true;
    }

    count = 1;
    // Verifica na diagonal secundária (\)
    for (int x = coluna + 1, y = linha - 1; x < 7 && y >= 0 && matriz[y][x] == peca; ++x, --y) {
        ++count;
    }
    for (int x = coluna - 1, y = linha + 1; x >= 0 && y < 6 && matriz[y][x] == peca; --x, ++y) {
        ++count;
    }
    if (count >= 4) {
        return true;
    }

    return false;
}
