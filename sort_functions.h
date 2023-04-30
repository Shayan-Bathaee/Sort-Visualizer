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

bool selection_sort(SDL_Renderer** renderer, int* a, int size) {
    SDL_Event e;
    for (int j = 0; j < size - 1; j++) {
        int min = a[j];
        int min_index;
        for (int i = j + 1; i < size; i++) {
            if (a[i] < min) {
                min = a[i];
                min_index = i;
                draw_array(renderer, a, size, min_index); // draw array with the minimum element colored
            }
            if (SDL_PollEvent(&e)) { // check if user wants to close window
                if (e.type == SDL_QUIT) {
                    return 0;
                }
            }
        }
        // swap min and a[j]
        int tmp = a[j];
        a[j] = min;
        a[min_index] = tmp;
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return 1;
}
 
bool insertion_sort(SDL_Renderer** renderer, int* a, int size) {
    SDL_Event e;
    for (int j = 1; j < size; j++) {
        int inserting = j;
        for (int i = inserting - 1; i >= 0; i--) { // check the elements before inserting
            if (a[i] > a[inserting]) { // if the element before inserting is greater, swap them
                int tmp = a[inserting];
                a[inserting] = a[i];
                a[i] = tmp;
                inserting = i;
                draw_array(renderer, a, size, inserting); // draw array with inserting colored
            }
            else { // inserting is in the correct spot
                break;
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