#pragma once

#include "GameNode.h"

class MainGame : public GameNode
{
private:
	struct tagBox
	{
		RECT rt;
		float speed;
	};

public:
	MainGame();
	~MainGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	POINT ptPos1;
	RECT rtBox1;
	float fMoveSpeed;

	int nScore;
	int nLevel;

	vector<tagBox> vecBox;
	int nDelay;
};