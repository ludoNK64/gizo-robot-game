#ifndef PLAYER_H
#define PLAYER_H

#define NB_FRAMES       8
#define SPRITE_SIZE     32
#define GRAVITY         80.0f

#include <SDL/SDL.h>

class Player 
{
public:
    Player();
    Player(const Player& ) = delete;

    ~Player();

    void render(SDL_Surface *scr);
    void jump();
    inline SDL_Rect& getPos() 
    {
        return m_pos;
    }

private:
    SDL_Surface *m_sprite;
    SDL_Surface *m_jumpImg;
    SDL_Rect m_frames[NB_FRAMES];
    SDL_Rect m_pos;
    int m_currentFrame;
    bool isJumping;
    float m_velY;
    int nbSpaces;
};

#endif 
