/*
 * Game Engine using raylib in C++ 
 * 
 * Christopher Bennett
 *
 * Start: 05/01/2025
 * End: ...
 * */

#include <iostream>
#include <vector>
#include "raylib.h"
#include <memory>
#include <chrono>
#include <thread>

//Classes
class Shape
{
	public:
		virtual ~Shape() = default;
		virtual void Draw() = 0;

		void changeX(int newX){ x = newX;}
		void changeY(int newY){ y = newY;}
		void changeColor(Color newColor){ color = newColor;}
		int getX() const { return x;}
		int getY() const { return y;}

	protected:
		int 
			width,
			height,
			x,
			y;
		Color color;
};

class Square: public Shape
{
	public:
		Square()
		{
			width = 40;
			height = 40;
			x = GetScreenWidth() / 10;
			y = GetScreenHeight() * 0.1;
			color = WHITE;
		}

		void Draw() override
		{
			DrawRectangle(x, y, width, height, color);
		}

		Rectangle GetShape() const
		{
			return Rectangle{(float)x, (float)y, (float)width, (float)height};
		}
};

class EmpireCircle: public Shape
{
	public:
		EmpireCircle()
		{
			x = GetScreenWidth() / 8.5;
			y = GetScreenHeight() * 0.25;
			radius = 20;
			color =  WHITE;
		}

		void Draw() override
		{
			DrawCircle(x, y, radius, color);
		}

		int getRadius() const { return radius;}

	private:
		int radius;
};

class HollowCircle: public Shape
{
	public:
		HollowCircle()
		{
			x = GetScreenWidth() / 8.5;
			y = GetScreenHeight() * 0.35;
			radius = 20;
			color =  WHITE;
		}

		void Draw() override
		{
			DrawCircleLines(x, y, radius, color);
		}

		int getRadius() const { return radius;}

	private:
		int radius;
};


//Functions
void MakeUserShape(int screenWidth, int shapeNum, std::vector<std::shared_ptr<Shape>>& shapes)
{
	//Wait for left click
	//If left click is past the Left hand panel
	//If left click is on the left hand panel then cancle
	//add shape to shapes vector
	//draw shapes in draw window function using DrawUserShapes() function 
	//end 
	std::cout << "Make User Shape function" << std::endl;
	bool timerOver = false;
	double startTime = GetTime();
	double timerLength = 5.00;
	std::shared_ptr<Shape> testShape = nullptr;


	while (timerOver == false)
	{
		//std::cout << "while loop" << std::endl;
		double elapsedTime = GetTime() - startTime;
		std::cout << "Elapsed Time: " << elapsedTime << std::endl;
	
		if (elapsedTime > timerLength){
			timerOver = true;
			std::cout << "Timer Over" << std::endl;
		}
	
		//Get New Shape position on mouse click
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (GetTime() - startTime) > 3){
			Vector2 MousePos = GetMousePosition();
			std::cout << "Mouse 'x': " << MousePos.x << " Mouse 'y': " << MousePos.y << std::endl;
			/*
			if (MousePos.x < screenWidth/3){ 
				std::cout << "Clicked on panel, cancling shape" << std::endl;
				return;
			}
			*/
			if (MousePos.x < screenWidth/3){
				switch (shapeNum)
				{
					case 0:
						//Square
						std::cout << "Square" << std::endl;
						//timerOver = true;
						testShape = std::make_shared<Square>();
						testShape->changeX(MousePos.x);
						testShape->changeY(MousePos.y);
						testShape->changeColor(RED);
						break;
					case 1:
						//Circle
						std::cout << "Circle" << std::endl;
						testShape = std::make_shared<EmpireCircle>();
						testShape->changeX(MousePos.x);
						testShape->changeY(MousePos.y);
						testShape->changeColor(RED);
						break;
					case 2:
						//Hollow Circle
						std::cout << "Hollow Circle" << std::endl;
						testShape = std::make_shared<HollowCircle>();
						testShape->changeX(MousePos.x);
						testShape->changeY(MousePos.y);
						testShape->changeColor(RED);
						break;
				}
				
				if (testShape != nullptr){ timerOver = true;}
			}	       
		}
	}
	if (testShape){ 
		shapes.push_back(testShape);
	}
	std::cout << "Function Over" << std::endl;
}

void DrawUserShapes(std::vector<std::shared_ptr<Shape>>& shapes)
{
	for (auto const& shape : shapes)
	{
		shape->Draw();
	}
}

void DrawPanelLeft(int screenWidth, int screenHeight, std::vector<std::shared_ptr<Shape>>& buttons, std::vector<std::shared_ptr<Shape>>& shapes)
{
	DrawRectangle(0,0, screenWidth/3, screenHeight, BLACK);
	DrawRectangleLines(0,0, screenWidth/3, screenHeight, GRAY);

	//Make Buttons
	if (buttons.empty()){
		buttons.push_back(std::make_shared<Square>());
		buttons.push_back(std::make_shared<EmpireCircle>());
		buttons.push_back(std::make_shared<HollowCircle>());
	}
	//Draw Buttons
	for (const auto& button : buttons)
	{
		button->Draw();
	}
	//Check if buttons are pressed
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		Vector2 MousePos = GetMousePosition();
		for (const auto& button : buttons)
		{
			if (auto square = std::dynamic_pointer_cast<Square>(button)){
				if (CheckCollisionPointRec(MousePos, square->GetShape())){
					std::cout << "Button Pressed" << std::endl;
					MakeUserShape(screenWidth, 0, shapes);
				}
			}
			else if (auto empireCircle = std::dynamic_pointer_cast<EmpireCircle>(button)){
				if (CheckCollisionPointCircle(MousePos,
							(Vector2){(float)empireCircle->getX(), (float)empireCircle->getY()}, (float)empireCircle->getRadius())){
					std::cout << "Circle Button Pressed" << std::endl;
					MakeUserShape(screenWidth, 1, shapes);
				}
			}
			else if (auto hollowCircle = std::dynamic_pointer_cast<HollowCircle>(button)){
				if (CheckCollisionPointCircle(MousePos, 
							(Vector2){(float)hollowCircle->getX(), (float)hollowCircle->getY()}, hollowCircle->getRadius())){
					std::cout << "Hollow Circle button pressed" << std::endl;
					MakeUserShape(screenWidth, 2, shapes);
				}
			}
		}				
	}
}

void DrawWindow(int screenWidth, int screenHeight, std::vector<std::shared_ptr<Shape>>& buttons, std::vector<std::shared_ptr<Shape>>& shapes)
{
	ClearBackground(BLUE);
	DrawPanelLeft(screenWidth, screenHeight, buttons, shapes);

	//Draw user shapes 
	DrawUserShapes(shapes);
}


int main()
{
	const int screenWidth = 1000;
	const int screenHeight = 800;

	std::vector<std::shared_ptr<Shape>> buttons;
	std::vector<std::shared_ptr<Shape>> shapes;


	InitWindow(screenWidth, screenHeight, "Empire");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();
			DrawWindow(screenWidth, screenHeight, buttons, shapes);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
