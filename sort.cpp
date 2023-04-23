#include <iostream>
#include <vector>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include "sort_functions.h"
#include "SDL_functions.h"

using namespace std;

void draw_array(SDL_Renderer** renderer, int* a, int size) {
   // clear screen
   SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0xFF);
   SDL_RenderClear(*renderer);
   SDL_PumpEvents();

   // draw array
   int space = 2;
   int width = 4;
   SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   int current_start_pos = 0;
   for (int i = 0; i < size; i++) {
      SDL_Rect new_bar = {current_start_pos, SCREEN_HEIGHT - a[i], width, a[i]};
      SDL_RenderFillRect(*renderer, &new_bar);
      SDL_PumpEvents();
      current_start_pos += (width + space);
   }
   SDL_RenderPresent(*renderer);
}

int main() {
   // Set up the SDL window
   SDL_Window* window = NULL;
   SDL_Renderer* renderer = NULL;
   if (!SDLinit(&window, &renderer)) {
      cout << "Initialization failure" << endl;
   }

   // build hardcoded array
   int array_size = 600;
   int hard_array[array_size];
   for (int i = 0; i < array_size; i++) {
      hard_array[i] = rand() % 800 + 1;
   }

   // display hardcoded array
   draw_array(&renderer, hard_array, array_size);
   
   // keep the window up
   SDL_Event e;
   bool quit = false;
   while(quit == false) {
      while(SDL_PollEvent(&e)) {
         if(e.type == SDL_QUIT) {
            quit = true; 
         }
      }
   }
   SDLclose(&window, &renderer);
   return 0;
}