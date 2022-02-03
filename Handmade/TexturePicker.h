#ifndef TEXTURE_PICKER_H
#define TEXTURE_PICKER_H

#include "GameObject.h"
#include "TextureButton.h"
#include "Utility.h"
#include <vector>

class TexturePicker : public GameObject
{
private:

	enum class Alignment { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

public:

	TexturePicker();
	~TexturePicker();

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	void CreateButtons();

public:

	TextureButton* GetTexture();
	const std::map<std::string, std::string>& GetTextures();
	
public:

	bool CheckCollision(AABB& collider);
	const std::string& OnClick();

private:

	Sprite m_background;
	std::string m_imageName;
	TextureButton* m_currentTexture;
	std::vector<TextureButton*> m_textureButtons;

	std::map <std::string, std::string> m_textures;
	std::map <std::string, int> m_settings;
};

#endif 

