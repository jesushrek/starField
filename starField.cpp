#include "Random.h"
#include <iostream>
#include <vector>
#include <array>
#include <raylib.h>

#define MAX_STARS 10000 
#define SPEED 10.0f

struct Star
{ 
    float x{};
    float y{};
    float z{};

    float previousZ{};
};

int main() 
{ 
    int screenWidth{ 1000 };
    int screenHeight{ 1000 };

    InitWindow(screenWidth, screenHeight, "Star Field");
    SetTargetFPS(60);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();


    std::vector<Star> stars(MAX_STARS);
    for(int i{}; i < MAX_STARS; ++i)
    { 
        stars[i].x = static_cast<float>(Random::get<int>(-screenWidth, screenWidth));
        stars[i].y = static_cast<float>(Random::get<int>(-screenHeight, screenHeight));
        stars[i].z = stars[i].previousZ = static_cast<float>(Random::get<int>(1, screenWidth));
    }
    while(!WindowShouldClose()) 
    { 
        HideCursor();
        BeginDrawing();
        ClearBackground(BLACK);
        for(auto& star : stars)
        { 
            star.previousZ = star.z;
            star.z -= IsKeyDown(KEY_SPACE)? 35 : SPEED;
            if(star.z <= 0)
            {   
                star.z = static_cast<float>(Random::get<int>(1, screenWidth));
                star.previousZ = star.z;
                star.x = static_cast<float>(Random::get<int>(-screenWidth, screenWidth));
                star.y = static_cast<float>(Random::get<int>(-screenHeight, screenHeight));
            }

            // (x / z) * FOV + centre
            float sx { (star.x / star.z) * (screenWidth / 2) + (screenWidth / 2) };
            float sy { (star.y / star.z) * (screenHeight / 2) + (screenHeight / 2) };

            float px { (star.x / star.previousZ) * (screenWidth / 2) + (screenWidth / 2) };
            float py { (star.y / star.previousZ) * (screenHeight / 2) + (screenHeight / 2) };


            float Starsize { 1.0f - (star.z / screenWidth) };
            Color starColor { ColorFromNormalized( { Starsize, Starsize, Starsize, 1.0f } )};

            if(sx >= 0 && sx < screenWidth && sy >= 0 && sy < screenHeight)
                DrawLineEx({px, py}, {sx, sy}, 1.0f * Starsize, starColor);

        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
