//コントローラー関係
#include "../header/controller.h"
#define MAX_JOYSTIC_AXIS 32767

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Controller_Maneger::Controller_Maneger()
{
}

bool Controller_Maneger::Init_Controller()
{
    if (SDL_NumJoysticks() > 0)
    {
        num_of_joystic++;
        Controller_Joystic joystic = Controller_Joystic(0);
        Joystics.push_back(joystic);
    }
    else
    {
        printf("error connect joystick\n");
        return false;
    }
    SDL_JoystickEventState(SDL_ENABLE);
}

void Controller_Maneger::Update_Controller()
{
    //SDL_PollEvent(&event);
    SDL_JoystickUpdate();
    for (int i = 0; i < num_of_joystic; i++)
    {
        Joystics[i].Read_State_Controller();
    }
}

void Controller_Maneger::Clear_Controller()
{
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Controller_Joystic::Controller_Joystic() : Controller_Joystic(0)
{
}
Controller_Joystic::Controller_Joystic(const int j_id)
{
    joystick = SDL_JoystickOpen(j_id);
}

SDL_Joystick *Controller_Joystic::get_joystic_pointer()
{
    return joystick;
}

void Controller_Joystic::Read_State_Controller()
{
}
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Controller_State::Controller_State()
{
}
