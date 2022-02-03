#include "Debug.h"
#include "Grid.h"
#include "Screen.h"
#include <set>
#include "Input.h"
#include <Windows.h>
#include <Commdlg.h>

const int MAX_UNDO = 15;

Grid::Grid()
{
	m_currentTile = nullptr;

	int startPos = Utility::FindInFile("Assets/Files/ini.txt", "[GRID_SETTINGS]");

	if (startPos != NULL)
	{
		std::vector<std::string> allSettings;
		Utility::GetFileStrings("Assets/Files/ini.txt", startPos, '[', allSettings);

		if (!allSettings.empty())
		{
			for (auto it = allSettings.begin(); it != allSettings.end(); it++)
			{
				std::vector strings = Utility::ParseString((*it), '=');
				m_settings.insert({ strings[0], std::stoi(strings[1]) });
			}
		}
	}
}

void Grid::Create()
{
	SDL_Point resolution = Screen::Instance()->GetResolution();

	m_position.x = (resolution.x / 2 - (m_settings["Columns"] * (m_settings["TileSize"] +
		m_settings["GutterSize"]) - m_settings["GutterSize"]) / 2);

	m_position.y = (resolution.y / 2 - (m_settings["Rows"] * (m_settings["TileSize"] +
		m_settings["GutterSize"]) - m_settings["GutterSize"]) / 2);

	int squareXPos = m_position.x;
	int squareYPos = m_position.y;

	for (int i = 0; i < m_settings["Rows"]; i++)
	{
		for (int j = 0; j < m_settings["Columns"]; j++)
		{
			m_tiles.push_back(new Tile(std::to_string(m_settings["DefaultTextureID"]), m_settings["TileSize"],
									   m_settings["TileSize"], m_settings["TileSize"], squareXPos, squareYPos));

			squareXPos += (m_settings["TileSize"] + m_settings["GutterSize"]);
		}

		squareXPos = m_position.x;
		squareYPos += (m_settings["TileSize"] + m_settings["GutterSize"]);
	}
}

void Grid::Update(int deltaTime)
{
	//instantiate a box collider at point of mouse pointer.
	//we define it outside "isMouseClicked" check because
	//we want to apply a nice hover over effect on grid squares
	AABB collider;

	int posX = Input::Instance()->GetMousePosition().x;
	int posY = Input::Instance()->GetMousePosition().y;

	collider.SetPosition(posX, posY);

	//tile returns to previous texture after mouse leaves
	OnMouseOut();

	if (CheckCollision(collider))
	{
		if (!m_currentTextureID.empty())
		{
			//tile changes to the currently selected texture when hovering over it
			OnMouseOver(m_currentTextureID);
		}
	}

	static bool isButtonClicked = false;

	if (Input::Instance()->IsMouseClicked())
	{
		//change texture of grid square on click
		if (CheckCollision(collider) && !isButtonClicked)
		{
			if (!m_currentTextureID.empty())
			{
				OnClick(m_currentTextureID);
			}

			isButtonClicked = true;
		}
	}

	isButtonClicked = Input::Instance()->IsMouseClicked();

	for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}

bool Grid::Draw()
{
	for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
	{
		(*it)->Draw();
	}

    return true;
}

void Grid::SetTextureID(const std::string& ID)
{
	m_currentTextureID = ID;
}

bool Grid::CheckCollision(AABB& collider)
{
	for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
	{
		if ((*it)->GetCollider().IsColliding(collider))
		{
			m_currentTile = (*it);

			return true;
		}
	}

	return false;
}

void Grid::OnClick(const std::string& ID)
{
	if (m_currentTile)
	{
		//add this "previous state" of the current tile to deque 
		//so we can return to it if we click the undo button
		m_states.push_front({ m_currentTile->GetID(), m_currentTile });

		if (m_states.size() > MAX_UNDO)
		{
			m_states.pop_back();
		}

		m_currentTile->SetID(ID);
	}
}

void Grid::OnMouseOver(const std::string& ID)
{
	if (m_currentTile)
	{
		m_currentTile->OnMouseOver(ID);
	}
}

void Grid::OnMouseOut()
{
	if (m_currentTile)
	{
		m_currentTile->OnMouseOut();
	}
}

void Grid::Clear()
{
	for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
	{
		delete (*it);
	}

	m_tiles.clear();
	m_states.clear();
	m_savePath.clear();
	m_currentTile = nullptr;

}

void Grid::Undo()
{
	if (!m_states.empty())
	{
		State lastState = m_states.front();

		m_states.pop_front();

		lastState.tile->SetID(lastState.textureID);
	}
}

void Grid::Load()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Binary Files\0*.dat\0";
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a File";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	GetOpenFileNameA(&ofn);

	if (Read(ofn.lpstrFile))
	{
		std::vector pathParsed = Utility::ParseString(ofn.lpstrFile, '\\');
		std::string name = pathParsed.back();

		Debug::Log(name + " loaded");
	}
}

bool Grid::Save(const std::map<std::string, std::string>& allTextures)
{
	if (m_savePath.empty())
	{
		SaveAs(allTextures);

		return true;
	}

	if (Write(allTextures))
	{
		std::vector pathParsed = Utility::ParseString(m_savePath, '\\');
		std::string name = pathParsed.back();

		Debug::Log(name + " saved");
		return true;
	}
	
	Debug::Log("Level failed to save.");
	return false;
}

void Grid::SaveAs(const std::map<std::string, std::string>& allTextures)
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Binary Files\0*.dat\0";
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select a file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	GetSaveFileNameA(&ofn);

	m_savePath = ofn.lpstrFile;

	if (Write(allTextures))
	{
		std::vector pathParsed = Utility::ParseString(m_savePath, '\\');
		std::string name = pathParsed.back();

		Debug::Log(name + " saved");
	}


}

bool Grid::Read(char* path)
{
	m_file.open(path, std::ios_base::in | std::ios_base::binary);

	if (m_file.is_open())
	{
		//clear the previous grid
		Clear();

		//store the path to the binary file for the open level
		m_savePath = path;

		//variable to store number of textures used
		int totalTextures = 0;
		
		m_file.read(reinterpret_cast<char*>(&totalTextures), sizeof(int));

		//we skip over loading in the textures because
		//they should all already be loaded in our editor
		for (int i = 0; i < totalTextures; i++)
		{
			size_t len = 0;
			m_file.read(reinterpret_cast<char*>(&len), sizeof(len));
			
			len += sizeof(int);

			m_file.seekg(len, m_file.cur);
		}

		//a variable to temporarily store each tile's info
		TileInfo tileInfo;

		//a container for storing the info needed to load in each tile
		std::vector<TileInfo> gridInfo;
		
		//get all tile info from file
		while (m_file.read(reinterpret_cast<char*>(&tileInfo), sizeof(TileInfo)))
		{
			gridInfo.push_back(tileInfo);
		}

		//make grid with new info
		for (auto it = gridInfo.begin(); it != gridInfo.end(); it++)
		{
			m_tiles.push_back(new Tile(std::to_string(it->ID), m_settings["TileSize"], m_settings["TileSize"],
									   m_settings["TileSize"], it->xPos, it->yPos));
		}

		m_file.close();

		return true;
	}

	return false;
}

bool Grid::Write(const std::map<std::string, std::string>& allTextures)
{
	//Write grid to file
	m_file.open(m_savePath, std::ios_base::out | std::ios_base::binary);

	if (m_file.is_open())
	{			
		m_currentTile = nullptr;

		//a container used to store the IDs 
		//of all textures used in the grid
		std::set<int> textureIDs;

		//a container that stores the ID and 
		//position of tile in the grid
		std::vector<TileInfo> tileSaveInfo;

		//get the ID and position of all the
		//grid tiles and store it in a container
		for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
		{
			int ID = std::stoi((*it)->GetID());
			int xPos = (*it)->GetPosition().x;
			int yPos = (*it)->GetPosition().y;

			tileSaveInfo.push_back({ ID, xPos, yPos });

			//add the ID of each square to the set
			textureIDs.insert(ID);
		}

		//a container used to store info
		//on each different texture used
		std::vector<TextureInfo> textureSaveInfo;

		//use the texture IDs to get the info of
		//each texture and store it in a container
		for (auto ID : textureIDs)
		{
			auto it = allTextures.find(std::to_string(ID));
			
			if (it != allTextures.end())
			{
				textureSaveInfo.push_back( { ID, it->second } );
			}
		}

		//total amount of different textures used
		int totalTextures = textureSaveInfo.size();

		m_file.write(reinterpret_cast<char*>(&totalTextures), sizeof(int));

		//write the info of each texture to file
		for (auto it = textureSaveInfo.begin(); it != textureSaveInfo.end(); it++)
		{
			size_t len = (*it).imageName.size();
			
			//image name is a string, so we first need write its length to file
			m_file.write(reinterpret_cast<char*>(&len), sizeof(len));

			//then write the contents of the string to file
			m_file.write((*it).imageName.c_str(), len);

			//lastly, write the texture ID to file
			m_file.write(reinterpret_cast<char*>(&(*it).ID), sizeof(int));
		}

		//write the info of each tile to file
		for (auto it = tileSaveInfo.begin(); it != tileSaveInfo.end(); it++)
		{
			m_file.write(reinterpret_cast<char*>(&(*it)), sizeof(TileInfo));
		}

		m_file.close();

		return true;
	}

	return false;
}

Grid::~Grid()
{
	for (auto it = m_tiles.begin(); it != m_tiles.end(); it++)
	{
		delete (*it);
	}

	m_tiles.clear();
}