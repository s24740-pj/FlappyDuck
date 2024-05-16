#ifndef FLAPPYDUCK_DUCK_H
#define FLAPPYDUCK_DUCK_H

#include <SDL2/SDL.h>
#include "pipe.h"

/*
 * +DESCRIPTION+
 * Duck is falling down by gravity and falling faster over the time
 * Flewing between the pipe is checking by duck X and pipe X, if they are the same then he flew through the pipe
 */

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

    // Resetting the position and rotation of duck
    void resetPos(){
        rect.x = defaultX;
        rect.y = defaultY;
        angle = 0;
        vy = 0;
        ay = 0.00001;
    }

    // Checks if duck is between pipe
    // By checking if duck is between the pipe is calculating if his X is the same as pipe X
    // If he is then return true and count the point
    // In this example we don't need to check where the gap is and what is the Y of duck
    bool isBetweenPipe(Pipe pipe){
        return rect.x+1 >= pipe.getPosX()+50 && rect.x-1 <= pipe.getPosX()+50;
    }

    // Rendering the duck
    void draw(SDL_Renderer* renderer){
        SDL_Surface* surface = SDL_LoadBMP("./textures/duck.bmp");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
        SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
    }

    // Enabling gravity of duck to falling only down
    void gravity(float dt){
        vy += ay * dt;
        rect.y += vy * dt + 0.5 * ay * dt * dt;
        // When falling, the duck is changing the rotation
        // Not affected where he is falling
        if (angle < 90){
            angle += 1.5;
        }
    }

    // Checks if duck collision with floor or ceiling
    bool collision(const int windowHeight) const{
        if (rect.y < 0 || rect.y + rect.h > windowHeight){
            return true;
        }
        return false;
    }

    // Flap is the same as jumping
    void flap(){
        // Changing the velocity to negative to "fall" upwards
        vy = -0.05;
        // Resetting the acceleration to slow down
        ay = 0.00001;
        // Changing his angle/rotation to make him looks like flying up
        angle = -35;
    }
};


#endif //FLAPPYDUCK_DUCK_H
