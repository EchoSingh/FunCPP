#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int HEART_CENTER_X = SCREEN_WIDTH / 2;
const int HEART_CENTER_Y = SCREEN_HEIGHT / 2;
const int HEART_SCALE_BASE = 50; // Base scale for the heart
const float HEART_BEAT_SPEED = 2.0f; // Speed of the heartbeat

void drawPolarHeart(SDL_Renderer* renderer, int centerX, int centerY, int scale) {
    // Set color for the heart
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw heart using polar equation
    for (float theta = 0; theta < 2 * M_PI; theta += 0.01f) {
        // Polar equation for the heart
        float r = 2 - 2 * std::sin(theta) + (std::sin(theta) * std::sqrt(std::cos(theta) * std::cos(theta))) / (std::sin(theta) + 1.4);

        // Convert polar to Cartesian
        int x = static_cast<int>(centerX + scale * r * std::cos(theta));
        int y = static_cast<int>(centerY - scale * r * std::sin(theta)); // Negative for SDL's y-axis

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Pumping Heart",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool isRunning = true;
    SDL_Event event;

    float time = 0.0f; // Time variable for heartbeat animation

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Calculate dynamic scale for the heartbeat
        int currentScale = HEART_SCALE_BASE + static_cast<int>(10 * std::sin(time * HEART_BEAT_SPEED));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawPolarHeart(renderer, HEART_CENTER_X, HEART_CENTER_Y, currentScale);

        SDL_RenderPresent(renderer);

        // Update time for animation
        time += 0.016f; // Approx. 60 FPS

        SDL_Delay(16); // Delay to limit frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
