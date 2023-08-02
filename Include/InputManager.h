#pragma once
#include "SDL.h"
#include <iostream>

class InputManager
{
public:
	enum class Action
	{
		LeftMovement,
		RightMovement,
		UpMovement,
		DownMovement,
		Left,
		Right,
		Up,
		Down,
		Shoot,
		Confirm,
		Back,
	};

	enum class Control
	{
		Keyboard,
		Controller
	};

	static bool GetKeyDown(Action _action);

	static SDL_GameController* GetController();
	static void SetController(SDL_GameController* _controller);

	Control GetControl() const;
	static void SetControl(Control _control);

private:
	static SDL_GameController* controller;

	static Control control;

	static bool KeyboardInput(Action _action);
	static bool ControllerInput(Action _action);
};