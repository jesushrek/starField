#include "Random.h"
#include <iostream>
#include <vector>
#include <array>
#include <raylib.h>

#define MAX_STARS 1000
#define SPEED 10.0f

struct Star
{ 
    float x{};
    float y{};
    float z{};
};

int main() 
{ 
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    int screenWidth{ 0 };
    int screenHeight{ 0 };

    InitWindow(screenWidth, screenHeight, "Star Field");
    SetTargetFPS(60);

    std::vector<Star> stars(MAX_STARS);
    for(int i{}; i < MAX_STARS; ++i)
    { 
        stars[i].x = static_cast<float>(Random::get<int>(-screenWidth, screenWidth));
        stars[i].y = static_cast<float>(Random::get<int>(-screenHeight, screenHeight));
        stars[i].z  = static_cast<float>(Random::get<int>(-screenWidth, screenWidth));
    }

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    while(!WindowShouldClose()) 
    { 
        HideCursor();
        BeginDrawing();
        ClearBackground(BLACK);
        for(auto& star : stars)
        { 
            star.z -= SPEED;
            if(star.z <= 0)
            {   
                star.x = static_cast<float>(Random::get<int>(-screenWidth, screenWidth));
                star.y = static_cast<float>(Random::get<int>(-screenHeight, screenHeight));
                star.z = static_cast<float>(Random::get<int>(0, screenWidth));
            }

            float sx { (star.x / star.z) * (screenWidth / 2) + (screenWidth / 2) };
            float sy { (star.y / star.z) * (screenHeight / 2) + (screenHeight / 2) };

            float Starsize { 2.5f - (star.z / screenWidth) };

            if(sx >= 0 && sy >= 0 && sy < screenHeight)
                DrawRectangle(sx, sy, Starsize, Starsize, WHITE);

        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
