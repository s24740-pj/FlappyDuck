#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdlib>

// Define the maximum number of particles in the system
#define MAX_PARTICLES 100

// Class to represent a single particle
class Particle {
public:
    float x, y;
    float vx, vy;
    // Lifespan of the particle; particle is active if life is greater than 0
    int life;
    // Color of the particle for rendering
    SDL_Color color;

    // Constructor initializes particle to default values
    Particle() {
        x = 0;
        y = 0;
        vx = 0;
        vy = 0;
        life = 0;
    }

    // Initialize a particle with position, velocity, color, and random lifespan
    void init(float x_, float y_, float vx_, float vy_, const SDL_Color& c) {
        x = x_;
        y = y_;
        vx = vx_;
        vy = vy_;
        color = c;
        // Lifespan between 20 to 80 frames
        life = rand() % 60 + 20;
    }

    // Update the particle's position and life status
    void update() {
        if (life > 0) {
            // Update horizontal position
            x += vx;
            // Update vertical position
            y += vy;
            // Simulate gravity effect
            vy += 0.1;
            // Decrease life each frame
            life--;
        }
    }
};

// Manages a collection of particles
class ParticleSystem {
public:
    // Array to store multiple particles
    Particle particles[MAX_PARTICLES];

    // Update all particles in the system
    void update() {
        // Call update on each particle
        for (int i = 0; i < MAX_PARTICLES; i++) {
            particles[i].update();
        }
    }

    // Trigger an explosion effect at a specified position with a specified number of particles
    void explosion(float x, float y, int amount, const SDL_Color& color) {
        for (int i = 0; i < MAX_PARTICLES && amount > 0; i++) {
            // Find an inactive particle to initialize
            if (particles[i].life <= 0) {
                // Random angle for direction
                float angle = (float)rand() / RAND_MAX * 2 * M_PI;
                // Random speed between 2 and 5
                float speed = (float)rand() / RAND_MAX * 3 + 2;
                // Initialize particle
                particles[i].init(x, y, cos(angle) * speed, sin(angle) * speed, color);
                amount--;
            }
        }
    }

    // Clear all particles by resetting their properties
    void clearParticles() {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            // Set life to 0 to deactivate
            particles[i].life = 0;
            // Reset position
            particles[i].x = 0;
            particles[i].y = 0;
            // Reset velocity
            particles[i].vx = 0;
            particles[i].vy = 0;
        }
    }
};

#endif // PARTICLE_H
