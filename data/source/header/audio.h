#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef enum {
    BGM_NULL   = 0,
    BGM_Title  = 1,
    BGM_Main   = 2,
    BGM_Boss   = 3,
    BGM_Clear  = 4,
    BGM_Lose   = 5,
    BGM_NUMBER = 6,
} BGM;

typedef enum {
    SE_NULL             = 0,
    SE_Player_Shot      = 1,
    SE_Player_Damaged   = 2,
    SE_Boss             = 3,
    SE_Enemy_Killed     = 4,
    SE_Enemy_Damaged    = 5,
    SE_Count            = 6,
    SE_Boss_Killed      = 7,
    SE_Player_Killed    = 8,
    SE_Player_Warning_1 = 9,
    SE_Player_Warning_2 = 10,
    SE_NUMBER           = 11,
} SE;
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Audio_Manager {
private:
public:
    static Mix_Music *music[BGM_NUMBER];
    static Mix_Chunk *chunk[SE_NUMBER];
    static bool Init_Audio();
    Audio_Manager();
};
