#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

// inspired by https://youtu.be/T31MoLJws4U?si=_h8ujkH34nowKIoB

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
private:
    sf::RectangleShape box;
    sf::Text textbox;
    std::ostringstream text;
    bool is_selected;
    bool has_limit;
    int limit;


    void inputLogic(int char_typed) {
        if(char_typed != DELETE_KEY && char_typed != ENTER_KEY && char_typed != ESCAPE_KEY) {
            text << static_cast<char>(char_typed);
        }
        else if (char_typed == DELETE_KEY) {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar() {
        std::string t = text.str();
        std::string new_t = "";
        for (int i = 0; i < t.length() - 1; i++) {
            new_t += t[i];
        }
        text.str("");
        text << new_t;
        textbox.setString(text.str());
    }
public:
    Textbox() { }

    // without background
    Textbox(int char_size, sf::Color txt_color, bool sel) {
        textbox.setCharacterSize(char_size);
        textbox.setFillColor(txt_color);

        is_selected = sel;
        if (sel) {
            textbox.setString("_");
        }
        else {
            textbox.setString("");
        }
    }

    // with background
    Textbox(int char_size, sf::Vector2f box_size, sf::Color txt_color, sf::Color box_color, bool sel) {
        textbox.setCharacterSize(char_size);
        textbox.setFillColor(txt_color);
        box.setSize(box_size);
        box.setFillColor(box_color);

        is_selected = sel;
        if (sel) {
            textbox.setString("_");
        }
        else {
            textbox.setString("");
        }
    }




    ~Textbox() { }

    void setFont(sf::Font& font) {
        textbox.setFont(font);
    }

    void setTextColor(sf::Color color) {
        textbox.setFillColor(color);
    }

    void setBackColor(sf::Color color) {
        box.setFillColor(color);
    }

    void setPosition(sf::Vector2f pos) { //FIXME: text centering is odd
        box.setPosition(pos);

        float xp = (pos.x + box.getLocalBounds().width / 20) - (textbox.getLocalBounds().width / 2);
        float yp = (pos.y + box.getLocalBounds().height / 20) - (textbox.getLocalBounds().height / 2);
        textbox.setPosition({xp, yp});

    }

    void setLimit(bool tof) {
        has_limit = tof;
    }

    void setLimit(bool tof, int lim) {
        has_limit = tof;
        limit = lim - 1;
    }

    void setSelected(bool sel) {
        is_selected = sel;
        if (!sel) {
            std::string t = text.str();
            std::string new_t = "";
            for (int i = 0; i < t.length(); i++) {
                new_t += t[i];
            }
            textbox.setString(new_t);
        }
        else {
            textbox.setString(text.str() + "_");
        }

    }

    std::string getText() {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(textbox);
    }

    void typeOn(sf::Event input) {
        if (is_selected) {
            int char_typed = input.text.unicode;
            if (char_typed < 128) {
                if (has_limit) {
                    if (text.str().length() <= limit) {
                        inputLogic(char_typed);
                    }
                    else if (text.str().length() <= limit && char_typed == DELETE_KEY) {
                        deleteLastChar();
                    }
                }
                else {
                    inputLogic(char_typed);
                }
            }
        }
    }

    bool isSelected() {
        return is_selected;
    }

    bool isMouseOver(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;

        float box_pos_x = box.getPosition().x;
        float box_pos_y = box.getPosition().y;

        float box_xpos_width = box.getPosition().x + box.getLocalBounds().width;
        float box_xpos_height = box.getPosition().y + box.getLocalBounds().height;

        // within bounds
        if (mouse_x < box_xpos_width && mouse_x > box_pos_x && mouse_y < box_xpos_height && mouse_y > box_pos_y) {
            return true;
        }
        return false;
    }
};
