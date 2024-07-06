#include "ball.hpp"
#include <random>
#include <algorithm>

#define WIDTH 400
#define HEIGHT 400
#define PI 3.1415926

#define MAX_SPEED 0.05
#define MAX_NOISE 0.1
#define WIGGLE 1.0
#define GAP 0.1

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> distribFloat(-MAX_SPEED, MAX_SPEED);
std::uniform_real_distribution<double> distribNoise(-MAX_NOISE, MAX_NOISE);


Ball::Ball(SDL_Renderer* renderer, double x0, double y0, int idx)
    : renderer(renderer), x0(x0), y0(y0), idx(idx) {
        radius = 10;
        Vx = distribFloat(gen);
        Vy = distribFloat(gen);

        std::cout<<"Ball initialised\n";
    }

void Ball::DrawBall() {
	double x = radius;
	double y = 0;
	double xChange = 1 - (radius * 2);
	double yChange = 0;
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


double Ball::dist(std::pair<double, double> a, std::pair<double, double> b){
	return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

void Ball::MoveBall(std::pair<double, double> centers[10], std::pair<double, double> speeds[10] ) {
    x0 += Vx;
    y0 += Vy;
	speeds[idx].first = Vx;
	speeds[idx].second = Vy;
    // noiseGen();
    if(x0 >= WIDTH - radius - WIGGLE || x0 <= radius + WIGGLE){
        Vx *= -1;
    }
    if(y0 >= HEIGHT - radius - WIGGLE || y0 <= radius + WIGGLE){
        Vy *= -1;
    }


	centers[idx].first = x0;
	centers[idx].second = y0;
	double theta_a = atan(speeds[idx].second/speeds[idx].first);
	double V1 = dist(speeds[idx], {0,0});
	for(int i = 0; i < 10; i++){
		if(i != idx){
			double distance = dist(centers[i],centers[idx]);
			if(distance <= ((radius*2) + GAP) && distance >= ((radius*2) - GAP)){
				double theta = atan((centers[idx].second - centers[i].second)/(centers[idx].first - centers[i].first));
				double theta1 = theta_a - theta;
				double theta2 = atan(speeds[i].second/speeds[i].first) - theta;
				double V2 = dist(speeds[i], {0,0});
				Vx = V2*cos(theta2)*cos(theta) + V1*sin(theta1)*sin(theta);
				Vy = V2*cos(theta2)*sin(theta) - V1*sin(theta1)*cos(theta);
			}
		}
	}
	

}