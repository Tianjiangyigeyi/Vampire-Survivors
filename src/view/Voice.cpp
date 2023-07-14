#include "../common/config.h"

Voice::Voice()
{
    sound = true;
    music = true;
    vfx = true;
    vis = true;
    dam = true;
}
 
Voice::~Voice()
{
    for(int i = 0; i < processes_sound.size(); i++){
        TerminateProcess(processes_sound[i].hProcess, 0);
        CloseHandle(processes_sound[i].hProcess);
        CloseHandle(processes_sound[i].hThread);
    }
    for(int i = 0; i < processes_music.size(); i++){
        TerminateProcess(processes_music[i].hProcess, 0);
        CloseHandle(processes_music[i].hProcess);
        CloseHandle(processes_music[i].hThread);
    }
}

void Voice::play(int id, int type)
{

    if(type == 0 && !sound) return;
    if(type == 1 && !music) return;

    
    std::string input = "assets/voice/play.exe " + std::to_string(id);
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi;
    CreateProcess(NULL, const_cast<LPSTR>(input.c_str()), 0, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if(type == 0)
    processes_sound[id] = pi;
    if(type == 1)
    processes_music[id] = pi;
   
}

void Voice::stop_play(int id, int type)
{
    if(type == 0)
    {
        TerminateProcess(processes_sound[id].hProcess, 0);
        CloseHandle(processes_sound[id].hProcess);
        CloseHandle(processes_sound[id].hThread);
    }
    if(type == 1)
    {
        TerminateProcess(processes_music[id].hProcess, 0);
        CloseHandle(processes_music[id].hProcess);
        CloseHandle(processes_music[id].hThread);
    }
    // std::cout << "stop play" << id<<std::endl;

    // std::cout<<"stop play after "<<std::endl;
}
