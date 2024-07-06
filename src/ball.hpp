#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <math.h>
#define WIDTH 400
#define HEIGHT 400

class Ball {
    private:
        double x0;
        double y0;
        double Vx;
        double Vy;
        double radius;
        int idx;
        SDL_Renderer *renderer;
    public:
        Ball(SDL_Renderer* renderer, double x, double y, int idx);
        void DrawBall();
        void MoveBall(std::pair<double, double> centers[20], std::pair<double, double> speeds[20]);
        double dist(std::pair<double, double> a, std::pair<double, double> b);
        void noiseGen();
};
