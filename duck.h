#ifndef FLAPPYDUCK_DUCK_H
#define FLAPPYDUCK_DUCK_H

#include <SDL2/SDL.h>

class Duck
{
public:
    SDL_Rect rect;
    SDL_Texture* texture;
    float vy; // Velocity
    float ay = 0.00001; // Acceleration
    double angle;
    int defaultX;
    int defaultY;

    Duck(int x, int y){
        defaultX = x;
        defaultY = y;
        rect.x = x;
        rect.y = y;
        rect.w = 30;
        rect.h = 20;
        angle = 0;
    }

    void resetPos(){
        rect.x = defaultX;
        rect.y = defaultY;
        angle = 0;
        vy = 0;
        ay = 0.00001;
    }

    void draw(SDL_Renderer* renderer){
        SDL_Surface* surf = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 255, 200, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);

        SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
    }

    void gravity(float dt){
        vy += ay * dt;
        rect.y += vy * dt + 0.5 * ay * dt * dt;
        if (angle < 90){
            angle += 1.5;
        }
    }

    bool collision(const int widnowHeight) const{
        if (rect.y < 0 || rect.y + rect.h > widnowHeight){
            return false;
        }
        return true;
    }

    void flap(){
        vy = -0.05;
        ay = 0.00001;
        angle = -35;
    }
};


#endif //FLAPPYDUCK_DUCK_H
