#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("arial.ttf"))
        cout << "No font is here!";

    // Play Button
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::Blue); // Highlight first option
    mainMenu[0].setString("PLAY");
    mainMenu[0].setCharacterSize(60);
    mainMenu[0].setPosition(50, 300);

    // Options Button
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("OPTIONS");
    mainMenu[1].setCharacterSize(60);
    mainMenu[1].setPosition(50, 400);

    // How to Play
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("HOW TO PLAY");
    mainMenu[2].setCharacterSize(60);
    mainMenu[2].setPosition(50, 500);

    // Exit Button
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("EXIT");
    mainMenu[3].setCharacterSize(60);
    mainMenu[3].setPosition(50, 600);

    MainMenuSelected = 0; // Highlight the first option
}

MainMenu::~MainMenu() {}

void MainMenu::draw(RenderWindow& window) {
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }
}

void MainMenu::Moveup() {
    if (MainMenuSelected - 1 >= 0) {
        mainMenu[MainMenuSelected].setFillColor(Color::White); // Reset current option color
        MainMenuSelected--;
        mainMenu[MainMenuSelected].setFillColor(Color::Blue); // Highlight the new option
    }
}

void MainMenu::MoveDown() {
    if (MainMenuSelected + 1 < Max_main_menu) {
        mainMenu[MainMenuSelected].setFillColor(Color::White); // Reset current option color
        MainMenuSelected++;
        mainMenu[MainMenuSelected].setFillColor(Color::Blue); // Highlight the new option
    }
}
