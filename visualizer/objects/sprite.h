#ifndef AGE_VISUALIZER_OBJECTS_SPRITE_H
#define AGE_VISUALIZER_OBJECTS_SPRITE_H
#include <vector>
#include <tuple>
#include <algorithm>

using std::vector, std::tuple, std::get;
class Sprite {
    vector<vector<char>> sprite;
    int width, height;
public:
    Sprite(vector<tuple<int, int, char>> bitmap) {
        width = 0, height = 0;
        for (auto t : bitmap) { // Insert the bitmap into the sprite.
            if (get<0>(t) >= width) width = get<0>(t) + 1;
            if (get<1>(t) >= height) height = get<1>(t) + 1;
            sprite.resize(height, vector<char>(width, NULL));
            sprite[get<1>(t)].resize(width, NULL);
            sprite[get<1>(t)][get<0>(t)] = get<2>(t);
        }
    }
    Sprite(int width, int height, char fill) : sprite(vector(height, vector(width, fill))), width(width), height(height) {}
    Sprite(char fill) : sprite(vector(1, vector(1, fill))), width(1), height(1) {}
    vector<vector<char>> getData() const noexcept { return sprite; }
    int getWidth() const noexcept { return width; }
    int getHeight() const noexcept { return height; }
};
#endif
