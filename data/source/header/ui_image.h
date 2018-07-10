#include <SDL2/SDL.h>

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class UI_Manager {
private:
public:
    bool Init_ui();
    UI_Manager();
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class UI_image {
private:
    SDL_Surface *image;
    SDL_Texture *texture;
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    unsigned int division_number;

public:
    UI_image();
    UI_image(const char *filename);
    UI_image(const char *filename, const int division_number);

    void Draw();
};