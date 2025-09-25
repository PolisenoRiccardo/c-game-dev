#include <stdio.h>
#include <SDL2/SDL.h>

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
  
  SDL_Rect paddle = {(window_w/2)-75, (window_h/2)-30, 150, 60};

  SDL_Event event;
  
  const Uint8* keys = SDL_GetKeyboardState(NULL);

  int debug = 0;

  while (1) {

    // definisce il colore da disegnare, l'ultimo argomento è l'alpha
    SDL_SetRenderDrawColor(renderer, 40, 0, 40, 255);
    // riempe la schermata con il colore settato
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    SDL_RenderPresent(renderer);

    if (keys[SDL_SCANCODE_RIGHT]) {
      paddle.x += 3;
    }
    if (keys[SDL_SCANCODE_LEFT]) {
      paddle.x -= 3;
    }
    if (keys[SDL_SCANCODE_UP]) {
      paddle.y -= 3;
    }
    if (keys[SDL_SCANCODE_DOWN]) {
      paddle.y += 3;
    }

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        SDL_Log("Keydown %d", debug);
        switch(event.key.keysym.scancode) {
          case SDL_SCANCODE_X:
            printf("Chiudo!\n");
            SDL_DestroyWindow(finestra);
            SDL_Quit();
            return 0;
          default:
            break;
        } 
      }  
    }
    
    SDL_Delay(16);
    debug++;
  }

  printf("Chiudo!\n");
  SDL_DestroyWindow(finestra);
  SDL_Quit();
  return 0;
}
