#include <stdio.h> //input and output for debugging
#include <SDL.h> //sdl2 library
#include <linux/types.h> //types

//structs & enums
typedef enum {false, true} bool;

typedef struct particle_t{
  __u32 id; //4 bytes, material id
  __u32 life_time; //4 bytes, only used for limited life particles
  __u32 colour; //4 bytes
  __u32 lastUpdatedFrame; //4 bytes
} particle_t; //16 bytes

//function prototypes
int exit_game(long window_addr); //exits the game, returns 0 if successful

//particle update functions
void update_empty(int x,int y);
void update_sand(int x,int y);

// material id, for particle info
#define mat_id_empty (__u8)0
#define mat_id_sand (__u8)1

// colours, alpha red green blue
#define mat_col_empty (__u32)0x00000000
#define mat_col_sand (__u32)0xffffc800

//screen settings, can be changed later
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 128;
__u32 frameNumber = 0; //frame number

const int array_x = SCREEN_WIDTH;
const int array_y = SCREEN_HEIGHT;

struct particle_t *array_ptr = NULL;

int main(int argc, char* args[])
{
  printf("foo\n");
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
  array_ptr = &particle_array;
  for (int i = 0; i < array_x; i++) {
    for (int j = 0; j < array_y; j++) {
      struct particle_t p; p.id=mat_id_empty, p.life_time=0, p.colour=mat_col_empty, p.lastUpdatedFrame=666; //random number chosen for last updated frame no difference
      particle_array[i][j] = p;
    }
  }
  printf("foo\n");

  //array starting pattern
  struct particle_t p; p.id=mat_id_sand, p.life_time=0, p.colour=mat_col_sand, p.lastUpdatedFrame=666;
  printf("foo\n");
  particle_array[11][11] = p;

  bool playing = true; //creates the playing variable

  do {
    //main game steps:
    frameNumber += 1; //increase frameNumber
    //update physics
    for (int i = 0; i < array_x; i++) {
      for (int j = array_y; j > 0; j--) {    //runs bottom up

      }
    }

    //update render
    {
      SDL_LockSurface(surface);
      for (int i = 0; i < array_x; i++) {
        for (int j = 0; j < array_y; j++) {
          //__u32 colour = 0xffffff;//testing colour
          Uint8 *target_pixel = (Uint8 *) surface->pixels + j * surface->pitch + i *4;
          *(Uint32 *)target_pixel = particle_array[i][j].colour;
        }
      }
      SDL_UnlockSurface(surface);
      SDL_UpdateWindowSurface(window);
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

  int error_code_exit = exit_game((long) &window);
  if (error_code_exit!=0){
    printf("Error in game exit\n");
    return 1;
  }
  free(particle_array);

  return 0;
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

//particle update functions
void update_empty(int x,int y)
{

}
void update_sand(int x,int y)
{

}
