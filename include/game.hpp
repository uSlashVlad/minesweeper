#pragma once

#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Game
{
public:
    void init();

private:
    sf::RenderWindow *window = nullptr;

    Grid *grid = nullptr;

    void processEvent(sf::Event event);
    void processLeftCellClick(int row, int column);
    void processRightCellClick(int row, int column);
};
