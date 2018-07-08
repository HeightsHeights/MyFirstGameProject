#include <SDL2/SDL.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Controller_State
{
private:
public:
  float Rx_axis;
  float Ry_axis;
  float Lx_axis;
  float Ly_axis;
  bool button_shoot_decition;
  bool button_shift_back;
  bool button_bomb;
  bool button_forward;
  bool button_pause;

  Controller_State();
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
class Controller_Maneger
{
private:
  static SDL_atomic_t atm;
  static unsigned int num_of_joystic;

public:
  static std::vector<Controller_Joystic> Joystics;

  Controller_Maneger();

  static bool Init_Controller();
  static int Update_Controller(void *data);
  static void Clear_Controller();
};
