#include <stdio.h> //input and output for debugging
#include <SDL.h> //sdl2 library
#include <linux/types.h> //types

//function prototypes
int initialise_window(long window_addr); //initialises the game screen, returns 0 if successful
int exit_game(long window_addr, long surface_addr); //exits the game, returns 0 if successful

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
#define mat_id_sand (__u8)1

// colours
#define mat_col_empty (colour_t){ 0, 0, 0, 0}
#define mat_col_sand (colour_t){ 255, 200, 0, 255}

//screen settings, can be changed later
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 128;
__u32 frameNumber = 0; //frame number

const int array_x = SCREEN_WIDTH;
const int array_y = SCREEN_HEIGHT;


int main(int argc, char* args[])
{
  SDL_Window *window;                    // Declare a pointer
  initialise_window((long) &window); //pointer is dealt with in function
  SDL_Event event;

  SDL_Surface *surface = NULL;
  surface = SDL_GetWindowSurface(window);
  if (surface == NULL){
    printf("surface nulled\n");
    return 1;
  }

  //initial creation of assets needed
  //create the array of particles
  struct particle_t (*particle_array)[array_x] = (struct particle_t (*)[array_y])malloc((unsigned long)array_x * (unsigned long)array_y*(unsigned long)sizeof(particle_t)); //creates array

  for (int i = 0; i < array_x; i++) {
    for (int j = 0; j < array_y; j++) {
      struct particle_t p; p.id=mat_id_empty, p.life_time=0, p.colour=mat_col_empty, p.lastUpdatedFrame=666; //random number chosen for last updated frame no difference
      particle_array[i][j] = p;
    }
  }

  //array starting pattern
  particle_array[10][10].id = mat_id_sand;
  particle_array[10][10].colour = mat_col_sand;

  bool playing = true; //creates the playing variable

  do {
    //main game steps:
    frameNumber += 1; //increase frameNumber
    //update physics
    //update render
    {
      SDL_LockSurface(surface);
      for (int i = 0; i < array_x; i++) {
        for (int j = 0; j < array_y; j++) {
          __u32 colour = particle_array[i][j].colour.r << 24 | particle_array[i][j].colour.g << 16 | particle_array[i][j].colour.b << 8 | particle_array[i][j].colour.a;
          Uint32 *target_pixel = (Uint32 *) surface->pixels + i * surface->pitch + j * 32;
          *target_pixel = colour;
        }
      }
      printf("foo\n");
      SDL_UnlockSurface(surface);
    }
    //check for human input

    //wait rest of frame

    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
      playing = false;
      printf("exiting via quit event\n");
    }
  }
  while (playing==1);

  int error_code_exit = exit_game((long) &window, (long) &surface);
  if (error_code_exit!=0){
    printf("Error in game exit\n");
    return 1;
  }
  free(particle_array);

  return 0;
}

int initialise_window(long window_addr) //initialises the game screen, returns 0 if successful
{
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
  SDL_Window *window;
  window = (void*) (long) window_addr;

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
  return 0;
}

int exit_game(long window_addr, long surface_addr) //exits the game, returns 0 if successful
{
  SDL_Window *window;
  window = (void*) (long) window_addr;

  SDL_Surface *surface;
  surface = (void*) (long) surface_addr;

  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_free(surface);

  SDL_Quit();

  return 0;
}
