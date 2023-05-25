# Sort Visualizer

This repository contains a C++ program that utilizes SDL 2 to animate multiple sorting algorithms.

## Usage
### Installation
To run this project, follow these steps:

1. Clone this repository.
2. Open a terminal and navigate to the local repository.
3. Use the make command to generate the sort executable.
4. Run ./sort to start the program.

Note: This project is compatible with Linux systems and Mac OS. On Windows, you can run it using WSL or a virtual machine.

### Options
Running `./sort -h` will display additional usage information:

```
Usage:
        ./sort -a <algorithm> -s <size> -d <delay>
Algorithms:
        bubble
        selection
        insertion
        merge
        quick
        counting
        shell
        bogo
Sizes:
        10, 25, 50, 100, 200, 300, 600, 1200
Delays:
        0 <= delay (ms) <= 1000
Defaults:
        algorithm: bubble
        size: 200
        delay: 0
```

## Implementation
### High level
The program is divided into three components. The main component handles user option parsing, calls the sorting functions, and spawns a thread to keep the window open. The second component manages the SDL 2 features, including window creation, destruction, array drawing, and animation parameter management. The third component handles all the sorting implementations. The main program acts as a controller, invoking both the SDL functions and the sorting functions to execute the program according to user preferences.

### Files
- `sort.cpp`: 

   This file contains the main program flow. It starts by assigning the algorithm, array size, bar width, and delay based on the user's command line arguments. Next, it sets up the SDL window and spawns a thread to continuously check if the user has closed the window. While the thread is running, the main thread creates an array with random values, draws it, and calls the appropriate sorting algorithm. 

   If the user closes the window, the sorting algorithm stops, the window thread is joined, and the main function returns. If the user doesn't close the window, the window thread waits at the `join()` statement before returning. 

- `sort_functions.h`:

   This file contains all the sorting functions and a helper function to swap two elements in the array. Each sorting function follows a similar format with respect to the animation. At each crucial step of the sorting process, `draw_array()` is called, highlighting the moving element in red. If this `draw_array()` call returns false, the sorting function also returns false. This mechanism allows the program to exit the sorting function if the user closes the window and indicates that the array did not finish sorting. At the end of each sorting function, the array is drawn entirely in white.

- `SDL_functions.h`:

   This file defines a class called `animation_data` and functions relating to the SDL window. The `animation_data` class contains the SDL window, SDL renderer, delay, size, bar spacing, bar width, and a boolean indicating whether the window should be open or not. Three main functions manage the SDL window: `SDL_init()` creates the window, `SDL_close()` closes the window, and `draw_array()` draws an array on the window. 

   The `draw_array()` function is the main point of interest in this file. It starts by checking the `open` attribute of the `animation_data` object. If the user wants the window open (`open == true`), the function proceeds. To draw the array, it first clears the screen by drawing a black box, and then loops through the array, drawing a white rectangle sized corresponding to the value of that element. The function then sleeps for the specified delay time, renders the changes, and returns. 

## Sources
[Programiz - Sorting Algorithms](https://www.programiz.com/dsa/sorting-algorithm)

[GeeksforGeeks - MergeSort](https://www.geeksforgeeks.org/merge-sort/#)

[Dipesh Mann - Concept & Idea](https://github.com/dipesh-m/Sorting-Visualizer)

[Lazy Foo' Productions - SDL2 Tutorial](https://lazyfoo.net/tutorials/SDL/index.php#Getting%20an%20Image%20on%20the%20Screen)
