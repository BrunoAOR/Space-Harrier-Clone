#ifndef H_INPUT_CONTROLLER
#define H_INPUT_CONTROLLER

#include <map>
#include "SDL2/include/SDL_stdinc.h"
#include "SDL2/include/SDL_scancode.h"


class InputController final
{
public:
	InputController();
	~InputController();

	bool getKey(SDL_Scancode scancode) const;
	bool getKeyUp(SDL_Scancode scancode) const;
	bool getKeyDown(SDL_Scancode scancode) const;

	void clearStates();
	void setKeyUp(SDL_Scancode scancode);
	void setKeyDown(SDL_Scancode scancode);

private:
	enum class KeyState {
		UP,
		DOWN
	};

	const Uint8* m_currentKeyStates = 0;
	std::map<SDL_Scancode, KeyState> m_keyUpDownStates;
};


#endif // !H_INPUT_CONTROLLER
