#pragma once
#include "GameNode.h"

class Object final: public GameNode
{
private:
	struct tagBox
	{
		RECT rt;
		float speed;
	};

public:
	Object();
	~Object();

	// GameNode��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetLevel(int n) { nLevel = n; }

	vector<tagBox>& GetBox() { return vecBox; }

private:
	vector<tagBox> vecBox;
	int nDelay;
	int nLevel;
};