#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define Max_main_menu 4

class MainMenu {
public:
    MainMenu(float width, float height);
    void draw(RenderWindow& window);
    void Moveup();
    void MoveDown();
    int mainMenuPressed() {
        return MainMenuSelected;
    }
    ~MainMenu();

private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
};
