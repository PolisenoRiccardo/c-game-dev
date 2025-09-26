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

  int upscale_num = 2;

  SDL_Renderer *renderer = SDL_CreateRenderer(finestra, -1, SDL_RENDERER_ACCELERATED);
  
  SDL_Rect paddle = {(window_w/2)-PADDLE_W*upscale_num/2, window_h-PADDLE_H*upscale_num, PADDLE_W*upscale_num, PADDLE_H*upscale_num};

  SDL_Rect ball = {window_w/2, window_h/2, 20*upscale_num, 20*upscale_num};

  SDL_Event event;
  
  const Uint8* keys = SDL_GetKeyboardState(NULL);


  float paddle_speed = 300.0f;
  float ball_speed = 200.0f;

  float ball_x = window_w/2.0f;
  float ball_y = window_h/2.0f;

  float paddle_x = paddle.x;
  float paddle_y = paddle.y;

  #define DIRECTION_UP 0
  #define DIRECTION_DOWN 1

  int direction = DIRECTION_DOWN;
  
  Uint32 last_time = SDL_GetTicks();
  float delta_time = 0.0f;

  while (1) {

    Uint32 current_time = SDL_GetTicks();
    delta_time = (current_time - last_time) / 1000.0f;  // converti in secondi
    last_time = current_time;
   
    if (keys[SDL_SCANCODE_RIGHT]) {
      if (paddle_x + paddle.w < window_w)
        paddle_x += (paddle_speed * delta_time);
      else paddle_x = window_w - paddle.w;
    }
    if (keys[SDL_SCANCODE_LEFT]) {
      if (paddle_x - (paddle_speed * delta_time) > 0) 
        paddle_x -= (paddle_speed * delta_time);
      else paddle_x = 0; 
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
    if (direction == DIRECTION_DOWN) {
      if (ball.y + ball.h < window_h &&
          !(SDL_HasIntersection(&ball, &paddle))) 
      {
        ball_y += ball_speed * delta_time;
      }
      else direction = DIRECTION_UP;
    }
    if (direction == DIRECTION_UP) {
      if (ball.y > 0) 
      {
        ball_y -= ball_speed * delta_time;
      }
      else direction = DIRECTION_DOWN;
    }

    paddle.x = (int)paddle_x;
    ball.y = (int)ball_y;

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
  }

  printf("Chiudo!\n");
  SDL_DestroyWindow(finestra);
  SDL_Quit();
  return 0;
}
