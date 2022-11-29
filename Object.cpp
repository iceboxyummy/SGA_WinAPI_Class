#include "stdafx.h"
#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Init()
{
	nDelay = 50;
}

void Object::Update()
{	// ���ڻ���
	if (nDelay >= 50)
	{
		tagBox box;

		box.rt.left = rand() % WINSIZE_X;
		box.rt.right = box.rt.left + 30;
		box.rt.top = -30;
		box.rt.bottom = 0;

		box.speed = rand() % 10 + 5;

		vecBox.push_back(box);

		nDelay = rand() % 40;
	}
	else nDelay += nLevel;

	// ���� �ϰ�
	for (auto iter = vecBox.begin(); iter != vecBox.end(); iter++)
	{
		iter->rt.top += iter->speed + nLevel;
		iter->rt.bottom += iter->speed + nLevel;

		RECT rtIter = iter->rt;
	}
}

void Object::Render()
{
	for (const auto& box : vecBox)
		RECT_DRAW(box.rt);
}
