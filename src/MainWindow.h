#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ProjectWindow.h"

class MainWindow {
public:
    sf::Font f;
    Button welcome_txt;
    Button sign_out_btn;
    Button projects_txt;
    sf::RectangleShape proj_bckgrnd;
    sf::Texture pgdown_img;
    sf::Sprite proj_pgdown_btn;
    Button contact_btn;
    Button create_proj_btn;
    Button create_users_btn;
    Button achvmts_notif_btn;
    Button access_logs_btn;
    std::vector<Button> lo_proj;

    MainWindow() { }
    MainWindow(sf::Font& font) {
        f = font;

        welcome_txt = Button("WELCOME! Unlock Time's Potential with QuestClock!", 25, sf::Color(64, 156, 120));
        welcome_txt.setPosition({30, 30});
        welcome_txt.setFont(font);

        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);

        projects_txt = Button("Project(s):", 20, sf::Color(64, 156, 120));
        projects_txt.setPosition({30, 110});
        projects_txt.setFont(font);

        proj_bckgrnd.setSize({800, 400});
        proj_bckgrnd.setPosition({30, 150});
        proj_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        //this is where we show all projects that are selectable
        Button test1 = Button("TEST1 : First test of them all.", {750, 50}, 25, sf::Color(230, 230, 230), sf::Color(64, 156, 120));
        test1.setPosition({50, 160});
        test1.setFont(font);

        Button test2 = Button("TEST2 : 2nd test for all 'em.", {750, 50}, 25, sf::Color(230, 230, 230), sf::Color(64, 156, 120));
        test2.setPosition({50, 160 + 75});
        test2.setFont(font);

        lo_proj.push_back(test1);
        lo_proj.push_back(test2);

        pgdown_img.loadFromFile("files/page_down.png");

        proj_pgdown_btn.setTexture(pgdown_img);
        proj_pgdown_btn.setScale({0.1, 0.1});
        proj_pgdown_btn.setPosition({370, 480});

        contact_btn = Button("Contact", {300, 50}, 25, sf::Color::White, sf::Color::Black);
        contact_btn.setPosition({30, 600});
        contact_btn.setFont(font);

        create_proj_btn = Button("Create Project", {300, 50}, 25, sf::Color::White, sf::Color::Black);
        create_proj_btn.setPosition({30, 670});
        create_proj_btn.setFont(font);

        create_users_btn = Button("Create User", {300, 50}, 25, sf::Color::White, sf::Color::Black);
        create_users_btn.setPosition({30, 750});
        create_users_btn.setFont(font);

        achvmts_notif_btn = Button("Achievments/\nNotifications", {300, 100}, 25, sf::Color::White, sf::Color::Black);
        achvmts_notif_btn.setPosition({550, 600});
        achvmts_notif_btn.setFont(font);

        access_logs_btn = Button("Access Timelogs", {350, 50}, 25, sf::Color::White, sf::Color::Black);
        access_logs_btn.setPosition({500, 720});
        access_logs_btn.setFont(font);
    }
    ~MainWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(proj_bckgrnd);
        window.draw(proj_pgdown_btn);
        welcome_txt.drawTo(window);
        sign_out_btn.drawTo(window);
        projects_txt.drawTo(window);
        contact_btn.drawTo(window);
        create_proj_btn.drawTo(window);
        create_users_btn.drawTo(window);
        achvmts_notif_btn.drawTo(window);
        access_logs_btn.drawTo(window);
        for (auto& proj : lo_proj) {
            proj.drawTo(window);
        }
    }

    bool isMouseOverProjPD(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;
        float btn_pos_x = proj_pgdown_btn.getPosition().x;
        float btn_pos_y = proj_pgdown_btn.getPosition().y;
        float btn_xpos_width = proj_pgdown_btn.getPosition().x + proj_pgdown_btn.getLocalBounds().width * 0.1;
        float btn_xpos_height = proj_pgdown_btn.getPosition().y + proj_pgdown_btn.getLocalBounds().height * 0.1;
        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }
};

void MainWindowEvents(sf::RenderWindow& window, MainWindow* mainWindow, ProjectWindow* projectWindow, bool& login_screen,
                      bool& main_screen, bool& time_logs_screen, bool& project_screen, bool& ach_not_screen, sf::Event& e) {
    // highlight buttons when hovered over
    if (e.type == sf::Event::MouseMoved) {
        if (mainWindow->sign_out_btn.isMouseOver(window)) {
            mainWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->sign_out_btn.setBackColor(sf::Color::White);
            mainWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->contact_btn.isMouseOver(window)) {
            mainWindow->contact_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->contact_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->contact_btn.setBackColor(sf::Color::White);
            mainWindow->contact_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->create_proj_btn.isMouseOver(window)) {
            mainWindow->create_proj_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->create_proj_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->create_proj_btn.setBackColor(sf::Color::White);
            mainWindow->create_proj_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->create_users_btn.isMouseOver(window)) {
            mainWindow->create_users_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->create_users_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->create_users_btn.setBackColor(sf::Color::White);
            mainWindow->create_users_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->achvmts_notif_btn.isMouseOver(window)) {
            mainWindow->achvmts_notif_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->achvmts_notif_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->achvmts_notif_btn.setBackColor(sf::Color::White);
            mainWindow->achvmts_notif_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->access_logs_btn.isMouseOver(window)) {
            mainWindow->access_logs_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->access_logs_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->access_logs_btn.setBackColor(sf::Color::White);
            mainWindow->access_logs_btn.setTextColor(sf::Color::Black);
        }
    }

    // action on click for buttons
    if (e.type == sf::Event::MouseButtonPressed) {
        if (mainWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            login_screen = true;
            main_screen = false;
        }

        if (mainWindow->contact_btn.isMouseOver(window)) {
            sf::RenderWindow contact_window(sf::VideoMode(400, 400), "Contact a User", sf::Style::Titlebar | sf::Style::Close);
            while (contact_window.isOpen()) {
                sf::Event event;
                while (contact_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        contact_window.close();
                    }
                }
                contact_window.clear(sf::Color(230, 230, 230));
                contact_window.display();
            }
        }

        if (mainWindow->create_users_btn.isMouseOver(window)) {
            sf::RenderWindow create_users_window(sf::VideoMode(400, 400), "Create a User", sf::Style::Titlebar | sf::Style::Close);
            while (create_users_window.isOpen()) {
                sf::Event event;
                while (create_users_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        create_users_window.close();
                    }
                }
                create_users_window.clear(sf::Color(230, 230, 230));
                create_users_window.display();
            }
        }

        if (mainWindow->create_proj_btn.isMouseOver(window)) {
            sf::RenderWindow create_proj_window(sf::VideoMode(400, 400), "Create and Assign a Project", sf::Style::Titlebar | sf::Style::Close);
            while (create_proj_window.isOpen()) {
                sf::Event event;
                while (create_proj_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        create_proj_window.close();
                    }
                }
                create_proj_window.clear(sf::Color(230, 230, 230));
                create_proj_window.display();
            }
        }


        if (mainWindow->access_logs_btn.isMouseOver(window)) {
            std::cout << "-> Timelog Screen" << std::endl;
            time_logs_screen = true;
            main_screen = false;
        }

        if (mainWindow->achvmts_notif_btn.isMouseOver(window)) {
            std::cout << "-> Achievements/Notifications Screen" << std::endl;
            ach_not_screen = true;
            main_screen = false;
        }

        if (mainWindow->isMouseOverProjPD(window)) {
            std::cout << "Projects page down" << std::endl;
        }
        for (auto& proj : mainWindow->lo_proj) {
            if (proj.isMouseOver(window)) {

                // split description and title
                std::string input = proj.getText();

                // Find the position of the colon
                size_t colonPos = input.find(':');

                // Extract the substring before the colon (excluding leading and trailing spaces)
                std::string title = input.substr(0, colonPos);
                // Trim leading and trailing spaces
                title.erase(0, title.find_first_not_of(" "));
                title.erase(title.find_last_not_of(" ") + 1);

                // Extract the substring after the colon (excluding leading and trailing spaces)
                std::string description = input.substr(colonPos + 1);
                // Trim leading and trailing spaces
                description.erase(0, description.find_first_not_of(" "));
                description.erase(description.find_last_not_of(" ") + 1);

                std::cout << "Title: " + title + "\nDescription: " + description << std::endl;

                delete projectWindow;
                projectWindow =  new ProjectWindow(mainWindow->f, title, description);

                project_screen = true;
                main_screen = false;
            }
        }
    }
}