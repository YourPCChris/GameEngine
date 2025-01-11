/*Empire 1.0
 *
 * Christopher Bennett
 *
 * */


#include <iostream>
#include <memory>
#include <vector>
#include "raylib.h"

//Classes
class Button
{
    public:
    protected:
        int x,
            y,
            width,
            height;
};
class Panel
{
    public:

    private:
        int x,
            y,
            width,
            height;
        std::vector<std::shared_ptr<Button>> buttons;
};


//Functions
void DrawLeftPanel(const int screenWidth, const int screenHeight)
{
    //panel->Draw();
}

void DrawWindow(const int screenWidth, const int screenHeight)
{
    ClearBackground(BLUE);

    //Draw Left Panel
    DrawLeftPanel(screenWidth, screenHeight);
    //Draw User made buttons
}


int main()
{
    std::cout << "We Ball" << std::endl;
     
    const int screenWidth = 1000, screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Empire");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();
            DrawWindow(screenWidth, screenHeight);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
