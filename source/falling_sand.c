#include <stdio.h> //input and output for debugging
#include <SDL.h> //sdl2 library

//function prototypes
int initialise_window(); //initialises the game screen, returns 0 if successful
int exit_game(long window_addr); //exits the game, returns 0 if successful

//structs & enums
typedef enum {false, true} bool;

//colour struct, 32 bits, standard pixel data
typedef struct colour_t
{
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} colour_t;

typedef struct particle_t
{
  u32 id; //4 bytes, material id
  f32 life_time; //4 bytes, only used for limited life particles
  colour_t colour; //4 bytes
  u32 lastUpdatedFrame; //4 bytes
} particle_t; //16 bytes


//screen settings, can be changed later
const int SCREEN_WIDTH = 110;
const int SCREEN_HEIGHT = 110;
u32 frameNumber = 0; //frame number

int main(int argc, char* args[])
{
  SDL_Window *window;                    // Declare a pointer
  window = (void*) (long) initialise_window();

  //initial creation of assets needed
  //create the array of particles

  bool playing = true; //creates the playing variable

  do {
    //main game steps:
    frameNumber += 1; //increase frameNumber
    //update physics
    //update render
    //check for human input
    //wait rest of frame
    //check if should quit
  }
  while (playing==1);

  int error_code_exit = exit_game((long) &window);
  if (error_code_exit!=0){
    printf("Error in game exit\n");
    return 1;
  }

  return 0;
}

int initialise_window() //initialises the game screen, returns 0 if successful
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
