#pragma once
#include "GameNode.h"
class Player final: public GameNode
{
public:
	Player();
	~Player();

	// GameNode을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	RECT& GetRect() { return rtBox1; }

private:
	POINT ptPos1;
	RECT rtBox1;
	float fMoveSpeed;
};

