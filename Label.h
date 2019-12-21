#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class Label 
{
public:
    Label() = default;
    Label(const char *label);

    void update(const char *label, SDL_Color& color, const char *fontpath="NeuePixelSans.ttf", int fontsize=20);
    void update(std::string label, SDL_Color& color, const char *fontpath="NeuePixelSans.ttf", int fontsize=20);
    void render(SDL_Surface *scr);
    void setPos(int x, int y);

    ~Label();

private:
    std::string m_label;
    SDL_Surface *m_surface = nullptr;
    SDL_Rect m_pos{0, 0, 0, 0};
    TTF_Font *m_font = nullptr;
};

#endif 
