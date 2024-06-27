#include <SDL2/SDL.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Function to draw the Mandelbrot fractal
void drawMandelbrot(double xMin, double xMax, double yMin, double yMax) {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            // Map pixel coordinates to fractal coordinates
            double zx = x * (xMax - xMin) / WIDTH + xMin;
            double zy = y * (yMax - yMin) / HEIGHT + yMin;

            double cRe = zx;
            double cIm = zy;

            double xRe = zx;
            double yIm = zy;

            int iteration = 0;
            int maxIteration = 5000;

            while (xRe * xRe + yIm * yIm <= 4 && iteration < maxIteration) {
                double xTemp = xRe * xRe - yIm * yIm + cRe;
                yIm = 2 * xRe * yIm + cIm;
                xRe = xTemp;
                ++iteration;
            }

            // Map iteration count to color
            Uint8 r = (iteration * 1000) % 256;
            Uint8 g = (iteration * 300) % 256;
            Uint8 b = (iteration * 1000) % 256;

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Fractal Zoom", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        std::cerr << "SDL_CreateWindow or SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        return 1;
    }

    bool quit = false;

    double zoomFactor = 1.0;
    double xMin = -2.0;
    double xMax = 2.0;
    double yMin = -1.5;
    double yMax = 1.5;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Zoom in when the mouse is clicked
                double mouseX = event.button.x * (xMax - xMin) / WIDTH + xMin;
                double mouseY = event.button.y * (yMax - yMin) / HEIGHT + yMin;

                xMin = mouseX - (mouseX - xMin) * 0.5 / zoomFactor;
                xMax = mouseX + (xMax - mouseX) * 0.5 / zoomFactor;
                yMin = mouseY - (mouseY - yMin) * 0.5 / zoomFactor;
                yMax = mouseY + (yMax - mouseY) * 0.5 / zoomFactor;

                zoomFactor *= 1.5;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMandelbrot(xMin, xMax, yMin, yMax);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}