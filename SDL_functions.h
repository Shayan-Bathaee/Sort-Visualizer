
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

/**
 * @brief Initializes SDL window and renderer, sets background to black
 * 
 * @param window a pointer to the window
 * @param renderer a pointer to the renderer
 * @return true if SDL was initialized correctly
 * @return false if SDL initialization failed
 */
bool SDLinit(SDL_Window** window, SDL_Renderer** renderer) {
   // initialize sdl
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      cout << "SDL could not be initialized. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // create window
   *window = SDL_CreateWindow("Sort-Visualizer, by Shayan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if (*window == NULL) {
      cout << "Window could not be created. SDL Error: " << SDL_GetError() << endl;
   }
   // create renderer for the window
   *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
   if (*renderer == NULL) {
      cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // fill background black
   SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(*renderer);
   SDL_RenderPresent(*renderer);

   return true;
}

/**
 * @brief Properly closes SDL by destroying renderer and window
 * 
 * @param window 
 * @param renderer 
 */
void SDLclose(SDL_Window** window, SDL_Renderer** renderer) {
   SDL_DestroyRenderer(*renderer);
   SDL_DestroyWindow(*window);
   *renderer = NULL;
   *window = NULL;
   SDL_Quit();
}