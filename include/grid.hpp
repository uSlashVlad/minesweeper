#pragma once

#include <SFML/Graphics.hpp>
#include "consts.hpp"

class Grid
{
public:
    Grid(sf::RenderWindow *newWindow);

    void loadResources();
    void generateCells();

    void drawCells();

    sf::Vector2i getCellPosAtWindowPos(sf::Vector2i pos);

    void revealCell(int row, int column);
    void flagCell(int row, int column);
    void unflagCell(int row, int column);

    int visibleCellAt(int row, int column);

    int minesAroundCell(int row, int column);
    int flagsAroundCell(int row, int column);
    int revealedAroundCell(int row, int column);

    bool isMineAt(int row, int column);
    bool isFlagAt(int row, int column);
    bool isRevealedAt(int row, int column);

private:
    sf::RenderWindow *window = nullptr;

    sf::Texture tilesTexture;
    sf::Sprite tileSprite;

    int logicGrid[gridSize][gridSize];
    int viewGrid[gridSize][gridSize];

    int cellAt(int row, int column);

    bool isCellOutOfGrid(int row, int column);
};
