#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

// inspired by https://youtu.be/T31MoLJws4U?si=_h8ujkH34nowKIoB


class Button {
private:
    sf::RectangleShape button;
    sf::Text text;

public:
    Button() { }
    Button(std::string t, sf::Vector2f size, int char_size, sf::Color bg_color, sf::Color text_color) {
        text.setString(t);
        text.setFillColor(text_color);
        text.setCharacterSize(char_size);

        button.setSize(size);
        button.setFillColor(bg_color);
    }

    // button w/o back (just text without interaction or possible interaction)
    Button(std::string t, int char_size, sf::Color text_color) {
        text.setString(t);
        text.setFillColor(text_color);
        text.setCharacterSize(char_size);
    }

    ~Button() { }

    void setFont(sf::Font& font) {
        text.setFont(font);
    }

    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos) { //FIXME: text centering is odd
        button.setPosition(pos);

        float xp = (pos.x + button.getLocalBounds().width / 4) - (text.getLocalBounds().width / 2);
        float yp = (pos.y + button.getLocalBounds().height / 6) - (text.getLocalBounds().height / 2);
        text.setPosition({xp, yp});
    }

    void setText(std::string t) {
        text.setString(t);
    }

    std::string getText() {
        return text.getString();
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;

        float btn_pos_x = button.getPosition().x;
        float btn_pos_y = button.getPosition().y;

        float btn_xpos_width = button.getPosition().x + button.getLocalBounds().width;
        float btn_xpos_height = button.getPosition().y + button.getLocalBounds().height;

        // within bounds
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }
};