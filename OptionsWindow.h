#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

#define Max_Options 4

class OptionsWindow {
public:
    OptionsWindow(float width, float height);
    void draw(RenderWindow& window);
    void Moveup();
    void MoveDown();
    void handleInput(Event event, RenderWindow& window);
    int OptionsPressed() const { return OptionSelected; }

    // Getter methods for Hints and Mistakes
    int getHintsCount() const { return hintsCount; }
    int getMistakesAllowed() const { return mistakesAllowed; }
    int getVolume() const { return volume; }

    ~OptionsWindow();

private:
    int OptionSelected;
    Font font;
    Text OptionMenu[Max_Options];

    // Editable fields
    Text hintsText;
    Text mistakesText;
    Text volumeText;

    // Editable values
    int hintsCount = 2;            // Default value
    int mistakesAllowed = 3;       // Default value
    int volume = 50;               // Default volume (0-100)

    // Textboxes for user input
    RectangleShape hintsBox;
    RectangleShape mistakesBox;

    // Slider for volume control
    RectangleShape sliderBar;
    RectangleShape sliderKnob;

    bool isEditingHints = false;   // Tracks if user is editing hints
    bool isEditingMistakes = false; // Tracks if user is editing mistakes
    bool isDraggingSlider = false; // Tracks if the slider is being dragged
};
