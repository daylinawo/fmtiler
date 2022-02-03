#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/*==============================================================================================#
|                                                                                               |
| Handmade Lite is an educational game engine, written by Karsten Vermeulen for the purposes of |
| educating other fellow programmers, programming students and anyone else wishing to learn     |
| about game development, C++ and OOP. The engine, class design and overall structure is by no  |
| means perfect and there is certainly room for improvement. Feel free to use, copy, break,     |
| update and do as you wish with this code - it is there, free, for all!                        |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|	                                                                                            |
| Please note, that this project is not open source and therefore has no license affiliated     |
| with it. However, feel free to use the engine to build your own game or learn from the code.  |
| Handmade Lite is an educational tool, designed to be used as such. Please be respectful and   |
| do not distribute the engine or its code as your own work. You may alter or tweak the engine  |
| code as a learning experience and you may also 'borrow' some code and functionality and use   |
| it to create your own game engine or game.                                                    |
|	                                                                                            |
#===============================================================================================#
|                                                                                               |
| If you like Handmade Lite and wish to show your support, if you have any questions about      |
| the project, or if you just want to reach out, please do get in touch:                        |
|																						        |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'GameObject' source files last updated in July 2020   	   			                        |
#==============================================================================================*/

#include <string>
#include <utility>
#include "Vector.h"

class GameObject 
{

public:

	GameObject();
	virtual ~GameObject() = 0 {}
	
public:

	bool IsAlive() const;
	bool IsActive() const;
	bool IsVisible() const;

	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsVisible(bool flag);

public:

	float GetAngle() const;
	int GetPriority() const;

	const std::string& GetTag() const;
	const Vector<int>& GetPosition() const;
	const Vector<int>& GetDimension() const;

	void SetPosition(int x, int y);
	void SetDimension(int x, int y);
	void SetTag(const std::string& tag);

public:

	virtual void Update(int deltaTime) = 0;
	virtual bool Draw() = 0;

protected:

	float m_angle;
	int m_priority;
	
	bool m_isAlive;
	bool m_isActive;
	bool m_isVisible;

	std::string m_tag;
	Vector<int> m_position;
	Vector<int> m_dimension;

};

#endif