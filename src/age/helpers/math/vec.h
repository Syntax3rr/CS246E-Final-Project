#ifndef AGE_MATH_VEC_H
#define AGE_MATH_VEC_H

#include <cmath>

// Mathematical 2D vector class for position.
struct Vec {
    int x, y;
    Vec& reset() noexcept { 
        x = 0; 
        y = 0; 
        return *this; 
    }
    bool operator==(const Vec& other) const noexcept { 
        return x == other.x && y == other.y; 
    }
    bool operator!=(const Vec& other) const noexcept { 
        return !(*this == other); 
    }
    bool operator==(int other) const noexcept { 
        return x == other && y == other; 
    }
    bool operator!=(int other) const noexcept { 
        return !(*this == other); 
    }
    Vec& operator+=(const Vec& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec& operator-=(const Vec& other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec& operator*=(const int& other) noexcept {
        x *= other;
        y *= other;
        return *this;
    }
    Vec& operator/=(const int& other) noexcept {
        x /= other;
        y /= other;
        return *this;
    }
    Vec operator+(const Vec& other) const noexcept {
        return Vec{x + other.x, y + other.y};
    }
    Vec operator-(const Vec& other) const noexcept {
        return Vec{x - other.x, y - other.y};
    }
    Vec operator*(const int& other) const noexcept {
        return Vec{x * other, y * other};
    }
    Vec operator/(const int& other) const noexcept {
        return Vec{x / other, y / other};
    }
    int dot(const Vec& other) const noexcept {
        return x * other.x + y * other.y;
    }
    Vec proj(const Vec& other) const noexcept {
        return other * (dot(other) / other.dot(other));
    }
    Vec refl(const Vec& norm) const noexcept {
        return *this - proj(norm) * 2;
    }
    double length() const noexcept {
        return sqrt(pow(x, 2) + pow(y, 2));
    }
    double distance(const Vec& other) const noexcept {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
    double getSlope() const noexcept {
        if (x == 0) return 0;
        return (double)y / (double)x;
    }
};

#endif
