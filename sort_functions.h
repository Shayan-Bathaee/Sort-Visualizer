#include <iostream>
#include "SDL_functions.h"
using namespace std;

bool bubble_sort(SDL_Renderer** renderer, int* a, int size) {
    SDL_Event e;
    for (int j = 1; j < size; j++) {
        for (int i = 0; i < size - 1; i++) {
            if (a[i] > a[i + 1]) {
                int tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                draw_array(renderer, a, size, i + 1); // draw array with the moving element colored
            }
            if (SDL_PollEvent(&e)) { // check if user wants to close window
                if (e.type == SDL_QUIT) {
                    return 0;
                }
            }
        }
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return 1;
}