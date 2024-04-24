#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"

class TimesWindow {
public:
    sf::Texture back_img;
    sf::Sprite back_btn;
    sf::Texture pgdown_img;
    sf::Texture pgup_img;
    sf::Sprite time_pgup_btn;
    sf::Sprite time_pgdown_btn;
    sf::Sprite spcfc_pgup_btn;
    sf::Sprite spcfc_pgdown_btn;
    sf::Sprite emp_pgup_btn;
    sf::Sprite emp_pgdown_btn;
    Button sign_out_btn;
    Button time_logs_txt;
    sf::RectangleShape time_bckgrnd;
    Button employee_txt;
    sf::RectangleShape employee_bckgrnd;
    Button alternate_btn;
    Button specific_txt;
    sf::RectangleShape specific_bckgrnd;
    std::vector<Button> lo_times;
    std::vector<Button> lo_projects;
    std::vector<Button> lo_employees;

    TimesWindow() { }
    TimesWindow(sf::Font& font) {
        back_img.loadFromFile("files/back.png"); // find it in a folder where you store images
        back_btn.setTexture(back_img);
        back_btn.setScale({0.15, 0.15});

        pgdown_img.loadFromFile("files/page_down.png");
        pgup_img.loadFromFile("files/page_up.png");

        time_pgup_btn.setTexture(pgup_img);
        time_pgup_btn.setScale({0.1, 0.1});
        time_pgup_btn.setPosition({290, 160});

        time_pgdown_btn.setTexture(pgdown_img);
        time_pgdown_btn.setScale({0.1, 0.1});
        time_pgdown_btn.setPosition({290, 480});

        spcfc_pgup_btn.setTexture(pgup_img);
        spcfc_pgup_btn.setScale({0.05, 0.05});
        spcfc_pgup_btn.setPosition({725, 160});

        spcfc_pgdown_btn.setTexture(pgdown_img);
        spcfc_pgdown_btn.setScale({0.05, 0.05});
        spcfc_pgdown_btn.setPosition({725, 510});

        emp_pgup_btn.setTexture(pgup_img);
        emp_pgup_btn.setScale({0.05, 0.05});
        emp_pgup_btn.setPosition({210, 640});

        emp_pgdown_btn.setTexture(pgdown_img);
        emp_pgdown_btn.setScale({0.05, 0.05});
        emp_pgdown_btn.setPosition({210, 790});

        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);

        time_logs_txt = Button("Timelogs:", 30, sf::Color(64, 156, 120));
        time_logs_txt.setPosition({250, 100});
        time_logs_txt.setFont(font);

        time_bckgrnd.setSize({600, 400});
        time_bckgrnd.setPosition({30, 150});
        time_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        employee_txt = Button("Employees:", 20, sf::Color(64, 156, 120));
        employee_txt.setPosition({30, 590});
        employee_txt.setFont(font);

        employee_bckgrnd.setSize({400, 200});
        employee_bckgrnd.setPosition({30, 630});
        employee_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        alternate_btn = Button("Company Times", {350, 50}, 25, sf::Color::White, sf::Color::Black);
        alternate_btn.setPosition({500, 650});
        alternate_btn.setFont(font);

        specific_txt = Button("Specific Project:", 18, sf::Color(64, 156, 120));
        specific_txt.setPosition({660, 120});
        specific_txt.setFont(font);

        specific_bckgrnd.setSize({175, 400});
        specific_bckgrnd.setPosition({660, 150});
        specific_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        Button time1 = Button("clockin #0: 4/23/2024, 01:21 AM", 20, sf::Color(64, 156, 120));
        time1.setPosition({50, 230});
        time1.setFont(font);

        Button time2 = Button("clockin #1: 4/23/2024, 01:21 AM", 20, sf::Color(64, 156, 120));
        time2.setPosition({50, 230 + 30}); // + 30 for mult
        time2.setFont(font);

        Button proj1 = Button("TEST PROJ", 15, sf::Color(64, 156, 120));
        proj1.setPosition({680, 200});
        proj1.setFont(font);

        Button proj2 = Button("TEST PROJ 2", 15, sf::Color(64, 156, 120));
        proj2.setPosition({680, 200 + 20}); // + 20 for mult
        proj2.setFont(font);

        Button emp1 = Button("employee overworked", 15, sf::Color(64, 156, 120));
        emp1.setPosition({50, 680});
        emp1.setFont(font);

        Button emp2 = Button("employee overworked 2", 15, sf::Color(64, 156, 120));
        emp2.setPosition({50, 680 + 20}); // +20 for mult
        emp2.setFont(font);

        lo_times.push_back(time1);
        lo_times.push_back(time2);
        lo_projects.push_back(proj1);
        lo_projects.push_back(proj2);
        lo_employees.push_back(emp1);
        lo_employees.push_back(emp2);
    }
    ~TimesWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(time_bckgrnd);
        window.draw(employee_bckgrnd);
        window.draw(specific_bckgrnd);
        window.draw(back_btn);
        window.draw(time_pgdown_btn);
        window.draw(time_pgup_btn);
        window.draw(spcfc_pgdown_btn);
        window.draw(spcfc_pgup_btn);
        window.draw(emp_pgdown_btn);
        window.draw(emp_pgup_btn);
        sign_out_btn.drawTo(window);
        time_logs_txt.drawTo(window);
        employee_txt.drawTo(window);
        alternate_btn.drawTo(window);
        specific_txt.drawTo(window);

        for (auto& time : lo_times) {
            time.drawTo(window);
        }
        for (auto& proj : lo_projects) {
            proj.drawTo(window);
        }
        for (auto& emp : lo_employees) {
            emp.drawTo(window);
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

    bool isMouseOverTimePD(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = time_pgdown_btn.getPosition().x;
        float btn_pos_y = time_pgdown_btn.getPosition().y;
        float btn_xpos_width = time_pgdown_btn.getPosition().x + time_pgdown_btn.getLocalBounds().width * 0.1;
        float btn_xpos_height = time_pgdown_btn.getPosition().y + time_pgdown_btn.getLocalBounds().height * 0.1;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverTimePU(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = time_pgup_btn.getPosition().x;
        float btn_pos_y = time_pgup_btn.getPosition().y;
        float btn_xpos_width = time_pgup_btn.getPosition().x + time_pgup_btn.getLocalBounds().width * 0.1;
        float btn_xpos_height = time_pgup_btn.getPosition().y + time_pgup_btn.getLocalBounds().height * 0.1;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverEmpPD(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = emp_pgdown_btn.getPosition().x;
        float btn_pos_y = emp_pgdown_btn.getPosition().y;
        float btn_xpos_width = emp_pgdown_btn.getPosition().x + emp_pgdown_btn.getLocalBounds().width * 0.05;
        float btn_xpos_height = emp_pgdown_btn.getPosition().y + emp_pgdown_btn.getLocalBounds().height * 0.05;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverEmpPU(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = emp_pgup_btn.getPosition().x;
        float btn_pos_y = emp_pgup_btn.getPosition().y;
        float btn_xpos_width = emp_pgup_btn.getPosition().x + emp_pgup_btn.getLocalBounds().width * 0.05;
        float btn_xpos_height = emp_pgup_btn.getPosition().y + emp_pgup_btn.getLocalBounds().height * 0.05;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverSpcPD(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = spcfc_pgdown_btn.getPosition().x;
        float btn_pos_y = spcfc_pgdown_btn.getPosition().y;
        float btn_xpos_width = spcfc_pgdown_btn.getPosition().x + spcfc_pgdown_btn.getLocalBounds().width * 0.05;
        float btn_xpos_height = spcfc_pgdown_btn.getPosition().y + spcfc_pgdown_btn.getLocalBounds().height * 0.05;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }

    bool isMouseOverSpcPU(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = spcfc_pgup_btn.getPosition().x;
        float btn_pos_y = spcfc_pgup_btn.getPosition().y;
        float btn_xpos_width = spcfc_pgup_btn.getPosition().x + spcfc_pgup_btn.getLocalBounds().width * 0.05;
        float btn_xpos_height = spcfc_pgup_btn.getPosition().y + spcfc_pgup_btn.getLocalBounds().height * 0.05;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }
};


void TimesWindowEvents(sf::RenderWindow& window, TimesWindow* timesWindow, bool& login_screen, bool& main_screen, bool& time_logs_screen, sf::Event& e) {
    // highlight buttons when hovered over
    if (e.type == sf::Event::MouseMoved) {
        if (timesWindow->sign_out_btn.isMouseOver(window)) {
            timesWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            timesWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            timesWindow->sign_out_btn.setBackColor(sf::Color::White);
            timesWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
        if (timesWindow->alternate_btn.isMouseOver(window)) {
            timesWindow->alternate_btn.setBackColor(sf::Color(64, 156, 120));
            timesWindow->alternate_btn.setTextColor(sf::Color::White);
        }
        else {
            timesWindow->alternate_btn.setBackColor(sf::Color::White);
            timesWindow->alternate_btn.setTextColor(sf::Color::Black);
        }
    }

    // action on click for buttons
    if (e.type == sf::Event::MouseButtonPressed) {
        if (timesWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            login_screen = true;
            time_logs_screen = false;
        }
        if (timesWindow->alternate_btn.isMouseOver(window)) {
            if (timesWindow->alternate_btn.getText() == "Company Times") {
                timesWindow->alternate_btn.setText("Personal Times");
            }
            else {
                timesWindow->alternate_btn.setText("Company Times");
            }
        }
        if (timesWindow->isMouseOverBack(window)) {
            std::cout << "-> Main Screen" << std::endl;
            main_screen = true;
            time_logs_screen = false;
        }
        if (timesWindow->isMouseOverTimePU(window)) {
            std::cout << "Time page up" << std::endl;
        }
        if (timesWindow->isMouseOverTimePD(window)) {
            std::cout << "Time page down" << std::endl;
        }
        if (timesWindow->isMouseOverEmpPU(window)) {
            std::cout << "Employee page up" << std::endl;
        }
        if (timesWindow->isMouseOverEmpPD(window)) {
            std::cout << "Employee page down" << std::endl;
        }
        if (timesWindow->isMouseOverSpcPU(window)) {
            std::cout << "Specific page up" << std::endl;
        }
        if (timesWindow->isMouseOverSpcPD(window)) {
            std::cout << "Specific page down" << std::endl;
        }
    }
}
