#include "boid.hpp"

double  Boid::turnfactor = 0.2;
double  Boid::visualRange = 20;
double  Boid::protectedRange = 2.0;
double  Boid::centeringfactor = 0.0005;
double  Boid::avoidfactor = 0.05;
double  Boid::matchingfactor = 0.05;
double  Boid::maxspeed = 3.0;
double  Boid::minspeed = 2.0;
Vec2f   Boid::screenMin = Vec2f(-1000.0, 1000.0);
Vec2f   Boid::screenMax = Vec2f(-1000.0, 1000.0);

bool  Boid::neighborCheck(Boid &neigh) {
  double  neighDist = (neigh.position - position).lenght();
  if (neighDist > visualRange)
    return (false);

  speedAvg += neigh.speed;
  massCenter += neigh.position;
  neighboringBoids += 1;
  if (neighDist < protectedRange) {
    separation += (position - neigh.position);
  }
  return (true);
}

void  Boid::update() {
  speed += separation * avoidfactor;
  if (neighboringBoids > 0) {
    speedAvg /= neighboringBoids;
    massCenter /= neighboringBoids;
    speed += (speedAvg - speed) * matchingfactor;
    speed += (massCenter - position) * centeringfactor;
  }
  if (position.x < screenMin.x)
    speed.x += turnfactor;
  if (position.y < screenMin.y)
    speed.y += turnfactor;
  if (position.x > screenMax.x)
    speed.x -= turnfactor;
  if (position.y > screenMax.y)
    speed.y -= turnfactor;

  double spd = speed.lenght();
  if (spd > maxspeed) {
    speed = (speed / spd) * maxspeed;
  }
  else if (spd < minspeed) {
    speed = (speed / spd) * minspeed;
  }

  position += speed;

  separation = Vec2f(0.0, 0.0);
  neighboringBoids = 0;
  speedAvg = Vec2f(0.0, 0.0);
}
