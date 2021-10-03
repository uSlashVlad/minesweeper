#include "grid.hpp"

using namespace sf;

Grid::Grid(RenderWindow *newWindow)
{
    window = newWindow;
}

void Grid::loadResources()
{
    tilesTexture.loadFromFile(globalAssetsPath + "tiles.png");
    tileSprite.setTexture(tilesTexture);
}

void Grid::generateCells()
{
    for (int x = 0; x < gridSize; x++)
    {
        for (int y = 0; y < gridSize; y++)
        {
            viewGrid[x][y] = 10;
            if (rand() % 7 == 0)
                logicGrid[x][y] = 9;
            else
                logicGrid[x][y] = 0;
        }
    }
    for (int x = 0; x < gridSize; x++)
    {
        for (int y = 0; y < gridSize; y++)
        {
            if (isMineAt(y, x))
                continue;
            else
                logicGrid[x][y] = minesAroundCell(y, x);
        }
    }
}

int Grid::minesAroundCell(int row, int column)
{
    int count{0};
    if (isMineAt(row, column - 1))
        count++;
    if (isMineAt(row - 1, column - 1))
        count++;
    if (isMineAt(row - 1, column))
        count++;
    if (isMineAt(row - 1, column + 1))
        count++;
    if (isMineAt(row, column + 1))
        count++;
    if (isMineAt(row + 1, column + 1))
        count++;
    if (isMineAt(row + 1, column))
        count++;
    if (isMineAt(row + 1, column - 1))
        count++;
    return count;
}

bool Grid::isMineAt(int row, int column)
{
    return cellAt(row, column) == 9;
}

int Grid::flagsAroundCell(int row, int column)
{
    int count{0};
    if (isFlagAt(row, column - 1))
        count++;
    if (isFlagAt(row - 1, column - 1))
        count++;
    if (isFlagAt(row - 1, column))
        count++;
    if (isFlagAt(row - 1, column + 1))
        count++;
    if (isFlagAt(row, column + 1))
        count++;
    if (isFlagAt(row + 1, column + 1))
        count++;
    if (isFlagAt(row + 1, column))
        count++;
    if (isFlagAt(row + 1, column - 1))
        count++;
    return count;
}

bool Grid::isFlagAt(int row, int column)
{
    return visibleCellAt(row, column) == 11;
}

int Grid::revealedAroundCell(int row, int column)
{
    int count{0};
    if (isRevealedAt(row, column - 1))
        count++;
    if (isRevealedAt(row - 1, column - 1))
        count++;
    if (isRevealedAt(row - 1, column))
        count++;
    if (isRevealedAt(row - 1, column + 1))
        count++;
    if (isRevealedAt(row, column + 1))
        count++;
    if (isRevealedAt(row + 1, column + 1))
        count++;
    if (isRevealedAt(row + 1, column))
        count++;
    if (isRevealedAt(row + 1, column - 1))
        count++;
    return count;
}

bool Grid::isRevealedAt(int row, int column)
{
    return visibleCellAt(row, column) != 10 && visibleCellAt(row, column) != 11;
}

int Grid::cellAt(int row, int column)
{
    if (isCellOutOfGrid(row, column))
        return 0;
    return logicGrid[column][row];
}

int Grid::visibleCellAt(int row, int column)
{
    if (isCellOutOfGrid(row, column))
        return -1;
    return viewGrid[column][row];
}

void Grid::drawCells()
{
    for (int x = 0; x < gridSize; x++)
    {
        for (int y = 0; y < gridSize; y++)
        {
            tileSprite.setTextureRect({viewGrid[x][y] * tileSize, 0, tileSize, tileSize});
            tileSprite.setPosition(x * tileSize, y * tileSize);
            window->draw(tileSprite);
        }
    }
}

Vector2i Grid::getCellPosAtWindowPos(Vector2i pos)
{
    return pos / tileSize;
}

void Grid::revealCell(int row, int column)
{
    if (isCellOutOfGrid(row, column))
        return;

    int value = cellAt(row, column);
    if (!isRevealedAt(row, column) && !isFlagAt(row, column))
    {
        if (value == 0)
        {
            viewGrid[column][row] = logicGrid[column][row];
            revealCell(row, column - 1);
            revealCell(row - 1, column - 1);
            revealCell(row - 1, column);
            revealCell(row - 1, column + 1);
            revealCell(row, column + 1);
            revealCell(row + 1, column + 1);
            revealCell(row + 1, column);
            revealCell(row + 1, column - 1);
        }
        else if (value != 9)
        {
            viewGrid[column][row] = logicGrid[column][row];
        }
        else
        {
            // Game end... but for test it just flags
            flagCell(row, column);
        }
    }
}

void Grid::flagCell(int row, int column)
{
    if (isCellOutOfGrid(row, column) || isRevealedAt(row, column))
        return;

    viewGrid[column][row] = 11;
}

void Grid::unflagCell(int row, int column)
{
    if (isCellOutOfGrid(row, column) || !isFlagAt(row, column))
        return;

    viewGrid[column][row] = 10;
}

bool Grid::isCellOutOfGrid(int row, int column)
{
    if (row < 0 || column < 0 || row >= gridSize || column >= gridSize)
        return true;
    return false;
}
