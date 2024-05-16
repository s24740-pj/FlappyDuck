#ifndef FLAPPYDUCK_PIPE_H
#define FLAPPYDUCK_PIPE_H

#include <SDL2/SDL.h>
#include "settings.h"

/*
 * +DESCRIPTION+
 * Pipe system works by always rendering 3 pipes over and over.
 * Moving with the same speed and acceleration to the left by setting dx in movement function.
 * If one hit the left wall then it will calculate his new position, and height of gap.
 * He will be setting off the screen to the right.
 * Calculate works that every pipe has the same space between each other.
 */

class Pipe {
public:
    SDL_Rect upperRect;
    SDL_Rect lowerRect;
    SDL_Texture *texture;

    // Setting width of pipe
    static const int pipe_width = 80;
    // Gap is the gap between the upper pipe and lower pipe
    static const int pipe_gap = 250;

    Pipe(SDL_Renderer* renderer, int x) {
        // Randomizing the height of the gap will be
        int randomY = rand() % (settings_windowHeight - pipe_gap);

        // Setting of upper pipe and lower pipe
        // Rendering them as Rect
        // First rendering upper pipe by the randomY and then lower is calculating by the gap size
        upperRect = {x, randomY - settings_windowHeight, pipe_width, settings_windowHeight};
        lowerRect = {x, randomY + pipe_gap, pipe_width, settings_windowHeight};

        SDL_Surface* surface = SDL_LoadBMP("./textures/pipe.bmp");
        texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, NULL, &upperRect);
        SDL_RenderCopy(renderer, texture, NULL, &lowerRect);
    }

    // Enabling the movement of pipe to the left by speed of dx
    void movement(float dx) {
        upperRect.x -= dx;
        lowerRect.x -= dx;

        wallCollision();
    }

    // Checks if pipe hit the wall to the left
    void wallCollision(){
        if (upperRect.x && lowerRect.x <= 1){
            updatePipe();
        }
    }

    // Recalculating the pipe that hit the left wall to his new localization off the screen to the right
    void updatePipe(){
        int newHeight = rand() % (settings_windowHeight - pipe_gap);

        upperRect.x = settings_windowWidth + 100 + pipe_width;
        lowerRect.x = settings_windowWidth + 100 + pipe_width;

        lowerRect.y = newHeight - settings_windowHeight;
        upperRect.y = newHeight + pipe_gap;
    }

    // Getting the X position
    int getPosX(){
        return lowerRect.x;
    }
};


#endif //FLAPPYDUCK_PIPE_H
