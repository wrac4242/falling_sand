#include <stdio.h> //input and output for debugging
#include <SDL.h> //sdl2 library

//function prototypes
int initialise_game(); //initialises the game screen, returns 0 if successful
int exit_game(long window_addr); //exits the game, returns 0 if successful


//screen settings, can be changed later
const int SCREEN_WIDTH = 110;
const int SCREEN_HEIGHT = 110;

int main(int argc, char* args[])
{
  SDL_Window *window;                    // Declare a pointer
  window = (void*) (long) initialise_game();

  SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

  int error_code_exit = exit_game((long) &window);
  if (error_code_exit!=0){
    printf("Error in game exit\n");
    return 1;
  }

  return 0;
}

int initialise_game() //initialises the game screen, returns 0 if successful
{
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
  SDL_Window *window;

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "falling_sand",                    // window title
    SDL_WINDOWPOS_UNDEFINED,           // initial x position
    SDL_WINDOWPOS_UNDEFINED,           // initial y position
    SCREEN_WIDTH,                      // width, in pixels
    SCREEN_HEIGHT,                     // height, in pixels
    SDL_WINDOW_OPENGL                  // flags - see below
  );

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }
}

int exit_game(long window_addr) //exits the game, returns 0 if successful
{
  SDL_Window *window;
  window = (void*) (long) window_addr;

  // Close and destroy the window
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
