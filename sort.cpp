#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include "sort_functions.h"
using namespace std;

#define NUM_INPUTS 3
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define MAX_ARRAY_LEN SCREEN_WIDTH / 4

vector<string> sort_types = {"sort-1", "sort-2"};

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

   return;
}

/*
Properly destroys the window and quits SDL
*/
void SDLclose(SDL_Window* window) {
   SDL_DestroyWindow(window);
   SDL_Quit();
   return;
}


int main(int argc, char* argv[]) {
   /* Take user input */
   if (argc != NUM_INPUTS) { // user needs help
      cout << "Usage: " << endl;
      cout << "\t./sort <array-len> <sort-type>" << endl;
      cout << "Requirements:" << endl;
      cout << "\t0 < array-len <= " << MAX_ARRAY_LEN << endl;
      cout << "\tSort types: ";
      for (uint i = 0; i < sort_types.size(); i++) {
         if (i == sort_types.size() - 1) cout << sort_types[i] << endl;
         else cout << sort_types[i] << ", ";
      }
      return 0;
   }

   // check array_len
   string array_len_string = argv[1];
   int i = 0;
   while (array_len_string[i]) {
      if (isdigit(array_len_string[i]) == false) {
         cout << "ERROR: ";
         cout << "array-len must be a positive integer" << endl;
         return 0;
      }
      i++;
   }
   int array_len = stoi(array_len_string);
   if (array_len == 0) {
      cout << "ERROR: ";
      cout << "array-len cannot be 0" << endl;
      return 0;
   }
   if (array_len > MAX_ARRAY_LEN) {
      cout << "ERROR: ";
      cout << "array-len cannot exceed " << MAX_ARRAY_LEN << endl;
      return 0;
   }

   // check sort type
   string sort_type = argv[2];
   if (find(sort_types.begin(), sort_types.end(), sort_type) == sort_types.end()) {
      cout << "ERROR: ";
      cout << sort_type << " is not a valid sort type" << endl;
      cout << "Valid sort types: ";
      for (uint i = 0; i < sort_types.size(); i++) {
         if (i == sort_types.size() - 1) cout << sort_types[i] << endl;
         else cout << sort_types[i] << ", ";
      }
      return 0;
   }

   

   
   // initialize window and screen surface variables
   SDL_Window* window = NULL;
   SDL_Surface* screen_surface = NULL;

   SDLinit(window, screen_surface);
   
   // hacky line to keep the window up
   SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
   
   SDLclose(window);
   
   return 0;
}