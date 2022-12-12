#ifndef AGE_ENGINE_OBJECTS_SPRITE_H
#define AGE_ENGINE_OBJECTS_SPRITE_H
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
        size_t width, height;
    public:
        Sprite(std::initializer_list<tuple<size_t, size_t, char>> bitmap) {
            width = 0, height = 0;
            for (auto t : bitmap) { // Insert the bitmap into the sprite.
                if (get<0>(t) >= width) width = get<0>(t) + 1;
                if (get<1>(t) >= height) height = get<1>(t) + 1;
                sprite.resize(height, vector<char>(width, ' '));
                sprite[get<1>(t)].resize(width, ' ');
                sprite[get<1>(t)][get<0>(t)] = get<2>(t);
            }
        }
        Sprite(size_t width, size_t height, char fill): sprite(vector<vector<char>>(height, vector<char>(width, fill))), width(width), height(height) {}
        Sprite(char c): sprite(vector<vector<char>>(1, vector<char>(1, c))), width(1), height(1) {}
        Sprite(string str): sprite(vector<vector<char>>(1, vector<char>(str.begin(), str.end()))), width(str.size()), height(1) {}
        Sprite(const Sprite& other): sprite(other.sprite), width(other.width), height(other.height) {}
        Sprite(Sprite&& other): sprite(std::move(other.sprite)), width(other.width), height(other.height) {}
        Sprite& operator=(const Sprite& other) {
            sprite = other.sprite;
            width = other.width;
            height = other.height;
            return *this;
        }
        Sprite& operator=(Sprite&& other) {
            std::swap(sprite, other.sprite);
            width = other.width;
            height = other.height;
            return *this;
        }
        ~Sprite() {
            sprite.clear();
        }

        vector<vector<char>> getData() const noexcept { return sprite; }
        char getAt(size_t x, size_t y) const noexcept {
            if (x < 0 || x >= width || y < 0 || y >= height) return ' ';
            if (sprite[y].size() <= x) return ' ';
            return sprite[y][x];
        };
        size_t getWidth() const noexcept { return width; }
        size_t getHeight() const noexcept { return height; }
    };
}

#endif
