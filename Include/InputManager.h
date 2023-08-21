#pragma once
#include "SDL.h"
#include <iostream>
#include "Game.h"
#include "MainMenu.h"
#include "Enums.h"

class InputManager
{
public:
	// Return if the given input action key is pressed
	static bool GetKey(Action _action);

	// Return current active controller
	static SDL_GameController* GetController();
	// Set current active controller
	static void SetController(SDL_GameController* _controller);

	// Return current control type
	static Control GetControl();
	// Set current control type
	static void SetControl(Control _control);

	// Event function when input action key is pressed
	static void InputKeyDown();
	// Event function when input action key is lifted up
	static void InputKeyUp();
	// Event function when input action key is held down
	static void InputHold();

private:
	static SDL_GameController* controller;
	static Game* game;

	static Control control;

	// Handle keyboard input
	static bool KeyboardInput(Action _action);
	// Handle controller input
	static bool ControllerInput(Action _action);
};