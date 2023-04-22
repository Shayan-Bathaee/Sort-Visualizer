#include <iostream>
#include <vector>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include "sort_functions.h"
#include "SDL_functions.h"
using namespace std;

vector<string> sort_types = {"sort-1", "sort-2"};

int main(int argc, char* argv[]) {
   /* Take user input */
   if (argc != 3) { // user needs help
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

   /* Set up SDL window */
   SDL_Window* window = NULL;
   SDL_Renderer* renderer = NULL;
   if (!SDLinit(&window, &renderer)) {
      cout << "Initialization failure" << endl;
   }

   // build hardcoded array
   vector<int> hard_array;
   for (int i = 1; i < 300; i++) {
      hard_array.push_back(rand() % 800 + 1); // push random number between 1 and 800
   }

   // display hardcoded array
   int barwidth = 3;
   int space = 1;
   int current_start_pos = 0;
   SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
   for (int i = 0; i < (int)hard_array.size(); i++) {
      SDL_Rect new_bar = {current_start_pos + i, SCREEN_HEIGHT - hard_array[i], barwidth, hard_array[i]}; // define the bar dimensions
      SDL_RenderFillRect(renderer, &new_bar); 
      SDL_PumpEvents(); // push the new change
      current_start_pos = current_start_pos + barwidth + space;
   }
   SDL_RenderPresent(renderer);
   
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