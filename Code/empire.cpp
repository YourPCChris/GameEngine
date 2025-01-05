/*
 * Raylib game engine using raylib 
 *
 * Christopher Bennett
 *
 * Start: 05/01/2025
 * */

#include <iostream>
#include "raylib.h"
#include <vector>
#include <algorithm>
#include <chrono>

//Classes 
class Shape
{
	public:
		void MakeShape()
		{
			DrawRectangle(x,y,width,height,color);
		}

	protected:
		int width,
		    height,
		    x,
		    y;
		Color color;
};


//Functions 
void DrawPanelLeft(int panWidth, int panHeight)
{
	DrawRectangle(0, 0, panWidth, panHeight, BLACK);
	DrawRectangleLines(0,0, panWidth, panHeight, GRAY);
	
	//Draw Square Button
	
	
}

void DrawWindow(int screenWidth, int screenHeight, int panWidth, int panHeight)
{
	//Background Colour
	ClearBackground(BLUE);

	//Draw left panel
	DrawPanelLeft(panWidth, panHeight);
}


int main()
{
	using namespace std;

	//Define Vars
	const int screenWidth = 1000;
	const int screenHeight = 800;
	const int panWidth = screenWidth/3;
	const int panHeight = screenHeight;
	vector<Shape> buttons;
	vector<Shape> shapes;

	
	InitWindow(screenWidth, screenHeight, "Empire");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	//Main Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
			DrawWindow(screenWidth, screenHeight, panWidth, panHeight);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}

	
	
