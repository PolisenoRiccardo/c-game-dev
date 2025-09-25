#include <stdio.h>
#include <SDL2/SDL.h>

#define PADDLE_W 100
#define PADDLE_H 30

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *finestra = SDL_CreateWindow(
      "Titolone", 
      SDL_WINDOWPOS_CENTERED, // posizione finestra x
      SDL_WINDOWPOS_CENTERED, // posizione finestra y
      800, // larghezza
      600, // altezza
      SDL_WINDOW_SHOWN // flag(s)
  );

  if (finestra == NULL) {
    printf("Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  int window_w, window_h;
  SDL_GetWindowSize(finestra, &window_w, &window_h);

  SDL_Renderer *renderer = SDL_CreateRenderer(finestra, -1, SDL_RENDERER_ACCELERATED);
  
  SDL_Rect paddle = {(window_w/2)-PADDLE_W/2, window_h-PADDLE_H - 100, PADDLE_W, PADDLE_H};

  SDL_Rect ball = {window_w/2, window_h/2, 20, 20};

  SDL_Event event;
  
  const Uint8* keys = SDL_GetKeyboardState(NULL);

  int debug = 0;

  int paddle_speed = 6;

  #define DIRECTION_UP 0
  #define DIRECTION_DOWN 1

  int direction = DIRECTION_DOWN;
  int ball_speed = 4;

  while (1) {

    // definisce il colore da disegnare, l'ultimo argomento è l'alpha
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // riempe la schermata con il colore settato
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &paddle);
   
    // ball render
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);


   
    if (keys[SDL_SCANCODE_RIGHT]) {
      if (paddle.x + paddle.w < window_w) paddle.x += paddle_speed;
      else paddle.x = window_w - paddle.w;
    }
    if (keys[SDL_SCANCODE_LEFT]) {
      if (paddle.x - paddle_speed > 0) {paddle.x -= paddle_speed;}
      else paddle.x = 0; 
    }
  
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.scancode) {
          case SDL_SCANCODE_X:
            SDL_DestroyWindow(finestra);
            SDL_Quit();
            return 0;
          default:
            break;
        } 
      }
      if (event.type == SDL_QUIT) {
        SDL_DestroyWindow(finestra);
        SDL_Quit();
        return 0;
      }     
    } 

    // ball update
    SDL_Log("%d", SDL_HasIntersection(&ball, &paddle));
    if (direction == DIRECTION_DOWN) {
      if (ball.y + ball.h < window_h && !(SDL_HasIntersection(&(SDL_Rect){ball.x, ball.y, ball.w, ball.h}, &paddle))) {ball.y += ball_speed;}
      else direction = DIRECTION_UP;
    }
    if (direction == DIRECTION_UP) {
      if (ball.y > 0) {ball.y -= ball_speed;}
      else direction = DIRECTION_DOWN;
    }

    SDL_Delay(16);
    debug++;
  }

  printf("Chiudo!\n");
  SDL_DestroyWindow(finestra);
  SDL_Quit();
  return 0;
}
