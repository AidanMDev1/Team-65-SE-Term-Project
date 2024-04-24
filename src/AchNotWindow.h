#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Achievements.h"

class AchNotWindow {
public:
    Button sign_out_btn;
    sf::Texture back_img;
    sf::Sprite back_btn;
    sf::Texture pgdown_img;
    sf::Texture pgup_img;
    sf::Sprite not_pgup_btn;
    sf::Sprite not_pgdown_btn;
    sf::Sprite ach_pgup_btn;
    sf::Sprite ach_pgdown_btn;
    Button not_txt;
    Button ach_txt;
    Button stats_txt;
    sf::RectangleShape not_bckgrnd;
    sf::RectangleShape ach_bckgrnd;
    std::vector<Button> lo_nots;
    Achievements* achievements;
    int total_proj;
    int total_clock_ins;

    AchNotWindow() { }
    AchNotWindow(sf::Font& font) {
        total_clock_ins = 100;
        total_proj = 10;
        achievements = new Achievements(font, total_clock_ins, total_proj);

        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);

        back_img.loadFromFile("files/back.png"); // find it in a folder where you store images

        back_btn.setTexture(back_img);
        back_btn.setScale({0.15, 0.15});

        pgdown_img.loadFromFile("files/page_down.png");
        pgup_img.loadFromFile("files/page_up.png");

        not_pgdown_btn.setTexture(pgdown_img);
        not_pgdown_btn.setScale({0.05, 0.05});
        not_pgdown_btn.setPosition({200, 750});

        not_pgup_btn.setTexture(pgup_img);
        not_pgup_btn.setScale({0.05, 0.05});
        not_pgup_btn.setPosition({200, 200});

        ach_pgdown_btn.setTexture(pgdown_img);
        ach_pgdown_btn.setScale({0.05, 0.05});
        ach_pgdown_btn.setPosition({630, 750});

        ach_pgup_btn.setTexture(pgup_img);
        ach_pgup_btn.setScale({0.05, 0.05});
        ach_pgup_btn.setPosition({630, 200});

        not_txt = Button("Notifications:", 30, sf::Color(64, 156, 120));
        not_txt.setPosition({100, 110});
        not_txt.setFont(font);

        ach_txt = Button("Achievements:", 30, sf::Color(64, 156, 120));
        ach_txt.setPosition({540, 110});
        ach_txt.setFont(font);

        stats_txt = Button("TOTAL CLOCK IN: " + std::to_string(total_clock_ins) + "   TOTAL PROJECTS: " + std::to_string(total_proj), 15, sf::Color(64, 156, 120));
        stats_txt.setPosition({450, 170});
        stats_txt.setFont(font);

        not_bckgrnd.setSize({400, 600});
        not_bckgrnd.setPosition({30, 200});
        not_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        ach_bckgrnd.setSize({400, 600});
        ach_bckgrnd.setPosition({450, 200});
        ach_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        Button not1 = Button("- Jerry: erm what the sigma?", 15, sf::Color(64, 156, 120));
        not1.setPosition({50, 250});
        not1.setFont(font);

        Button not2 = Button("- Jerry: erm what the sigma?????", 15, sf::Color(64, 156, 120));
        not2.setPosition({50, 250 + 30}); // 250 + i*30
        not2.setFont(font);

        lo_nots.push_back(not1);
        lo_nots.push_back(not2);
    }
    ~AchNotWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(not_bckgrnd);
        window.draw(ach_bckgrnd);
        window.draw(back_btn);
        window.draw(not_pgdown_btn);
        window.draw(ach_pgdown_btn);
        window.draw(not_pgup_btn);
        window.draw(ach_pgup_btn);
        sign_out_btn.drawTo(window);
        not_txt.drawTo(window);
        ach_txt.drawTo(window);
        stats_txt.drawTo(window);

        for (auto& notif : lo_nots) {
            notif.drawTo(window);
        }
        for (auto& ach : achievements->lo_achs) {
            ach.drawTo(window);
        }
    }

    bool isMouseOverBack(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = back_btn.getPosition().x;
        float btn_pos_y = back_btn.getPosition().y;
        float btn_xpos_width = back_btn.getLocalBounds().width * 0.15;
        float btn_xpos_height = back_btn.getLocalBounds().height * 0.15;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverNotPD(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = not_pgdown_btn.getPosition().x;
        float btn_pos_y = not_pgdown_btn.getPosition().y;
        float btn_xpos_width = not_pgdown_btn.getPosition().x + not_pgdown_btn.getLocalBounds().width * 0.05;
        float btn_xpos_height = not_pgdown_btn.getPosition().y + not_pgdown_btn.getLocalBounds().height * 0.05;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverNotPU(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = not_pgup_btn.getPosition().x;
        float btn_pos_y = not_pgup_btn.getPosition().y;
        float btn_xpos_width = not_pgup_btn.getPosition().x + not_pgup_btn.getLocalBounds().width * 0.05;
        float btn_xpos_height = not_pgup_btn.getPosition().y + not_pgup_btn.getLocalBounds().height * 0.05;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverAchPD(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = ach_pgdown_btn.getPosition().x;
        float btn_pos_y = ach_pgdown_btn.getPosition().y;
        float btn_xpos_width = ach_pgdown_btn.getPosition().x + ach_pgdown_btn.getLocalBounds().width * 0.1;
        float btn_xpos_height = ach_pgdown_btn.getPosition().y + ach_pgdown_btn.getLocalBounds().height * 0.1;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverAchPU(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = ach_pgup_btn.getPosition().x;
        float btn_pos_y = ach_pgup_btn.getPosition().y;
        float btn_xpos_width = ach_pgup_btn.getPosition().x + ach_pgup_btn.getLocalBounds().width * 0.1;
        float btn_xpos_height = ach_pgup_btn.getPosition().y + ach_pgup_btn.getLocalBounds().height * 0.1;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }
};

void AchNotWindowEvents(sf::RenderWindow& window, AchNotWindow* achNotWindow, bool& login_screen, bool& main_screen, bool& ach_not_screen, sf::Event& e) {
    if (e.type == sf::Event::MouseMoved) {
        if (achNotWindow->sign_out_btn.isMouseOver(window)) {
            achNotWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            achNotWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            achNotWindow->sign_out_btn.setBackColor(sf::Color::White);
            achNotWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
    }

    if (e.type == sf::Event::MouseButtonPressed) {
        if (achNotWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            login_screen = true;
            ach_not_screen = false;
        }
        if(achNotWindow->isMouseOverAchPU(window)) {
            std::cout << "Achievement pg up" << std::endl;
        }
        if (achNotWindow->isMouseOverAchPD(window)) {
            std::cout << "Achievement pg down" << std::endl;
        }
        if (achNotWindow->isMouseOverNotPU(window)) {
            std::cout << "Notification pg up" << std::endl;
        }
        if (achNotWindow->isMouseOverNotPD(window)) {
            std::cout << "Notification pg down" << std::endl;
        }
        if (achNotWindow->isMouseOverBack(window)) {
            std::cout << "-> Main Screen" << std::endl;
            main_screen = true;
            ach_not_screen = false;
        }
    }
}