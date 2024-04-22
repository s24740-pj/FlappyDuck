#ifndef FLAPPYDUCK_PIPE_H
#define FLAPPYDUCK_PIPE_H

#include <SDL2/SDL.h>
#include "settings.h"

class Pipe {
public:
    SDL_Rect upperRect;
    SDL_Rect lowerRect;
    SDL_Texture *texture;

    static const int pipe_width = 80;
    static const int pipe_gap = 250;

    Pipe(SDL_Renderer* renderer, int x) {
        int randomY = rand() % (settings_windowHeight - pipe_gap);

        upperRect = {x, randomY - settings_windowHeight, pipe_width, settings_windowHeight};
        lowerRect = {x, randomY + pipe_gap, pipe_width, settings_windowHeight};

        SDL_Surface* surf = SDL_CreateRGBSurface(0, pipe_width, settings_windowHeight, 32, 0, 0, 0, 0);
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0, 200, 0));
        texture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, NULL, &upperRect);
        SDL_RenderCopy(renderer, texture, NULL, &lowerRect);
    }

    void movement(float dx) {
        upperRect.x -= dx;
        lowerRect.x -= dx;

        wallCollision();
    }

    void wallCollision(){
        if (upperRect.x && lowerRect.x <= 1){
            updatePipe();
        }
    }

    void updatePipe(){
        int newHeight = rand() % (settings_windowHeight - pipe_gap);

        upperRect.x = settings_windowWidth + 101 + pipe_width;
        lowerRect.x = settings_windowWidth + 101 + pipe_width;

        lowerRect.y = newHeight - settings_windowHeight;
        upperRect.y = newHeight + pipe_gap;
    }
};


#endif //FLAPPYDUCK_PIPE_H
