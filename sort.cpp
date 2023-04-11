#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>  
#include <stdio.h>
#include <string>
using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

vector<string> sort_types = {"sort 1", "sort 2"};

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
   // take user input
   if ((argc != 3) || ((string)argv[1] == "-h") || ((string)argv[1] == "-H")) { // user needs help
      cout << "Usage: " << endl;
      cout << "\t./sort <array-len> <sort-type>" << endl;
      cout << "Requirements:" << endl;
      cout << "\t0 < array-len < " << SCREEN_WIDTH / 4 << endl;
      cout << "\tSort types: ";
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