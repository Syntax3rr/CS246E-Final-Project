#include "bullethell.h"
#include "../../age/engine/objects/update/updateTypes/cycleVisibility.h"
#include "../../age/engine/objects/entity.h"
#include <tuple>
#include <ncurses.h>

using namespace age;
using std::vector;
using std::make_tuple;
namespace bulletHell {
    BulletHell::BulletHell(Input& input): Engine(input), player(Player({ Sprite{'P'} }, *this)),
        mainMenu{
        Entity(12, 5, 0, Sprite{
            make_tuple(0, 0, 'B'), make_tuple(0, 1, 'B'), make_tuple(0, 2, 'B'), make_tuple(0, 3, 'B'), make_tuple(0, 4, 'B'), make_tuple(1, 0, 'B'), make_tuple(2, 1, 'B'), make_tuple(1, 2, 'B'), make_tuple(2, 3, 'B'), make_tuple(1, 4, 'B'),
            make_tuple(5, 0, 'U'), make_tuple(5, 1, 'U'), make_tuple(5, 2, 'U'), make_tuple(5, 3, 'U'), make_tuple(5, 4, 'U'), make_tuple(7, 0, 'U'), make_tuple(7, 1, 'U'), make_tuple(7, 2, 'U'), make_tuple(7, 3, 'U'), make_tuple(6, 4, 'U'), make_tuple(7, 4, 'U'),
            make_tuple(10, 0, 'L'), make_tuple(10, 1, 'L'), make_tuple(10, 2, 'L'), make_tuple(10, 3, 'L'), make_tuple(10, 4, 'L'), make_tuple(11, 4, 'L'), make_tuple(12, 4, 'L'),
            make_tuple(15, 0, 'L'), make_tuple(15, 1, 'L'), make_tuple(15, 2, 'L'), make_tuple(15, 3, 'L'), make_tuple(15, 4, 'L'), make_tuple(16, 4, 'L'), make_tuple(16, 4, 'L'),
            make_tuple(20, 0, 'E'), make_tuple(20, 1, 'E'), make_tuple(20, 2, 'E'), make_tuple(20, 3, 'E'), make_tuple(20, 4, 'E'), make_tuple(21, 0, 'E'), make_tuple(22, 0, 'E'), make_tuple(21, 2, 'E'), make_tuple(21, 4, 'E'), make_tuple(22, 4, 'E'),
            make_tuple(25, 0, 'T'), make_tuple(26, 0, 'T'), make_tuple(27, 0, 'T'), make_tuple(26, 0, 'T'), make_tuple(26, 1, 'T'), make_tuple(26, 2, 'T'), make_tuple(26, 3, 'T'), make_tuple(26, 4, 'T'),
            make_tuple(35, 0, 'H'), make_tuple(35, 1, 'H'), make_tuple(35, 2, 'H'), make_tuple(35, 3, 'H'), make_tuple(35, 4, 'H'), make_tuple(37, 0, 'H'), make_tuple(37, 1, 'H'), make_tuple(36, 2, 'H'), make_tuple(37, 2, 'H'), make_tuple(37, 3, 'H'), make_tuple(37, 4, 'H'),
            make_tuple(40, 0, 'E'), make_tuple(40, 1, 'E'), make_tuple(40, 2, 'E'), make_tuple(40, 3, 'E'), make_tuple(40, 4, 'E'), make_tuple(41, 0, 'E'), make_tuple(42, 0, 'E'), make_tuple(41, 2, 'E'), make_tuple(41, 4, 'E'), make_tuple(42, 4, 'E'),
            make_tuple(45, 0, 'L'), make_tuple(45, 1, 'L'), make_tuple(45, 2, 'L'), make_tuple(45, 3, 'L'), make_tuple(45, 4, 'L'), make_tuple(46, 4, 'L'), make_tuple(47, 4, 'L'),
            make_tuple(50, 0, 'L'), make_tuple(50, 1, 'L'), make_tuple(50, 2, 'L'), make_tuple(50, 3, 'L'), make_tuple(50, 4, 'L'), make_tuple(51, 4, 'L'), make_tuple(52, 4, 'L')
        }),
        Entity(28, 15, 0, {Sprite{ "Press Any Key To Start" }}, false, {
            new CycleVisiblity(30)
        })
    },
        gameOver{ Entity(34, 10, 0, {Sprite{ "Game Over!" }}, false, {})
    } {
        for (auto& entity : mainMenu) {
            addEntity(&entity);
        }
    };

    void BulletHell::onUpdate() {
        if (gameState == GameState::PLAYING) {
            time++;

            //Use Bomb
            if (input->getKeyState('x')) {
                if (bombCount > 0) {
                    bombCount--;
                    for (auto& enemy : enemies) {
                        enemy.damage(-1);
                    }
                    for (auto& bullet : bullets) {
                        bullet.damage();
                    }
                }
            }

            //Bullet and Enemy culling. Super inefficient but it works.
            for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
                //If not in entities, delete it
                if (std::find(entities[1].begin(), entities[1].end(), &(*iter)) == entities[1].end()) {
                    enemies.erase(iter);
                    iter--;
                }
            }
            for (auto iter = bullets.begin(); iter != bullets.end(); ++iter) {
                //If not in entities, delete it
                if (std::find(entities[1].begin(), entities[1].end(), &(*iter)) == entities[1].end()) {
                    bullets.erase(iter);
                    iter--;
                }
            }

            //Spawn enemies


        }

        if (gameState == MAIN_MENU && input->getPressedKeys().size() > 0 && input->getPressedKeys()[0] > 31 && input->getPressedKeys()[0] < 127) {
            gameState = PLAYING;
            entities.clear();
            addEntity(&player);
        }

        //If the player has no lives, go to game over screen
        if (player.getLives() == 0) {
            gameState = GAME_OVER;
            entities.clear();
            for (auto& entity : gameOver) {
                addEntity(&entity);
            }
            setTextLine(0, "You survived for " + std::to_string(time / 20) + " seconds");
            setTextLine(1, "Press 'esc' to quit");
            setTextLine(2, "");
        }

        //Quit
        if (input->getKeyState(27)) {
            entities.clear();
            player.getWidth();
            throw "quit";
        }

    };


}
