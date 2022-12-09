#ifndef AGE_VISUALIZER_OBJECTS_SPRITE_H
#define AGE_VISUALIZER_OBJECTS_SPRITE_H
#include <vector>
#include <initializer_list>
#include <tuple>
#include <string>
#include <algorithm>

namespace age {
using std::vector;
using std::tuple;
using std::string;
using std::get;
class Sprite {
    vector<vector<char>> sprite;
    int width, height;
public:
    Sprite(std::initializer_list<tuple<int, int, char>> bitmap) {
        width = 0, height = 0;
        for (auto t : bitmap) { // Insert the bitmap into the sprite.
            if (get<0>(t) >= width) width = get<0>(t) + 1;
            if (get<1>(t) >= height) height = get<1>(t) + 1;
            sprite.resize(height, vector<char>(width, NULL));
            sprite[get<1>(t)].resize(width, NULL);
            sprite[get<1>(t)][get<0>(t)] = get<2>(t);
        }
    }
    Sprite(int width, int height, char fill) : sprite(vector<vector<char>>(height, vector<char>(width, fill))), width(width), height(height) {}
    Sprite(char fill) : sprite(vector<vector<char>>(1, vector<char>(1, fill))), width(1), height(1) {}
    Sprite(string str) : sprite(vector<vector<char>>(1, vector<char>(str.begin(), str.end()))), width(str.size()), height(1) {}
    vector<vector<char>> getData() const noexcept { return sprite; }
    char getAt(int x, int y) const noexcept;
    int getWidth() const noexcept { return width; }
    int getHeight() const noexcept { return height; }
};
}
#endif
