#include <iostream>
#include <vector>  
#include <stdio.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <thread>
#include "sort_functions.h"

using namespace std;

/**
 * @brief Keeps the window up, and sets animation_data's open attribute to false when user closes the window.
 * 
 * @param animation_data_obj 
 */
void close_program_check(animation_data &animation_data_obj) {
   SDL_Event e;
   SDL_PollEvent(&e);
   while (e.type != SDL_QUIT) {
      SDL_PollEvent(&e);
   }
   animation_data_obj.open = false;
}

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
            // determine bar size
            switch (animation_data_obj.size) {
               case 10:
                  animation_data_obj.bar_space = 40;
                  animation_data_obj.bar_width = 80;
                  break;
               case 25:
                  animation_data_obj.bar_space = 16;
                  animation_data_obj.bar_width = 32;
                  break;
               case 50:
                  animation_data_obj.bar_space = 8;
                  animation_data_obj.bar_width = 16;
                  break;
               case 100:
                  animation_data_obj.bar_space = 4;
                  animation_data_obj.bar_width = 8;
                  break;
               case 200:
                  animation_data_obj.bar_space = 2;
                  animation_data_obj.bar_width = 4;
                  break;
               case 300: 
                  animation_data_obj.bar_space = 1;
                  animation_data_obj.bar_width = 3;
                  break;
               case 400:
                  animation_data_obj.bar_space = 1;
                  animation_data_obj.bar_width = 2;
                  break;
               case 600:
                  animation_data_obj.bar_space = 1;
                  animation_data_obj.bar_width = 1;
                  break;
               case 1200: 
                  animation_data_obj.bar_space = 0;
                  animation_data_obj.bar_width = 1;
                  break;
               default:
                  animation_data_obj.bar_space = 1;
                  animation_data_obj.bar_width = 1;
            }
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
   if (!SDL_init(animation_data_obj)) {
      return 0;
   }

   // spawn thread to keep window up
   thread window_thread(close_program_check, ref(animation_data_obj));
   
   // build hardcoded array and draw it
   int a[animation_data_obj.size];
   for (int i = 0; i < animation_data_obj.size; i++) {
      a[i] = rand() % SCREEN_HEIGHT + 1;
   }
   draw_array(animation_data_obj, a, -1);

   // sort the array and animate its progress
   if (algorithm == "bubble") bubble_sort(animation_data_obj, a);
   else if (algorithm == "selection") selection_sort(animation_data_obj, a);
   else if (algorithm == "insertion") insertion_sort(animation_data_obj, a);
   else if (algorithm == "merge") merge_sort(animation_data_obj, a, 0, animation_data_obj.size - 1);
   else if (algorithm == "quick") quick_sort(animation_data_obj, a, 0, animation_data_obj.size - 1);
   else if (algorithm == "counting") counting_sort(animation_data_obj, a);
   else if (algorithm == "shell") shell_sort(animation_data_obj, a);
   else if (algorithm == "bogo") bogo_sort(animation_data_obj, a);
   else {
      cout << "ERROR: Invalid algorithm, bubble sort will be used." << endl;
      bubble_sort(animation_data_obj, a);
   }
   draw_array(animation_data_obj, a, -1);
   
   // wait for user to close window
   window_thread.join();
   SDL_close(animation_data_obj);
   return 0;
}

