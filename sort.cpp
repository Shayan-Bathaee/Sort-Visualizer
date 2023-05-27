#include <iostream>
#include <thread>
#include "sort_functions.h"

using namespace std;

/**
 * @brief Keeps the window up, and sets animation_data's open attribute to false when user closes the window.
 * 
 * @param ad 
 */
void close_program_check(animation_data &ad) {
   SDL_Event e;
   SDL_PollEvent(&e);
   while (e.type != SDL_QUIT) {
      SDL_PollEvent(&e);
   }
   ad.open = false;
}


int main(int argc, char* argv[]) {
   // set default parameters
   string algorithm = "bubble";
   animation_data ad;
   int valid_sizes[] = {10, 25, 50, 100, 200, 300, 400, 600, 1200};
   
   // handle command line arguments
   if (argc > 1) {
      for (int i = 0; i < argc; i++) {
         if ((string)argv[i] == "-h") { // help flag
            cout << "Usage:\n\t./sort -a <algorithm> -s <size> -d <delay>" << endl;
            cout << "Algorithms:\n\tbubble\n\tselection\n\tinsertion\n\tmerge\n\tquick\n\tcounting\n\tshell\n\tbogo" << endl;
            cout << "Sizes:\n\t10, 25, 50, 100, 200, 300, 400, 600, 1200" << endl;
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
            // get the size
            int tmp_size = stoi(argv[i]);
            int j = 0;
            while (valid_sizes[j]) {
               if (tmp_size == valid_sizes[j]) {
                  ad.size = tmp_size;
                  break;
               }
               j++;
            }
            if (ad.size != tmp_size) {
               cout << "ERROR: Invalid size, 600 will be used." << endl;
               ad.size = 600;
            }
            // set the bar width and bar space
            if (ad.size == 300) {
               ad.bar_width = 2;
               ad.bar_space = 2;
            }
            else if (ad.size < 600) {
               ad.bar_width = ((1200 / ad.size) / 3) * 2;
               ad.bar_space = ad.bar_width / 2;
            }
            else {
               ad.bar_width = 1;
               ad.bar_space = (1200 / ad.size) - 1;
            }
            continue;
         }

         else if ((string)argv[i] == "-d") { // delay flag
            i++;
            ad.delay = stoi(argv[i]);
            if (ad.delay > 1000 || ad.delay < 0) {
               cout << "ERROR: Invalid delay, 0 ms will be used." << endl;
               ad.delay = 0;
            }
            ad.delay *= 1000; // convert to microseconds (for usleep() function)
            continue;
         }
      }
   }

   // Set up the SDL window
   if (!SDL_init(ad)) {
      return 0;
   }

   // spawn thread to keep window up
   thread window_thread(close_program_check, ref(ad));
   
   // build hardcoded array and draw it
   int a[ad.size];
   for (int i = 0; i < ad.size; i++) {
      a[i] = rand() % SCREEN_HEIGHT + 1;
   }
   draw_array(ad, a, -1);

   // sort the array and animate its progress
   if (algorithm == "bubble") bubble_sort(ad, a);
   else if (algorithm == "selection") selection_sort(ad, a);
   else if (algorithm == "insertion") insertion_sort(ad, a);
   else if (algorithm == "merge") merge_sort(ad, a, 0, ad.size - 1);
   else if (algorithm == "quick") quick_sort(ad, a, 0, ad.size - 1);
   else if (algorithm == "counting") counting_sort(ad, a);
   else if (algorithm == "shell") shell_sort(ad, a);
   else if (algorithm == "bogo") bogo_sort(ad, a);
   else {
      cout << "ERROR: Invalid algorithm, bubble sort will be used." << endl;
      bubble_sort(ad, a);
   }
   draw_array(ad, a, -1);
   
   // wait for user to close window
   window_thread.join();
   SDL_close(ad);
   return 0;
}

