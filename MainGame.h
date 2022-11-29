#pragma once
#include "GameNode.h"

class MainGame final : public GameNode
{
public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	int nScore;
	int nLevel;

	class Player* pPlayer;
	class Object* pObject;
};