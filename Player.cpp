#include <stdexcept>
#include <SDL/SDL_image.h>

#include "Player.h"

using namespace std;


Player::Player() : m_sprite(nullptr)
    , m_jumpImg(nullptr)
    , m_frames{0, 0, 0, 0}
    , m_pos{0, 0, 0, 0}
    , m_currentFrame(0)
    , isJumping(false)
    , m_velY(0.0f)
    , nbSpaces(0)
{
    m_sprite = IMG_Load("img/gizo-robot-running-animation.png");
    if(!m_sprite)
        throw runtime_error(IMG_GetError());

    m_jumpImg = IMG_Load("img/gizo-robot-jump.png");
    if(!m_jumpImg)
        throw runtime_error(IMG_GetError());

    for(int i = 0 ; i < NB_FRAMES ; i++)
    {
        m_frames[i].w = m_frames[i].h = SPRITE_SIZE;
        m_frames[i].x = i * SPRITE_SIZE;
        m_frames[i].y = 0;
    }

    m_pos.y = SDL_GetVideoSurface()->h - SPRITE_SIZE*2;
}

Player::~Player()
{
    SDL_FreeSurface(m_sprite);
    SDL_FreeSurface(m_jumpImg);
}

void Player::render(SDL_Surface *scr)
{
    if(!isJumping)
    {
        SDL_BlitSurface(m_sprite, &m_frames[m_currentFrame], scr, &m_pos);
        ++m_currentFrame;
        if(m_currentFrame >= NB_FRAMES)
            m_currentFrame = 0;
    }
    else 
    {
        m_pos.y += (int) m_velY * 0.25f;
        m_velY += GRAVITY * 0.25f;
        SDL_BlitSurface(m_jumpImg, nullptr, scr, &m_pos);
        if((m_pos.y + SPRITE_SIZE) >= (SDL_GetVideoSurface()->h - SPRITE_SIZE))
        {
            m_pos.y = SDL_GetVideoSurface()->h - SPRITE_SIZE*2;
            isJumping = false;
            m_velY = 0.0f;
            nbSpaces = 0;
        }
    }
}

void Player::jump()
{
    if(nbSpaces <= 2)
    {
        nbSpaces++;
        isJumping = true;
        m_velY = -50.0f;
    }
}
