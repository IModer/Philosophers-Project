#include "../Header/global.h"
#include <raylib.h>

int main()
{
    InitWindow(800, 400, "test");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        ClearBackground(RAYWHITE);
        BeginDrawing();
        DrawRectangle(200, 200, 100, 100, RED);
        EndDrawing();
    }
}