#include <stdexcept>
#include "Label.h"

using namespace std;


Label::Label(const char *label) : m_label(label)
    , m_surface(nullptr)
    , m_pos{0, 0, 0, 0}
    , m_font(nullptr)
{
    SDL_Color black = {0, 0, 0, 255};
    update(label, black);
}

void Label::update(const char *label, SDL_Color& color, const char *fontpath, int fontsize)
{
    if(!m_font)
    {
        m_font = TTF_OpenFont(fontpath, fontsize);
        if(!m_font)
            throw runtime_error(TTF_GetError());
    }
    if(m_surface) 
    {
        SDL_FreeSurface(m_surface);
        m_surface = nullptr;
    }
    m_surface = TTF_RenderText_Blended(m_font, label, color);

    if(!m_surface)
        throw runtime_error(TTF_GetError());
}

void Label::update(string label, SDL_Color& color, const char *fontpath, int fontsize)
{
    update(label.c_str(), color, fontpath, fontsize);
}

void Label::render(SDL_Surface *scr)
{
    if(m_surface)
    {
        SDL_BlitSurface(m_surface, nullptr, scr, &m_pos);
    }
}

void Label::setPos(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
}

Label::~Label()
{
    if(m_surface) SDL_FreeSurface(m_surface);
    if(m_font) TTF_CloseFont(m_font);
}
