
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

using namespace std;

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
      return false;
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

bool draw_array(SDL_Renderer** renderer, int* a, int size, int special_index) {
   // clear screen
   SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(*renderer);
   SDL_PumpEvents();

   // determine bar sizes
   int space, width;
   switch (size) {
      case 10:
         space = 40;
         width = 80;
         break;
      case 25:
         space = 16;
         width = 32;
         break;
      case 50:
         space = 8;
         width = 16;
         break;
      case 100:
         space = 4;
         width = 8;
         break;
      case 200:
         space = 2;
         width = 4;
         break;
      case 300: 
         space = 1;
         width = 3;
         break;
      case 400:
         space = 1;
         width = 2;
         break;
      case 600:
         space = 1;
         width = 1;
         break;
      case 1200: 
         space = 0;
         width = 1;
         break;
      default:
         space = 1;
         width = 1;
   }

   // draw array
   SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   int current_start_pos = 0;
   for (int i = 0; i < size; i++) {
      if (i == special_index) { // draw this bar in a different color
         SDL_SetRenderDrawColor(*renderer, 0xFF, 0x00, 0x00, 0xFF);
         SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], width, a[i]};
         SDL_RenderFillRect(*renderer, &new_bar);
         SDL_PumpEvents();
         current_start_pos += (width + space);
         SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         continue;
      }
      SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], width, a[i]};
      SDL_RenderFillRect(*renderer, &new_bar);
      SDL_PumpEvents();
      current_start_pos += (width + space);
   }

   // check if user wants to close window
   SDL_Event e;
   if (SDL_PollEvent(&e)) { // check if user wants to close window
      if (e.type == SDL_QUIT) {
         return false;
      }
   }

   // render and return true
   SDL_RenderPresent(*renderer);
   return true;
}