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
    Textbox(int size, sf::Color color, bool sel) {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
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

    void setPosition(sf::Vector2f pos) {
        textbox.setPosition(pos);
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
    }

    std::string getText() {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window) {
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
};
