#pragma once


class GameNode
{
public: 
	GameNode();
	virtual ~GameNode();

	  virtual void Init() = 0;
	  virtual void Update() = 0;
	  virtual void Render() = 0;
};