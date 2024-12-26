#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(float width, float height) {
    if (!font.loadFromFile("arial.ttf"))
        cout << "No font is here!" << endl;

    // Volume Option
    OptionMenu[0].setFont(font);
    OptionMenu[0].setFillColor(Color::Blue); // Highlight the first option
    OptionMenu[0].setString("Volume: ");
    OptionMenu[0].setCharacterSize(60);
    OptionMenu[0].setPosition(50, 300);

    volumeText.setFont(font);
    volumeText.setString(to_string(volume));
    volumeText.setCharacterSize(60);
    volumeText.setFillColor(Color::Black);
    volumeText.setPosition(400, 300);

    sliderBar.setSize(Vector2f(300, 10));
    sliderBar.setFillColor(Color::White);
    sliderBar.setPosition(500, 330);

    sliderKnob.setSize(Vector2f(20, 40));
    sliderKnob.setFillColor(Color::Blue);
    sliderKnob.setPosition(500 + (volume * 3), 315); // Knob position depends on volume

    // Hints Count
    OptionMenu[1].setFont(font);
    OptionMenu[1].setFillColor(Color::White);
    OptionMenu[1].setString("Hints Count: ");
    OptionMenu[1].setCharacterSize(60);
    OptionMenu[1].setPosition(50, 400);

    hintsText.setFont(font);
    hintsText.setString(to_string(hintsCount));
    hintsText.setCharacterSize(60);
    hintsText.setFillColor(Color::Black);
    hintsText.setPosition(395, 400);

    hintsBox.setSize(Vector2f(100, 70));
    hintsBox.setOutlineColor(Color::Blue);
    hintsBox.setOutlineThickness(2);
    hintsBox.setFillColor(Color::White);
    hintsBox.setPosition(395, 400);

    // Mistakes Allowed
    OptionMenu[2].setFont(font);
    OptionMenu[2].setFillColor(Color::White);
    OptionMenu[2].setString("Mistakes Allowed: ");
    OptionMenu[2].setCharacterSize(60);
    OptionMenu[2].setPosition(50, 500);

    mistakesText.setFont(font);
    mistakesText.setString(to_string(mistakesAllowed));
    mistakesText.setCharacterSize(60);
    mistakesText.setFillColor(Color::Black);
    mistakesText.setPosition(530, 505);

    mistakesBox.setSize(Vector2f(100, 70));
    mistakesBox.setOutlineColor(Color::Blue);
    mistakesBox.setOutlineThickness(2);
    mistakesBox.setFillColor(Color::White);
    mistakesBox.setPosition(532, 505);

    OptionSelected = 0; // Highlight the first option
}

OptionsWindow::~OptionsWindow() {}
void OptionsWindow::draw(RenderWindow& window) {
    // Draw options window background
    static RectangleShape Obackground(Vector2f(1550, 850)); // Static to avoid reinitialization
    static Texture Option_Texture;
    static bool isTextureLoaded = false;

    if (!isTextureLoaded) {
        if (!Option_Texture.loadFromFile("optionspic.jpg")) {
            cout << "Error: Failed to load options window background texture!" << endl;
        }
        else {
            isTextureLoaded = true;
            Obackground.setTexture(&Option_Texture);
        }
    }

    if (isTextureLoaded) {
        window.draw(Obackground);
    }

    // Draw menu options
    for (int i = 0; i < Max_Options; ++i) {
        window.draw(OptionMenu[i]);
    }

    // Draw volume slider
    window.draw(sliderBar);
    window.draw(sliderKnob);
    window.draw(volumeText);

    // Draw editable fields
    window.draw(hintsBox);
    window.draw(hintsText);
    window.draw(mistakesBox);
    window.draw(mistakesText);
}

void OptionsWindow::Moveup() {
    if (OptionSelected - 1 >= 0) {
        OptionMenu[OptionSelected].setFillColor(Color::White); // Reset current option color
        OptionSelected--;
        OptionMenu[OptionSelected].setFillColor(Color::Blue); // Highlight the new option
    }
}

void OptionsWindow::MoveDown() {
    if (OptionSelected + 1 < Max_Options) {
        OptionMenu[OptionSelected].setFillColor(Color::White); // Reset current option color
        OptionSelected++;
        OptionMenu[OptionSelected].setFillColor(Color::Blue); // Highlight the new option
    }
}

void OptionsWindow::handleInput(Event event, RenderWindow& window) {
    // Handle mouse clicks for slider
    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (sliderKnob.getGlobalBounds().contains(mousePos)) {
            isDraggingSlider = true;
        }

        if (hintsBox.getGlobalBounds().contains(mousePos)) {
            isEditingHints = true;
            isEditingMistakes = false;
        }
        else if (mistakesBox.getGlobalBounds().contains(mousePos)) {
            isEditingHints = false;
            isEditingMistakes = true;
        }
        else {
            isEditingHints = false;
            isEditingMistakes = false;
        }
    }

    if (event.type == Event::MouseButtonReleased) {
        isDraggingSlider = false;
    }

    // Handle slider dragging
    if (isDraggingSlider && event.type == Event::MouseMoved) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window)); 
        float newX = mousePos.x;
        if (newX < sliderBar.getPosition().x) {
            newX = sliderBar.getPosition().x;
        }
        if (newX > sliderBar.getPosition().x + sliderBar.getSize().x) {
            newX = sliderBar.getPosition().x + sliderBar.getSize().x;
        }

        sliderKnob.setPosition(newX, sliderKnob.getPosition().y);
        volume = static_cast<int>((newX - sliderBar.getPosition().x) / 3); // Update volume value
        volumeText.setString(to_string(volume));
    }

    // Handle user interactions for text input (same as before)
    if (event.type == Event::TextEntered) {
        // Handle text editing for hints and mistakes here...
    }
}
