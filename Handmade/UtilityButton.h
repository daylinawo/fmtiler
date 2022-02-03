#ifndef UTILITY_BUTTON_H
#define UTILITY_BUTTON_H

#include "Button.h"
#include "Text.h"

const int BUTTON_TEXT_CHAR_W = 14;
const int BUTTON_TEXT_CHAR_H = 28;

class UtilityButton : public Button
{

public:

	UtilityButton(const std::string& imageFilename, const std::string& text, int ID, int width, int height, int xPos, int yPos);
	~UtilityButton();

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	int GetID();

private:

	int m_ID;
	Text m_text;
	std::string m_imageName;
};


#endif

