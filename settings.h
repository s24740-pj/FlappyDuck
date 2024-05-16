#ifndef FLAPPYDUCK_SETTINGS_H
#define FLAPPYDUCK_SETTINGS_H

/*
 * +DESCRIPTION+
 * Here is every global settings that will be accessible everywhere and not changed
 */

// SCREEN
const int settings_windowWidth = 600;
const int settings_windowHeight = 900;

// PIPE
float settings_pipeSpeed = 3;
static const int settings_pipeGap = 250;

// DUCK
int settings_duckX = 200;
int settings_duckY = 300;
int settings_duckGravity = 200;

// PARTICLE
SDL_Color settings_color = { 255, 0,  0, 255 };
int settings_amount = 25;


#endif //FLAPPYDUCK_SETTINGS_H
