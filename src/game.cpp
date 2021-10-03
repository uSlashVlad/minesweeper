#include <iostream>
#include "game.hpp"

using namespace sf;

void Game::init()
{
    window = new RenderWindow({tileSize * gridSize, tileSize * gridSize}, "MineSweeper");
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    grid = new Grid(window);
    grid->loadResources();
    grid->generateCells();

    std::cout << "Game is loaded" << std::endl;

    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
            processEvent(event);

        window->clear();
        grid->drawCells();
        window->display();
    }
}

void Game::processEvent(Event event)
{
    if (event.type == Event::Closed)
        window->close();
    if (event.type == Event::Resized)
    {
        auto wSize = window->getSize();
        window->setView({{static_cast<float>(wSize.x / 2),
                          static_cast<float>(wSize.y / 2)},
                         {static_cast<float>(wSize.x),
                          static_cast<float>(wSize.y)}});
    }
    if (event.type == Event::MouseButtonPressed)
    {
        auto mousePos = Mouse::getPosition(*window);
        Vector2i cellPos = grid->getCellPosAtWindowPos(mousePos);
        int row = cellPos.y;
        int column = cellPos.x;

        if (event.mouseButton.button == Mouse::Left)
            processLeftCellClick(row, column);
        else if (event.mouseButton.button == Mouse::Right)
            processRightCellClick(row, column);
    }
}

void Game::processLeftCellClick(int row, int column)
{
    if (!grid->isRevealedAt(row, column))
    {
        grid->revealCell(row, column);
    }
    else if (grid->flagsAroundCell(row, column) >= grid->minesAroundCell(row, column))
    {
        if (!grid->isRevealedAt(row, column - 1))
            grid->revealCell(row, column - 1);
        if (!grid->isRevealedAt(row - 1, column - 1))
            grid->revealCell(row - 1, column - 1);
        if (!grid->isRevealedAt(row - 1, column))
            grid->revealCell(row - 1, column);
        if (!grid->isRevealedAt(row - 1, column + 1))
            grid->revealCell(row - 1, column + 1);
        if (!grid->isRevealedAt(row, column + 1))
            grid->revealCell(row, column + 1);
        if (!grid->isRevealedAt(row + 1, column + 1))
            grid->revealCell(row + 1, column + 1);
        if (!grid->isRevealedAt(row + 1, column))
            grid->revealCell(row + 1, column);
        if (!grid->isRevealedAt(row + 1, column - 1))
            grid->revealCell(row + 1, column - 1);
    }
}

void Game::processRightCellClick(int row, int column)
{
    // mines around == unrevealed + flagged
    // unrevealed = 8 - revealed - flagged
    if (!grid->isRevealedAt(row, column) || grid->isFlagAt(row, column))
    {
        if (grid->isFlagAt(row, column))
            grid->unflagCell(row, column);
        else
            grid->flagCell(row, column);
    }
    else if (grid->minesAroundCell(row, column) == 8 - grid->revealedAroundCell(row, column))
    {
        if (!grid->isFlagAt(row, column - 1))
            grid->flagCell(row, column - 1);
        if (!grid->isFlagAt(row - 1, column - 1))
            grid->flagCell(row - 1, column - 1);
        if (!grid->isFlagAt(row - 1, column))
            grid->flagCell(row - 1, column);
        if (!grid->isFlagAt(row - 1, column + 1))
            grid->flagCell(row - 1, column + 1);
        if (!grid->isFlagAt(row, column + 1))
            grid->flagCell(row, column + 1);
        if (!grid->isFlagAt(row + 1, column + 1))
            grid->flagCell(row + 1, column + 1);
        if (!grid->isFlagAt(row + 1, column))
            grid->flagCell(row + 1, column);
        if (!grid->isFlagAt(row + 1, column - 1))
            grid->flagCell(row + 1, column - 1);
    }
}
