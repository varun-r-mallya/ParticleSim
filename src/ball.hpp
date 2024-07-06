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
    public:
        Ball(SDL_Renderer* renderer, float x, float y, int idx);
        void DrawBall();
        void MoveBall(std::pair<float, float> centers[10], std::pair<float, float> speeds[10]);
        float dist(std::pair<float, float> a, std::pair<float, float> b);
        void noiseGen();
};
