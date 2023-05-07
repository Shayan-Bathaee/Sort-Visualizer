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
   animation_data animation_data_obj;
   
   // handle command line arguments
   if (argc > 1) {
      for (int i = 0; i < argc; i++) {
         if ((string)argv[i] == "-h") { // help flag
            cout << "Usage:\n\t./sort -a <algorithm> -s <size> -d <delay>" << endl;
            cout << "Algorithms:\n\tbubble\n\tselection\n\tinsertion\n\tmerge\n\tquick\n\tcounting\n\tshell\n\tbogo" << endl;
            cout << "Sizes:\n\t10, 25, 50, 100, 200, 300, 600, 1200" << endl;
            cout << "Delays:\n\t0 <= delay (ms) <= 1000" << endl;
            cout << "Defaults:\n\talgorithm: bubble\n\tsize: 200\n\tdelay: 0" << endl;
            return 0;
         }
         else if ((string)argv[i] == "-a") { // algorithm flag
            i++;
            algorithm = argv[i];
            continue;
         }
         else if ((string)argv[i] == "-s") { // size flag
            i++;
            animation_data_obj.size = stoi(argv[i]);
            continue;
         }
         else if ((string)argv[i] == "-d") { // delay flag
            i++;
            animation_data_obj.delay = stoi(argv[i]);
            if (animation_data_obj.delay > 1000 || animation_data_obj.delay < 0) {
               cout << "ERROR: Invalid delay, 0 ms will be used." << endl;
               animation_data_obj.delay = 0;
            }
            animation_data_obj.delay *= 1000; // convert to microseconds (for usleep() function)
            continue;
         }
      }
   }

   // Set up the SDL window
   if (!SDLinit(animation_data_obj)) {
      return 0;
   }


   // Create a thread to run close program check!!!!!!!! -------------------------------------------------------------------------------------------------------------
   
   // build hardcoded array and draw it
   int a[animation_data_obj.size];
   for (int i = 0; i < animation_data_obj.size; i++) {
      a[i] = rand() % SCREEN_HEIGHT + 1;
   }
   draw_array(animation_data_obj, a, -1);

   // sort the array and animate its progress
   bool sorted = false;
   if (algorithm == "bubble") sorted = bubble_sort(animation_data_obj, a);
   else if (algorithm == "selection") sorted = selection_sort(animation_data_obj, a);
   else if (algorithm == "insertion") sorted = insertion_sort(animation_data_obj, a);
   else if (algorithm == "merge") sorted = merge_sort(animation_data_obj, a, 0, animation_data_obj.size - 1);
   else if (algorithm == "quick") sorted = quick_sort(animation_data_obj, a, 0, animation_data_obj.size - 1);
   else if (algorithm == "counting") sorted = counting_sort(animation_data_obj, a);
   else if (algorithm == "shell") sorted = shell_sort(animation_data_obj, a);
   else if (algorithm == "bogo") sorted = bogo_sort(animation_data_obj, a);
   else {
      cout << "ERROR: Invalid algorithm, bubble sort will be used." << endl;
      sorted = bubble_sort(animation_data_obj, a);
   }
   draw_array(animation_data_obj, a, -1);
   
   
   // user closed window
   if (!sorted) {
      SDLclose(animation_data_obj);
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

