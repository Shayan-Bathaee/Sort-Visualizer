#include <SDL2/SDL.h>
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
      bool open = true; // determines if user wants the window open
};

/**
 * @brief Initializes SDL window and renderer, and fills the window black.
 * 
 * @param ad 
 * @return true - if the window was created successfully
 * @return false - if the window could not be created
 */
bool SDL_init(animation_data &ad) {
   // initialize sdl
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      cout << "SDL could not be initialized. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // create window
   ad.window = SDL_CreateWindow("Sort-Visualizer, by Shayan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if (ad.window == NULL) {
      cout << "Window could not be created. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // create renderer for the window
   ad.renderer = SDL_CreateRenderer(ad.window, -1, SDL_RENDERER_ACCELERATED);
   if (ad.renderer == NULL) {
      cout << "Renderer could not be created. SDL Error: " << SDL_GetError() << endl;
      return false;
   }
   // fill background black
   SDL_SetRenderDrawColor(ad.renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(ad.renderer);
   SDL_RenderPresent(ad.renderer);

   return true;
}

/**
 * @brief Properly closes animation window
 * 
 * @param ad 
 */
void SDL_close(animation_data &ad) {
   SDL_DestroyRenderer(ad.renderer);
   SDL_DestroyWindow(ad.window);
   ad.renderer = NULL;
   ad.window = NULL;
   SDL_Quit();
}

/**
 * @brief Draws the array in the window
 * 
 * @param ad 
 * @param a - array
 * @param special_index - an index of a bar to draw red (-1 will draw all boxes white)
 * @return true - if the array was drawn
 * @return false - if the user has closed the window
 */
bool draw_array(animation_data &ad, int* a, int special_index) {
   // check if window is open
   if (ad.open == false) {
      return false;
   }
   
   // clear screen
   SDL_SetRenderDrawColor(ad.renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(ad.renderer);
   SDL_PumpEvents();

   // draw array
   SDL_SetRenderDrawColor(ad.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   int current_start_pos = 0;
   for (int i = 0; i < ad.size; i++) {
      if (i == special_index) { // draw this bar in a different color
         SDL_SetRenderDrawColor(ad.renderer, 0xFF, 0x00, 0x00, 0xFF);
         SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], ad.bar_width, a[i]};
         SDL_RenderFillRect(ad.renderer, &new_bar);
         SDL_PumpEvents();
         current_start_pos += (ad.bar_width + ad.bar_space);
         SDL_SetRenderDrawColor(ad.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
         continue;
      }
      SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], ad.bar_width, a[i]};
      SDL_RenderFillRect(ad.renderer, &new_bar);
      SDL_PumpEvents();
      current_start_pos += (ad.bar_width + ad.bar_space);
   }

   // delay
   if (ad.delay) {
      usleep(ad.delay);
   }

   // render and return true
   SDL_RenderPresent(ad.renderer);
   return true;
}
