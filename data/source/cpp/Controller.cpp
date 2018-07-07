//コントローラー関係
#include "../header/controller.h"
#define MAX_JOYSTIC_AXIS 32767

SDL_atomic_t Controller_Maneger::atm;
SDL_Event Controller_Maneger::event;
unsigned int Controller_Maneger::num_of_joystic;
std::vector<Controller_Joystic> Controller_Maneger::Joystics;

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

    SDL_AtomicSet(&atm, 1);
    SDL_Thread *controller_thread = SDL_CreateThread(Update_Controller, "InputThread", &atm);
    if (controller_thread == NULL)
    {
        printf("error create thread");
        return false;
    }
}

int Controller_Maneger::Update_Controller(void *data)
{
    //SDL_PollEvent(&event);
    while (SDL_AtomicGet((SDL_atomic_t *)data) > 0)
    {
        SDL_JoystickUpdate();
        for (int i = 0; i < num_of_joystic; i++)
        {
            Joystics[i].Read_State_Controller();
        }

        if (Joystics[0].state.button_pause)
        {
            SDL_AtomicDecRef((SDL_atomic_t *)data);
        }
    }

    return 0;
}

void Controller_Maneger::Clear_Controller()
{
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Controller_Joystic::Controller_Joystic()
{
    joystick = SDL_JoystickOpen(0);
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
    // 軸0 (X)
    state.Lx_axis = SDL_JoystickGetAxis(joystick, 0) / MAX_JOYSTIC_AXIS;

    if (state.Lx_axis > 1)
    {
        state.Lx_axis = 1;
    }
    else if (state.Lx_axis < -1)
    {
        state.Lx_axis = -1;
    }

    // 軸1 (Y)
    state.Ly_axis = SDL_JoystickGetAxis(joystick, 1) / MAX_JOYSTIC_AXIS;

    if (state.Ly_axis > 1)
    {
        state.Ly_axis = 1;
    }
    else if (state.Ly_axis < -1)
    {
        state.Ly_axis = -1;
    }

    if (SDL_JoystickGetButton(joystick, 11) > 0)
    {
        state.button_pause = true;
    }
    else
    {
        state.button_pause = false;
    }
}
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Controller_State::Controller_State()
{
    Rx_axis = 0;
    Ry_axis = 0;
    Lx_axis = 0;
    Ly_axis = 0;
    button_shoot_decition = false;
    button_shift_back = false;
    button_bomb = false;
    button_forward = false;
    button_pause = false;
}
