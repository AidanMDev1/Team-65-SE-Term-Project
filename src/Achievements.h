#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"

class Achievements {
    bool ten_clock_ins = false;
    bool hundred_clock_ins = false;
    bool thousand_clock_ins = false;
    bool one_proj = false;
    bool two_proj = false;
    bool five_proj = false;
    bool ten_proj = false;
public:
    std::vector<Button> lo_achs;
    Achievements(sf::Font& font, int clock_ins, int projs) {
        Button ach1 = Button("Newbie Ten: Clock in 10 times", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach1.setPosition({470, 250});
        ach1.setFont(font);

        Button ach2 = Button("A whole century?: Clock in 100 times", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach2.setPosition({470, 250 + 50}); // 250 + i * 30
        ach2.setFont(font);

        Button ach3 = Button("Eternity: Clock in 1000 times", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach3.setPosition({470, 250 + 100}); // 250 + i * 30
        ach3.setFont(font);

        Button ach4 = Button("Training Wheels: Work on 1 project", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach4.setPosition({470, 250 + 150}); // 250 + i * 30
        ach4.setFont(font);

        Button ach5 = Button("Ambidextrous: Work on 2 projects", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach5.setPosition({470, 250 + 200}); // 250 + i * 30
        ach5.setFont(font);

        Button ach6 = Button("Trained Veteran: Work on 5 projects", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach6.setPosition({470, 250 + 250}); // 250 + i * 30
        ach6.setFont(font);

        Button ach7 = Button("Are you okay?: Work on 10 projects", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach7.setPosition({470, 250 + 300}); // 250 + i * 30
        ach7.setFont(font);

        Button ach8 = Button("Buddies: Send a Message", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach8.setPosition({470, 250 + 350}); // 250 + i * 30
        ach8.setFont(font);

        Button ach9 = Button("Team Leader!: become a manager", {370, 30}, 12,  sf::Color(146, 176, 164), sf::Color(64, 156, 120));
        ach9.setPosition({470, 250 + 400}); // 250 + i * 30
        ach9.setFont(font);

        sf::Color t_c = sf::Color(230, 230, 230);
        if (clock_ins >= 10) {
            ten_clock_ins = true;
            ach1.setBackColor(t_c);
        }
        if (clock_ins >= 100) {
            hundred_clock_ins = true;
            ach2.setBackColor(t_c);
        }
        if (clock_ins >= 1000) {
            thousand_clock_ins = true;
            ach3.setBackColor(t_c);
        }
        if (projs >= 1) {
            one_proj = true;
            ach4.setBackColor(t_c);
        }
        if (projs >= 2) {
            two_proj = true;
            ach5.setBackColor(t_c);
        }
        if (projs >= 5) {
            five_proj = true;
            ach6.setBackColor(t_c);
        }
        if (projs >= 10) {
            ten_proj = true;
            ach7.setBackColor(t_c);
        }
        lo_achs.push_back(ach1);
        lo_achs.push_back(ach2);
        lo_achs.push_back(ach3);
        lo_achs.push_back(ach4);
        lo_achs.push_back(ach5);
        lo_achs.push_back(ach6);
        lo_achs.push_back(ach7);
        lo_achs.push_back(ach8);
        lo_achs.push_back(ach9);
    }
    void checkCompleted(int clock_ins, int projs) { // leaving out some functionality for sake of time
        if (clock_ins >= 10) {
            ten_clock_ins = true;
        }
        if (clock_ins >= 100) {
            hundred_clock_ins = true;
        }
        if (clock_ins >= 1000) {
            thousand_clock_ins = true;
        }
        if (projs >= 1) {
            one_proj = true;
        }
        if (projs >= 2) {
            two_proj = true;
        }
        if (projs >= 5) {
            five_proj = true;
        }
        if (projs >= 10) {
            ten_proj = true;
        }
    }

};