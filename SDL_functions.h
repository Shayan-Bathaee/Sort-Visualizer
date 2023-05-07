
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <unistd.h>

using namespace std;

class animation_data {
   public:
      SDL_Window* window = NULL;
      SDL_Renderer* renderer = NULL;
      int delay = 0;
      int size = 200;
};

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
bool SDLinit(animation_data &animation_data_obj) {
   // initialize sdl
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      cout << "SDL could not be initialized. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // create window
   animation_data_obj.window = SDL_CreateWindow("Sort-Visualizer, by Shayan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if (animation_data_obj.window == NULL) {
      cout << "Window could not be created. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // create renderer for the window
   animation_data_obj.renderer = SDL_CreateRenderer(animation_data_obj.window, -1, SDL_RENDERER_ACCELERATED);
   if (animation_data_obj.renderer == NULL) {
      cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // fill background black
   SDL_SetRenderDrawColor(animation_data_obj.renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(animation_data_obj.renderer);
   SDL_RenderPresent(animation_data_obj.renderer);

   return true;
}

/**
 * @brief Properly closes SDL by destroying renderer and window
 * 
 * @param window 
 * @param renderer 
 */
void SDLclose(animation_data &animation_data_obj) {
   SDL_DestroyRenderer(animation_data_obj.renderer);
   SDL_DestroyWindow(animation_data_obj.window);
   animation_data_obj.renderer = NULL;
   animation_data_obj.window = NULL;
   SDL_Quit();
}

bool draw_array(animation_data &animation_data_obj, int* a, int special_index) {
   // clear screen
   SDL_SetRenderDrawColor(animation_data_obj.renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(animation_data_obj.renderer);
   SDL_PumpEvents();

   // determine bar sizes
   int space, width;
   switch (animation_data_obj.size) {
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
   SDL_SetRenderDrawColor(animation_data_obj.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   int current_start_pos = 0;
   for (int i = 0; i < animation_data_obj.size; i++) {
      if (i == special_index) { // draw this bar in a different color
         SDL_SetRenderDrawColor(animation_data_obj.renderer, 0xFF, 0x00, 0x00, 0xFF);
         SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], width, a[i]};
         SDL_RenderFillRect(animation_data_obj.renderer, &new_bar);
         SDL_PumpEvents();
         current_start_pos += (width + space);
         SDL_SetRenderDrawColor(animation_data_obj.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         continue;
      }
      SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], width, a[i]};
      SDL_RenderFillRect(animation_data_obj.renderer, &new_bar);
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

   // render, delay, and return true
   SDL_RenderPresent(animation_data_obj.renderer);

   // thread to delay, thread to check event
   return true;
}
