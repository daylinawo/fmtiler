#ifndef EDITOR_MENU_H
#define EDITOR_MENU_H

#include "UtilityButton.h"
#include <vector>

const int BUTTON_WIDTH = 128;
const int BUTTON_HEIGHT = 52;

class EditorMenu : GameObject
{

public:

	EditorMenu(int xPos, int yPos);
	~EditorMenu();

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	void AddMenuItem(const std::string& text);
	int GetMenuOption();

public:

	void Reset();

private:

	int m_menuOptionChoice;
	std::vector<UtilityButton*> m_buttons;

};


#endif
