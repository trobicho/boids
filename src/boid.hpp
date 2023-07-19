#pragma once
#include "vector.hpp"

class Boid {
  public:
    static double turnfactor;
    static double visualRange;
    static double protectedRange;
    static double centeringfactor;
    static double avoidfactor;
    static double matchingfactor;
    static double maxspeed;
    static double minspeed;
    static Vec2f  screenMin;
    static Vec2f  screenMax;

    bool  neighborCheck(Boid& neigh);
    void  update();

    Vec2f position;
    Vec2f speed;

  private:
    Vec2f separation;
    Vec2f speedAvg;
    Vec2f massCenter;
    int   neighboringBoids = 0;
};
