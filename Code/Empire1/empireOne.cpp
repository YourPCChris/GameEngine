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

    public:
        virtual void Update() = 0;
        virtual void Draw() = 0;
};
class Panel : public GameObj
{
    public:
        void Update() override
        {
            std::cout << "Update..." << std::endl;
        }
        void Draw() override
        {
            std::cout << "Draw..." << std::endl;
        }
    private:

};

class Game
{
    public:
        Game()
        {
            InitWindow(screenWidth, screenHeight, "Empire");
            SetTargetFPS(60);

            //add game objs
            //gameObjects.push_back(std::make_unique<Panel>());
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
