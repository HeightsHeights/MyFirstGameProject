#include <SDL2/SDL.h>
#include <vector>
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Controller_Maneger
{
  private:
    static SDL_Event event;
    static unsigned int num_of_joystic;

  public:
    static std::vector<Controller_Joystic> Joystics;

    Controller_Maneger();

    static bool Init_Controller();
    static void Update_Controller();
    static void Clear_Controller();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Controller_Joystic
{
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
class Controller_State
{
  private:
  public:
    int Rx_axis = 0;
    int Ry_axis = 0;
    int Lx_axis = 0;
    int Ly_axis = 0;
    bool button_shoot_decition = false;
    bool button_shift_back = false;
    bool button_bomb = false;
    bool button_forward = false;
    bool button_pause = false;

    Controller_State();
};
