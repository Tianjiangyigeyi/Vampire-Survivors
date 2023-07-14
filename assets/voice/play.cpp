#include <Windows.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


int main(int argc, char const *argv[])
{
    std::cout<<"argc: "<<argc<<std::endl;
    if(strcmp(argv[1], "0") == 0) {
        std::string path = "1-1.wav";
        std::cout<<"path: "<<path<<std::endl;
        PlaySound(TEXT(path.c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        Sleep(1000000);
    }

    if(strcmp(argv[1], "1") == 0) {
        std::string path = "press.wav";
        PlaySound(TEXT(path.c_str()), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(1000);
    }

    if(strcmp(argv[1], "2") == 0) {
        std::string path = "1-2.wav";
        PlaySound(TEXT(path.c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        Sleep(1000000);
    }

    if(strcmp(argv[1], "3") == 0) {
        std::string path = "hurt.wav";
        PlaySound(TEXT(path.c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        Sleep(3500);
    }

    return 0;
}
