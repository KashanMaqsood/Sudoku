#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "HowToPlayWindow.h"
#include "OptionsWindow.h"
#include "PlayGameWindow.h"
using namespace std;
using namespace sf;

int main() {
    // Create the main menu window
    RenderWindow MENU(VideoMode(1550, 850), "MAIN MENU", Style::Fullscreen);
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

    // Main menu background setup
    RectangleShape background;
    background.setSize(Vector2f(1550, 850));
    Texture Maintexture;
    if (!Maintexture.loadFromFile("mainmenu.jpg")) {
        cout << "Error: Failed to load main menu background texture!" << endl;
    }
    background.setTexture(&Maintexture);

    // Play window background
    RectangleShape Pbackground;
    Pbackground.setSize(Vector2f(1550, 850));
    Texture Play_Texture;
    if (!Play_Texture.loadFromFile("playpic.jpg")) {
        cout << "Error: Failed to load play window background texture!" << endl;
    }
    Pbackground.setTexture(&Play_Texture);

    // How to Play window instance
    HowToPlayWindow howToPlayWindow(MENU.getSize().x, MENU.getSize().y);

    // Main game loop
    while (MENU.isOpen()) {
        Event event;
        while (MENU.pollEvent(event)) {
            if (event.type == Event::Closed) {
                MENU.close();
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    mainMenu.Moveup();
                    break;
                }
                if (event.key.code == Keyboard::Down) {
                    mainMenu.MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return) {
                    int selectedOption = mainMenu.mainMenuPressed();

                    // Play Window
                    if (selectedOption == 0) { // Play Game
                        RenderWindow Play(VideoMode(1550, 850), "Sudoku Game", Style::Fullscreen);
                        Play.draw(Pbackground);
                        int difficulty = 30; // Example: Set difficulty based on menu choice
                        PlayGameWindow playWindow(difficulty, Play);

                        while (Play.isOpen()) {
                            Event playEvent;
                            while (Play.pollEvent(playEvent)) {
                                if (playEvent.type == Event::Closed) {
                                    Play.close();
                                }
                                playWindow.handleInput(playEvent);
                            }

                            Play.clear();
                            playWindow.draw(Play);
                            Play.display();
                        }
                    }

                    // Options Window
                    if (selectedOption == 1) {
                        RenderWindow OPTIONS(VideoMode(1550, 850), "OPTIONS", Style::Fullscreen);
                        OptionsWindow OptionWindow(OPTIONS.getSize().x, OPTIONS.getSize().y);
                        while (OPTIONS.isOpen()) {
                            Event optionsEvent;
                            while (OPTIONS.pollEvent(optionsEvent)) {
                                if (optionsEvent.type == Event::Closed ||
                                    (optionsEvent.type == Event::KeyPressed && optionsEvent.key.code == Keyboard::Escape)) {
                                    OPTIONS.close();
                                }
                                else if (optionsEvent.type == Event::KeyPressed && optionsEvent.key.code == Keyboard::Up)
                                {
                                    OptionWindow.Moveup();
                                }
                                else if (optionsEvent.type == Event::KeyPressed && optionsEvent.key.code == Keyboard::Down)
                                {
                                    OptionWindow.MoveDown();
                                }
                                // Handle input for editing hints and mistakes
                                OptionWindow.handleInput(optionsEvent, OPTIONS);
                            }
                            OPTIONS.clear();
                            OptionWindow.draw(OPTIONS);
                            OPTIONS.display();
                        }

                        // Display updated values for hints and mistakes (for debug purposes)
                        cout << "Updated Hints Count: " << OptionWindow.getHintsCount() << endl;
                        cout << "Updated Mistakes Allowed: " << OptionWindow.getMistakesAllowed() << endl;
                    }

                    // How to Play Window section:
                    if (selectedOption == 2) {
                        RenderWindow HOW_TO_PLAY(VideoMode(1550, 850), "HOW TO PLAY", Style::Fullscreen);
                        while (HOW_TO_PLAY.isOpen()) {
                            Event htpEvent;
                            while (HOW_TO_PLAY.pollEvent(htpEvent)) {
                                if (htpEvent.type == Event::Closed ||
                                    (htpEvent.type == Event::KeyPressed && htpEvent.key.code == Keyboard::Escape)) {
                                    HOW_TO_PLAY.close();
                                }
                            }
                            HOW_TO_PLAY.clear();
                            howToPlayWindow.draw(HOW_TO_PLAY); // Correctly draw background and contents
                            HOW_TO_PLAY.display();
                        }
                    }

                    // Exit
                    if (selectedOption == 3) {
                        MENU.close();
                    }
                    break;
                }
            }
        }

        // Main menu rendering
        MENU.clear();
        MENU.draw(background);
        mainMenu.draw(MENU);
        MENU.display();
    }
    return 0;
}
