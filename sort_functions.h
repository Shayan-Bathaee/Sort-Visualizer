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

int merge(SDL_Renderer** renderer, int* a, int left_index, int middle_index, int right_index, int size) {
    SDL_Event e;

    // create two arrays for the left and right
    int left_size = middle_index - left_index + 1;
    int right_size = right_index - middle_index;
    int left_array[left_size];
    int right_array[right_size];
    for (int i = 0; i < left_size; i++) {
        left_array[i] = a[left_index + i];
    }
    for (int i = 0; i < right_size; i++) {
        right_array[i] = a[middle_index + i + 1];
    }

    // merge temporary arrays back into a
    int left_curr = 0;
    int right_curr = 0;
    int merged_curr = left_index;
    // take the smaller element and put it into merged
    while ((left_curr < left_size) && (right_curr < right_size)) {
        if (left_array[left_curr] <= right_array[right_curr]) {
            a[merged_curr] = left_array[left_curr];
            left_curr++;
        }
        else {
            a[merged_curr] = right_array[right_curr];
            right_curr++;
        }
        draw_array(renderer, a, size, merged_curr); // draw array with merged_curr colored
        if (SDL_PollEvent(&e)) { // check if user wants to close window
            if (e.type == SDL_QUIT) {
                return 0;
            }
        }
        merged_curr++;
    }

    // copy the rest of left array if necesssary
    while (left_curr < left_size) {
        a[merged_curr] = left_array[left_curr];
        left_curr++;
        merged_curr++;
    }

    // copy the left of right array if necessary
    while (right_curr < right_size) {
        a[merged_curr] = right_array[right_curr];
        right_curr++;
        merged_curr++;
    }
    return 1;

}

bool merge_sort(SDL_Renderer** renderer, int* a, int left_index, int right_index, int size) {
    int result = 0;
    if (left_index < right_index) {
        int middle_index = left_index + (right_index - left_index) / 2;

        merge_sort(renderer, a, left_index, middle_index, size);
        merge_sort(renderer, a, middle_index + 1, right_index, size);

        result = merge(renderer, a, left_index, middle_index, right_index, size);
    }
    if (result == 0) {
        return result;
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return 1;
}