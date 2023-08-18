#include "InputManager.h"
#include "GameManager.h"

SDL_GameController* InputManager::controller = nullptr;
InputManager::Control InputManager::control = InputManager::Control::Keyboard;

// get if input key is pressed
bool InputManager::GetKeyDown(Action _action)
{
    switch (control)
    {
    case InputManager::Control::Keyboard:
        return KeyboardInput(_action);
    case InputManager::Control::Controller:
        return ControllerInput(_action);
    default:
        return false;
    }
}

// return the connected controller, nullptr if no connected controller
SDL_GameController* InputManager::GetController()
{
    return controller;
}

// set controller reference
void InputManager::SetController(SDL_GameController* _controller)
{
    controller = _controller;
}

// get current control method: keyboard / controller
InputManager::Control InputManager::GetControl()
{
    return control;
}

// update current control method
void InputManager::SetControl(Control _control)
{
    control = _control;
}

// handle keyboard input
bool InputManager::KeyboardInput(Action _action)
{
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    switch (_action)
    {
    case Action::LeftMovement:
        return keyState[SDL_SCANCODE_LEFT] != 0;
    case Action::RightMovement:
        return keyState[SDL_SCANCODE_RIGHT] != 0;
    case Action::UpMovement:
        return keyState[SDL_SCANCODE_UP] != 0;
    case Action::DownMovement:
        return keyState[SDL_SCANCODE_DOWN] != 0;
    case Action::Left:
        return keyState[SDL_SCANCODE_LEFT] != 0;
    case Action::Right:
        return keyState[SDL_SCANCODE_RIGHT] != 0;
    case Action::Up:
        return keyState[SDL_SCANCODE_UP] != 0;
    case Action::Down:
        return keyState[SDL_SCANCODE_DOWN] != 0;
    case Action::Shoot:
        return keyState[SDL_SCANCODE_SPACE] != 0;
    case Action::Confirm:
        return keyState[SDL_SCANCODE_RETURN] != 0;
    case Action::Back:
        return keyState[SDL_SCANCODE_ESCAPE] != 0;
    default:
        return false;
    }
}

// handle controller input
bool InputManager::ControllerInput(Action _action)
{
    if (controller != nullptr)
    {
        int deadZone = 8000;
        switch (_action)
        {
        case Action::LeftMovement:
            return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) < -deadZone;
        case Action::RightMovement:
            return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) > deadZone;
        case Action::UpMovement:
            return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < -deadZone;
        case Action::DownMovement:
            return SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > deadZone;
        case Action::Up:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) != 0;
        case Action::Down:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) != 0;
        case Action::Left:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) != 0;
        case Action::Right:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) != 0;
        case Action::Shoot:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) != 0;
        case Action::Confirm:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) != 0;
        case Action::Back:
            return SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) != 0;
        default:
            return false;
        }
    }
    else
    {
        std::cout << "no controller" << std::endl;
        return false;
    }
}
