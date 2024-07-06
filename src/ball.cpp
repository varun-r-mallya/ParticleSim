#include "ball.hpp"
#include <random>
#define WIDTH 400
#define HEIGHT 400
#define PI 3.1415926

#define MAX_SPEED 0.05
#define MAX_NOISE 0.1
#define WIGGLE 4.0

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> distribFloat(-MAX_SPEED, MAX_SPEED);
std::uniform_real_distribution<float> distribNoise(-MAX_NOISE, MAX_NOISE);


Ball::Ball(SDL_Renderer* renderer, float x0, float y0, int idx)
    : renderer(renderer), x0(x0), y0(y0), idx(idx) {
        radius = 10;
        Vx = distribFloat(gen);
        Vy = distribFloat(gen);

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


float Ball::dist(std::pair<float, float> a, std::pair<float, float> b){
	return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

void Ball::MoveBall(std::pair<float, float> centers[10], std::pair<float, float> speeds[10] ) {
    x0 += Vx;
    y0 += Vy;
    // noiseGen();
    if(x0 > WIDTH - radius - WIGGLE || x0 < radius + WIGGLE){
        Vx *= -1;
    }
    if(y0 > HEIGHT - radius - WIGGLE || y0 < radius + WIGGLE){
        Vy *= -1;
    }
	// if(x0 > WIDTH)
	// x0 = 0;
	// if(x0 < 0)
	// x0 = WIDTH;
	// if(y0 > HEIGHT)
	// y0 = 0;
	// if(y0 < 0)
	// y0 = HEIGHT;


	centers[idx].first = x0;
	centers[idx].second = y0;
	_Float64 theta_a = atan(speeds[idx].second/speeds[idx].first);
	_Float64 V1 = dist(speeds[idx], {0,0});
	for(int i = 0; i < 10; i++){
		if(i != idx){
			if(dist(centers[i],centers[idx]) < ((radius*2))){
				_Float64 theta = atan((centers[idx].second - centers[i].second)/(centers[idx].first - centers[i].first));
				_Float64 theta1 = theta_a - theta;
				_Float64 theta2 = atan(speeds[i].second/speeds[i].first) - theta;
				_Float64 V2 = dist(speeds[i], {0,0});
				Vx = V2*cos(theta2)*cos(theta) + V1*sin(theta1)*sin(theta);
				Vy = V2*cos(theta2)*sin(theta) - V1*sin(theta1)*cos(theta);
			}
		}
	}
	speeds[idx].first = Vx;
	speeds[idx].second = Vy;

}