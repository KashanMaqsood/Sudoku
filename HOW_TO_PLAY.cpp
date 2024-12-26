#include "HowToPlayWindow.h"

HowToPlayWindow::HowToPlayWindow(float width, float height) {
    // Load font
    if (!font.loadFromFile("Font/Alexandria.ttf")) {
        cout << "Failed to load font!" << endl;
    }

    // Set up heading
    heading.setFont(font);
    heading.setString("How to Play Sudoku");
    heading.setCharacterSize(40);
    heading.setFillColor(Color::White);
    heading.setPosition(50, 50);

    // Set up instructions
    instructions.setFont(font);
    instructions.setString(
        "Here are the steps to play Sudoku:\n\n"
        "1. Identify the Filled Cells:\n\tWhen you start a Sudoku puzzle, the first thing you should do is identify the cells that are already filled in.\n\tThese cells usually form a crucial part of the solution and can guide your progress.\n\n"
        "2. Use Process of Elimination:\n\tAfter identifying the filled cells, identify missing numbers in each row, column, or box.\n\tDeduce where those numbers should go.\n\n"
        "3. Avoid Guessing:\n\tSudoku is a game of logic and reasoning. Guessing can lead to errors and make the puzzle harder.\n\n"
        "4. Keep Moving:\n\tIf you're stuck, move to another part of the grid. This can reveal new possibilities.\n\n"
        "5. Re-evaluate:\n\tAfter each move, re-evaluate the grid. Consider what has changed and how it might impact other parts of the puzzle.\n\n"
        "Remember, Sudoku is a game of logic and pattern recognition. It requires patience, insights, and recognition of patterns.");
    instructions.setCharacterSize(18);
    instructions.setFillColor(Color::Cyan);
    instructions.setPosition(50, 150);
    instructions.setLineSpacing(1.5f);

    // Set up escape hint
    escapeHint.setFont(font);
    escapeHint.setString("Press Escape key to go back to the main menu");
    escapeHint.setCharacterSize(25);
    escapeHint.setFillColor(Color::Yellow);
    escapeHint.setPosition(50, height - 50);

    // Set up background
    background.setSize(Vector2f(width, height));
    if (!backgroundTexture.loadFromFile("howtoplay.jpg")) {
        cout << "Error: Failed to load How to Play window background texture!" << endl;
    }
    background.setTexture(&backgroundTexture);
}

void HowToPlayWindow::draw(RenderWindow& window) {
    window.draw(background);
    window.draw(heading);
    window.draw(instructions);
    window.draw(escapeHint);
}

HowToPlayWindow::~HowToPlayWindow() {}
