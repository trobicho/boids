#pragma once

struct  Vec2f {
  Vec2f(double arg_x, double arg_y): x(arg_x), y(arg_y);

  double x = 0.0;
  double y = 0.0;

  double  lenght() {
    std::sqrt(x * x + y * y);
  }

  Vec2f& operator+=(const Vec2f& rhs) {
    x += rhs.x;
    y += rhs.y;
    return (*this);
  }

  Vec2f& operator-=(const Vec2f& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return (*this);
  }

  friend Vec2f operator+(Vec2f lhs, const Vec2f& rhs) {
    lhs += rhs;
    return (lhs);
  }

  friend Vec2f operator-(Vec2f lhs, const Vec2f& rhs) {
    lhs += rhs;
    return (lhs);
  }

  Vec2f& operator*=(const double rhs) {
    x *= rhs;
    y *= rhs;
    return (*this);
  }

  Vec2f& operator/=(const double rhs) {
    x /= rhs;
    y /= rhs;
    return (*this);
  }

  friend Vec2f operator*(Vec2f lhs, const double rhs) {
    lhs *= rhs;
    return (*lhs);
  }

  friend Vec2f operator/(Vec2f lhs, const double rhs) {
    lhs /= rhs;
    return (*lhs);
  }
};
};
