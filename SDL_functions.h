#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define MAX_ARRAY_LEN SCREEN_WIDTH / 4

/*
Initializes SDL, creating the window.
*/
void SDLinit(SDL_Window* window, SDL_Surface* screen_surface) {
   // initialize sdl
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      cout << "SDL Couldn't be initialized\n";
   }

   else {
      // create the window (undefined start position)
      window = SDL_CreateWindow("First SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (window == NULL) {
         cout << "Window could not be made. Error " << SDL_GetError() << "\n";
      }
      else {
         // set the screen surface and fill it black
         screen_surface = SDL_GetWindowSurface(window);
         SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));

         // update the surface
         SDL_UpdateWindowSurface(window);
      }
   }
}

/*
Properly destroys the window and quits SDL
*/
void SDLclose(SDL_Window* window) {
   SDL_DestroyWindow(window);
   SDL_Quit();
}