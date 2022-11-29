#pragma once

enum KEY_STATE
{
	Release,
	Down,
	Up,
	State
};

class KeyManager final
{
public:
	static KeyManager& Get()
	{
		static KeyManager key;
		return key;
	}

	void Init();

	void update();

	bool IsRelease(int key) { return key_state[key] == Release; }
	bool IsDown(int key) { return key_state[key] == Down; }
	bool IsUp(int key) { return key_state[key] == Up; }
	bool IsState(int key) { return key_state[key] == State; }

private:
	KeyManager() = default;

private:
	KEY_STATE key_state[256];
};