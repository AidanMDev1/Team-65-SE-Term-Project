#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "request.h"
#include <chrono>

class ProjectWindow {
public:
    int proj_sel;
    sf::Font f;
    sf::Texture back_img;
    sf::Sprite back_btn;
    Button sign_out_btn;
    Button proj_plain_txt;
    Button proj_t_txt;
    Button proj_d_txt;
    sf::RectangleShape proj_bckgrnd;
    Button clockio_btn;
    Button time_txt;
    Button assign_user_btn;
    Button edit_btn;
    std::string proj_title = "TEST123";
    std::string proj_desc = "This is a test project.\nAssigned:\nAidan\nBrian\nAbigail\nAkeeb";
    std::chrono::time_point<std::chrono::high_resolution_clock> begin_time;
    int hours;
    int minutes;
    int seconds;

    ProjectWindow() { }
    ProjectWindow(sf::Font& font, request& req, int& proj_sel) {

        //only shuld work if the proj_sel is updated (when a project is selected)
        if (proj_sel != -1){
            proj_title = req.assigned_projects[proj_sel];
            // proj_desc = client and project manager info;
        }
        
        f = font;
        back_img.loadFromFile("files/back.png"); // find it in a folder where you store images
        back_btn.setTexture(back_img);
        back_btn.setScale({0.15, 0.15});

        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);

        proj_plain_txt = Button("Project:", 30, sf::Color(64, 156, 120));
        proj_plain_txt.setPosition({30, 110});
        proj_plain_txt.setFont(font);

        proj_t_txt = Button(proj_title, 30, sf::Color(64, 156, 120));
        proj_t_txt.setPosition({200, 110});
        proj_t_txt.setFont(font);

        proj_d_txt = Button(proj_desc, 20, sf::Color(64, 156, 120));
        proj_d_txt.setPosition({35, 160});
        proj_d_txt.setFont(font);

        proj_bckgrnd.setSize({800, 200});
        proj_bckgrnd.setPosition({30, 150});
        proj_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        clockio_btn = Button("CLOCK-IN", {500, 100}, 50, sf::Color::White, sf::Color::Black);
        clockio_btn.setPosition({210, 400});
        clockio_btn.setFont(font);

        time_txt = Button("Time - 00:00:00", 40, sf::Color(64, 156, 120));
        time_txt.setPosition({280, 580});
        time_txt.setFont(font);

        assign_user_btn = Button("Assign User", {200, 40}, 20, sf::Color::White, sf::Color::Black);
        assign_user_btn.setPosition({220, 30});
        assign_user_btn.setFont(font);

        edit_btn = Button("Edit", {100, 40}, 20, sf::Color::White, sf::Color::Black);
        edit_btn.setPosition({480, 30});
        edit_btn.setFont(font);
    }
    ~ProjectWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(proj_bckgrnd);
        window.draw(back_btn);
        sign_out_btn.drawTo(window);
        proj_plain_txt.drawTo(window);
        proj_t_txt.drawTo(window);
        proj_d_txt.drawTo(window);
        clockio_btn.drawTo(window);
        time_txt.drawTo(window);
        assign_user_btn.drawTo(window);
        edit_btn.drawTo(window);
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
};

void ProjectWindowEvents(sf::RenderWindow& window, ProjectWindow* projectWindow, bool& login_screen, bool& main_screen, bool& project_screen, sf::Event& e, request& req, int& proj_sel) {
    // highlight buttons when hovered over
    if (e.type == sf::Event::MouseMoved) {
        if (projectWindow->sign_out_btn.isMouseOver(window)) {
            projectWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->sign_out_btn.setBackColor(sf::Color::White);
            projectWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
        if (projectWindow->clockio_btn.isMouseOver(window)) {
            projectWindow->clockio_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->clockio_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->clockio_btn.setBackColor(sf::Color::White);
            projectWindow->clockio_btn.setTextColor(sf::Color::Black);
        }
        if (projectWindow->assign_user_btn.isMouseOver(window)) {
            projectWindow->assign_user_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->assign_user_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->assign_user_btn.setBackColor(sf::Color::White);
            projectWindow->assign_user_btn.setTextColor(sf::Color::Black);
        }
        if (projectWindow->edit_btn.isMouseOver(window)) {
            projectWindow->edit_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->edit_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->edit_btn.setBackColor(sf::Color::White);
            projectWindow->edit_btn.setTextColor(sf::Color::Black);
        }
    }

    if (e.type == sf::Event::MouseButtonPressed) {
        if (projectWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            req.clockout(req.username, req.assigned_projects[proj_sel]);
            login_screen = true;
            project_screen = false;
        }
        if (projectWindow->clockio_btn.isMouseOver(window)) {
            if (projectWindow->clockio_btn.getText() == "CLOCK-IN") {

                bool check = false;
                bool check2 = false;
                check = req.check_time(req.username, req.assigned_projects[proj_sel]); //checks if time table exits in db

                if (check){    //if it exists append into array
                    bool check2 = false;
                    check2 = req.clockin(req.username, req.assigned_projects[proj_sel]);
                    if (check2){
                        projectWindow->clockio_btn.setText("CLOCK-OUT");
                    }

                }else{     //if it doesnt exist create it
                    bool check2 = false;
                    check2 = req.create_clockin(req.username, req.assigned_projects[proj_sel]);
                    if (check2){
                        projectWindow->clockio_btn.setText("CLOCK-OUT");

                        //clock in chronos handling
                        projectWindow->begin_time = std::chrono::high_resolution_clock::now();
                        projectWindow->time_txt.setText("Time - 00:00:00");                        
                    }
                }
                
            }
            else if (projectWindow->clockio_btn.getText() == "CLOCK-OUT") {

                bool check = false;
                check = req.clockout(req.username, req.assigned_projects[proj_sel]);
                if (check){
                    std::cout << "clocking out" << std::endl;
                    projectWindow->clockio_btn.setText("CLOCK-IN");

                    //clock out chronos handling
                    auto end_time = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - projectWindow->begin_time);
                    std::cout << "time worked: " << duration.count() << std::endl;
                    projectWindow->hours = duration.count() / 3600;
                    projectWindow->minutes = (duration.count() % 3600) / 60;
                    projectWindow->seconds = duration.count() % 60;
                    std::string ci_string = "Time - ";
                    if (projectWindow->hours >= 10) {
                        ci_string+=std::to_string(projectWindow->hours);
                    }
                    else {
                        ci_string+="0";
                        if (projectWindow->hours == 0) {
                            ci_string+="0";
                        }
                        else {
                            ci_string+=std::to_string(projectWindow->hours);
                        }
                    }
                    ci_string += ":";
                    if (projectWindow->minutes >= 10) {
                        ci_string+=std::to_string(projectWindow->minutes);
                    }
                    else {
                        ci_string+="0";
                        if (projectWindow->minutes == 0) {
                            ci_string+="0";
                        }
                        else {
                            ci_string+=std::to_string(projectWindow->minutes);
                        }
                    }
                    ci_string += ":";
                    if (projectWindow->seconds >= 10) {
                        ci_string+=std::to_string(projectWindow->seconds);
                    }
                    else {
                        ci_string+="0";
                        if (projectWindow->seconds == 0) {
                            ci_string+="0";
                        }
                        else {
                            ci_string+=std::to_string(projectWindow->seconds);
                        }
                    }
                    projectWindow->time_txt.setText(ci_string);
                }
            }
        }
        if (projectWindow->assign_user_btn.isMouseOver(window) && req.user_role == "admin") {
            sf::RectangleShape a_user_bckrnd;
            a_user_bckrnd.setSize({600, 400});
            a_user_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button user_txt = Button("User:", 15, sf::Color(64, 156, 120));
            user_txt.setPosition({30, 30});
            user_txt.setFont(projectWindow->f);

            Textbox user_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            user_tbox.setFont(projectWindow->f);
            user_tbox.setPosition({150, 30});

            Button assign_btn = Button("Create", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            assign_btn.setPosition({100, 200});
            assign_btn.setFont(projectWindow->f);

            sf::RenderWindow a_user_window(sf::VideoMode(600, 400), "Assign User", sf::Style::Titlebar | sf::Style::Close);

            while (a_user_window.isOpen()) {
                sf::Event a_user_event;

                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    user_tbox.setSelected(false);
                }

                while (a_user_window.pollEvent(a_user_event)) {
                    if (a_user_event.type == sf::Event::Closed) {
                        a_user_window.close();
                    }

                    if (a_user_event.type == sf::Event::TextEntered) {
                        if (user_tbox.isSelected()) {
                            user_tbox.typeOn(a_user_event);
                        }
                    }

                    if (a_user_event.type == sf::Event::MouseMoved) {
                        if (assign_btn.isMouseOver(a_user_window)) {
                            assign_btn.setBackColor(sf::Color(64, 156, 120));
                            assign_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            assign_btn.setBackColor(sf::Color::White);
                            assign_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (a_user_event.type == sf::Event::MouseButtonPressed) {
                        if (user_tbox.isMouseOver(a_user_window)) {
                            user_tbox.setSelected(true);
                        }
                        else {
                            user_tbox.setSelected(false);
                        }

                        if (assign_btn.isMouseOver(a_user_window)) {
                            std::cout << user_tbox.getText() << " Assigned" << std::endl;
                            a_user_window.close();
                        }
                    }
                }
                a_user_window.clear();
                a_user_window.draw(a_user_bckrnd);
                user_txt.drawTo(a_user_window);
                user_tbox.drawTo(a_user_window);
                assign_btn.drawTo(a_user_window);
                a_user_window.display();
            }
        }
        if (projectWindow->edit_btn.isMouseOver(window) && req.user_role == "admin") {
            sf::RectangleShape edit_proj_bckrnd;
            edit_proj_bckrnd.setSize({600, 400});
            edit_proj_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button title_txt = Button("Title:", 15, sf::Color(64, 156, 120));
            title_txt.setPosition({30, 30});
            title_txt.setFont(projectWindow->f);

            Textbox title_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            title_tbox.setFont(projectWindow->f);
            title_tbox.setPosition({150, 30});

            Button manager_txt = Button("Manager:", 15, sf::Color(64, 156, 120));
            manager_txt.setPosition({30, 100});
            manager_txt.setFont(projectWindow->f);

            Textbox manager_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            manager_tbox.setFont(projectWindow->f);
            manager_tbox.setPosition({150, 100});

            Button client_txt = Button("Client:", 15, sf::Color(64, 156, 120));
            client_txt.setPosition({30, 170});
            client_txt.setFont(projectWindow->f);

            Textbox client_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            client_tbox.setFont(projectWindow->f);
            client_tbox.setPosition({150, 170});


            Button create_btn = Button("Finalize Edit", {200, 50}, 15, sf::Color::White, sf::Color::Black);
            create_btn.setPosition({100, 250});
            create_btn.setFont(projectWindow->f);

            sf::RenderWindow edit_proj_window(sf::VideoMode(600, 400), "Edit Project", sf::Style::Titlebar | sf::Style::Close);

            while (edit_proj_window.isOpen()) {
                sf::Event edit_proj_event;

                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    title_tbox.setSelected(false);
                    manager_tbox.setSelected(false);
                    client_tbox.setSelected(false);
                }

                while (edit_proj_window.pollEvent(edit_proj_event)) {
                    if (edit_proj_event.type == sf::Event::Closed) {
                        edit_proj_window.close();
                    }

                    if (edit_proj_event.type == sf::Event::TextEntered) {
                        if (title_tbox.isSelected()) {
                            title_tbox.typeOn(edit_proj_event);
                        }
                        if (manager_tbox.isSelected()) {
                            manager_tbox.typeOn(edit_proj_event);
                        }
                        if (client_tbox.isSelected()) {
                            client_tbox.typeOn(edit_proj_event);
                        }
                    }

                    if (edit_proj_event.type == sf::Event::MouseMoved) {
                        if (create_btn.isMouseOver(edit_proj_window)) {
                            create_btn.setBackColor(sf::Color(64, 156, 120));
                            create_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            create_btn.setBackColor(sf::Color::White);
                            create_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (edit_proj_event.type == sf::Event::MouseButtonPressed) {
                        if (title_tbox.isMouseOver(edit_proj_window)) {
                            title_tbox.setSelected(true);
                        }
                        else {
                            title_tbox.setSelected(false);
                        }

                        if (manager_tbox.isMouseOver(edit_proj_window)) {
                            manager_tbox.setSelected(true);
                        }
                        else {
                            manager_tbox.setSelected(false);
                        }

                        if (client_tbox.isMouseOver(edit_proj_window)) {
                            client_tbox.setSelected(true);
                        }
                        else {
                            client_tbox.setSelected(false);
                        }

                        if (create_btn.isMouseOver(edit_proj_window)) {
                            projectWindow->proj_t_txt.setText( title_tbox.getText());
                            std::cout << title_tbox.getText() << " - is the New Title\nManager: " << manager_tbox.getText() << "\n" << "Client: " << client_tbox.getText() << std::endl;
                            edit_proj_window.close();
                        }
                    }
                }
                edit_proj_window.clear();
                edit_proj_window.draw(edit_proj_bckrnd);
                title_txt.drawTo(edit_proj_window);
                title_tbox.drawTo(edit_proj_window);
                manager_txt.drawTo(edit_proj_window);
                manager_tbox.drawTo(edit_proj_window);
                client_txt.drawTo(edit_proj_window);
                client_tbox.drawTo(edit_proj_window);
                create_btn.drawTo(edit_proj_window);
                edit_proj_window.display();
            }
        }
        if (projectWindow->isMouseOverBack(window)) {
            std::cout << "-> Main Screen" << std::endl;
            req.clockout(req.username, req.assigned_projects[proj_sel]);
            main_screen = true;
            project_screen = false;
        }
    }

}