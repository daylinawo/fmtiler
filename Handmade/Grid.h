#ifndef GRID_H
#define GRID_H

#include <deque>
#include <fstream>
#include "GameObject.h"
#include "Tile.h"
#include "TexturePicker.h"
#include "Utility.h"
#include <vector>

class Grid : public GameObject
{
public:

	struct TileInfo
	{
	public:
		int ID;
		int xPos;
		int yPos;
	};

	struct TextureInfo
	{
	public:
		int ID;
		std::string imageName;
	};

	struct State
	{
	public:
		std::string textureID;
		Tile* tile;
	};

public:

	Grid();
	~Grid();

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	void SetTextureID(const std::string& ID);
	bool CheckCollision(AABB& collider);
	
public:

	void OnClick(const std::string& ID);
	void OnMouseOver(const std::string& ID);
	void OnMouseOut();

public:

	void Create();
	void Clear();
	void Load();
	bool Save(const std::map<std::string, std::string>& allTextures);
	void SaveAs(const std::map<std::string, std::string>& allTextures);
	void Undo();

private:

	bool Read(char* path);
	bool Write(const std::map<std::string, std::string>& allTextures);

private:

	Tile* m_currentTile;
	std::fstream m_file;
	std::string m_savePath;
	std::vector<Tile*> m_tiles;
	std::deque<State> m_states;
	std::string m_currentTextureID;
	std::map<std::string, int> m_settings;
};


#endif 
