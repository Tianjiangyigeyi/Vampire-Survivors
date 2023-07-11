#include "GameView.h"

extern double cursor_x, cursor_y;
extern bool LeftButtonPressed;

extern GLFWwindow *window;

std::map<int , Button*> People_select_button_map;
std::map<int , Button*> Weapon_select_button_map;
std::map<int , Button*> Map_select_button_map;
std::map<int , Button*> Prop_select_button_map;



void GameView::ProcessInput(float dt)
{
    if (game->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        glm::vec2 dir = glm::vec2(0.0f, 0.0f);
        // move playerboard
        if (game->Keys[GLFW_KEY_A])
        {
            if (game->Player->Position.x >= 0.0f)
                dir.x -= 1;
        }
        if (game->Keys[GLFW_KEY_D])
        {
            if (game->Player->Position.x <= game->BG_Width - ResourceManager::GetTexture(game->Player->Sprite).Width)
                dir.x += 1;
        }
        if (game->Keys[GLFW_KEY_W])
        {
            if (game->Player->Position.y >= 0.0f)
                dir.y -= 1;
        }
        if (game->Keys[GLFW_KEY_S])
        {
            if (game->Player->Position.y <= game->BG_Height - ResourceManager::GetTexture(game->Player->Sprite).Height)
                dir.y += 1;
        }
        if (dir != glm::vec2(0.0f, 0.0f))
        {
            dir = glm::normalize(dir) * velocity;
        }
        // TODO : 这里最好用notification实现函数的调用，具体的操作暂时还不会
        game->Player->Move(dir);
        game->Player->the_weapon->Move(dir);
    }
}

void GameView::Render()
{
    if (game->State == GAME_ACTIVE)
    {
        // 每次渲染必须reset相机位置, scale是缩放的比例
        float scale = 0.5;
        Utility::ResetCamera(game->Player->Position, glm::vec2(game->Width / 2.0f, game->Height / 2.0f), scale);
        // std::cout<<Player->Position.x<<" "<<Player->Position.y<<std::endl;
        // std::cout<<Width<<" "<<Height<<std::endl;
        // draw background
        Utility::DrawBackground();
        game->Player->Draw();
        game->Player->the_weapon->Draw();
        for (auto it = game->Enemy.begin(); it != game->Enemy.end(); it++)
            (*it)->Draw();
    }


    if (game->State == GAME_START_MENU)
    {
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));

        Button start_button(game->Width * 0.45, game->Height * 0.9, game->Width * 0.1, game->Height * 0.05, std::string("StartM start"));
        Button exit_button(game->Width * 0.1, game->Height * 0.1, game->Width * 0.1, game->Height * 0.1, std::string("StartM exit"));
        Button setting_button(game->Width * 0.9, game->Height * 0.1, game->Width * 0.1, game->Height * 0.1, std::string("StartM setting"));


        start_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        exit_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);
        setting_button.DrawButton(cursor_x, cursor_y, LeftButtonPressed);

        if(start_button.pressed)
        {
            game->State = GAME_SELECT_MENU;
        }

        if(exit_button.pressed)
        {
            glfwSetWindowShouldClose(window, true);
            glfwTerminate();
        }

        if(setting_button.pressed)
        {
            game->State = GAME_SETTING_MENU;
        }


    }

    if(game->State == GAME_SETTING_MENU)
    {
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"));
    }

    if(game->State == GAME_SELECT_MENU)
    {
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

        if(People_select_button->pressed)
        {
            People_select = true;
            Weapon_select = false;
            Map_select = false;
            Prop_select = false;
            SelectMenu::RenderPeopleSelect(cursor_x, cursor_y, LeftButtonPressed);
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

    }

}

void SelectMenu::RenderPeopleSelect(double x, double y, bool button_left)
{
    std::string tmp = "temp";
    for(int i = 1; i <= 20; i++)
        {
            People_select_button_map[i] = new Button(0.12*(i % 5)*WINDOW_WIDTH, 0.12*(i / 5)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp);
            People_select_button_map[i]->DrawButton(x, y, button_left);
        }
}

void SelectMenu::RenderWeaponSelect(double x, double y, bool button_left)
{
    std::string tmp = "temp";
    for(int i = 1; i <= 20; i++)
        {
            Weapon_select_button_map[i] = new Button(0.12*(i % 5)*WINDOW_WIDTH, 0.12*(i / 5)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp);
            Weapon_select_button_map[i]->DrawButton(x, y, button_left);
        }

}

void SelectMenu::RenderMapSelect(double x, double y, bool button_left)
{
    std::string tmp = "temp";
    for(int i = 1; i <= 20; i++)
        {
            Map_select_button_map[i] = new Button(0.12*(i % 5)*WINDOW_WIDTH, 0.12*(i / 5)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp);
            Map_select_button_map[i]->DrawButton(x, y, button_left);
        }

}

void SelectMenu::RenderPropSelect(double x, double y, bool button_left)
{
    std::string tmp = "temp";
    for(int i = 1; i <= 20; i++)
        {
            Prop_select_button_map[i] = new Button(0.12*(i % 5)*WINDOW_WIDTH, 0.12*(i / 5)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp);
            Prop_select_button_map[i]->DrawButton(x, y, button_left);
        }

}