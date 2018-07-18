//オーディオ関係
#include "../header/audio.h"

Mix_Music* Audio_Manager::music[BGM_NUMBER];
Mix_Chunk* Audio_Manager::chunk[SE_NUMBER];
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Audio_Manager::Audio_Manager()
{
}

bool Audio_Manager::Init_Audio()
{
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("error open audio device\n");
        return false;
    }

    music[BGM_Title] = Mix_LoadMUS("data/sounds/bgm/Title.mp3");
    music[BGM_Main]  = Mix_LoadMUS("data/sounds/bgm/Main.mp3");
    music[BGM_Boss]  = Mix_LoadMUS("data/sounds/bgm/Boss.mp3");
    music[BGM_Clear] = Mix_LoadMUS("data/sounds/bgm/Win.mp3");
    music[BGM_Lose]  = Mix_LoadMUS("data/sounds/bgm/Lose.mp3");

    chunk[SE_Player_Shot] = Mix_LoadWAV("data/sounds/se/shot03.mp3");
    chunk[SE_Boss]        = Mix_LoadWAV("data/sounds/se/boss.mp3");

    chunk[SE_Enemy_Killed]   = Mix_LoadWAV("data/sounds/se/dead.mp3");
    chunk[SE_Player_Damaged] = Mix_LoadWAV("data/sounds/se/damaged01.mp3");
    chunk[SE_Enemy_Damaged]  = Mix_LoadWAV("data/sounds/se/damaged02.mp3");

    chunk[SE_Boss_Killed]   = Mix_LoadWAV("data/sounds/se/bossdead.mp3");
    chunk[SE_Player_Killed] = Mix_LoadWAV("data/sounds/se/playerkilled.mp3");

    chunk[SE_Player_Warning_1] = Mix_LoadWAV("data/sounds/se/warning1.mp3");
    chunk[SE_Player_Warning_2] = Mix_LoadWAV("data/sounds/se/warning2.mp3");

    chunk[SE_Count] = Mix_LoadWAV("data/sounds/se/count.mp3");

    return true;
}