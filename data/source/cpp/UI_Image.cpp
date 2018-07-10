//UI関係
#include "../header/ui_image.h"
#include "../header/game.h"

#include <SDL2/SDL_image.h>

//http://d.hatena.ne.jp/unk_pizza/20130120/p1
//https://www.opengl.org/discussion_boards/showthread.php/182865-Texture-on-SDL-OpenGL

bool UI_image::LoadFile(const char *filename)
{
    surface = IMG_Load(filename);
    if (surface == NULL) {
        printf("failed to open background image.\n");
        return false;
    }
    return true;
}

UI_image::UI_image()
{
}
UI_image::UI_image(const char *filename)
{
    LoadFile(filename);

    src_rect.w   = surface->w;
    src_rect.h   = surface->h;
    frame_number = 1;
}
UI_image::UI_image(const char *filename, const int division_w, const int division_h)
{
    LoadFile(filename);

    src_rect.w   = surface->w / division_w;
    src_rect.h   = surface->h / division_h;
    frame_number = division_w * division_h;
}

void UI_image::Draw(unsigned int num, Vector2f vec, Vector2f scale)
{
    if (num > frame_number) {
        return;
    }
    num--;
    src_rect.x = src_rect.w * num;
    src_rect.y = src_rect.y * num;

    dst_rect.x = vec.x;
    dst_rect.y = vec.y;

    dst_rect.w = src_rect.w * scale.x;
    dst_rect.h = src_rect.h * scale.y;

    SDL_RenderCopy(GameManager::renderer, texture, &src_rect, &dst_rect);
}