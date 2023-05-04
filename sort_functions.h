#include <iostream>
#include "SDL_functions.h"
using namespace std;

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

bool bubble_sort(SDL_Renderer** renderer, int* a, int size) {
    for (int j = 1; j < size; j++) {
        for (int i = 0; i < size - 1; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                if (!draw_array(renderer, a, size, i + 1)) return false; // draw array with the moving element colored
            }
        }
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}

bool selection_sort(SDL_Renderer** renderer, int* a, int size) {
    for (int j = 0; j < size - 1; j++) {
        int min = a[j];
        int min_index;
        for (int i = j + 1; i < size; i++) {
            if (a[i] < min) {
                min = a[i];
                min_index = i;
                if (!draw_array(renderer, a, size, min_index)) return false; // draw array with the minimum element colored
            }
        }
        swap(a[j], a[min_index]);
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}
 
bool insertion_sort(SDL_Renderer** renderer, int* a, int size) {
    for (int j = 1; j < size; j++) {
        int inserting = j;
        for (int i = inserting - 1; i >= 0; i--) { // check the elements before inserting
            if (a[i] > a[inserting]) { // if the element before inserting is greater, swap them
                swap(a[i], a[inserting]);
                inserting = i;
                if (!draw_array(renderer, a, size, inserting)) return false; // draw array with inserting colored
            }
            else { // inserting is in the correct spot
                break;
            }
        }
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}

bool merge(SDL_Renderer** renderer, int* a, int left_index, int middle_index, int right_index, int size) {
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
        if (!draw_array(renderer, a, size, merged_curr)) return false; // draw array with merged_curr colored
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
    
    return true;
}

bool merge_sort(SDL_Renderer** renderer, int* a, int left_index, int right_index, int size) {
    if (left_index < right_index) {
        int middle_index = left_index + (right_index - left_index) / 2;

        if (!merge_sort(renderer, a, left_index, middle_index, size)) return false;
        if (!merge_sort(renderer, a, middle_index + 1, right_index, size)) return false;

        if (!merge(renderer, a, left_index, middle_index, right_index, size)) return false;

    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}

int partition(SDL_Renderer** renderer, int* a, int left_index, int right_index, int size, int &return_pivot_index) {
    // set rightmost index as pivot
    int pivot_index = right_index;
    int store_index = left_index;
    for (int i = left_index; i < right_index; i++) {
        if (a[i] <= a[pivot_index]) {
            swap(a[i], a[store_index]);
            store_index++;
            if (!draw_array(renderer, a, size, store_index)) return false; // draw array with store_index colored
        }
    }
    swap(a[right_index], a[store_index]);
    if (!draw_array(renderer, a, size, store_index)) return false; // draw array with store_index colored
    return_pivot_index = store_index;
    return true;
}

bool quick_sort(SDL_Renderer** renderer, int* a, int left_index, int right_index, int size) {
    if (left_index < right_index) {
        // choose pivot, partition the array, and call quicksort on each partition
        int pivot_index;
        if (!partition(renderer, a, left_index, right_index, size, pivot_index)) return false;
        if (!quick_sort(renderer, a, left_index, pivot_index - 1, size)) return false;
        if (!quick_sort(renderer, a, pivot_index + 1, right_index, size)) return false;
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}

bool counting_sort(SDL_Renderer** renderer, int* a, int size) {
    // copy a into output for animation
    int* output = new int[size];
    memcpy(output, a, sizeof(int) * size);
    
    // find max
    int max = a[0];
    for (int i = 1; i < size; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    max = max + 1;

    // create count array to store the count of each element
    int count[max] = {0};
    for (int i = 0; i < size; i++) {
        count[a[i]]++;
        if (!draw_array(renderer, a, size, i)) return false; // draw array with index colored
    }

    // take cumulative sum
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // do the sorting magic
    for (int i = size - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        if (!draw_array(renderer, output, size, count[a[i] - 1])) return false; // draw output array with changing index colored
        count[a[i]]--;
    }

    // copy output into a
    for (int i = 0; i < size; i++) {
        a[i] = output[i];
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}

bool shell_sort(SDL_Renderer** renderer, int* a, int size) {
    for (int interval = size / 2; interval > 0; interval = interval / 2) {
        for (int i = interval; i < size; i++) {
            int tmp = a[i];
            int j;
            for (j = i; (j >= interval) && (a[j - interval] > tmp); j = j - interval) {
                a[j] = a[j - interval];
                if (!draw_array(renderer, a, size, j)) return false; // draw output array with the changing index colored
            }
            a[j] = tmp;
            if (!draw_array(renderer, a, size, j)) return false; // draw output array with the changing index colored
        }
    }
    draw_array(renderer, a, size, -1); // draw sorted array in white only
    return true;
}

bool bogo_sort(SDL_Renderer** renderer, int* a, int size) {
    bool sorted = false;
    while (!sorted) {
        // generate permutation of the array (Fisher-Yates shuffling)
        for (int i = size - 1; i >= 0; i--) {
            int j = rand() % (i + 1);
            swap(a[i], a[j]);
        }
        if (!draw_array(renderer, a, size, -1)) return false; // draw array in white only
        // check if permutation is sorted
        sorted = true;
        for (int i = 0; i < size - 1; i++) {
            if (a[i] > a[i + 1]) {
                sorted = false;
                break;
            }
        }
    }
    return true;
}

