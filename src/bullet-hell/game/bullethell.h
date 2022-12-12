#ifndef BULLETHELL_GAME_BULLETHELL_H
#define BULLETHELL_GAME_BULLETHELL_H
#include "../game-constants.h"
#include "../../age/engine/engine.h"
#include "../objects/player.h"
#include "../objects/enemy.h"
#include "../objects/bullet.h"
#include <vector>
namespace bulletHell {

    using namespace age;
    using std::make_tuple;

    class BulletHell: public age::Engine {
        Player player;

        std::vector<Entity> mainMenu;

        std::vector<Entity> gameOver;

        unsigned long int time = 0;

        enum GameState {
            MAIN_MENU,
            PLAYING,
            GAME_OVER
        };

        GameState gameState = MAIN_MENU;

        std::vector<Bullet> bullets{};
        std::vector<Enemy> enemies{};
        int bombCount = MAX_BOMBS;

    public:
        BulletHell(Input& input);

        void onUpdate() override;
    };
}

#endif
