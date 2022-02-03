#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

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
| 'PlayState' source files last updated in May 2020   							                |
#==============================================================================================*/

#include "Background.h"
#include "GameObject.h"
#include "GameState.h"
#include "Grid.h"
#include <map>
#include "Sprite.h"
#include "TexturePicker.h"
#include "EditorMenu.h"
#include <vector>

class EditorState : public GameState
{

public:

	enum class MenuOption { NEW, SAVE, SAVEAS, LOAD, UNDO, QUIT };

public:

	EditorState();
	virtual ~EditorState() {}

public:

	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

private:

	Grid* m_grid;
	Background* m_image;
	EditorMenu* m_editorMenu;
	TexturePicker* m_texturePicker;

};

#endif