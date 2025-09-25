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

//  SDL_Renderer *renderer = SDL_CreateRenderer(finestra, -1, SDL_RENDERER_SOFTWARE);

  SDL_Event event; 
/*
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_MOUSEMOTION:       
        SDL_Log("We got a motion event.");
        SDL_Log("Current mouse position is: (%d, %d)", event.motion.x, event.motion.y);
        break;
      case SDL_KEYDOWN:
        SDL_Log("TASTIERA PREMUTA");
        SDL_Log("HA PREMUTO IL TASTO: %d", event.key.keysym.scancode);
      default:
        SDL_Log("Unhandled Event!");
        break;
    }
    SDL_Log("Event queue empty.");
  }
 */

  while (1) {  
    if (SDL_PollEvent(&event)) {
      SDL_Log("%x", event.type);
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_X) {
            break;
        }
      }  
    }
  }

  printf("Chiudo!\n");
  SDL_DestroyWindow(finestra);
  SDL_Quit();
  return 0;
}
