#include "raylib.h"

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib - get text bounds");

    const char *buttonText = "Click Me!";
    int fontSize = 30;

    // Measure text width
    int textWidth = MeasureText(buttonText, fontSize);
    int textHeight = fontSize;  // In raylib, the text height is typically the font size

    // Position the button
    Rectangle buttonBounds;
    buttonBounds.x = screenWidth / 2 - textWidth / 2 - 10; // 10 pixels padding
    buttonBounds.y = screenHeight / 2 - textHeight / 2 - 5; // 5 pixels padding
    buttonBounds.width = textWidth + 20;  // Add padding to width
    buttonBounds.height = textHeight + 10; // Add padding to height

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw button (rectangle)
        DrawRectangleRec(buttonBounds, LIGHTGRAY);

        // Draw button text
        DrawText(buttonText, 
                 buttonBounds.x + buttonBounds.width/2 - textWidth/2, 
                 buttonBounds.y + buttonBounds.height/2 - textHeight/2, 
                 fontSize, 
                 BLACK);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
