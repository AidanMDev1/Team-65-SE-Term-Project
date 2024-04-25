#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "request.h"

class TimesWindow {
public:
    bool signed_in2;
    sf::Font f;
    sf::Texture back_img;
    sf::Sprite back_btn;
    sf::Texture pgdown_img;
    sf::Sprite time_pgdown_btn;
    sf::Texture pgup_img;
    sf::Sprite time_pgup_btn;
    sf::Sprite spcfc_pgdown_btn;
    sf::Sprite spcfc_pgup_btn;
    sf::Sprite emp_pgdown_btn;
    sf::Sprite emp_pgup_btn;
    Button sign_out_btn;
    Button time_logs_txt;
    sf::RectangleShape time_bckgrnd;
    Button employee_txt;
    Button employee_btn;
    sf::RectangleShape employee_bckgrnd;
    Button alternate_btn;
    Button specific_txt;
    Button specify_btn;
    sf::RectangleShape specific_bckgrnd;
    std::vector<Button> lo_times;
    std::vector<Button> lo_projects;
    std::vector<Button> lo_employees;
    std::string chosen_user;
    std::string chosen_project;
    int time_paging_num; // max displayed at a time 6
    int proj_paging_num; // max displayed at a time 10
    int employee_paging_num; // max displayed at a time 4
    
    TimesWindow() { }
    TimesWindow(sf::Font& font, request& req, bool s, std::string& cho_project, std::string& cho_user) {
        time_paging_num = 0;
        proj_paging_num = 0;
        employee_paging_num = 0;
        f = font;
        signed_in2 = s;
        chosen_project = cho_project;
        chosen_user = cho_user;
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

        employee_btn = Button("Who?", {120, 40}, 15, sf::Color::White, sf::Color::Black);
        employee_btn.setPosition({440, 780});
        employee_btn.setFont(font);

        employee_bckgrnd.setSize({400, 200});
        employee_bckgrnd.setPosition({30, 630});
        employee_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        alternate_btn = Button("Company Times", {350, 50}, 25, sf::Color::White, sf::Color::Black);
        alternate_btn.setPosition({500, 650});
        alternate_btn.setFont(font);

        specific_txt = Button("Specific Project:", 20, sf::Color(64, 156, 120));
        specific_txt.setPosition({660, 120});
        specific_txt.setFont(font);
    
        specify_btn = Button("Which One?", {150, 40}, 15, sf::Color::White, sf::Color::Black);
        specify_btn.setPosition({670, 560});
        specify_btn.setFont(font);

        specific_bckgrnd.setSize({175, 400});
        specific_bckgrnd.setPosition({660, 150});
        specific_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        if (req.assigned_projects.size() > 0){   //the user has projects, otherwise show nothing on the timetables
            if (chosen_project == ""){      //base case initializes to show logged in users first project

                bool check = false;
                check = req.check_time(req.username, req.assigned_projects[0]); 
                if (check){                 //checks if user has time logged for this project
                    std::vector<std::string> clockin_times = req.get_clockin(req.username, req.assigned_projects[0]);
                    std::vector<std::string> clockout_times = req.get_clockout(req.username, req.assigned_projects[0]);
                    for (int i = 0; i < clockin_times.size(); i++){
                        Button time = Button(req.username + "-> CI: " + clockin_times[i] + " | CO: " + clockout_times[i], 15, sf::Color(64, 156, 120));
                        time.setPosition({50, 230 + (i * 30)});
                        time.setFont(font);
                        lo_times.push_back(time);
                    }
                }else{
                    std::cout << req.username << " has no time logged for " << req.assigned_projects[0] << endl;
                }
                
                for (int i = 0; i < req.assigned_projects.size();i++){
                    Button proj = Button(req.assigned_projects[i], 20, sf::Color(64, 156, 120));
                    proj.setPosition({680, 200 + (i * 20)});
                    proj.setFont(font);
                    lo_projects.push_back(proj);
                }

                if (req.user_role == "manager" || req.user_role == "admin"){
                    std::vector<std::string> project_members = req.get_project_members(req.assigned_projects[0]);  ///currently hard coded to show members of a admin/managers first project
                    for (int i = 0; i < project_members.size(); i++){
                        Button emp = Button(project_members[i], 20, sf::Color(64, 156, 120));
                        emp.setPosition({50, 680 + (i * 20)});
                        emp.setFont(font);
                        lo_employees.push_back(emp);
                    }
                }
            }
            else if (chosen_project != ""  && chosen_user != ""){ //a project and user have been selected

                bool check = false;
                check = req.check_time(chosen_user, chosen_project); 
                if (check){                 //checks if user has time logged for this project
                    std::vector<std::string> clockin_times = req.get_clockin(chosen_user, chosen_project);
                    std::vector<std::string> clockout_times = req.get_clockout(chosen_user, chosen_project);
                    for (int i = 0; i < clockin_times.size(); i++){
                        Button time = Button(chosen_user + "-> CI: " + clockin_times[i] + " | CO: " + clockout_times[i], 15, sf::Color(64, 156, 120));
                        time.setPosition({50, 230 + (i * 30)});
                        time.setFont(font);
                        lo_times.push_back(time);
                    }
                }else{
                    std::cout << chosen_user << " has no time logged for " << chosen_project << endl;
                }
                
                for (int i = 0; i < req.assigned_projects.size();i++){   ///the projects shown should still be of the user logged in not the chosen user
                    Button proj = Button(req.assigned_projects[i], 20, sf::Color(64, 156, 120));
                    proj.setPosition({680, 200 + (i * 20)});
                    proj.setFont(font);
                    lo_projects.push_back(proj);
                }

                if (req.user_role == "manager" || req.user_role == "admin"){
                    std::vector<std::string> project_members = req.get_project_members(chosen_project);  //shows list of employees on the chosen project
                    for (int i = 0; i < project_members.size(); i++){
                        Button emp = Button(project_members[i], 20, sf::Color(64, 156, 120));
                        emp.setPosition({50, 680 + (i * 20)});
                        emp.setFont(font);
                        lo_employees.push_back(emp);
                    }
                }
            }
            else{ //only a project was selected
                bool check = false;
                check = req.check_time(req.username, chosen_project); 
                if (check){                 //checks if user has time logged for this project
                    std::vector<std::string> clockin_times = req.get_clockin(req.username, chosen_project);
                    std::vector<std::string> clockout_times = req.get_clockout(req.username, chosen_project);
                    for (int i = 0; i < clockin_times.size(); i++){
                        Button time = Button(req.username + "-> CI: " + clockin_times[i] + " | CO: " + clockout_times[i], 15, sf::Color(64, 156, 120));
                        time.setPosition({50, 230 + (i * 30)});
                        time.setFont(font);
                        lo_times.push_back(time);
                    }
                }else{
                    std::cout << req.username << " has no time logged for " << chosen_project << endl;
                }
                
                for (int i = 0; i < req.assigned_projects.size();i++){   
                    Button proj = Button(req.assigned_projects[i], 20, sf::Color(64, 156, 120));
                    proj.setPosition({680, 200 + (i * 20)});
                    proj.setFont(font);
                    lo_projects.push_back(proj);
                }

                if (req.user_role == "manager" || req.user_role == "admin"){
                    std::vector<std::string> project_members = req.get_project_members(chosen_project);  //shows list of employees on the chosen project
                    for (int i = 0; i < project_members.size(); i++){
                        Button emp = Button(project_members[i], 20, sf::Color(64, 156, 120));
                        emp.setPosition({50, 680 + (i * 20)});
                        emp.setFont(font);
                        lo_employees.push_back(emp);
                    }
                }
            }
        }
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
        employee_btn.drawTo(window);
        alternate_btn.drawTo(window);
        specific_txt.drawTo(window);
        specify_btn.drawTo(window);

        for (int i = time_paging_num; i < lo_times.size(); i++) {
            if (i < time_paging_num + 6) {
                lo_times.at(i).drawTo(window);
            }
        }
        for (int i = proj_paging_num; i < lo_projects.size(); i++) {
            if (i < proj_paging_num + 10) {
                lo_projects.at(i).drawTo(window);
            }
        }
        for (int i = employee_paging_num; i < lo_employees.size(); i++) {
            if (i < employee_paging_num + 4) {
                lo_employees.at(i).drawTo(window);
            }
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


void TimesWindowEvents(sf::RenderWindow& window, TimesWindow* timesWindow, bool& login_screen, bool& main_screen, bool& time_logs_screen, sf::Event& e, request& req, std::string& chosen_project, std::string& chosen_user) {
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
        if (timesWindow->specify_btn.isMouseOver(window)) {
            timesWindow->specify_btn.setBackColor(sf::Color(64, 156, 120));
            timesWindow->specify_btn.setTextColor(sf::Color::White);
        }
        else {
            timesWindow->specify_btn.setBackColor(sf::Color::White);
            timesWindow->specify_btn.setTextColor(sf::Color::Black);
        }
        if (timesWindow->employee_btn.isMouseOver(window)) {
            timesWindow->employee_btn.setBackColor(sf::Color(64, 156, 120));
            timesWindow->employee_btn.setTextColor(sf::Color::White);
        }
        else {
            timesWindow->employee_btn.setBackColor(sf::Color::White);
            timesWindow->employee_btn.setTextColor(sf::Color::Black);
        }
    }

    // action on click for buttons
    if (e.type == sf::Event::MouseButtonPressed) {
        if (timesWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            login_screen = true;
            time_logs_screen = false;
        }
        if (timesWindow->alternate_btn.isMouseOver(window) && (req.user_role == "manager" || req.user_role == "admin")) {
            if (timesWindow->alternate_btn.getText() == "Company Times") {
                timesWindow->alternate_btn.setText("Personal Times");
            }
            else {
                timesWindow->alternate_btn.setText("Company Times");
            }
        }
        if (timesWindow->employee_btn.isMouseOver(window) && (req.user_role == "manager" || req.user_role == "admin")) {
            sf::RectangleShape emp_bckrnd;
            emp_bckrnd.setSize({600, 400});
            emp_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button emp_txt = Button("Employee:", 15, sf::Color(64, 156, 120));
            emp_txt.setPosition({30, 30});
            emp_txt.setFont(timesWindow->f);

            Textbox emp_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            emp_tbox.setFont(timesWindow->f);
            emp_tbox.setPosition({150, 30});

            Button choose_btn = Button("Choose", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            choose_btn.setPosition({100, 200});
            choose_btn.setFont(timesWindow->f);

            sf::RenderWindow emp_window(sf::VideoMode(600, 400), "Choose Employee", sf::Style::Titlebar | sf::Style::Close);

            while (emp_window.isOpen()) {
                sf::Event emp_event;

                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    emp_tbox.setSelected(false);
                }

                while (emp_window.pollEvent(emp_event)) {
                    if (emp_event.type == sf::Event::Closed) {
                        emp_window.close();
                    }

                    if (emp_event.type == sf::Event::TextEntered) {
                        if (emp_tbox.isSelected()) {
                            emp_tbox.typeOn(emp_event);
                        }
                    }

                    if (emp_event.type == sf::Event::MouseMoved) {
                        if (choose_btn.isMouseOver(emp_window)) {
                            choose_btn.setBackColor(sf::Color(64, 156, 120));
                            choose_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            choose_btn.setBackColor(sf::Color::White);
                            choose_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (emp_event.type == sf::Event::MouseButtonPressed) {
                        if (emp_tbox.isMouseOver(emp_window)) {
                            emp_tbox.setSelected(true);
                        }
                        else {
                            emp_tbox.setSelected(false);
                        }

                        if (choose_btn.isMouseOver(emp_window)) {
                            std::cout << emp_tbox.getText() << " Chosen" << std::endl;
                        
                            bool check = false;
                            check = req.check_user_project(emp_tbox.getText(), chosen_project);
                            if(check){
                                chosen_user = emp_tbox.getText();
                            }else{
                                std::cout << emp_tbox.getText() << " is not a valid employee choice" << endl;
                            }
                            emp_window.close();
                        }
                    }
                }
                emp_window.clear();
                emp_window.draw(emp_bckrnd);
                emp_txt.drawTo(emp_window);
                emp_tbox.drawTo(emp_window);
                choose_btn.drawTo(emp_window);
                emp_window.display();
            }
        }

        if (timesWindow->specify_btn.isMouseOver(window) && (req.user_role == "manager" || req.user_role == "admin")) {
            sf::RectangleShape spec_bckrnd;
            spec_bckrnd.setSize({600, 400});
            spec_bckrnd.setFillColor(sf::Color(230, 230, 230)); // GREY

            Button spec_txt = Button("Project:", 15, sf::Color(64, 156, 120));
            spec_txt.setPosition({30, 30});
            spec_txt.setFont(timesWindow->f);

            Textbox spec_tbox = Textbox(15, {400, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
            spec_tbox.setFont(timesWindow->f);
            spec_tbox.setPosition({150, 30});

            Button choose_btn = Button("Choose", {100, 50}, 15, sf::Color::White, sf::Color::Black);
            choose_btn.setPosition({100, 200});
            choose_btn.setFont(timesWindow->f);

            sf::RenderWindow spec_window(sf::VideoMode(600, 400), "Specify Project", sf::Style::Titlebar | sf::Style::Close);

            while (spec_window.isOpen()) {
                sf::Event spec_event;

                // Key Presses and Info
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    spec_tbox.setSelected(false);
                }

                while (spec_window.pollEvent(spec_event)) {
                    if (spec_event.type == sf::Event::Closed) {
                        spec_window.close();
                    }

                    if (spec_event.type == sf::Event::TextEntered) {
                        if (spec_tbox.isSelected()) {
                            spec_tbox.typeOn(spec_event);
                        }
                    }

                    if (spec_event.type == sf::Event::MouseMoved) {
                        if (choose_btn.isMouseOver(spec_window)) {
                            choose_btn.setBackColor(sf::Color(64, 156, 120));
                            choose_btn.setTextColor(sf::Color::White);
                        }
                        else {
                            choose_btn.setBackColor(sf::Color::White);
                            choose_btn.setTextColor(sf::Color::Black);
                        }
                    }

                    if (spec_event.type == sf::Event::MouseButtonPressed) {
                        if (spec_tbox.isMouseOver(spec_window)) {
                            spec_tbox.setSelected(true);
                        }
                        else {
                            spec_tbox.setSelected(false);
                        }

                        if (choose_btn.isMouseOver(spec_window)) {
                            std::cout << spec_tbox.getText() << " Chosen" << std::endl;
                            
                            bool check = false;
                            check = req.check_project(spec_tbox.getText());
                            if(check){
                                chosen_project = spec_tbox.getText();
                            }else{
                                std::cout << spec_tbox.getText() << " is not a valid project choice";
                            }
                            spec_window.close();
                        }
                    }
                }
                spec_window.clear();
                spec_window.draw(spec_bckrnd);
                spec_txt.drawTo(spec_window);
                spec_tbox.drawTo(spec_window);
                choose_btn.drawTo(spec_window);
                spec_window.display();
            }
        }
        if (timesWindow->isMouseOverBack(window)) {
            std::cout << "-> Main Screen" << std::endl;
            main_screen = true;
            time_logs_screen = false;
        }
        if (timesWindow->isMouseOverTimePU(window)) {
            std::cout << "Time page up" << std::endl;
            timesWindow->time_paging_num-=6;
            if (timesWindow->time_paging_num <= 0) {
                timesWindow->time_paging_num+=6;
            }
        }       
        if (timesWindow->isMouseOverTimePD(window)) {
            std::cout << "Time page down" << std::endl;
            timesWindow->time_paging_num+=6;
            if (timesWindow->time_paging_num >= timesWindow->lo_times.size()) {
                timesWindow->time_paging_num-=6;
            }
        }
        if (timesWindow->isMouseOverEmpPU(window)) {
            std::cout << "Employee page up" << std::endl;
            timesWindow->employee_paging_num-=4;
            if (timesWindow->employee_paging_num <= 0) {
                timesWindow->employee_paging_num+=4;
            }
        }
        if (timesWindow->isMouseOverEmpPD(window)) {
            std::cout << "Employee page down" << std::endl;
            timesWindow->employee_paging_num+=4;
            if (timesWindow->employee_paging_num >= timesWindow->lo_employees.size()) {
                timesWindow->employee_paging_num-=4;
            }
        }
        if (timesWindow->isMouseOverSpcPU(window)) {
            std::cout << "Specific page up" << std::endl;
            timesWindow->proj_paging_num-=10;
            if (timesWindow->proj_paging_num <= 0) {
                timesWindow->proj_paging_num+=10;
            }
        }
        if (timesWindow->isMouseOverSpcPD(window)) {
            std::cout << "Specific page down" << std::endl;
            timesWindow->proj_paging_num+=10;
            if (timesWindow->proj_paging_num >= timesWindow->lo_projects.size()) {
                timesWindow->proj_paging_num-=10;
            }
        }
    }
}