#include "GameView.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

extern double cursor_x, cursor_y;
extern bool LeftButtonPressed;

extern GLFWwindow *window;

extern bool shouldswap;

extern std::vector<glm::vec4> areas_to_check;
extern int button_id;
extern bool render_in_game;

std::map<int , Button*> People_select_button_map;
std::map<int , Button*> Weapon_select_button_map;
std::map<int , Button*> Map_select_button_map;
std::map<int , Button*> Prop_select_button_map;

std::map<int, static_Player*> players_to_select;
int player_id;
int map_id;
int weapon_id;
int prop_id;

void GameView::Render()
{
    if (game->State == GAME_ACTIVE)
    {
        static bool blood_change = true;
        static int blood = -1;
        if(blood != game->Player->current_health)
        {
            blood_change = true;
            blood = game->Player->current_health;
        }
        else
        {
            blood_change = false;
        }
        areas_to_check.clear();
        render_in_game = true;
        shouldswap = true;
        // 每次渲染必须reset相机位置, scale是缩放的比例
        float scale = 0.5;
        Utility::ResetCamera(game->Player->Position, glm::vec2(game->Width / 2.0f, game->Height / 2.0f), scale);
        // std::cout<<Player->Position.x<<" "<<Player->Position.y<<std::endl;
        // std::cout<<Width<<" "<<Height<<std::endl;
        // draw background
        Utility::DrawBackground();
        if(game->Player->Destroyed){
            game->Player->Destroyed--;
            game->Player->Draw(glm::vec3(255, 255, 255));
        }
        else    game->Player->Draw();

        game->Player->the_weapon->Draw();

        for (auto it = game->Enemy.begin(); it != game->Enemy.end(); it++) {
            if ((*it)->Destroyed) {
                (*it)->Destroyed--;
                (*it)->Draw(glm::vec3(255, 255, 255));
            } else (*it)->Draw();
        }
        int posx, posy;
        posx = game->Player->Position.x;
        posy = game->Player->Position.y;

        // std::cout<<"player pos: "<<posx<<" "<<posy<<std::endl;

        Button ExitGame( posx-0.3*WINDOW_WIDTH/scale, posy - 0.4*WINDOW_HEIGHT/scale, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Exit"));
        ExitGame.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        // std::cout<<"ExitGame pos: "<<ExitGame.x<<" "<<ExitGame.y<<std::endl;

        Button PauseGame(-0.3*WINDOW_WIDTH/scale + posx, -0.3*WINDOW_HEIGHT/scale + posy, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Pause"));
        PauseGame.DrawButton(cursor_x, cursor_y, LeftButtonPressed);

        areas_to_check.push_back(glm::vec4(scale* (ExitGame.x-posx)+0.5*WINDOW_WIDTH, scale*(ExitGame.y-posy)+0.5*WINDOW_HEIGHT, scale * (ExitGame.x+ExitGame.width-posx)+0.5*WINDOW_WIDTH,  scale * (ExitGame.y+ExitGame.height-posy)+0.5*WINDOW_HEIGHT));
        areas_to_check.push_back(glm::vec4(scale* (PauseGame.x-posx)+0.5*WINDOW_WIDTH, scale*(PauseGame.y-posy)+0.5*WINDOW_HEIGHT, scale * (PauseGame.x+PauseGame.width-posx)+0.5*WINDOW_WIDTH,  scale * (PauseGame.y+PauseGame.height-posy)+0.5*WINDOW_HEIGHT));

        if(button_id == 0)
        {
            game->State = GAME_OVER;
            ExitGame.pressed = false;
        }
        if(button_id == 1)
        {
            game->State = GAME_PAUSE;
            PauseGame.pressed = false;
        }

        ValLine BloodLine(0.1*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, posx, posy-10, game->Player->current_health, game->Player->max_health, glm::vec3(255,0,0), glm::vec3(128,128,128));
        BloodLine.Render(blood_change);

    }


    if (game->State == GAME_START_MENU) 
    {
        game->State = GAME_ACTIVE;
        std::cout<<"In func GAME_START_MENU"<<std::endl;
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

        Button start_button(game->Width * 0.45, game->Height * 0.9, game->Width * 0.1, game->Height * 0.05, std::string("StartM start"));
        Button exit_button(game->Width * 0.1, game->Height * 0.1, game->Width * 0.1, game->Height * 0.1, std::string("StartM exit"));
        Button setting_button(game->Width * 0.9, game->Height * 0.1, game->Width * 0.1, game->Height * 0.1, std::string("StartM setting"));


        start_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        exit_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        setting_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);

        areas_to_check.push_back(glm::vec4(start_button.x, start_button.y, start_button.width, start_button.height));
        areas_to_check.push_back(glm::vec4(exit_button.x, exit_button.y, exit_button.width, exit_button.height));
        areas_to_check.push_back(glm::vec4(setting_button.x, setting_button.y, setting_button.width, setting_button.height));

        if(start_button.pressed)
        {
            game->State = GAME_SELECT_MENU;
            areas_to_check.clear();
        }

        if(exit_button.pressed)
        {
            glfwSetWindowShouldClose(window, true);
            glfwTerminate();
        }

        if(setting_button.pressed)
        {
            game->State = GAME_SETTING_MENU;
            areas_to_check.clear();
        }
        shouldswap = false;

    }

    if(game->State == GAME_SETTING_MENU)
    {
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));
    }

    if(game->State == GAME_SELECT_MENU)
    {
        std::cout<<"In func GAME_SELECT_MENU"<<std::endl;
//        mciSendString("stop mp3", NULL, 0, NULL);
//        mciSendString(TEXT("open ../bgm/bgm_forest.mp3 alias mp3"), 0, 0, 0);
//        mciSendString(TEXT("play mp3 repeat"), 0, 0, 0);

        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

        bool People_select;
        bool Weapon_select;
        bool Map_select;
        bool Prop_select;
        bool Start_game;

        Button *People_select_button;
        Button *Weapon_select_button;
        Button *Map_select_button;
        Button *Prop_select_button;
        Button *Start_game_button;

        People_select = false;
        Weapon_select = false;
        Map_select = false;
        Prop_select = false;
        Start_game = false;

        std::string p_s_b = "People select";
        std::string w_s_b = "Weapon select";
        std::string m_s_b = "Map select";
        std::string pro_s_b = "Prop select";
        std::string s_g_b = "Start game";

        std::string empty = " ";

        People_select_button = new Button(0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT,p_s_b);
        Weapon_select_button = new Button(0.1*WINDOW_WIDTH, 0.2*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT,w_s_b);
        Map_select_button = new Button(0.1*WINDOW_WIDTH, 0.3*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT,m_s_b);
        Prop_select_button = new Button(0.1*WINDOW_WIDTH, 0.4*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT,pro_s_b);
        Start_game_button = new Button(0.9*WINDOW_WIDTH, 0.9*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT,s_g_b);

        People_select_button->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        Weapon_select_button->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        Map_select_button->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        Prop_select_button->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        Start_game_button->DrawButton(cursor_x, cursor_y, LeftButtonPressed);

        areas_to_check.push_back(glm::vec4(People_select_button->x, People_select_button->y, People_select_button->width, People_select_button->height));
        areas_to_check.push_back(glm::vec4(Weapon_select_button->x, Weapon_select_button->y, Weapon_select_button->width, Weapon_select_button->height));
        areas_to_check.push_back(glm::vec4(Map_select_button->x, Map_select_button->y, Map_select_button->width, Map_select_button->height));
        areas_to_check.push_back(glm::vec4(Prop_select_button->x, Prop_select_button->y, Prop_select_button->width, Prop_select_button->height));
        areas_to_check.push_back(glm::vec4(Start_game_button->x, Start_game_button->y, Start_game_button->width, Start_game_button->height));

        if(People_select_button->pressed)
        {
            game->State = GAME_PEOPLE_SELECT;
            shouldswap = true;
        }
        if(Weapon_select_button->pressed)
        {
            Weapon_select = true;
            People_select = false;
            Map_select = false;
            Prop_select = false;

        }
        if(Map_select_button->pressed)
        {
            Map_select = true;
            People_select = false;
            Weapon_select = false;
            Prop_select = false;
        }
        if(Prop_select_button->pressed)
        {
            Prop_select = true;
            People_select = false;
            Weapon_select = false;
            Map_select = false;
        }
        if(Start_game_button->pressed)
        {
            Start_game = true;
            game->State = GAME_ACTIVE;
        }

        shouldswap = false;

    }

    if(game->State == GAME_OVER)
    {
        std::cout<<"In func GAME_OVER"<<std::endl;
//        mciSendString("stop mp3", NULL, 0, NULL);
//        mciSendString("close mp3", NULL, 0, NULL);

        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

        Button start_button(game->Width * 0.4, game->Height * 0.4, game->Width * 0.2, game->Height * 0.1, std::string("GAME OVER!"));
        start_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        if (start_button.pressed)
        {
            game->State = GAME_START_MENU;
            start_button.pressed = false;
        }

        for (auto it = game->Exp.begin(); it != game->Exp.end(); it++) {
            (*it)->Draw();
        }
    }

    if(game->State == GAME_PEOPLE_SELECT)
    {
        static bool selected = false;


        areas_to_check.clear();
        players_to_select[0] = new static_Player(std::string("Alan"), 100, 200, 100, 100, 50);
        players_to_select[1] = new static_Player(std::string("Tom"), 200, 100, 50, 60, 100);
        players_to_select[2] = new static_Player(std::string("Tony"), 150, 130, 40, 50,100);
        players_to_select[3] = new static_Player(std::string("Mary"), 100, 200, 30, 40, 20);

        Utility::ClearBckGnd(std::string("StartMenu"));
        Utility::generateBackgroundColorTexture(0.85*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.60*WINDOW_HEIGHT, 128, 128, 128, true);
        std::cout<<"In func RenderPeopleSelect after bckgnd"<<std::endl;
        std::map<int, std::string> People_select_texts;
        People_select_texts[0] = "Name ";
        People_select_texts[1] = "HP ";
        People_select_texts[2] = "MP ";
        People_select_texts[3] = "ATK ";


        std::map<int, TextBox*> People_select_TextBoxes;
        std::map<int, TextBox*> People_select_Changing_Boxes;

        for(int i = 0; i < 4; i++)
        {
            People_select_TextBoxes[i] = new TextBox(0.86*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            People_select_TextBoxes[i]->Render();
            std::cout<<"In func RenderPeopleSelect after TextBox"<<std::endl;
        }


        for(int i = 0; i < 4; i++)
        {
            std::string tmp_name = players_to_select[i]->name;
            People_select_button_map[i] = new Button(0.25*((i % 2) + 1)*WINDOW_WIDTH, 0.25*((i / 2) + 1)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp_name);
            People_select_button_map[i]->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
            areas_to_check.push_back(glm::vec4(People_select_button_map[i]->x, People_select_button_map[i]->y, People_select_button_map[i]->width, People_select_button_map[i]->height));

            std::cout<<"In func RenderPeopleSelect after Button"<<std::endl;
        }

        for(int i = 0; i < 4; i++)
        {
            People_select_Changing_Boxes[i] = new TextBox(0.91*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            if(button_id != MAX_INT && button_id != 4) {
                player_id = button_id;

                if(i == 0)
                People_select_Changing_Boxes[0]->setText(players_to_select[button_id]->name);
                if(i == 1)
                People_select_Changing_Boxes[1]->setText(std::to_string(players_to_select[button_id]->max_health));
                if(i == 2)
                People_select_Changing_Boxes[2]->setText(std::to_string(players_to_select[button_id]->attack));
                if(i == 3)
                People_select_Changing_Boxes[3]->setText(std::to_string(players_to_select[button_id]->speed));
            }
            People_select_Changing_Boxes[i]->Render();
        }

        Button Confirm(0.9*WINDOW_WIDTH, 0.9*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Confirm"));
        Confirm.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        areas_to_check.push_back(glm::vec4(Confirm.x, Confirm.y, Confirm.width, Confirm.height));

        if(button_id == 4) {

            areas_to_check.clear();
            button_id = MAX_INT;
            game->State = GAME_WEAPON_SELECT;
            
        }
        shouldswap = false;
        

    }

    if(game->State == GAME_WEAPON_SELECT)
    {
        //static bool selected = false;
        std::cout<<"In func GAME_WEAPON_SELECT"<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;

        areas_to_check.clear();
        players_to_select[0] = new static_Player(std::string("Alan"), 100, 200, 100, 100, 50);
        players_to_select[1] = new static_Player(std::string("Tom"), 200, 100, 50, 60, 100);
        players_to_select[2] = new static_Player(std::string("Tony"), 150, 130, 40, 50,100);
        players_to_select[3] = new static_Player(std::string("Mary"), 100, 200, 30, 40, 20);

        Utility::ClearBckGnd(std::string("StartMenu"));
        Utility::generateBackgroundColorTexture(0.85*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.60*WINDOW_HEIGHT, 128, 128, 128, true);
 
        std::map<int, std::string> People_select_texts;
        People_select_texts[0] = "Type ";
        People_select_texts[1] = "Power ";
        People_select_texts[2] = "MPadd ";
        People_select_texts[3] = "ATK ";


        std::map<int, TextBox*> People_select_TextBoxes;
        std::map<int, TextBox*> People_select_Changing_Boxes;

        for(int i = 0; i < 4; i++)
        {
            People_select_TextBoxes[i] = new TextBox(0.86*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            People_select_TextBoxes[i]->Render();
  
        }


        for(int i = 0; i < 4; i++)
        {
            std::string tmp_name = players_to_select[i]->name;
            People_select_button_map[i] = new Button(0.25*((i % 2) + 1)*WINDOW_WIDTH, 0.25*((i / 2) + 1)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp_name);
            People_select_button_map[i]->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
            areas_to_check.push_back(glm::vec4(People_select_button_map[i]->x, People_select_button_map[i]->y, People_select_button_map[i]->width, People_select_button_map[i]->height));

        
        }

        for(int i = 0; i < 4; i++)
        {
            People_select_Changing_Boxes[i] = new TextBox(0.91*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            if(button_id != MAX_INT && button_id != 4) {
                player_id = button_id;

                if(i == 0)
                People_select_Changing_Boxes[0]->setText(players_to_select[button_id]->name);
                if(i == 1)
                People_select_Changing_Boxes[1]->setText(std::to_string(players_to_select[button_id]->max_health));
                if(i == 2)
                People_select_Changing_Boxes[2]->setText(std::to_string(players_to_select[button_id]->attack));
                if(i == 3)
                People_select_Changing_Boxes[3]->setText(std::to_string(players_to_select[button_id]->speed));
            }
            People_select_Changing_Boxes[i]->Render();
        }

        Button Confirm(0.9*WINDOW_WIDTH, 0.9*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Confirm"));
        Confirm.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        areas_to_check.push_back(glm::vec4(Confirm.x, Confirm.y, Confirm.width, Confirm.height));

        if(button_id == 4) {

            game->State = GAME_MAP_SELECT;
            areas_to_check.clear();
            button_id = MAX_INT;
        }
        
        shouldswap = false;
    }
    if(game->State == GAME_MAP_SELECT)
    {
        std::cout<<"In func GAME_MAP_SELECT"<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;

        areas_to_check.clear();
        players_to_select[0] = new static_Player(std::string("Alan"), 100, 200, 100, 100, 50);
        players_to_select[1] = new static_Player(std::string("Tom"), 200, 100, 50, 60, 100);
        players_to_select[2] = new static_Player(std::string("Tony"), 150, 130, 40, 50,100);
        players_to_select[3] = new static_Player(std::string("Mary"), 100, 200, 30, 40, 20);

        Utility::ClearBckGnd(std::string("StartMenu"));
        Utility::generateBackgroundColorTexture(0.85*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.60*WINDOW_HEIGHT, 128, 128, 128, true);
 
        std::map<int, std::string> People_select_texts;
        People_select_texts[0] = "Type ";
        People_select_texts[1] = "Power ";
        People_select_texts[2] = "MPadd ";
        People_select_texts[3] = "ATK ";


        std::map<int, TextBox*> People_select_TextBoxes;
        std::map<int, TextBox*> People_select_Changing_Boxes;

        for(int i = 0; i < 4; i++)
        {
            People_select_TextBoxes[i] = new TextBox(0.86*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            People_select_TextBoxes[i]->Render();
  
        }


        for(int i = 0; i < 4; i++)
        {
            std::string tmp_name = players_to_select[i]->name;
            People_select_button_map[i] = new Button(0.25*((i % 2) + 1)*WINDOW_WIDTH, 0.25*((i / 2) + 1)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp_name);
            People_select_button_map[i]->DrawButton(cursor_x, cursor_y, LeftButtonPressed);
            areas_to_check.push_back(glm::vec4(People_select_button_map[i]->x, People_select_button_map[i]->y, People_select_button_map[i]->width, People_select_button_map[i]->height));

        
        }

        for(int i = 0; i < 4; i++)
        {
            People_select_Changing_Boxes[i] = new TextBox(0.91*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            if(button_id != MAX_INT && button_id != 4) {
                player_id = button_id;

                if(i == 0)
                People_select_Changing_Boxes[0]->setText(players_to_select[button_id]->name);
                if(i == 1)
                People_select_Changing_Boxes[1]->setText(std::to_string(players_to_select[button_id]->max_health));
                if(i == 2)
                People_select_Changing_Boxes[2]->setText(std::to_string(players_to_select[button_id]->attack));
                if(i == 3)
                People_select_Changing_Boxes[3]->setText(std::to_string(players_to_select[button_id]->speed));
            }
            People_select_Changing_Boxes[i]->Render();
        }

        Button Confirm(0.9*WINDOW_WIDTH, 0.9*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Confirm"));
        Confirm.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        areas_to_check.push_back(glm::vec4(Confirm.x, Confirm.y, Confirm.width, Confirm.height));

        if(button_id == 4) {

            game->State = GAME_ACTIVE;
            areas_to_check.clear();
            button_id = MAX_INT;
        }
        
        shouldswap = false;
        if(game->State == GAME_ACTIVE)
            shouldswap = true;

    }

    if(game->State == GAME_PAUSE)
    {
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

        Button start_button(game->Width * 0.4, game->Height * 0.4, game->Width * 0.2, game->Height * 0.1, std::string("GAME PAUSE!"));
        start_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        if (start_button.pressed)
        {
            game->State = GAME_ACTIVE;
            start_button.pressed = false;
        }
    }

}