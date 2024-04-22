#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "duck.h"
#include "pipe.h"
#include "collision.h"
#include "settings.h"

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

    Duck duck(200, 300);

    std::vector<Pipe> pipes;

    for (int i = 0; i < 3; i++) {
        pipes.push_back(Pipe(renderer, settings_windowWidth + 101 + i * (Pipe::pipe_width + (settings_windowWidth-(Pipe::pipe_width*3))/2)));
    }

    milliseconds dt(15);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time

    bool start = false;

    for (bool game_active = true; game_active;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                game_active = false;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_p && !start && event.key.repeat == 0) {
                    // p - Play
                    start = true;
                    duck.resetPos();
                }
                else if (event.key.keysym.sym == SDLK_SPACE && start && event.key.repeat == 0) {
                    // space - Flap/Jump
                    duck.flap();
                }
                else if (event.key.keysym.sym == SDLK_r && event.key.repeat == 0) {
                    // r - Restart the game
                    duck.resetPos();
                    pipes.clear();
                    for (int i = 0; i < 3; i++) {
                        pipes.push_back(Pipe(renderer, settings_windowWidth + 101 + i * (Pipe::pipe_width + (settings_windowWidth-(Pipe::pipe_width*3))/2)));
                    }
                }
            }
        }

        if(start){
            duck.gravity(200);
            start = duck.collision(settings_windowHeight);

            for (auto& pipe : pipes) {
                pipe.movement(3);
                if (check_pipe_collision(&duck.rect, pipe)) {
                    start = false;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        duck.draw(renderer);
        for (auto& pipe : pipes) {
            pipe.draw(renderer);
        }

        SDL_RenderPresent(renderer);

        this_thread::sleep_until(current_time = current_time + dt);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}