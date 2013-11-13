#pragma once
#include "Main.h"
#include "Objects/Actor.h"

class Hero : public Actor
{
public:
	Hero();
	~Hero();

	virtual void Update();
};