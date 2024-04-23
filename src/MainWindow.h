#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ProjectWindow.h"
#include "request.h"

class MainWindow {
public:
    sf::Font f;
    bool signed_in;
    int proj_sel;

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
    request req;

    MainWindow() { }
    MainWindow(sf::Font& font, request& req, bool s, int& proj_sel) {
        
        f = font;
        signed_in = s;
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
        for (int i = 0; i < req.assigned_projects.size(); i++){
            Button test = Button(req.assigned_projects[i], {750, 50}, 25, sf::Color(230, 230, 230), sf::Color(64, 156, 120));
            test.setPosition({50, 160 + 75*i});
            test.setFont(font);
            lo_proj.push_back(test);
        }

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

        create_users_btn = Button("Create/Delete User", {420, 50}, 25, sf::Color::White, sf::Color::Black);
        create_users_btn.setPosition({30, 730});
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
                        bool& main_screen, bool& time_logs_screen, bool& project_screen, bool& ach_not_screen, sf::Event& e, request& req, int& proj_sel) {
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

        //opens contact window for users to message other users
        if (mainWindow->contact_btn.isMouseOver(window)) {
            sf::RectangleShape contact_bckrnd;
            contact_bckrnd.setSize({600, 400});
            contact_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button to_txt = Button("To:", 15, sf::Color(64, 156, 120));
            to_txt.setPosition({30, 30});
            to_txt.setFont(mainWindow->f);

            Button msg_txt = Button("Message: ", 15, sf::Color(64, 156, 120));
            msg_txt.setPosition({30, 150});
            msg_txt.setFont(mainWindow->f);

            Textbox to_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            to_tbox.setFont(mainWindow->f);
            to_tbox.setPosition({150, 30});

            Textbox msg_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            msg_tbox.setFont(mainWindow->f);
            msg_tbox.setPosition({150, 150});

            Button send_btn = Button("Send", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            send_btn.setPosition({200, 200});
            send_btn.setFont(mainWindow->f);

            sf::RenderWindow contact_window(sf::VideoMode(600, 400), "Contact a User", sf::Style::Titlebar | sf::Style::Close);

            while (contact_window.isOpen()) {
                sf::Event contact_event;


                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    to_tbox.setSelected(false);
                    msg_tbox.setSelected(false);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (to_tbox.isSelected()) {
                        to_tbox.setSelected(false);
                        msg_tbox.setSelected(true);
                    }
                }

                while (contact_window.pollEvent(contact_event)) {
                    if (contact_event.type == sf::Event::Closed) {
                        contact_window.close();
                    }

                    if (contact_event.type == sf::Event::TextEntered) {
                        if (to_tbox.isSelected()) {
                            to_tbox.typeOn(contact_event);
                        }
                        if (msg_tbox.isSelected()) {
                            msg_tbox.typeOn(contact_event);
                        }
                    }

                    if (contact_event.type == sf::Event::MouseMoved) {
                        if (send_btn.isMouseOver(contact_window)) {
                            send_btn.setBackColor(sf::Color(64, 156, 120));
                            send_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            send_btn.setBackColor(sf::Color::White);
                            send_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (contact_event.type == sf::Event::MouseButtonPressed) {
                        // click in username box
                        if (to_tbox.isMouseOver(contact_window)) {
                            to_tbox.setSelected(true);
                            msg_tbox.setSelected(false);
                        }
                        else {
                            to_tbox.setSelected(false);
                        }

                        // click in password box
                        if (msg_tbox.isMouseOver(contact_window)) {
                            msg_tbox.setSelected(true);
                            to_tbox.setSelected(false);
                        }
                        else {
                            msg_tbox.setSelected(false);
                        }

                        if (send_btn.isMouseOver(contact_window)) {
                            std::cout << "To: " << to_tbox.getText() << "\n" << "Message: " << msg_tbox.getText() << std::endl;
                            std::string username = to_tbox.getText();
                            std::string notif = msg_tbox.getText();

                            bool check = false;
                            bool check2 = false;
                            check = req.check_user(username); //checks if user exists in db
                            if(check){
                                check2 = req.send_notification(username, req.username, notif);
                            }

                            contact_window.close();
                        }
                    }
                }
                contact_window.clear();
                contact_window.draw(contact_bckrnd);
                to_txt.drawTo(contact_window);
                msg_txt.drawTo(contact_window);
                to_tbox.drawTo(contact_window);
                msg_tbox.drawTo(contact_window);
                send_btn.drawTo(contact_window);
                contact_window.display();
            }
        }

        //opens create/delete users window
        if (mainWindow->create_users_btn.isMouseOver(window) && req.user_role == "admin") {
            sf::RectangleShape cr_del_bckrnd;
            cr_del_bckrnd.setSize({600, 400});
            cr_del_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button user_txt = Button("User:", 15, sf::Color(64, 156, 120));
            user_txt.setPosition({30, 30});
            user_txt.setFont(mainWindow->f);

            Textbox user_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            user_tbox.setFont(mainWindow->f);
            user_tbox.setPosition({150, 30});

            Button create_btn = Button("Create", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            create_btn.setPosition({100, 200});
            create_btn.setFont(mainWindow->f);

            Button delete_btn = Button("Delete", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            delete_btn.setPosition({300, 200});
            delete_btn.setFont(mainWindow->f);

            sf::RenderWindow cr_del_window(sf::VideoMode(600, 400), "Create or Delete User", sf::Style::Titlebar | sf::Style::Close);

            while (cr_del_window.isOpen()) {
                sf::Event cr_del_event;

                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    user_tbox.setSelected(false);
                }

                while (cr_del_window.pollEvent(cr_del_event)) {
                    if (cr_del_event.type == sf::Event::Closed) {
                        cr_del_window.close();
                    }

                    if (cr_del_event.type == sf::Event::TextEntered) {
                        if (user_tbox.isSelected()) {
                            user_tbox.typeOn(cr_del_event);
                        }
                    }

                    if (cr_del_event.type == sf::Event::MouseMoved) {
                        if (create_btn.isMouseOver(cr_del_window)) {
                            create_btn.setBackColor(sf::Color(64, 156, 120));
                            create_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            create_btn.setBackColor(sf::Color::White);
                            create_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (cr_del_event.type == sf::Event::MouseMoved) {
                        if (delete_btn.isMouseOver(cr_del_window)) {
                            delete_btn.setBackColor(sf::Color(64, 156, 120));
                            delete_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            delete_btn.setBackColor(sf::Color::White);
                            delete_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (cr_del_event.type == sf::Event::MouseButtonPressed) {
                        if (user_tbox.isMouseOver(cr_del_window)) {
                            user_tbox.setSelected(true);
                        }
                        else {
                            user_tbox.setSelected(false);
                        }

                        if (create_btn.isMouseOver(cr_del_window)) {
                            std::cout << user_tbox.getText() << " Created" << std::endl;
                            // string username = user_tbox.getText();
                            // bool check  = false;
                            // check = req.create_user(username, password, role, proj);
                            cr_del_window.close();
                        }
                        if (delete_btn.isMouseOver(cr_del_window)) {
                            std::cout << user_tbox.getText() << " Deleted" << std::endl;

                            string username = user_tbox.getText();
                            bool check = false;
                            check = req.delete_user(username);

                            cr_del_window.close();
                        }
                    }
                }
                cr_del_window.clear();
                cr_del_window.draw(cr_del_bckrnd);
                user_txt.drawTo(cr_del_window);
                user_tbox.drawTo(cr_del_window);
                create_btn.drawTo(cr_del_window);
                delete_btn.drawTo(cr_del_window);
                cr_del_window.display();
            }
        }

        //opens the create project window
        if (mainWindow->create_proj_btn.isMouseOver(window) && req.user_role == "admin") {
            sf::RectangleShape cr_proj_bckrnd;
            cr_proj_bckrnd.setSize({600, 400});
            cr_proj_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button title_txt = Button("Title:", 15, sf::Color(64, 156, 120));
            title_txt.setPosition({30, 30});
            title_txt.setFont(mainWindow->f);

            Textbox title_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            title_tbox.setFont(mainWindow->f);
            title_tbox.setPosition({150, 30});

            Button manager_txt = Button("Manager:", 15, sf::Color(64, 156, 120));
            manager_txt.setPosition({30, 100});
            manager_txt.setFont(mainWindow->f);

            Textbox manager_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            manager_tbox.setFont(mainWindow->f);
            manager_tbox.setPosition({150, 100});

            Button client_txt = Button("Client:", 15, sf::Color(64, 156, 120));
            client_txt.setPosition({30, 170});
            client_txt.setFont(mainWindow->f);

            Textbox client_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            client_tbox.setFont(mainWindow->f);
            client_tbox.setPosition({150, 170});


            Button create_btn = Button("Create", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            create_btn.setPosition({100, 250});
            create_btn.setFont(mainWindow->f);

            sf::RenderWindow cr_proj_window(sf::VideoMode(600, 400), "Create Project", sf::Style::Titlebar | sf::Style::Close);

            while (cr_proj_window.isOpen()) {
                sf::Event cr_proj_event;

                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    title_tbox.setSelected(false);
                    manager_tbox.setSelected(false);
                    client_tbox.setSelected(false);
                }

                while (cr_proj_window.pollEvent(cr_proj_event)) {
                    if (cr_proj_event.type == sf::Event::Closed) {
                        cr_proj_window.close();
                    }

                    if (cr_proj_event.type == sf::Event::TextEntered) {
                        if (title_tbox.isSelected()) {
                            title_tbox.typeOn(cr_proj_event);
                        }
                        if (manager_tbox.isSelected()) {
                            manager_tbox.typeOn(cr_proj_event);
                        }
                        if (client_tbox.isSelected()) {
                            client_tbox.typeOn(cr_proj_event);
                        }
                    }

                    if (cr_proj_event.type == sf::Event::MouseMoved) {
                        if (create_btn.isMouseOver(cr_proj_window)) {
                            create_btn.setBackColor(sf::Color(64, 156, 120));
                            create_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            create_btn.setBackColor(sf::Color::White);
                            create_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (cr_proj_event.type == sf::Event::MouseButtonPressed) {
                        if (title_tbox.isMouseOver(cr_proj_window)) {
                            title_tbox.setSelected(true);
                        }
                        else {
                            title_tbox.setSelected(false);
                        }

                        if (manager_tbox.isMouseOver(cr_proj_window)) {
                            manager_tbox.setSelected(true);
                        }
                        else {
                            manager_tbox.setSelected(false);
                        }

                        if (client_tbox.isMouseOver(cr_proj_window)) {
                            client_tbox.setSelected(true);
                        }
                        else {
                            client_tbox.setSelected(false);
                        }

                        if (create_btn.isMouseOver(cr_proj_window)) {
                            std::cout << title_tbox.getText() << " Created\nManager: " << manager_tbox.getText() << "\n" << "Client: " << client_tbox.getText() << std::endl;
                            std::string proj_name = title_tbox.getText();
                            std::string proj_mana = manager_tbox.getText();
                            std::string proj_client = client_tbox.getText();

                            bool check = false;
                            bool check2 = false;
                            check = req.check_user(proj_mana);
                            if (check){
                                check2 = req.create_project(proj_name, proj_mana, proj_client);
                            }
                            
                            cr_proj_window.close();
                        }
                    }
                }
                cr_proj_window.clear();
                cr_proj_window.draw(cr_proj_bckrnd);
                title_txt.drawTo(cr_proj_window);
                title_tbox.drawTo(cr_proj_window);
                manager_txt.drawTo(cr_proj_window);
                manager_tbox.drawTo(cr_proj_window);
                client_txt.drawTo(cr_proj_window);
                client_tbox.drawTo(cr_proj_window);
                create_btn.drawTo(cr_proj_window);
                cr_proj_window.display();
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

                // // split description and title
                std::string input = proj.getText();
                auto it = find(req.assigned_projects.begin(), req.assigned_projects.end(), input);
                if (it != req.assigned_projects.end()){
                    int index = it - req.assigned_projects.begin();
                    std::cout << index << std::endl;
                    proj_sel = index;
                }

                delete projectWindow;
                projectWindow = new ProjectWindow(mainWindow->f, req, proj_sel);

                project_screen = true;
                main_screen = false;
            }
        }
    }
}