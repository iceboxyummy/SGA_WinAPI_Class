#include "stdafx.h"
#include "KeyManager.h"

void KeyManager::Init()
{
	ZeroMemory(key_state, sizeof(key_state));
}

void KeyManager::update()
{
	for (int key = 0; key < 256; key++)
	{
		if (GetAsyncKeyState(key) & 0x8000)
		{
			switch (key_state[key])
			{
			case Up:
			case Release:
				key_state[key] = Down;
				break;

			case Down:
				key_state[key] = State;
			}
		}
		else
		{
			switch (key_state[key])
			{
			case Down:
			case State:
				key_state[key] = Up;
				break;
			case Up:
				key_state[key] = Release;
				break;
			}
		}
	}
}