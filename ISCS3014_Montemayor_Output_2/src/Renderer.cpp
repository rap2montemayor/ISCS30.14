#include "Renderer.hpp"

#include "Constants.hpp"

Renderer::Renderer(SpriteManager& spriteManager, Player& player) :
    spriteManager(spriteManager), player(player) {}

void Renderer::update(double deltaTime) {
    timedCallbacks.process(deltaTime);
    animator.update(deltaTime);
}

void Renderer::animateTiles(TileGrid& grid) {
    for (auto& row : grid) {
        for (TilePointer& tile: row) {
            tile->nextSprite();
        }
    }
    timedCallback(moveInterval/2, [&]{ animateTiles(grid); });
}

void Renderer::renderTile(Tile& tile, poly::Window& window, int i, int j) {
    auto& [w, l] = tileSize; // std::pair<int, int>
    float width = w;
    float length = l;
    rect.setSize({width, length});
    rect.setPosition({j*width, i*length});
    rect.setTexture(spriteManager.getSpriteSheet());
    rect.setTextureRect(spriteManager.getSpriteRect(tile.getCurrentSpriteID()));
    window.render(rect);
}

void Renderer::renderPlayer(poly::Window& window) {
    auto& [w, l] = tileSize; // ints
    auto& [x, y] = player.getSpritePosition(); // double

    float width = w;
    float length = l;

    rect.setSize({width, length});
    rect.setPosition({x, y});
    rect.setTexture(spriteManager.getSpriteSheet());
    rect.setTextureRect(spriteManager.getSpriteRect(
            player.getCurrentSpriteID()));
    window.render(rect);
}

void Renderer::moveSprite(const Direction& direction) {
    auto xcallback = [&](double newx) {
        auto [x, y] = player.getSpritePosition();
        player.setSpritePosition(newx, y);
    };
    auto ycallback = [&](double newy) {
        auto [x, y] = player.getSpritePosition();
        player.setSpritePosition(x, newy);
    };

    auto [row, col] = player.getEndPosition(direction);
    auto [x, y] = player.getSpritePosition();
    double xend = col*tileSize.first;
    double yend = row*tileSize.second;
    animator.interpolate(x, xend, moveInterval, xcallback);
    animator.interpolate(y, yend, moveInterval, ycallback);
}

void Renderer::moveAnimate(const Direction& direction) {
    PlayerSprite sprites[4] = {};
    switch (direction) {
    case Direction::Up:
        sprites[0] = PlayerSprite::MoveUp1;
        sprites[1] = PlayerSprite::IdleUp;
        sprites[2] = PlayerSprite::MoveUp2;
        sprites[3] = PlayerSprite::IdleUp;
        break;
    case Direction::Down:
        sprites[0] = PlayerSprite::MoveDown1;
        sprites[1] = PlayerSprite::IdleDown;
        sprites[2] = PlayerSprite::MoveDown2;
        sprites[3] = PlayerSprite::IdleDown;
        break;
    case Direction::Left:
        sprites[0] = PlayerSprite::MoveLeft1;
        sprites[1] = PlayerSprite::IdleLeft;
        sprites[2] = PlayerSprite::MoveLeft2;
        sprites[3] = PlayerSprite::IdleLeft;
        break;
    case Direction::Right:
        sprites[0] = PlayerSprite::MoveRight1;
        sprites[1] = PlayerSprite::IdleRight;
        sprites[2] = PlayerSprite::MoveRight2;
        sprites[3] = PlayerSprite::IdleRight;
        break;
    default:
        break;
    }

    player.changeSprite(sprites[0]);
    timedCallback(moveInterval * 1/3,
        [&, sprites] { player.changeSprite(sprites[1]); }
    );
    timedCallback(moveInterval * 2/3,
        [&, sprites] { player.changeSprite(sprites[2]); }
    );
    timedCallback(moveInterval,
        [&, sprites] { player.changeSprite(sprites[3]); }
    );
}

void Renderer::changePlayerFace(const Direction& direction) {
    switch (direction) {
    case Direction::Up:
        player.changeSprite(PlayerSprite::IdleUp);
        break;
    case Direction::Down:
        player.changeSprite(PlayerSprite::IdleDown);
        break;
    case Direction::Left:
        player.changeSprite(PlayerSprite::IdleLeft);
        break;
    case Direction::Right:
        player.changeSprite(PlayerSprite::IdleRight);
        break;
    default:
        break;
    }
}

void Renderer::timedCallback(double duration, std::function<void()> callback,
        double curTime, double deltaTime) {
    curTime += deltaTime;
    if (curTime < duration) {
        timedCallbacks.enqueue(
            [this, duration, callback, curTime](double deltaTime) {
                timedCallback(duration, callback, curTime, deltaTime);
            }
        );
    } else {
        callback();
    }
}
