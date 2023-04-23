#include <iostream>
#include <vector>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include "sort_functions.h"

#define ARRAY_SIZE 100

using namespace std;

int main() {
   // Set up the SDL window
   SDL_Window* window = NULL;
   SDL_Renderer* renderer = NULL;
   if (!SDLinit(&window, &renderer)) {
      cout << "Initialization failure" << endl;
   }

   // build hardcoded array
   int a[ARRAY_SIZE];
   for (int i = 0; i < ARRAY_SIZE; i++) {
      a[i] = rand() % SCREEN_HEIGHT + 1;
   }
   // display hardcoded array and start sorting
   draw_array(&renderer, a, ARRAY_SIZE, -1);
   bubble_sort(&renderer, a, ARRAY_SIZE);
   
   // keep the window up
   SDL_Event e;
   bool quit = false;
   while(quit == false) {
      while(SDL_PollEvent(&e)) {
         if (e.type == SDL_QUIT) {
            quit = true; 
         }
      }
   }
   SDLclose(&window, &renderer);
   return 0;
}