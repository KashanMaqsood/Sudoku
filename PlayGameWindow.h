#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Game {
public:
    Game(int difficulty);
    bool isValid(int row, int col, int value);
    bool hasEmptyCell();
    bool fillPuzzle();
    void sudoku(int emptyCells);
    int getPuzzleValue(int row, int col) const { return puzzle[row][col]; }
    int getSolutionValue(int row, int col) const { return puzzleSolution[row][col]; }
    void setPuzzleValue(int row, int col, int value) { puzzle[row][col] = value; }

    static const int PUZZLE_SIZE = 9;
    static const int EMPTY_VALUE = 0;

private:
    array<int, 9> values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int puzzle[PUZZLE_SIZE][PUZZLE_SIZE]{};
    int puzzleSolution[PUZZLE_SIZE][PUZZLE_SIZE]{};
};

class PlayGameWindow {
public:
    PlayGameWindow(int difficulty, RenderWindow& window);
    void draw(RenderWindow& window);
    void handleInput(Event event);
    void handleHintButton();

private:
    void renderGrid(RenderWindow& window);
    void renderButtons(RenderWindow& window);
    void updateSelectedCell(int row, int col);
    void applyNumberToCell(int number);
    void giveUp();
    void useHint();

    Game game;
    int selectedRow = -1;
    int selectedCol = -1;
    bool hintMode = false;

    Font font;
    Text hintsText, mistakesText, titleText, giveUpText, hintButtonText;
    RectangleShape grid[Game::PUZZLE_SIZE][Game::PUZZLE_SIZE];
    RectangleShape numberButtons[9];
    Text numberTexts[9];
    RectangleShape giveUpButton, hintButton;

    int hintsCount = 3;
    int mistakesCount = 0;
};
