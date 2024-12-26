#include "PlayGameWindow.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;
using namespace sf;

Game::Game(int difficulty) {
    fillPuzzle();
    copy(&puzzle[0][0], &puzzle[0][0] + PUZZLE_SIZE * PUZZLE_SIZE, &puzzleSolution[0][0]);
    sudoku(difficulty);
}

bool Game::isValid(int row, int col, int value) {
    for (int c = 0; c < PUZZLE_SIZE; c++)
        if (puzzle[row][c] == value) return false;

    for (int r = 0; r < PUZZLE_SIZE; r++)
        if (puzzle[r][col] == value) return false;

    int startRow = (row / 3) * 3, startCol = (col / 3) * 3;
    for (int r = startRow; r < startRow + 3; r++)
        for (int c = startCol; c < startCol + 3; c++)
            if (puzzle[r][c] == value) return false;

    return true;
}

bool Game::hasEmptyCell() {
    for (int r = 0; r < PUZZLE_SIZE; r++)
        for (int c = 0; c < PUZZLE_SIZE; c++)
            if (puzzle[r][c] == EMPTY_VALUE) return true;
    return false;
}

bool Game::fillPuzzle() {
    for (int i = 0; i < PUZZLE_SIZE * PUZZLE_SIZE; i++) {
        int row = i / PUZZLE_SIZE, col = i % PUZZLE_SIZE;
        if (puzzle[row][col] == EMPTY_VALUE) {
            shuffle(values.begin(), values.end(), default_random_engine(time(nullptr)));
            for (int value : values) {
                if (isValid(row, col, value)) {
                    puzzle[row][col] = value;
                    if (!hasEmptyCell() || fillPuzzle()) return true;
                }
            }
            puzzle[row][col] = EMPTY_VALUE;
            return false;
        }
    }
    return true;
}

void Game::sudoku(int emptyCells) {
    srand(time(nullptr));
    for (int i = 0; i < emptyCells; i++) {
        int row, col;
        do {
            row = rand() % PUZZLE_SIZE;
            col = rand() % PUZZLE_SIZE;
        } while (puzzle[row][col] == EMPTY_VALUE);
        puzzle[row][col] = EMPTY_VALUE;
    }
}

PlayGameWindow::PlayGameWindow(int difficulty, RenderWindow& window)
    : game(difficulty) {
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error loading font!" << endl;
    }

    // Initialize grid
    for (int r = 0; r < Game::PUZZLE_SIZE; r++) {
        for (int c = 0; c < Game::PUZZLE_SIZE; c++) {
            grid[r][c].setSize(Vector2f(50, 50));
            grid[r][c].setPosition(100 + c * 55, 100 + r * 55);
            grid[r][c].setOutlineColor(Color::Black);
            grid[r][c].setOutlineThickness(2);
            grid[r][c].setFillColor(Color::Yellow);
        }
    }

    // Initialize number buttons
    for (int i = 0; i < 9; i++) {
        numberButtons[i].setSize(Vector2f(50, 50));
        numberButtons[i].setPosition(200 + i * 60, 700);
        numberButtons[i].setFillColor(Color::Green);

        numberTexts[i].setFont(font);
        numberTexts[i].setString(to_string(i + 1));
        numberTexts[i].setCharacterSize(20);
        numberTexts[i].setFillColor(Color::White);
        numberTexts[i].setPosition(numberButtons[i].getPosition().x + 15, numberButtons[i].getPosition().y + 10);
    }

    // Initialize give up button
    giveUpButton.setSize(Vector2f(150, 50));
    giveUpButton.setPosition(1000, 700);
    giveUpButton.setFillColor(Color::Red);
    Text giveUpText;
    giveUpText.setString("GIVE UP");


    // Initialize hint button
    hintButton.setSize(Vector2f(150, 50));
    hintButton.setPosition(800, 700);
    hintButton.setFillColor(Color::Blue);

    hintButtonText.setFont(font);
    hintButtonText.setString("Hint");
    hintButtonText.setCharacterSize(20);
    hintButtonText.setFillColor(Color::White);
    hintButtonText.setPosition(825, 715);

    // Initialize text for hints and mistakes
    hintsText.setFont(font);
    hintsText.setCharacterSize(20);
    hintsText.setFillColor(Color::White);

    mistakesText.setFont(font);
    mistakesText.setCharacterSize(20);
    mistakesText.setFillColor(Color::White);
}

void PlayGameWindow::draw(RenderWindow& window) {
    // Draw the grid
    for (int r = 0; r < Game::PUZZLE_SIZE; r++) {
        for (int c = 0; c < Game::PUZZLE_SIZE; c++) {
            window.draw(grid[r][c]);

            if (game.getPuzzleValue(r, c) != Game::EMPTY_VALUE) {
                Text cellText;
                cellText.setFont(font);
                cellText.setString(to_string(game.getPuzzleValue(r, c)));
                cellText.setCharacterSize(20);
                cellText.setFillColor(Color::Black);
                cellText.setPosition(grid[r][c].getPosition().x + 15, grid[r][c].getPosition().y + 10);
                window.draw(cellText);
            }
        }
    }

    // Draw number buttons
    for (int i = 0; i < 9; i++) {
        window.draw(numberButtons[i]);
        window.draw(numberTexts[i]);
    }

    // Draw give up button
    window.draw(giveUpButton);
    window.draw(giveUpText);

    // Draw hint button
    window.draw(hintButton);
    window.draw(hintButtonText);

    // Draw hints and mistakes
    hintsText.setString("Hints: " + to_string(hintsCount));
    hintsText.setPosition(50, 700);
    window.draw(hintsText);

    mistakesText.setString("Mistakes: " + to_string(mistakesCount));
    mistakesText.setPosition(50, 730);
    window.draw(mistakesText);
}

void PlayGameWindow::handleInput(Event event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        // Check if hint button clicked
        if (hintButton.getGlobalBounds().contains(mousePos)) {
            handleHintButton();
        }

        // Check if give up button clicked
        if (giveUpButton.getGlobalBounds().contains(mousePos)) {
            exit(0); // Exit the program
        }

        // Check grid selection
        for (int r = 0; r < Game::PUZZLE_SIZE; r++) {
            for (int c = 0; c < Game::PUZZLE_SIZE; c++) {
                if (grid[r][c].getGlobalBounds().contains(mousePos)) {
                    updateSelectedCell(r, c);
                    if (hintMode) {
                        useHint();
                        hintMode = false;
                        hintButton.setFillColor(Color::Blue);
                    }
                }
            }
        }

        // Check number button selection
        for (int i = 0; i < 9; i++) {
            if (numberButtons[i].getGlobalBounds().contains(mousePos)) {
                applyNumberToCell(i + 1);
            }
        }
    }
}

void PlayGameWindow::handleHintButton() {
    hintMode = !hintMode;
    hintButton.setFillColor(hintMode ? Color::Cyan : Color::Blue);
}

void PlayGameWindow::useHint() {
    if (hintsCount > 0 && selectedRow != -1 && selectedCol != -1) {
        int solution = game.getSolutionValue(selectedRow, selectedCol);
        if (game.getPuzzleValue(selectedRow, selectedCol) == Game::EMPTY_VALUE) {
            game.setPuzzleValue(selectedRow, selectedCol, solution);
            hintsCount--;
        }
    }
}

void PlayGameWindow::updateSelectedCell(int row, int col) {
    selectedRow = row;
    selectedCol = col;
}

void PlayGameWindow::applyNumberToCell(int number) {
    if (selectedRow != -1 && selectedCol != -1) {
        if (game.getSolutionValue(selectedRow, selectedCol) == number) {
            game.setPuzzleValue(selectedRow, selectedCol, number);
        }
        else {
            mistakesCount++;
        }
    }
}
