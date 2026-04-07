#include <SDL3/SDL.h>
void DrawSimpleCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
 for (int x = cx - radius; x <= cx + radius; x++) {
        for (int y = cy - radius; y <= cy + radius; y++) {
            // (x - cx)^2 + (y - cy)^2 <= radius^2 সূত্র
            int dx = x - cx;
            int dy = y - cy;
            if ((dx * dx) + (dy * dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    int width = 800;
    int height = 600;
    SDL_Window *window = SDL_CreateWindow("Task 101", width, height, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    int running = 1;
    SDL_Event event;

    int centerX = width / 2;
    int centerY = height / 2;
    int radius = 100;

    while (running == 1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0; 
            }
        }

        // ব্যাকগ্রাউন্ড কালো (0, 0, 0)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // বৃত্ত সাদা (255, 255, 255)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DrawSimpleCircle(renderer, centerX, centerY, radius);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
