#include "ball.hpp"
#include <random>
#define WIDTH 400
#define HEIGHT 400
#define MAX_SPEED 0.03
#define MAX_NOISE 0.1

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> distribFloat(-MAX_SPEED, MAX_SPEED);
std::uniform_real_distribution<float> distribNoise(-MAX_NOISE, MAX_NOISE);

Ball::Ball(SDL_Renderer* renderer, float x0, float y0, int idx)
    : renderer(renderer), x0(x0), y0(y0) {
        radius = 10;
        Vx = distribFloat(gen);
        Vy = distribFloat(gen);
		centers[idx] = {x0, y0};

        std::cout<<"Ball initialised\n";

    }

void Ball::DrawBall() {
	float x = radius;
	float y = 0;
	float xChange = 1 - (radius * 2);
	float yChange = 0;
	int radiusError = 0;

	while (x >= y) {
		for (int i = x0 - x; i < x0 + x; i++) {
			SDL_RenderDrawPoint(renderer, i, y0 + y);
			SDL_RenderDrawPoint(renderer, i, y0 - y);
		}
		for (int i = x0 - y; i <= x0 + y; i++) {
			SDL_RenderDrawPoint(renderer, i, y0 + x);
			SDL_RenderDrawPoint(renderer, i, y0 - x);
		}
		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0) {
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void Ball::noiseGen(){
    x0 += distribNoise(gen);
    y0 += distribNoise(gen);
}

void Ball::MoveBall() {
    x0 += Vx;
    y0 += Vy;
    noiseGen();
    if(x0 > WIDTH - radius || x0 < radius){
        Vx *= -1;
    }
    if(y0 > HEIGHT - radius || y0 < radius){
        Vy *= -1;
    }

}