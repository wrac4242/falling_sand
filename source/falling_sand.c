#include <stdio.h> //input and output for debugging
#include <SDL.h> //sdl2 library
#include <linux/types.h> //types

//function prototypes
int initialise_window(); //initialises the game screen, returns 0 if successful
int exit_game(long window_addr, int* array); //exits the game, returns 0 if successful

int * createArray(int array_x, int array_y); //creates array of given size of particles, returns array pointer

//structs & enums
typedef enum {false, true} bool;

//colour struct, 32 bits, standard pixel data
typedef struct colour_t{
  __u8 r;
  __u8 g;
  __u8 b;
  __u8 a;
}colour_t;

typedef struct particle_t{
  __u32 id; //4 bytes, material id
  __u32 life_time; //4 bytes, only used for limited life particles
  colour_t colour; //4 bytes
  __u32 lastUpdatedFrame; //4 bytes
} particle_t; //16 bytes

// material id, for particle info
#define mat_id_empty (__u8)0

// colours
#define mat_col_empty (colour_t){ 0, 0, 0, 0}

//screen settings, can be changed later
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 128;
__u32 frameNumber = 0; //frame number

int main(int argc, char* args[])
{
  SDL_Window *window;                    // Declare a pointer
  window = (void*) (long) initialise_window();
  SDL_Event event;

  //initial creation of assets needed
  //create the array of particles
  int* particle_array = createArray(123,321); //pointer to the array in memory

  bool playing = true; //creates the playing variable

  do {
    //main game steps:
    frameNumber += 1; //increase frameNumber
    //update physics
    //update render
    //check for human input
    //wait rest of frame
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
      playing = false;
      printf("exiting via quit event\n");

      //printf("Number of rows: %d\n", ((int) (sizeof (particle_array) / sizeof (particle_array)[0])));
      //printf("Number of columns: %d\n", ((int) (sizeof (particle_array[0]) / sizeof (particle_array[0])[0])));
    }
  }
  while (playing==1);

  int error_code_exit = exit_game((long) &window, particle_array);
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

int exit_game(long window_addr, int* array) //exits the game, returns 0 if successful
{
  SDL_Window *window;
  window = (void*) (long) window_addr;

  // Close and destroy the window
  SDL_DestroyWindow(window);

  SDL_Quit();

  free(array);

  return 0;
}

int * createArray(int array_x, int array_y)
{
  particle_t (*array)[array_x] = (int (*)[array_y])malloc(array_x * array_y*sizeof(particle_t)); //creates array

  for (int i = 0; i < array_x; i++) {
    for (int j = 0; j < array_y; j++) {
      struct particle_t p; p.id=mat_id_empty, p.life_time=0, p.colour=mat_col_empty, p.lastUpdatedFrame=666; //random number chosen for last updated frame no difference
      array[i][j] = p;
    }
  }

  return array;
}
