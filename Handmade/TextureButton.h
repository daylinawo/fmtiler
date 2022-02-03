#ifndef TEXTURE_BUTTON_H
#define TEXTURE_BUTTON_H

#include "Button.h"

class TextureButton : public Button
{
public:

	TextureButton(const std::string& imageFilename, const std::string& ID, int width, int height, int size, int xPos = 0, int yPos = 0);
	~TextureButton();

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	void OnClick();

public:

	const std::string& GetID();
	void SetPosition(int x, int y);

private:

	std::string m_ID;
	Sprite m_activeImage;
};

#endif 
