#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class HowToPlayWindow {
public:
    HowToPlayWindow(float width, float height);
    void draw(RenderWindow& window);
    ~HowToPlayWindow();

private:
    Font font;
    Text heading;
    Text instructions;
    Text escapeHint;
    RectangleShape background; // Store background as a member
    Texture backgroundTexture; // Store texture as a member
};
