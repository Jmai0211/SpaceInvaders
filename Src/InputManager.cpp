#include "InputManager.h"
#include "GameManager.h"
#include "ECS.h"
#include "Components.h"

SDL_GameController* InputManager::controller = nullptr;
InputManager::Control InputManager::control = InputManager::Control::Keyboard;

Game* InputManager::game;

// get if input key is pressed
bool InputManager::GetKey(Action _action)
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

void InputManager::InputKeyDown()
{
    switch (GameManager::GetInstance().GetState())
    {
    case GameManager::GameState::Menu:
        if (GetKey(Action::Confirm))
        {
            game->menu.MenuConfirm();
        }
        else if (GetKey(Action::Up))
        {
            game->menu.MenuUp();
        }
        else if (GetKey(Action::Down))
        {
            game->menu.MenuDown();
        }
        break;
    case GameManager::GameState::Option:
        if (GetKey(Action::Back))
        {
            game->menu.OptionBack();
        }
        else if (GetKey(Action::Left))
        {
            game->menu.OptionLeft();
        }
        else if (GetKey(Action::Right))
        {
            game->menu.OptionRight();
        }
        else if (GetKey(Action::Up))
        {
            game->menu.OptionUp();
        }
        else if (GetKey(Action::Down))
        {
            game->menu.OptionDown();
        }
        break;
    case GameManager::GameState::Playing:
        break;
    case GameManager::GameState::GameOver:
        if (GetKey(Action::Back))
        {
            game->Restart();
        }
        break;
    default:
        break;
    }
}

void InputManager::InputKeyUp()
{
    switch (GameManager::GetInstance().GetState())
    {
    case GameManager::GameState::Menu:
        break;
    case GameManager::GameState::Option:
        break;
    case GameManager::GameState::Playing:
        if (!GetKey(Action::LeftMovement) && !GetKey(Action::RightMovement))
        {
            game->player->GetComponent<PlayerComponent>().HorizontalMovement(0);
        }
        break;
    case GameManager::GameState::GameOver:
        break;
    default:
        break;
    }
}

void InputManager::InputHold()
{
    switch (GameManager::GetInstance().GetState())
    {
    case GameManager::GameState::Menu:
        break;
    case GameManager::GameState::Option:
        break;
    case GameManager::GameState::Playing:
        if (GetKey(Action::LeftMovement))
        {
            game->player->GetComponent<PlayerComponent>().HorizontalMovement(-1);
        }
        else if (GetKey(Action::RightMovement))
        {
            game->player->GetComponent<PlayerComponent>().HorizontalMovement(1);
        }
        else if (!GetKey(Action::LeftMovement) && !GetKey(Action::RightMovement))
        {
            game->player->GetComponent<PlayerComponent>().HorizontalMovement(0);
        }
        
        if (GetKey(Action::Shoot))
        {
            game->player->GetComponent<PlayerComponent>().Attack();
        }
        break;
    case GameManager::GameState::GameOver:
        break;
    default:
        break;
    }
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
