#include <SDL3/SDL.h>
#include <stdbool.h>
#include <math.h>

void DrawCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius * 2);

    while (x >= y) {
        SDL_RenderPoint(renderer, cx + x, cy + y);
        SDL_RenderPoint(renderer, cx + y, cy + x);
        SDL_RenderPoint(renderer, cx - y, cy + x);
        SDL_RenderPoint(renderer, cx - x, cy + y);
        SDL_RenderPoint(renderer, cx - x, cy - y);
        SDL_RenderPoint(renderer, cx - y, cy - x);
        SDL_RenderPoint(renderer, cx + y, cy - x);
        SDL_RenderPoint(renderer, cx + x, cy - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius * 2);
        }
    }
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return 1;
    }

    int windowWidth = 800;
    int windowHeight = 600;
    SDL_Window *window = SDL_CreateWindow("Task 103 - Collision Detection", windowWidth, windowHeight, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    bool running = true;
    SDL_Event event;

    // Circle 1: Left to right continuously move করবে
    float c1_x = 0.0f;
    float c1_y = windowHeight / 2.0f;
    int c1_r = 40;
    float c1_speed = 4.0f;

    // Circle 2: Keyboard দিয়ে control করা হবে
    float c2_x = windowWidth / 2.0f;
    float c2_y = 50.0f; // Initial y=0 এর কাছাকাছি
    int c2_r = 40;
    float c2_speed = 5.0f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

       // Circle 2 (Player) এর Keyboard Input (Up, Down, Left, Right)
        const bool *keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_UP])    c2_y -= c2_speed;
        if (keyboardState[SDL_SCANCODE_DOWN])  c2_y += c2_speed;
        if (keyboardState[SDL_SCANCODE_LEFT])  c2_x -= c2_speed;
        if (keyboardState[SDL_SCANCODE_RIGHT]) c2_x += c2_speed;

        // Circle 1 (Auto) এর Movement
        c1_x += c1_speed;
        if (c1_x - c1_r > windowWidth) {
            c1_x = -c1_r; // ডান দিকে পার হয়ে গেলে বাম দিক থেকে আবার শুরু
        }
        // Collision Detection: দুটি বৃত্তের কেন্দ্রের দূরত্ব মাপা
        float distanceX = c2_x - c1_x;
        float distanceY = c2_y - c1_y;
        float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
        
        bool isColliding = (distance <= (c1_r + c2_r));

        if (isColliding) {
            // Collision হলে Background কালার লাল হয়ে যাবে
            SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255); 
        } else {
            // Collision না হলে Background কালো থাকবে
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        SDL_RenderClear(renderer);

        // Draw Circle 1 (সবুজ)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        DrawCircle(renderer, (int)c1_x, (int)c1_y, c1_r);

        // Draw Circle 2 (নীল)
        SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
        DrawCircle(renderer, (int)c2_x, (int)c2_y, c2_r);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
