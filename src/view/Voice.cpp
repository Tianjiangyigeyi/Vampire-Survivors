#include "../common/config.h"

Voice::Voice()
{
    voices[0] = "assets/voice/1-1.wav";
    voices[1] = "assets/voice/press.wav";
}

Voice::~Voice()
{
    for(int i = 0; i < processes.size(); i++){
        TerminateProcess(processes[i].hProcess, 0);
        CloseHandle(processes[i].hProcess);
        CloseHandle(processes[i].hThread);
    }
}

void Voice::play(int id)
{
    std::string input = "assets/voice/play.exe " + std::to_string(id);
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    PROCESS_INFORMATION pi;
    CreateProcess(NULL, const_cast<LPSTR>(input.c_str()), 0, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    processes[id] = pi;
   
}

void Voice::stop_play(int id)
{
    // std::cout << "stop play" << id<<std::endl;
    TerminateProcess(processes[id].hProcess, 0);
    CloseHandle(processes[id].hProcess);
    CloseHandle(processes[id].hThread);
    // std::cout<<"stop play after "<<std::endl;
}
