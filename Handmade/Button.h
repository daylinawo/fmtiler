#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include "Sprite.h"
#include "AABB.h"


class Button : public GameObject
{
public:

	enum class State { DEFAULT = 1, HOVER = 2, ACTIVE = 3 };

public:

	Button();
	virtual ~Button() = 0;

public:

	virtual void Update(int deltaTime) = 0;
	virtual bool Draw() = 0;
	
public:

	virtual const AABB& GetCollider();

	virtual void SetState(State state);
	

protected:

	State m_state;
	Sprite m_image;
	AABB m_boxCollider;

};

#endif

