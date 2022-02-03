#include "Tile.h"

Tile::Tile(const std::string& textureID, int ImageWidth, int imageHeight, int size, int xPos, int yPos)
{
	m_ID = textureID;
	m_defaultTexture = textureID;

	static bool isLoaded = false;

	m_image.SetImage(textureID);
	m_image.SetSpriteDimension(size, size);
	m_image.SetImageDimension(1, 1, size, size);

	m_position = { xPos, yPos };
	m_boxCollider.SetDimension(size, size);
	m_boxCollider.SetPosition(xPos, yPos);
}

void Tile::Update(int deltaTime)
{

}

bool Tile::Draw()
{
	m_image.Draw(m_position.x, m_position.y);

	return true;
}

const std::string& Tile::GetID()
{
	return m_ID;
}

void Tile::SetID(const std::string& ID)
{
	m_ID = ID;
	m_image.SetImage(ID);
}

void Tile::OnMouseOver(const std::string& ID)
{
	m_image.SetImage(ID);
}

void Tile::OnMouseOut()
{
	m_image.SetImage(m_ID);
}

void Tile::Reset()
{
	m_ID = m_defaultTexture;
	m_image.SetImage(m_ID);
}

Tile::~Tile()
{

}