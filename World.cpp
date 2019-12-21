#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <SDL/SDL_image.h>

#include "World.h"

using namespace std;


World::World()
{
    srand(time(nullptr));
    m_clouds[0] = IMG_Load("img/cloud1.png");
    m_clouds[1] = IMG_Load("img/cloud2.png");
    m_mountain  = IMG_Load("img/mountain.png");
    m_ground    = IMG_Load("img/ground.png");
    m_picks[0]  = IMG_Load("img/pick-small.png");
    m_picks[1]  = IMG_Load("img/pick-large.png");

    int screenW = SDL_GetVideoSurface()->w, nb = 0,
        screenH = SDL_GetVideoSurface()->h;
    // ground
    nb = (screenW / GROUND_W + 1) * 2;
    for(int i = 0 ; i <= nb ; i++)
        ground.push_back(Point(i*GROUND_W, screenH-32));
    // mountain
    nb = (screenW / MOUNTAIN_W + 1) * 2;
    for(int i = 0 ; i <= nb ; i++)
        mountains.push_back(Point(i*MOUNTAIN_W, 164));
    // cloud
    for(int i = 0 ; i < 5 ; i++)
        clouds.push_back(Point((rand()%8) * CLOUD_W, 50, m_clouds[rand()%2]));

    int random = 0, y = 0, pos = 200;
    // pick
    for(int i = 0 ; i < 3 ; i++)
    {
        random = rand()%2;
        y = random == 0 ? screenH-55 : screenH-64;
        pos += rand() % (MAX-MIN) + MIN;
        picks.push_back(Point(pos, y, m_picks[random]));
    }
}

World::~World()
{
    for(int i = 0 ; i < 2 ; i++)
    {
        SDL_FreeSurface(m_clouds[i]);
        SDL_FreeSurface(m_picks[i]);
    }
    SDL_FreeSurface(m_mountain);
    SDL_FreeSurface(m_ground);
}

void World::render(SDL_Surface *scr)
{
    SDL_Rect pos;
    int screenW = SDL_GetVideoSurface()->w, 
        screenH = SDL_GetVideoSurface()->h;
    // Rendering mountains and clouds
    for(auto& p : mountains)
    {
        pos.x = p.x; pos.y = p.y;
        SDL_BlitSurface(m_mountain, nullptr, scr, &pos);
        p.x -= SPEED;
        if(p.x + MOUNTAIN_W <= 0) p.x = screenW;
    }
    for(auto& p : clouds)
    {
        pos.x = p.x; pos.y = p.y;
        SDL_BlitSurface(p.image, nullptr, scr, &pos);
        p.x -= SPEED;
        if(p.x + CLOUD_W <= 0) p.x = screenW;
    }
    // Rendering ground and picks
    for(auto& p : ground)
    {
        pos.x = p.x; pos.y = p.y;
        SDL_BlitSurface(m_ground, nullptr, scr, &pos);
        p.x -= SPEED;
        if(p.x + GROUND_W <= 0) p.x = screenW;
    }
    int random = 0, y = 0;
    for(auto& p : picks)
    {
        pos.x = p.x; pos.y = p.y;
        SDL_BlitSurface(p.image, nullptr, scr, &pos);
        p.x -= SPEED;
        if(p.x + PICK_W <= 0)
        {
            random = rand()%2;
            y = random == 0 ? screenH-55 : screenH-64;
            p.x = screenW; p.y = y;
            p.image = m_picks[random];
        }
    }
}
