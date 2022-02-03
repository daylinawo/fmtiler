#ifndef TILE_H
#define TILE_H

#include "Button.h"

class Tile : public Button
{

public:

	Tile(const std::string& textureID, int ImageWidth, int imageHeight, int size, int xPos, int yPos);
	~Tile();

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	const std::string& GetID();
	void SetID(const std::string& ID);

	void OnMouseOver(const std::string& ID);
	void OnMouseOut();

public:

	void Reset();

private:

	std::string m_ID;
	std::string m_defaultTexture;
};

#endif
