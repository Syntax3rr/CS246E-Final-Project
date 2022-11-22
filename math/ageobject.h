#ifndef AGE_MATH_AGEOBJECT_H
#define AGE_MATH_AGEOBJECT_H
#include <vector>

class AGEObject {
    vector<int> width, height;
    int x, y;
    int stateCount;
    int currentState;
public:
    AGEObject(int x, int y, int stateCount, vector<int> width, vector<int> height) : width(width), height(height), x(x), y(y), stateCount(stateCount), currentState(0) {}
    void setX(int x) noexcept { this->x = x; }
    void setY(int y) noexcept { this->y = y; }
    void setState(int state) { 
        if (state >= stateCount) throw "State out of bounds";    
        currentState = state; 
    }
    int getWidth() { return width[currentState]; }
    int getHeight() { return height[currentState]; }
    int getX() const noexcept { return x; }
    int getY() const noexcept { return y; }
    int getState() const noexcept { return currentState; }
};

#endif
