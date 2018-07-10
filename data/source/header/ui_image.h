#include "../header/vector.h"
#include <SDL2/SDL.h>
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class UI_Manager {
private:
public:
    bool Init_UI();
    UI_Manager();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class UI_image {
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    unsigned int frame_number;

    bool LoadFile(const char *filename);

public:
    UI_image();
    UI_image(const char *filename);
    UI_image(const char *filename, const int division_w, const int division_h);

    void Draw(unsigned int num, Vector2f vec, Vector2f scale);
};