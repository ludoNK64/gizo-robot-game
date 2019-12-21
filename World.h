#ifndef WORLD_H
#define WORLD_H

#include <deque>
#include <SDL/SDL.h>

#define SPEED       10
#define GROUND_W    32
#define MOUNTAIN_W  128
#define PICK_W      10
#define CLOUD_W GROUND_W
#define MAX         120
#define MIN         80

class World
{
public:
    struct Point
    {
        int x;
        int y;
        SDL_Surface *image;

        Point(int _x, int _y, SDL_Surface *img=nullptr) 
        { 
            x = _x; y = _y; 
            image = img;
        }
    };


    World();
    ~World();

    void render(SDL_Surface *scr);

    inline const std::deque<Point>& getPicks() const 
    {
        return picks;
    }

private:
    SDL_Surface *m_clouds[2];
    SDL_Surface *m_mountain;
    SDL_Surface *m_ground;
    SDL_Surface *m_picks[2];

    std::deque<Point> ground;
    std::deque<Point> mountains;
    std::deque<Point> clouds;
    std::deque<Point> picks;
};

#endif 
