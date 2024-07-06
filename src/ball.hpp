#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#define WIDTH 400
#define HEIGHT 400

class Ball {
    private:
        float x0;
        float y0;
        float Vx;
        float Vy;
        float radius;
        int idx;
        SDL_Renderer *renderer;
        std::pair<float, float> centers[10];
    public:
        void DrawBall();
        void MoveBall();
        
        Ball(SDL_Renderer* renderer, float x, float y, int idx);
        void noiseGen();
};
