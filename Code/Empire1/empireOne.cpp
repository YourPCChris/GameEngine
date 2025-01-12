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
class GameObj
{
    protected:
        Vector2 coord;
        Color color;
        int width,
            height;
        bool isButton;

    public:
        virtual void Update() = 0;
        virtual void Draw() = 0;
};
class Square : public GameObj
{
    public:
        Square(bool isNewButton, int x, int y, int newWidth=40, int newHeight=40)
        {
            color = GRAY;
            coord.x = x;
            coord.y = y;
            width = newWidth;
            height = newHeight;
            isButton = isNewButton;
        }

        void Update() override 
        {
            if (!isButton){
                std::cout << "Updating Square..." << std::endl;
            }
        }

        void Draw() override 
        {
            DrawRectangle(coord.x, coord.y, width, height, color);
        }
};
class ECircle : public GameObj
{
    public:
        ECircle(bool isNewButton, int x, int y, int newRadius=20)
        {
            coord.x = x+newRadius;
            coord.y = y;
            radius = newRadius;
            color = GRAY;
            isButton = isNewButton;
        }

        void Update() override 
        {
            if (!isButton){
                std::cout << "Updating ECircle..." << std::endl;
            }
        }

        void Draw() override
        {
            DrawCircle(coord.x, coord.y, radius, color);
        }
        
    private:
        int radius;
};
                    
class Panel : public GameObj
{
    public:
        Panel()
        {
            coord.x= 0;
            coord.y= 0;
            width = GetScreenWidth() / 3;
            height = GetScreenHeight();
            color = BLACK;
            isButton = false;

            buttons.push_back(std::make_unique<Square>(true, width/4, height*0.3));
            buttons.push_back(std::make_unique<ECircle>(true, width/4, height*0.4));
        }

        void Update() override
        {
            if (!isButton){
                std::cout << "Updating Panel.." << std::endl;
            }
        }

        void Draw() override
        {
            std::cout << "Draw..." << std::endl;
            DrawRectangle(coord.x, coord.y, width, height, color);

            for (auto& button : buttons)
            {
                if (button){
                    button->Draw();
                }
            }
        }

    private:
        std::vector<std::unique_ptr<GameObj>> buttons;
};

class Game
{
    public:
        Game()
        {
            InitWindow(screenWidth, screenHeight, "Empire");
            SetTargetFPS(60);

            //add game objs
            gameObjs.push_back(std::make_unique<Panel>());
        }

        void Run()
        {
            while (!WindowShouldClose())
            {
                for (auto& obj : gameObjs)
                {
                    obj->Update();
                }

                BeginDrawing();
                    ClearBackground(RAYWHITE);

                    for (auto& obj : gameObjs)
                    {
                        obj->Draw();
                    }
                EndDrawing();
            }
            CloseWindow();
        }

    private:
        const int screenWidth = 1000;
        const int screenHeight = 800;
        std::vector<std::unique_ptr<GameObj>> gameObjs;
};

int main()
{
    std::cout << "We Ball" << std::endl;

    try
    {
        auto game = std::make_unique<Game>();
        game->Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
