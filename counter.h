#ifndef FLAPPYDUCK_COUNTER_H
#define FLAPPYDUCK_COUNTER_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Counter {
public:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect numberRects[10];
    SDL_Rect destRect[4];

    Counter(SDL_Renderer* renderer) : renderer(renderer) {
        SDL_Surface* tempSurface = SDL_LoadBMP("textures/numbers.bmp");
        if (!tempSurface) {
            std::cerr << "Nie udało się załadować BMP: " << SDL_GetError() << std::endl;
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
            SDL_FreeSurface(tempSurface);
            if (!texture) {
                std::cerr << "Nie udało się stworzyć tekstury: " << SDL_GetError() << std::endl;
            }
        }

        // Ustawienie prostokątów źródłowych dla cyfr 0-9
        for (int i = 0; i < 10; ++i) {
            numberRects[i] = { i * 132, 0, 132, 187 };
        }

        // Ustawienie prostokątów docelowych dla wyświetlania cyfr z odstępami
        for (int i = 0; i < 4; ++i) {
            destRect[i] = { i * 45, 0, 50, 80 }; // dodanie odstępu 5 pikseli między cyframi
        }
    }

    ~Counter() {
        SDL_DestroyTexture(texture);
    }

    void display(int points) {
        std::string pointsStr = std::to_string(points);
        int len = pointsStr.length();

        // Wypełnienie reszty '0', jeśli punktów jest mniej niż 4 cyfry
        for (int i = 0; i < 4 - len; ++i) {
            SDL_RenderCopy(renderer, texture, &numberRects[0], &destRect[i]);
        }

        // Renderowanie rzeczywistych cyfr
        for (int i = 0; i < len; ++i) {
            int digit = pointsStr[i] - '0';
            SDL_RenderCopy(renderer, texture, &numberRects[digit], &destRect[4 - len + i]);
        }
    }
};

#endif // FLAPPYDUCK_COUNTER_H
