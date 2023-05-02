#include <iostream>
#include <vector>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <thread>
#include "sort_functions.h"

using namespace std;

int main(int argc, char* argv[]) {
   // set default parameters
   string algorithm = "bubble";
   int size = 200;
   // handle command line arguments
   if (argc > 1) {
      for (int i = 0; i < argc; i++) {
         if ((string)argv[i] == "-h") { // help flag
            cout << "Usage:\n\t./sort -a <algorithm> -s <size>" << endl;
            cout << "Algorithms:\n\tbubble\n\tselection\n\tinsertion\n\tmerge" << endl;
            cout << "Sizes:\n\t10, 25, 50, 100, 200, 300, 600, 1200" << endl;
            cout << "Defaults:\n\talgorithm: bubble\n\tsize: 200" << endl;
            return 0;
         }
         else if ((string)argv[i] == "-a") { // algorithm flag
            i++;
            algorithm = argv[i];
            continue;
         }
         else if ((string)argv[i] == "-s") { // size flag
            i++;
            size = stoi(argv[i]);
            continue;
         }
      }
   }

   // Set up the SDL window
   SDL_Window* window = NULL;
   SDL_Renderer* renderer = NULL;
   if (!SDLinit(&window, &renderer)) {
      return 0;
   }
   
   // build hardcoded array and draw it
   int a[size];
   for (int i = 0; i < size; i++) {
      a[i] = rand() % SCREEN_HEIGHT + 1;
   }
   draw_array(&renderer, a, size, -1);

   // sort the array and display animate its progress
   bool sorted = false;
   if (algorithm == "bubble") sorted = bubble_sort(&renderer, a, size);
   else if (algorithm == "selection") sorted = selection_sort(&renderer, a, size);
   else if (algorithm == "insertion") sorted = insertion_sort(&renderer, a, size);
   else if (algorithm == "merge") sorted = merge_sort(&renderer, a, 0, size - 1, size);
   else if (algorithm == "quick") sorted = quick_sort(&renderer, a, 0, size - 1, size);
   else {
      cout << "ERROR: Invalid algorithm, bubble sort will be used." << endl;
      sorted = bubble_sort(&renderer, a, size);
   }
   draw_array(&renderer, a, size, -1);
   
   
   // user closed window
   if (!sorted) {
      SDLclose(&window, &renderer);
      return 0;
   }

   // array was sorted, keep the window up
   SDL_Event e;
   bool quit = false;
   while(quit == false) {
      while(SDL_PollEvent(&e)) {
         if (e.type == SDL_QUIT) {
            quit = true; 
         }
      }
   }
   
   return 0;
}