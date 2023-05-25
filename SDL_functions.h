
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <unistd.h>

using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

/**
 * @brief contains the animation data to be passed into functions
 * 
 */
class animation_data {
   public:
      SDL_Window* window = NULL;
      SDL_Renderer* renderer = NULL;
      int delay = 0;
      int size = 200;
      int bar_space = 2;
      int bar_width = 4;
      bool open = true; // determines if user has the window open
};

/**
 * @brief Initializes SDL window and renderer, and fills the window black.
 * 
 * @param animation_data_obj 
 * @return true - if the window was created successfully
 * @return false - if the window could not be created
 */
bool SDL_init(animation_data &animation_data_obj) {
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
 * @brief Properly closes animation window
 * 
 * @param animation_data_obj 
 */
void SDL_close(animation_data &animation_data_obj) {
   SDL_DestroyRenderer(animation_data_obj.renderer);
   SDL_DestroyWindow(animation_data_obj.window);
   animation_data_obj.renderer = NULL;
   animation_data_obj.window = NULL;
   SDL_Quit();
}

/**
 * @brief Draws the array in the window
 * 
 * @param animation_data_obj 
 * @param a - array
 * @param special_index - an index of a bar to draw red (-1 will draw all boxes white)
 * @return true - if the array was drawn
 * @return false - if the user has closed the window
 */
bool draw_array(animation_data &animation_data_obj, int* a, int special_index) {
   // check if window is open
   if (animation_data_obj.open == false) {
      return false;
   }
   
   // clear screen
   SDL_SetRenderDrawColor(animation_data_obj.renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(animation_data_obj.renderer);
   SDL_PumpEvents();

   // draw array
   SDL_SetRenderDrawColor(animation_data_obj.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   int current_start_pos = 0;
   for (int i = 0; i < animation_data_obj.size; i++) {
      if (i == special_index) { // draw this bar in a different color
         SDL_SetRenderDrawColor(animation_data_obj.renderer, 0xFF, 0x00, 0x00, 0xFF);
         SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], animation_data_obj.bar_width, a[i]};
         SDL_RenderFillRect(animation_data_obj.renderer, &new_bar);
         SDL_PumpEvents();
         current_start_pos += (animation_data_obj.bar_width + animation_data_obj.bar_space);
         SDL_SetRenderDrawColor(animation_data_obj.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         continue;
      }
      SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], animation_data_obj.bar_width, a[i]};
      SDL_RenderFillRect(animation_data_obj.renderer, &new_bar);
      SDL_PumpEvents();
      current_start_pos += (animation_data_obj.bar_width + animation_data_obj.bar_space);
   }

   // delay
   if (animation_data_obj.delay) {
      usleep(animation_data_obj.delay);
   }

   // render and return true
   SDL_RenderPresent(animation_data_obj.renderer);
   return true;
}
