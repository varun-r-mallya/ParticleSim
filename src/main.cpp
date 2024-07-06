#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>  
#include "ball.hpp"
#define WIDTH 400
#define HEIGHT 400


int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Ball moving",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
        
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    // SDL_Texture * path = SDL_CreateTexture(renderer,
    // SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    std::pair<double, double> centers[20];
    std::pair<double, double> speeds[20];
    Ball* A[20];
    for(int i = 0; i < 20; ++i) {
    A[i] = new Ball(renderer, (rand() % (201)), (rand() % (201)), i); // Initialise each Ball object
    }
    
    while (!quit)
    {

        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        for(int i = 0; i < 20; ++i) {
        A[i]->DrawBall(); 
        A[i]->MoveBall(centers, speeds);
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
 
    return 0;
}