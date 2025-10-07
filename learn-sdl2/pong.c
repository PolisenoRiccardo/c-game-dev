#include <stdio.h>
#include <SDL2/SDL.h>

#define PADDLE_W 100
#define PADDLE_H 30

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //printf("SDL_Init failed: %s\n", SDL_GetError());
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
    //printf("Window creation failed: %s\n", SDL_GetError());
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

  const int paddle_speed = 300;
  const int ball_speed = 200;

  float ball_x = window_w/2.0f;
  float ball_y = window_h/2.0f;

  float paddle_x = paddle.x;

  #define DIRECTION_UP 0
  #define DIRECTION_DOWN 1

  int direction = DIRECTION_DOWN;
  
  int fps = 120;

  double drawInterval = 1000 / fps;
  Uint32 last_time = SDL_GetTicks();
  double delta_time = 0;
  Uint32 current_time;
  Uint32 timer = 0;
  int drawCount;

  while (1) {

    current_time = SDL_GetTicks();
  
    delta_time += (current_time - last_time) / drawInterval;
    timer += (current_time - last_time);
    last_time = current_time;


    if (delta_time  > 1) {

      double delta_util = (delta_time * drawInterval) / 1000;
      
      //printf("First BALL SPEED: %d\nDelta Util: %f\n", ball_speed * delta_util, delta_util);
      //printf("PADDLE SPEED: %d\n", paddle_speed * delta_util);

      // printf("DELTA: %f\nBALL SPEED: %d\n__________\n",delta_util, ball_speed * delta_util);
      if (keys[SDL_SCANCODE_RIGHT]) {
        if (paddle_x + paddle.w < window_w)
          paddle_x += (paddle_speed * delta_util);
        else paddle_x = window_w - paddle.w;
      }
      if (keys[SDL_SCANCODE_LEFT]) {
        if (paddle_x - (paddle_speed * delta_util) > 0) 
          paddle_x -= (paddle_speed * delta_util);
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
          ball_y += ball_speed * delta_util;
          // printf("BALL SPEED: %d\nDelta Util: %f\n", ball_speed * delta_util, delta_util);
        }
        else direction = DIRECTION_UP;
      }
      if (direction == DIRECTION_UP) {
        // printf("BALL SPEED: %d\nDelta Util: %f\n", ball_speed * delta_util, delta_util);
        if (ball.y > 0) 
        {
          ball_y -= ball_speed * delta_util;
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
      
      delta_time--;
      drawCount++;
    }

    if (timer >= 1000) {
      printf("FPS:%d\n", drawCount);
      drawCount = 0;
      timer = 0;
    }
  }

  printf("Chiudo!\n");
  SDL_DestroyWindow(finestra);
  SDL_Quit();
  return 0;
}
