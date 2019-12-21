#include <stdexcept>
#include <SDL/SDL_ttf.h>
#include <fstream>
#include <deque>

#include "Game.h"
#include "World.h"
#include "Label.h"
#include "Player.h"

using namespace std;

#define SCREEN_W    320
#define SCREEN_H    256
#define SCREEN_BPP  32


SDL_Surface *Game::m_screen = nullptr;

void Game::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw runtime_error("Could not load SDL library!");
    if(TTF_Init() < 0)
        throw runtime_error("Could not load TTF library!");

    m_screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(!m_screen)
        throw runtime_error("Could not create screen!");

    SDL_WM_SetCaption("Gizo Robot - Running game", "Gizo Robot");
}

void Game::quit()
{
    TTF_Quit();
    SDL_Quit();
}

bool collide(SDL_Rect &pos, int spritesize, const deque<World::Point>& picks)
{
    int x1 = pos.x, x2 = pos.x + spritesize - 15, 
        y1 = pos.y, y2 = pos.y + spritesize,
        posY = SDL_GetVideoSurface()->h - 64;

    for(auto& pick : picks)
    {
        if(x2 >= pick.x && x2 < pick.x + PICK_W)
        {
            if(y1 == posY)
            {
                return true;
            }
            if(y1 < posY && y2 >= pick.y)
            {
                return true;
            }
        }
    }
    return false;
}

void Game::mainloop()
{
    int distance = 0, delay = 80;

    Player player; 
    World world;
    Label distance_text;

    distance_text.setPos(10, 10);
    char label[150];

    SDL_Event event;
    SDL_Color black = {0, 0, 0, 255};

    bool quit = false;

    while(!quit)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: quit = true; break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_SPACE)
                    player.jump();
                break;
        }
        if(collide(player.getPos(), SPRITE_SIZE, world.getPicks()))
        {
            quit = true;
            break;
        }
        SDL_FillRect(m_screen, &m_screen->clip_rect, 0xDDDDFF);

        world.render(m_screen);
        player.render(m_screen);
        distance_text.render(m_screen);

        SDL_Flip(m_screen);
        SDL_Delay(delay);

        distance++;
        sprintf(label, "Distance: %dm", distance);
        distance_text.update(label, black);

        if(distance % 200 == 0) 
        {
            delay -= 5;
            delay = delay <= 30 ? 30 : delay;
        }
    }
    // Output score
    ofstream file("highscore", ios::trunc);
    file << "High score: " << distance << "m" << endl;
    file.close();
}
