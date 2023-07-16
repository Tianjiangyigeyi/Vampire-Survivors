#include "GameView.h"

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

extern Renders R;
Voice v;


void GameView::Render()
{
    if (game->State == GAME_ACTIVE)
    {
        
        static bool music_change = true;
        if(music_change) {
            v.stop_play(0, 1);
            v.play(2, 1);
            music_change = false;
        }
    
        static bool render_blood = true;
        static bool render_exp = true;
        static int blood = -1;
        static int exp = -1;
        if(blood != game->Player->current_health)
        {
            //std::cout<<"blood change"<< blood <<game->Player->current_health<<std::endl;
            if(blood > game->Player->current_health)
                v.play(3, 0);
            
 
            render_blood = true;
            blood = game->Player->current_health;
    
        }
        if(exp != game->Player->exp)
        {
            //std::cout<<"exp change"<<std::endl;
            exp = game->Player->exp;
            render_exp = true;
        }
        R.areas_to_check.clear();
        R.shouldswap = true;
        // 每次渲染必须reset相机位置, scale是缩放的比例
        float scale = 0.5;
        Utility::ResetCamera(game->Player->Position, glm::vec2(game->Width / 2.0f, game->Height / 2.0f), scale);

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
        for (auto it = game->Exp.begin(); it != game->Exp.end(); it++) {
            (*it)->Draw();
        }

        int posx, posy;
        posx = game->Player->Position.x;
        posy = game->Player->Position.y;

        // std::cout<<"player pos: "<<posx<<" "<<posy<<std::endl;

        // Button ExitGame( posx-0.3*WINDOW_WIDTH/scale, posy - 0.4*WINDOW_HEIGHT/scale, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Exit"));
        // ExitGame.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed);
        // // std::cout<<"ExitGame pos: "<<ExitGame.x<<" "<<ExitGame.y<<std::endl;

        Button PauseGame(0.4*WINDOW_WIDTH/scale + posx, posy-0.46*WINDOW_HEIGHT/scale, 0.16*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT/scale, std::string("1-3"));
        PauseGame.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        // R.areas_to_check.push_back(glm::vec4(scale* (ExitGame.x-posx)+0.5*WINDOW_WIDTH, scale*(ExitGame.y-posy)+0.5*WINDOW_HEIGHT, scale * (ExitGame.x+ExitGame.width-posx)+0.5*WINDOW_WIDTH,  scale * (ExitGame.y+ExitGame.height-posy)+0.5*WINDOW_HEIGHT));
        R.areas_to_check.push_back(glm::vec4(scale* (PauseGame.x-posx)+0.5*WINDOW_WIDTH, scale*(PauseGame.y-posy)+0.5*WINDOW_HEIGHT, scale * (PauseGame.x+PauseGame.width-posx)+0.5*WINDOW_WIDTH,  scale * (PauseGame.y+PauseGame.height-posy)+0.5*WINDOW_HEIGHT));

        if(R.button_id == 0)
        {
            game->State = GAME_PAUSE;
            R.flush();

        }

        ValLine BloodLine(0.1*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, posx, posy-15, game->Player->current_health, game->Player->max_health, glm::vec3(255,0,0), glm::vec3(128,128,128));
        BloodLine.Render(render_blood, 3);
        render_blood = false;
        // std::cout<<"Exp:"<<game->Player->exp<<std::endl;
        ValLine ExpLine(0.8*WINDOW_WIDTH/scale, 0.05*WINDOW_HEIGHT/scale, posx-0.45*WINDOW_WIDTH/scale, posy-0.45*WINDOW_HEIGHT/scale, game->Player->exp, game->Player->next_exp, glm::vec3(0,0,255), glm::vec3(128,128,128));
        ExpLine.Render(render_exp, 4);
        render_exp = false;
        // std::cout<<"exp: "<<game->Player->exp<<" next_exp: "<<game->Player->next_exp<<std::endl;

        if(game->Player->exp >=  game->Player->next_exp)
            R.flush();
    }

    else if (game->State == GAME_START_MENU) 
    {
        static bool music_change = true;
        if(music_change) {
            v.play(0, 1);
            music_change = false;
        }
        // std::cout<<"------In func GAME_START_MENU-------"<<std::endl;
        R.shouldswap = false;
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("bkg2"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));

        Button start_button(game->Width * 0.4, game->Height * 0.65, game->Width * 0.2, game->Height * 0.1, std::string("1-1"));
        Button exit_button(game->Width * 0.26, game->Height * 0.67, game->Width * 0.1, game->Height * 0.07, std::string("1-2"));
        Button setting_button(game->Width * 0.65, game->Height * 0.01, game->Width * 0.1, game->Height * 0.08, std::string("1-3"));
        Button achieves_button(game->Width * 0.64, game->Height * 0.67, game->Width * 0.1, game->Height * 0.07, std::string("achs"));
        Button credits_button(game->Width * 0.45, game->Height * 0.8, game->Width * 0.1, game->Height * 0.07, std::string("cres"));

        start_button.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        exit_button.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed,true);
        setting_button.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        achieves_button.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        credits_button.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        R.areas_to_check.push_back(glm::vec4(start_button.x, start_button.y, start_button.width, start_button.height));
        R.areas_to_check.push_back(glm::vec4(exit_button.x, exit_button.y, exit_button.width, exit_button.height));
        R.areas_to_check.push_back(glm::vec4(setting_button.x, setting_button.y, setting_button.width, setting_button.height));
        R.areas_to_check.push_back(glm::vec4(achieves_button.x, achieves_button.y, achieves_button.width, achieves_button.height));
        R.areas_to_check.push_back(glm::vec4(credits_button.x, credits_button.y, credits_button.width, credits_button.height));

        R.shouldswap = false;
        if(R.button_id == 2)
        {
            R.flush();
            game->State = GAME_SETTING_MENU;
            //game->State = GAME_OVER;
        }

        if(R.button_id == 1)
        {
            R.shouldswap = true;
            v.~Voice();
            glfwSetWindowShouldClose(R.window, true);
            glfwTerminate();
        }

        if(R.button_id == 0)
        {
            R.flush();
            game->State = GAME_SELECT_MENU;
        }

        if(R.button_id == 4)
        {
            R.flush();
            game->State = GAME_CREDITS;
        }
        
    }

    else if(game->State == GAME_SETTING_MENU)
    {
        Button *Sound, *Music, *VFX, *Vis, *Dam;
        
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("bkg2"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));
        Utility::DrawBackground(std::string("opt"), glm::vec2(WINDOW_WIDTH*0.35, WINDOW_HEIGHT*0.12));

        Button Back(0.25*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT, std::string("1-2"));
        Back.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.sound)
            Sound = new Button(0.55*WINDOW_WIDTH, 0.23*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Sound = new Button(0.55*WINDOW_WIDTH, 0.23*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Sound->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.music)
            Music = new Button(0.55*WINDOW_WIDTH, 0.331*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Music = new Button(0.55*WINDOW_WIDTH, 0.331*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Music->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);  

        if(v.vfx)
            VFX = new Button(0.55*WINDOW_WIDTH, 0.432*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            VFX = new Button(0.55*WINDOW_WIDTH, 0.432*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        VFX->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.vis)
            Vis = new Button(0.55*WINDOW_WIDTH, 0.533*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Vis = new Button(0.55*WINDOW_WIDTH, 0.533*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Vis->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.dam)
            Dam = new Button(0.55*WINDOW_WIDTH, 0.634*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Dam = new Button(0.55*WINDOW_WIDTH, 0.634*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Dam->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);


        R.areas_to_check.push_back(glm::vec4(Back.x, Back.y, Back.width, Back.height));
        R.areas_to_check.push_back(glm::vec4(Sound->x, Sound->y, Sound->width, Sound->height));
        R.areas_to_check.push_back(glm::vec4(Music->x, Music->y, Music->width, Music->height));
        R.areas_to_check.push_back(glm::vec4(VFX->x, VFX->y, VFX->width, VFX->height));
        R.areas_to_check.push_back(glm::vec4(Vis->x, Vis->y, Vis->width, Vis->height));
        R.areas_to_check.push_back(glm::vec4(Dam->x, Dam->y, Dam->width, Dam->height));
    
        
        R.shouldswap = false;
        if(R.button_id == 0) {
            R.flush();
            game->State = GAME_START_MENU;
        }
        if(R.button_id == 1) {
         
            R.flush();
            v.sound = !v.sound;
            
        }
        if(R.button_id == 2) {
        
            R.flush();
            v.music = !v.music;
            if(!v.music) {
                v.stop_play(0, 1);
            }
            else {
                v.play(0, 1);
            
            }
        }
        if(R.button_id == 3) {
 
            R.flush();
            v.vfx = !v.vfx;
        }
        if(R.button_id == 4) {
            R.flush();
            v.vis = !v.vis;
        }
        if(R.button_id == 5) {
            R.flush();
            v.dam = !v.dam;
        }

    }

    else if(game->State == GAME_SELECT_MENU)
    {
        
        std::map<int , Button*> People_select_button_map;
        std::map<int, static_Player*> players_to_select;
        static int player_id = 0;
        // std::cout<<"------In func GAME_SELECT_MENU-------"<<std::endl;
        R.shouldswap = false;
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("b1-2"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));

        switch (player_id){
            case 0:
                Utility::DrawBackground(std::string("Ant-ski"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.65));
                break;
            case 1:
                Utility::DrawBackground(std::string("Arc-ski"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.65));
                break;
            case 2: 
                Utility::DrawBackground(std::string("Gen-ski"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.65));
                break;
            case 3:
                Utility::DrawBackground(std::string("Pas-ski"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.65));
                break;
        }

        players_to_select[0] = new static_Player(std::string("Antonio"), 100, 200, 100, 100, 50);
        players_to_select[1] = new static_Player(std::string("Arca"), 200, 100, 50, 60, 100);
        players_to_select[2] = new static_Player(std::string("Genn"), 150, 130, 40, 50,100);
        players_to_select[3] = new static_Player(std::string("Pasq"), 100, 200, 30, 40, 20);


        for(int i = 0; i < 4; i++)
        {
            std::string tmp_name = "Sel_" + players_to_select[i]->name;
            People_select_button_map[i] = new Button((0.2*((i % 2) + 1) + 0.15)*WINDOW_WIDTH, 0.2*((i / 2) + 1)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.15*WINDOW_HEIGHT, tmp_name);
            People_select_button_map[i]->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
            R.areas_to_check.push_back(glm::vec4(People_select_button_map[i]->x, People_select_button_map[i]->y, People_select_button_map[i]->width, People_select_button_map[i]->height));
        }
  

        Button Confirm(0.4*WINDOW_WIDTH, 0.85*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Confirm_button"));
        Confirm.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        R.areas_to_check.push_back(glm::vec4(Confirm.x, Confirm.y, Confirm.width, Confirm.height));

        Button Back(0.8*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT, std::string("1-2"));
        Back.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        R.areas_to_check.push_back(glm::vec4(Back.x, Back.y, Back.width, Back.height));

        if(R.button_id != MAX_INT && R.button_id != 4 && R.button_id != 5) {
            // std::cout<<"R.button_id: "<<R.button_id<<std::endl;
            R.shouldswap = true;
            player_id = R.button_id;
            R.areas_to_check.clear();
            R.button_id = MAX_INT;
        }

        if(R.button_id == 4) 
        {
            R.flush();
            game->State = GAME_ACTIVE;
            
        }

        if(R.button_id == 5) 
        {
            // std::cout<<"R.button_id == 5"<<std::endl;
            R.flush();
            game->State = GAME_START_MENU;
        }
        
    }

    else if(game->State == GAME_OVER)
    {
        R.shouldswap = false;
        v.stop_play(2, 1);
        v.play(5, 0);

        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));
        Utility::DrawBackground(std::string("bgg"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.35));

        Button start_button(game->Width * 0.4, game->Height * 0.6, game->Width * 0.2, game->Height * 0.1, std::string("quit"));
        start_button.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        R.areas_to_check.push_back(glm::vec4(start_button.x, start_button.y, start_button.width, start_button.height));
        // std::cout<<"R.button_id: "<<R.button_id<<std::endl;
        if (R.button_id == 1)
        {
            // std::cout<<"State from GAME_OVER to GAME_START_MENU"<<std::endl;
            game->State = GAME_RESULT;
            R.flush();
        }

     
    }

    
    else if(game->State == GAME_PAUSE)
    {
        Button *Sound, *Music, *VFX, *Vis, *Dam;
        
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("bkg2"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));
        Utility::DrawBackground(std::string("opt"), glm::vec2(WINDOW_WIDTH*0.35, WINDOW_HEIGHT*0.12));

        Button Back(0.25*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT, std::string("1-2"));
        Back.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.sound)
            Sound = new Button(0.55*WINDOW_WIDTH, 0.23*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Sound = new Button(0.55*WINDOW_WIDTH, 0.23*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Sound->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.music)
            Music = new Button(0.55*WINDOW_WIDTH, 0.331*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Music = new Button(0.55*WINDOW_WIDTH, 0.331*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Music->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);  

        if(v.vfx)
            VFX = new Button(0.55*WINDOW_WIDTH, 0.432*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            VFX = new Button(0.55*WINDOW_WIDTH, 0.432*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        VFX->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.vis)
            Vis = new Button(0.55*WINDOW_WIDTH, 0.533*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Vis = new Button(0.55*WINDOW_WIDTH, 0.533*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Vis->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        if(v.dam)
            Dam = new Button(0.55*WINDOW_WIDTH, 0.634*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("sure"));
        else
            Dam = new Button(0.55*WINDOW_WIDTH, 0.634*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, std::string("not"));
        Dam->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);


        R.areas_to_check.push_back(glm::vec4(Back.x, Back.y, Back.width, Back.height));
        R.areas_to_check.push_back(glm::vec4(Sound->x, Sound->y, Sound->width, Sound->height));
        R.areas_to_check.push_back(glm::vec4(Music->x, Music->y, Music->width, Music->height));
        R.areas_to_check.push_back(glm::vec4(VFX->x, VFX->y, VFX->width, VFX->height));
        R.areas_to_check.push_back(glm::vec4(Vis->x, Vis->y, Vis->width, Vis->height));
        R.areas_to_check.push_back(glm::vec4(Dam->x, Dam->y, Dam->width, Dam->height));
    
        
        R.shouldswap = false;
        if(R.button_id == 0) {
            R.flush();
            game->State = GAME_ACTIVE;
        }
        if(R.button_id == 1) {
         
            R.flush();
            v.sound = !v.sound;
            
        }
        if(R.button_id == 2) {
        
            R.flush();
            v.music = !v.music;
            if(!v.music) {
                v.stop_play(2, 1);
            }
            else {
                v.play(2, 1);
            }
        }
        if(R.button_id == 3) {
 
            R.flush();
            v.vfx = !v.vfx;
        }
        if(R.button_id == 4) {
            R.flush();
            v.vis = !v.vis;
        }
        if(R.button_id == 5) {
            R.flush();
            v.dam = !v.dam;
        }
    }

    else if(game->State == GAME_LEVEL_UP) {
        float cur_health = game->Player->current_health;
        float cur_max_health = game->Player->max_health;
        float cur_might = game->Player->might;
    
        v.stop_play(2, 1);
        v.play(4, 0);

        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("bkg2"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));
        Utility::DrawBackground(std::string("lev-up"), glm::vec2(WINDOW_WIDTH*0.35, WINDOW_HEIGHT*0.11));

        Button Back(0.25*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT, std::string("1-2"));
        Back.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        Button HealthUp(0.37*WINDOW_WIDTH, 0.2*WINDOW_HEIGHT, 0.26*WINDOW_WIDTH, 0.13*WINDOW_HEIGHT, std::string("Hea-up"));
        HealthUp.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        Button SpeedUp(0.37*WINDOW_WIDTH, 0.35*WINDOW_HEIGHT, 0.26*WINDOW_WIDTH, 0.13*WINDOW_HEIGHT, std::string("Spd-up"));
        SpeedUp.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        Button ArmorUp(0.37*WINDOW_WIDTH, 0.5*WINDOW_HEIGHT, 0.26*WINDOW_WIDTH, 0.13*WINDOW_HEIGHT, std::string("Hea-up"));
        ArmorUp.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        Button SpUp(0.37*WINDOW_WIDTH, 0.65*WINDOW_HEIGHT, 0.26*WINDOW_WIDTH, 0.13*WINDOW_HEIGHT, std::string("Spd-up"));
        SpUp.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);


        Button Cfm(0.43*WINDOW_WIDTH, 0.85*WINDOW_HEIGHT, 0.14*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Confirm_button"));
        Cfm.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);

        std::string heal = "Health add by 20";
        std::string spd = "Might add by 20";
        std::string arm = "Armor add by 5";
        std::string sp = "Speed add by 10";

        TextBox Health(0.42*WINDOW_WIDTH, 0.22*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.045*WINDOW_HEIGHT, glm::vec3(127,127,127), heal);
        TextBox Speed(0.42*WINDOW_WIDTH, 0.37*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.045*WINDOW_HEIGHT, glm::vec3(127,127,127), spd);
        TextBox Armor(0.42*WINDOW_WIDTH, 0.52*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.045*WINDOW_HEIGHT, glm::vec3(127,127,127), arm);
        TextBox SpeUp(0.42*WINDOW_WIDTH, 0.67*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.045*WINDOW_HEIGHT, glm::vec3(127,127,127), sp);

        Health.Render();
        Speed.Render();
        Armor.Render();
        SpeUp.Render();

        R.areas_to_check.push_back(glm::vec4(Back.x, Back.y, Back.width, Back.height));
        R.areas_to_check.push_back(glm::vec4(HealthUp.x, HealthUp.y, HealthUp.width, HealthUp.height));
        R.areas_to_check.push_back(glm::vec4(SpeedUp.x, SpeedUp.y, SpeedUp.width, SpeedUp.height));
        R.areas_to_check.push_back(glm::vec4(ArmorUp.x, ArmorUp.y, ArmorUp.width, ArmorUp.height));
        R.areas_to_check.push_back(glm::vec4(SpUp.x, SpUp.y, SpUp.width, SpUp.height));
        R.areas_to_check.push_back(glm::vec4(Cfm.x, Cfm.y, Cfm.width, Cfm.height));

        R.shouldswap = false;
        

        if(R.button_id == 0) {
            v.play(2, 1);
            R.flush();
            game->Player->current_health = cur_health;
            game->Player->max_health = cur_max_health;
            game->Player->might = cur_might;

            game->State = GAME_ACTIVE;
        }

        if(R.button_id == 1 || R.button_id == 2 || R.button_id == 3 || R.button_id == 4) {
            game->Player->Upgrade(R.button_id);
            R.flush();
        }

        if(R.button_id == 5) {
            v.play(2, 1);
            R.flush();
            game->State = GAME_ACTIVE;
        }

    }

    else if(game->State == GAME_CREDITS) 
    {
        R.shouldswap = false;
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));
        Utility::DrawBackground(std::string("bcre"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.12));

        Button Back(0.25*WINDOW_WIDTH, 0.01*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT, std::string("1-2"));
        Back.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        R.areas_to_check.push_back(glm::vec4(Back.x, Back.y, Back.width, Back.height));

        if(R.button_id == 0) {
            R.flush();
            game->State = GAME_START_MENU;
        }

        std::string Infomats = "CREDITS";
        std::string Instructor = "Instructor   Dr Xin Yuan";
        std::string s1 = "S1   Zuoquan Lin";
        std::string s2 = "S2   Shengyuan Huang";
        std::string s3 = "S3   Yang Xie";
        std::string s4 = "S4   Hangqi Li";
        std::string ver = "Version 2";
        TextBox Infos(0.32*WINDOW_WIDTH, 0.13*WINDOW_HEIGHT, 0.11*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, glm::vec3(127,127,127), Infomats);
        TextBox Ins(0.34*WINDOW_WIDTH, 0.2*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.04*WINDOW_HEIGHT, glm::vec3(127,127,127), Instructor);
        TextBox S1(0.34*WINDOW_WIDTH, 0.27*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.04*WINDOW_HEIGHT, glm::vec3(127,127,127), s1);
        TextBox S2(0.34*WINDOW_WIDTH, 0.34*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.04*WINDOW_HEIGHT, glm::vec3(127,127,127), s2);
        TextBox S3(0.34*WINDOW_WIDTH, 0.41*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.04*WINDOW_HEIGHT, glm::vec3(127,127,127), s3);
        TextBox S4(0.34*WINDOW_WIDTH, 0.48*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.04*WINDOW_HEIGHT, glm::vec3(127,127,127), s4);
        TextBox Ver(0.34*WINDOW_WIDTH, 0.6*WINDOW_HEIGHT, 0.11*WINDOW_WIDTH, 0.04*WINDOW_HEIGHT, glm::vec3(127,127,127), ver);
        
        Infos.Render();
        Ins.Render();
        S1.Render();
        S2.Render();
        S3.Render();
        S4.Render();
        Ver.Render();

    }

    else if(game->State == GAME_RESULT)
    {
        Utility::ResetCamera(glm::vec2(game->Width / 2.0f, game->Height / 2.0f), glm::vec2(game->Width / 2.0f, game->Height / 2.0f), 1.0f);
        Utility::DrawBackground(std::string("StartMenu"), glm::vec2(0, WINDOW_HEIGHT*0.1));
        Utility::DrawBackground(std::string("head"));
        Utility::DrawBackground(std::string("result"), glm::vec2(WINDOW_WIDTH*0.3, WINDOW_HEIGHT*0.12));

        Button Done(0.4*WINDOW_WIDTH, 0.85*WINDOW_HEIGHT, 0.2*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("done"));
        Done.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        R.areas_to_check.push_back(glm::vec4(Done.x, Done.y, Done.width, Done.height));

        R.shouldswap = false;
        if(R.button_id == 0) {

            game->Player->current_health = 100;
            game->Player->max_health = 100;
            game->Player->might = 50;

            game->Player->exp = 0;
            game->Player->next_exp = 100;
            R.flush();
            game->State = GAME_START_MENU;
            
        }


    }

    else if(game->State == GAME_PEOPLE_SELECT)
    {
        std::map<int , Button*> People_select_button_map;
        std::map<int, static_Player*> players_to_select;
        R.areas_to_check.clear();
        players_to_select[0] = new static_Player(std::string("Antonio"), 100, 200, 100, 100, 50);
        players_to_select[1] = new static_Player(std::string("Arca"), 200, 100, 50, 60, 100);
        players_to_select[2] = new static_Player(std::string("Genn"), 150, 130, 40, 50,100);
        players_to_select[3] = new static_Player(std::string("Pasq"), 100, 200, 30, 40, 20);

        Utility::ClearBckGnd(std::string("StartMenu"));
        Utility::generateBackgroundColorTexture(0.85*WINDOW_WIDTH, 0.05*WINDOW_HEIGHT, 0.13*WINDOW_WIDTH, 0.60*WINDOW_HEIGHT, 128, 128, 128, true, 0);
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
        }


        for(int i = 0; i < 4; i++)
        {
            std::string tmp_name = "Sel_" + players_to_select[i]->name;
            People_select_button_map[i] = new Button(0.25*((i % 2) + 1)*WINDOW_WIDTH, 0.25*((i / 2) + 1)*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, tmp_name);
            People_select_button_map[i]->DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
            R.areas_to_check.push_back(glm::vec4(People_select_button_map[i]->x, People_select_button_map[i]->y, People_select_button_map[i]->width, People_select_button_map[i]->height));

        
        }
        for(int i = 0; i < 4; i++)
        {
            People_select_Changing_Boxes[i] = new TextBox(0.91*WINDOW_WIDTH, (0.05 + 0.06*i)*WINDOW_HEIGHT, 0.1*WINDOW_HEIGHT, 0.03*WINDOW_WIDTH, glm::vec3(255,255,255), People_select_texts[i]);
            if(R.button_id != MAX_INT && R.button_id != 4) {

                if(i == 0)
                People_select_Changing_Boxes[0]->setText(players_to_select[R.button_id]->name);
                if(i == 1)
                People_select_Changing_Boxes[1]->setText(std::to_string(players_to_select[R.button_id]->max_health));
                if(i == 2)
                People_select_Changing_Boxes[2]->setText(std::to_string(players_to_select[R.button_id]->attack));
                if(i == 3)
                People_select_Changing_Boxes[3]->setText(std::to_string(players_to_select[R.button_id]->speed));
            }
            People_select_Changing_Boxes[i]->Render();
        }

        Button Confirm(0.4*WINDOW_WIDTH, 0.8*WINDOW_HEIGHT, 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, std::string("Confirm_button"));
        Confirm.DrawButton(R.cursor_x, R.cursor_y, R.LeftButtonPressed, true);
        R.areas_to_check.push_back(glm::vec4(Confirm.x, Confirm.y, Confirm.width, Confirm.height));

        if(R.button_id == 4) {

            R.areas_to_check.clear();
            R.button_id = MAX_INT;
            game->State = GAME_PEOPLE_SELECT;
            
        }
        R.shouldswap = false;
        

    }


}