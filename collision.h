#ifndef FLAPPYDUCK_COLLISION_H
#define FLAPPYDUCK_COLLISION_H

#include "duck.h"
#include "pipe.h"

/*
 * +DESCRIPTION+
 * Collision is checking by the overlapping two textures
 */

bool check_collision(SDL_Rect* A, SDL_Rect* B) {
    int leftA = A->x;
    int rightA = A->x + A->w;
    int topA = A->y;
    int bottomA = A->y + A->h;

    int leftB = B->x;
    int rightB = B->x + B->w;
    int topB = B->y;
    int bottomB = B->y + B->h;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }
    return true;
}

// Checks if duck hit the pipe
bool check_pipe_collision(SDL_Rect* duckRect, Pipe& pipe) {
    return check_collision(duckRect, &pipe.upperRect) || check_collision(duckRect, &pipe.lowerRect);
}


#endif //FLAPPYDUCK_COLLISION_H
