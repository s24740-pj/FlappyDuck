#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "duck.h"
#include "pipe.h"
#include "collision.h"
#include "settings.h"
#include "particle.h"

// check for errors
#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                                                   \
      cout << SDL_GetError() << endl;                                          \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }

int main(int , char **) {
    using namespace std;
    using namespace std::chrono;

    errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);

    SDL_Window *window = SDL_CreateWindow(
            "FlappyDuck", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, settings_windowWidth, settings_windowHeight, SDL_WINDOW_SHOWN);
    errcheck(window == nullptr);

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC
    errcheck(renderer == nullptr);

    // Placing the duck to default position
    Duck duck(200, 300);

    // Implementing particleSystem
    ParticleSystem particleSystem;

    // Setting the pipes off screen to default localization by putting them into the pipe array
    std::vector<Pipe> pipes;
    for (int i = 0; i < 3; i++) {
        pipes.push_back(Pipe(renderer, settings_windowWidth + 100 + i * (Pipe::pipe_width + (settings_windowWidth-(Pipe::pipe_width*3))/2)));
    }

    milliseconds dt(15);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time

    bool start = false;
    bool explosionTriggered = false;
    bool hit = false;
    int points = 0;

    // Whole game loop
    for (bool game_active = true; game_active;) {
        SDL_Event event;
        // Checks for key event (input from keyboard)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                game_active = false;
            else if (event.type == SDL_KEYDOWN) {
                // Button "P" start the game
                if (event.key.keysym.sym == SDLK_p && !start && event.key.repeat == 0) {
                    start = true;
                    duck.resetPos();
                }
                // Button "Space" is jumping/flapping
                else if (event.key.keysym.sym == SDLK_SPACE && start && event.key.repeat == 0) {
                    duck.flap();
                }
                // Button "R" restarting the game by resetting positions and clearing arrays
                else if (event.key.keysym.sym == SDLK_r && event.key.repeat == 0) {
                    // Resetting the duck position to default
                    duck.resetPos();
                    // Clearing the pipe array
                    pipes.clear();
                    // Clearing the particle array
                    particleSystem.clearParticles();
                    // Pushing back the pipes off the screen
                    for (int i = 0; i < 3; i++) {
                        pipes.push_back(Pipe(renderer, settings_windowWidth + 101 + i * (Pipe::pipe_width + (settings_windowWidth-(Pipe::pipe_width*3))/2)));
                    }
                    // Resetting points to 0
                    points = 0;
                    // Reset the particle trigger explosion
                    explosionTriggered = false;
                    // Reset the hit bool because he is not hiiting anything at start
                    hit = false;
                }
            }
        }

        SDL_RenderClear(renderer);

        // Waiting to start the game
        if(start){
            // Enabling the duck gravity
            duck.gravity(200);
            // Stopping the game when duck collision the floor or ceiling
            start = !duck.collision(settings_windowHeight);

            // Checks if duck hit floor or ceiling and then run particle explosion at his position
            if(duck.collision(settings_windowHeight)){
                explosionTriggered = true;
                hit = true;
            }

            // Runs pipe to move with dx speed
            for (auto& pipe : pipes) {
                pipe.movement(3);
                // Checks if duck hit the pipe (has the collision with the pipe)
                if (check_pipe_collision(&duck.rect, pipe)) {
                    start = false;
                    cout << "Przegrałeś z ilością: " << points << " punktów!" << endl;
                    explosionTriggered = true;
                    hit = true;
                    break;
                }
                // Checks if the duck is flew correctly between the pipe and added points +1
                if (duck.isBetweenPipe(pipe)){
                    points++;
                }
            }
        }

        // Setting background texture
        SDL_Surface* surface = SDL_LoadBMP("./textures/background.bmp");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);

        SDL_Rect background;
        background.x = 0;
        background.y = 0;
        background.w = settings_windowWidth;
        background.h = settings_windowHeight;

        SDL_RenderCopy(renderer, texture, NULL, &background);
        SDL_DestroyTexture(texture);

        // Rendering all the pipes in pipes array
        duck.draw(renderer);
        for (auto& pipe : pipes) {
            pipe.draw(renderer);
        }


        // Waiting to trigger the explosion with the settings below (colors, localization, amount)
        if(explosionTriggered){
            SDL_Color color = { 255, 0,  0, 255 };
            particleSystem.explosion(duck.rect.x + duck.rect.w, duck.rect.y + (duck.rect.h/2), 25, color);
            // Instantly disabling trigger to trigger only once
            explosionTriggered = false;
        }


        // Checks if duck hit something, then starts updating the particles render
        if(hit){
            // Update particle system
            particleSystem.update();

            // Draw all particles in array
            for (int i = 0; i < MAX_PARTICLES; i++) {
                if (particleSystem.particles[i].life > 0) {
                    SDL_Rect rect = {static_cast<int>(particleSystem.particles[i].x), static_cast<int>(particleSystem.particles[i].y), 5, 5};
                    SDL_SetRenderDrawColor(renderer, particleSystem.particles[i].color.r, particleSystem.particles[i].color.g, particleSystem.particles[i].color.b, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }


        SDL_RenderPresent(renderer);
        this_thread::sleep_until(current_time = current_time + dt);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}