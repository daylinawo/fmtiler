#include "TextureButton.h"

TextureButton::TextureButton(const std::string& imageFilename, const std::string& ID, int width, int height, int size, int xPos, int yPos)
{
	m_ID = ID;

	m_image.Load(imageFilename, ID);
	m_image.SetImage(ID);
	m_image.SetSpriteDimension(size, size);
	m_image.SetImageDimension(1, 1, width, height);

	static bool isLoaded = false;

	if (!isLoaded)
	{
		m_image.Load("Assets/Images/Textures/Active_32x32.png", "TextureButton_Active");
		isLoaded = true;
	}

	m_activeImage.SetImage("TextureButton_Active");
	m_activeImage.SetSpriteDimension(size, size);
	m_activeImage.SetImageDimension(1, 1, width, height);

	m_position = { xPos, yPos };
	m_boxCollider.SetDimension(size, size);
	m_boxCollider.SetPosition(GetPosition().x, GetPosition().y);

}

void TextureButton::Update(int deltaTime)
{

}

bool TextureButton::Draw()
{
	m_image.Draw(m_position.x, m_position.y);

	switch (m_state)
	{
	case State::DEFAULT:
	{
		//
		break;
	}
	case State::HOVER:
	{
		//
		break;
	}
	case State::ACTIVE:
	{
		m_activeImage.Draw(m_position.x, m_position.y);
		break;
	}
	}

	return false;
}

void TextureButton::SetPosition(int x, int y)
{
	m_position = { x, y };
	m_boxCollider.SetPosition(x, y);
}

void TextureButton::OnClick()
{
	m_state = State::ACTIVE;
}

const std::string& TextureButton::GetID()
{
	return m_ID;
}

TextureButton::~TextureButton()
{
	m_image.Unload(m_ID);

	static bool isUnloaded = false;

	if (!isUnloaded)
	{
		m_activeImage.Unload("TextureButton_Active");
		isUnloaded = true;
	}
}