#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <thread>

// check for errors
#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                                                   \
      cout << SDL_GetError() << endl;                                          \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }

class Duck
{
public:
    SDL_Rect rect;
    SDL_Texture* texture;
    float vy; //velocity
    float ay = 0.00001; //acceleration
    double angle;

    Duck(int x, int y){
        rect.x = x;
        rect.y = y;
        rect.w = 30;
        rect.h = 20;
        angle = 0;
    }

    void resetPos(int x, int y){
        rect.x = x;
        rect.y = y;
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

    bool collision(const int height) const{
        if (rect.y < 0 || rect.y + rect.h > height){
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

int main(int , char **) {
    using namespace std;
    using namespace std::chrono;
    const int width = 700;
    const int height = 900;

    errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);

    SDL_Window *window = SDL_CreateWindow(
            "FlappyDuck", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    errcheck(window == nullptr);

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC
    errcheck(renderer == nullptr);

    Duck duck(200, 300);

    milliseconds dt(15);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time

    bool start = false;

    for (bool game_active = true; game_active;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) { // check if there are some events
            if (event.type == SDL_QUIT)
                game_active = false;
            else if (event.key.keysym.sym == SDLK_p and not start)
            {
                start = true;
                duck.resetPos(200, 300);
            }
            else if (event.key.keysym.sym == SDLK_SPACE and start)
            {
                duck.flap();
            }
        }
        if(start){
            duck.gravity(200);
            start = duck.collision(height);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        duck.draw(renderer);

        SDL_RenderPresent(renderer);

        this_thread::sleep_until(current_time = current_time + dt);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}