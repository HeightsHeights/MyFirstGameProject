#pragma once
#include <SDL2/SDL.h>
#include <vector>

typedef enum {
    B_SHOOT_DICITION = 0,
    B_SHIFT_BACK     = 1,
    B_PAUSE          = 2,
    B_NUMBER         = 3,
} ButtonMode;
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Controller_State {
private:
public:
    float Rx_axis;
    float Ry_axis;
    float Lx_axis;
    float Ly_axis;
    bool button[B_NUMBER];

    Controller_State();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Controller_Joystic {
private:
    SDL_Joystick *joystick;

public:
    Controller_Joystic();
    Controller_Joystic(const int j_id);
    SDL_Joystick *get_joystic_pointer();
    void Read_State_Controller();
    Controller_State state;
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Controller_Maneger {
private:

public:
    static SDL_atomic_t atm;
    static unsigned int num_of_joystic;
    static SDL_Event event;
    static std::vector<Controller_Joystic> Joystics;

    Controller_Maneger();

    static bool Init_Controller();
    static int Update_Controller(void *data);
    static void Clear_Controller();
};
