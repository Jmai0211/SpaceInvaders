#pragma once
#include "SDL.h"
#include <iostream>
#include "Game.h"
#include "MainMenu.h"

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

	static bool GetKey(Action _action);

	static SDL_GameController* GetController();
	static void SetController(SDL_GameController* _controller);

	static Control GetControl();
	static void SetControl(Control _control);

	static void InputKeyDown();
	static void InputKeyUp();

	static void InputHold();

private:
	static SDL_GameController* controller;
	static Game* game;

	static Control control;

	static bool KeyboardInput(Action _action);
	static bool ControllerInput(Action _action);
};