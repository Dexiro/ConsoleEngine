#pragma once
#include <SDL.h>
#include "Vec2.h"

struct SDLInput
{
	const int keyMapSize = 512;
	bool keyMapPressed[512];
	bool keyMapReleased[512];
	bool keyMapDown[512];

	void Init()
	{
		for (int i = 0; i < keyMapSize; i++)
		{
			keyMapPressed[i] = false;
			keyMapReleased[i] = false;
			keyMapDown[i] = false;
		}
	}

	bool IsPressed(SDL_Scancode key)
	{
		return keyMapPressed[(int)key];
	}
	bool IsReleased(SDL_Scancode key)
	{
		return keyMapReleased[(int)key];
	}
	bool IsDown(SDL_Scancode key)
	{
		return keyMapDown[(int)key];
	}

	void UpdateKey(SDL_Scancode key, const Uint8 *keys)
	{
		int ikey = (int)key;

		keyMapPressed[ikey] = false;
		keyMapReleased[ikey] = false;

		if (keys[key])
		{
			if (keyMapDown[ikey] == false)
				keyMapPressed[ikey] = true;
			keyMapDown[ikey] = true;
		}
		else
		{
			if (keyMapDown[ikey] == true)
				keyMapReleased[ikey] = true;
			keyMapDown[ikey] = false;
		}
	}

	void Update()
	{
		SDL_PumpEvents();

		int x, y;
		SDL_GetMouseState(&x, &y);
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		/* Enter which keys are required */
		UpdateKey(SDL_SCANCODE_LEFT, keys);
		UpdateKey(SDL_SCANCODE_RIGHT, keys);
		UpdateKey(SDL_SCANCODE_UP, keys);
		UpdateKey(SDL_SCANCODE_DOWN, keys);
		UpdateKey(SDL_SCANCODE_W, keys);
		UpdateKey(SDL_SCANCODE_A, keys);
		UpdateKey(SDL_SCANCODE_S, keys);
		UpdateKey(SDL_SCANCODE_D, keys);
	}
};

class DirectionKeys
{
private:
	bool l_up, l_down, l_left, l_right;
	bool moveHoriz;

	void Init()
	{
		l_up = false;
		l_down = false;
		l_left = false;
		l_right = false;
		moveHoriz = false;
	}

	bool CheckPressed(bool key, bool& last_key)
	{
		if (key)
		{
			if (!last_key)
			{
				last_key = true;
				return true;
			}
		}
		else
		{
			last_key = false;
		}

		return false;
	}

public:
	DirectionKeys()
	{
		Init();
	}

	Vec2I GetDirectionVec(bool up, bool down, bool left, bool right)
	{
		Vec2I vec;

		if (up)
			vec += Vec2I(0, -1);

		if (down)
			vec += Vec2I(0, 1);

		if (left)
			vec += Vec2I(-1, 0);

		if (right)
			vec += Vec2I(1, 0);

		return vec;
	}



	Vec2I GetOrthDirectionVec(bool up, bool down, bool left, bool right)
	{
		//Check if a new key was pressed since last time
		int lastPressed = -1;
		if (CheckPressed(up, l_up)) lastPressed = 0;
		if (CheckPressed(down, l_down)) lastPressed = 1;
		if (CheckPressed(left, l_left)) lastPressed = 2;
		if (CheckPressed(right, l_right)) lastPressed = 3;

		// If Up or Down was pressed then set direction to vertical
		if (lastPressed == 0 || lastPressed == 1)
			moveHoriz = false;

		// If Left or Right was pressed then set direction to horizontal
		if (lastPressed == 2 || lastPressed == 3)
			moveHoriz = true;

		// If horizontal and left or right are pressed
		if (moveHoriz && (left || right))
		{
			return GetDirectionVec(false, false, left, right);
		}
		// If vertical and up or down are pressed
		else if (!moveHoriz && (up || down))
		{
			return GetDirectionVec(up, down, false, false);
		}

		return GetDirectionVec(up, down, left, right);
	}

};