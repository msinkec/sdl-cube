#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "matrix.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

double cubeCoords[8][4] = {
    // Front
    {-100.0, -100.0, -100.0, 1.0},
    {100.0, -100.0, -100.0, 1.0},
    {100.0, 100.0, -100.0, 1.0},
    {-100.0, 100.0, -100.0, 1.0},
    // Back
    {-100.0, -100.0, 100.0, 1.0},
    {100.0, -100.0, 100.0, 1.0},
    {100.0, 100.0, 100.0, 1.0},
    {-100.0, 100.0, 100.0, 1.0},
};


int constructNewFrame(SDL_Renderer *renderer, double deltaTime) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    double transMatrix[16];
    double tmp[16];

    identityMatrix(transMatrix);
    rotateY(transMatrix, SDL_GetTicks()*0.001, tmp);
    translate(tmp, 900, 600, 0, transMatrix);
    rotateX(transMatrix, -0.8, tmp);
    translate(tmp, 0, 50, 0, transMatrix);
    project(transMatrix, 2.0, SCREEN_WIDTH / SCREEN_HEIGHT, 0.1, 100.0, tmp);


    double transPoints[8][4];
    for (int i = 0; i < 8; i++) {
        double tmpP[4];
        transformPoint(cubeCoords[i], tmp, transPoints[i]);
    }
   
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == j)
                continue;
            SDL_RenderDrawLine(renderer, 
                    transPoints[i][0], transPoints[i][1], 
                    transPoints[j][0], transPoints[j][1]);
        }
    }
}

int main(int argc, char *argv[]) {
    int err;

    err = SDL_Init(SDL_INIT_VIDEO);
    if (err != 0) {
        fprintf(stderr, "Error while initializing SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Cube", 100, 100, 
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Event e;
    int quit = 0;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            default: {}
            }
        }

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double) ((NOW - LAST)*1000 / (double) SDL_GetPerformanceFrequency());  // milliseconds

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        constructNewFrame(renderer, deltaTime);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
