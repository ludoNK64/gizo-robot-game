#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>

class Game 
{
public:
    static void init();
    static void mainloop();
    static void quit();

private:
    static SDL_Surface *m_screen;
};

#endif 
