#include "InputController.h"

#include "SDL2/include/SDL_keyboard.h"


InputController::InputController()
{
	m_currentKeyStates = SDL_GetKeyboardState(NULL);
}


InputController::~InputController()
{
	m_currentKeyStates = nullptr;
}


bool InputController::getKey(SDL_Scancode scancode) const
{
	return m_currentKeyStates[scancode];
}


bool InputController::getKeyUp(SDL_Scancode scancode) const
{
	if (m_keyUpDownStates.count(scancode))
	{
		return m_keyUpDownStates.at(scancode) == KeyState::UP;
	}
	return false;
}


bool InputController::getKeyDown(SDL_Scancode scancode) const
{
	if (m_keyUpDownStates.count(scancode))
	{
		return m_keyUpDownStates.at(scancode) == KeyState::DOWN;
	}
	return false;
}


void InputController::clearStates()
{
	m_keyUpDownStates.clear();
}


void InputController::setKeyUp(SDL_Scancode scancode)
{
	m_keyUpDownStates[scancode] = KeyState::UP;
}


void InputController::setKeyDown(SDL_Scancode scancode)
{
	m_keyUpDownStates[scancode] = KeyState::DOWN;
}
