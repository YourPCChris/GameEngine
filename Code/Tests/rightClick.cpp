//Testing if right click works 
//
//



#include <iostream>
#include "raylib.h"



int main ()
{
	std::cout << "Main" << std::endl;

	InitWindow(1000, 800, "Test");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{

		BeginDrawing();
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
					std::cout << "Right Clicked" << std::endl;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				std::cout << "Left clicked" << std::endl;

			EndDrawing();
	}
}	
