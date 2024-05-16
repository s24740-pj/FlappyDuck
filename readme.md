# FlappyDuck
## Overview
FlappyDuck is a simple recreation of the popular game FlappyBird. In this game, you control a duck that must navigate through a series of pipes without colliding with them. The objective is to achieve the highest score by flying as far as possible without hitting any obstacles.

## Screenshots
![alt text](https://raw.githubusercontent.com/s24740-pj/FlappyDuck/main/screenshots/Screenshot1.png)
![alt text](https://raw.githubusercontent.com/s24740-pj/FlappyDuck/main/screenshots/Screenshot2.png)

## Installation
To set up and run FlappyDuck, follow these steps: <br>
1. **Clone the Repository**
    ```sh
    git clone https://github.com/yourusername/FlappyDuck.git
    cd FlappyDuck
    ```
2. **Create Build Directory**
    ```sh
    mkdir build
    cd build
    ```
3. **Build the Project**
    ```sh
    cmake ../
    make
    ```
4. **Run the Game**
    ```sh
    ./FlappyDuck
    ```

## Keybinds
`p` - Play/Start the game<br>
`r`  - Restart the game<br>
`space` - Flap/Jump<br>

## Code Structure

`CMakeLists.txt` This file is the build configuration for the project. It specifies the minimum CMake version required, project name, C++ standard, and necessary packages and libraries.

`main.cpp` This is the main entry point of the game where the game loop is managed. It initializes SDL2, sets up the game objects, and handles the main game logic.

`duck.h` Defines the Duck class which manages the player's character, including its properties and behavior such as flapping and collision detection.

`pipe.h` Defines the Pipe class which represents the obstacles in the game. It handles the generation, movement, and collision logic for the pipes.

`collision.h` Contains functions and logic for detecting collisions between the duck and the pipes.

`settings.h` Provides customizable settings for the game, such as the game window size, gravity, and other physics parameters.

`particle.h` Defines the Particle class for any particle effects used in the game, enhancing the visual experience.