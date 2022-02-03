#include "Debug.h"
#include <fstream>
#include "Input.h"
#include "TexturePicker.h"
#include "Screen.h"

const int MARGIN = 50;

TexturePicker::TexturePicker()
{
	m_imageName = "";
	m_currentTexture = nullptr;

	//locate the start position of the settings in the text file
	int startPos = Utility::FindInFile("Assets/Files/ini.txt", "[TEXTURE_PICKER_SETTINGS]");
	
	//get all texture picker settings from the text file and store it in a map
	if (startPos != NULL)
	{
		std::vector<std::string> settings;
		Utility::GetFileStrings("Assets/Files/ini.txt", startPos, '[', settings);

		if (!settings.empty())
		{
			for (auto it = settings.begin(); it != settings.end(); it++)
			{
				std::vector info = Utility::ParseString((*it), '=');

				if (info[0] == "BackgroundImage")
				{
					m_imageName = info[1];
					continue;
				}

				m_settings.insert({ info[0], std::stoi(info[1]) });
			}
		}
	}
	
	SDL_Point resolution = Screen::Instance()->GetResolution();

	Alignment alignment = static_cast<Alignment>(m_settings["Alignment"]);

	//we use a switch statement to set 
	//the position of the picker panel
	switch (alignment)
	{
		case Alignment::TOP_LEFT:
			m_position = {MARGIN, MARGIN};
			break;	
		case Alignment::TOP_RIGHT:
			m_position = { resolution.x - (m_settings["Width"] + MARGIN), MARGIN };
			break;	
		case Alignment::BOTTOM_LEFT:
			m_position = { MARGIN, resolution.y - (m_settings["Height"] + MARGIN) };
			break;
		case Alignment::BOTTOM_RIGHT:
			m_position = { resolution.x - (m_settings["Width"] + MARGIN), 
						   resolution.y - (m_settings["Height"] + MARGIN) };
			break;
		default:
			m_position = { resolution.x - (m_settings["Width"] + MARGIN), MARGIN };
	}

	//setup background image
	m_background.Load(m_imageName, m_imageName);
	m_background.SetImage(m_imageName);
	m_background.SetImageDimension(1, 1, m_settings["Width"], m_settings["Height"]);
	m_background.SetSpriteDimension(m_settings["Width"], m_settings["Height"]);
}

void TexturePicker::CreateButtons()
{
	//locate the start position of the textures info in the text file
	int startPos = Utility::FindInFile("Assets/Files/ini.txt", "[TEXTURES]");

	//get each texture's info from ini file and store it in a map
	if (startPos != NULL)
	{
		std::vector<std::string> loadedTextures;
		Utility::GetFileStrings("Assets/Files/ini.txt", startPos, '[', loadedTextures);

		if (!loadedTextures.empty())
		{
			for (auto it = loadedTextures.begin(); it != loadedTextures.end(); it++)
			{
				std::vector texture = Utility::ParseString((*it), '=');
				m_textures.insert({ texture[0], texture[1] });
			}
		}
	}

	//loop through and create a button from each texture
	for (auto it = m_textures.begin(); it != m_textures.end(); it++)
	{
		m_textureButtons.push_back(new TextureButton(it->second, it->first, m_settings["ButtonSize"],
			m_settings["ButtonSize"], m_settings["ButtonSize"]));
	}

	//algorithm to structure the layout of the
	//texture buttons in the texture picker
	int gutter = 15;
	int TexturesPerRow = Utility::FindElemsPerRow(m_settings["Width"], m_settings["ButtonSize"], gutter, m_textureButtons.size());
	int rowWidth = ((m_settings["ButtonSize"] + gutter) * TexturesPerRow) - gutter;

	int leftPadding = (m_settings["Width"] - rowWidth) / 2;
	int topPadding = leftPadding;

	int buttonXPos = m_position.x + leftPadding;
	int buttonYPos = m_position.y + topPadding;

	//loop through and set the position of each texture button
	for (size_t i = 0; i < m_textureButtons.size(); i++)
	{
		m_textureButtons[i]->SetPosition(buttonXPos, buttonYPos);

		buttonXPos += m_settings["ButtonSize"] + gutter;

		if ((i + 1) % TexturesPerRow == 0)
		{
			buttonXPos = m_position.x + leftPadding;
			buttonYPos += m_settings["ButtonSize"] + gutter;
		}
	}
}

void TexturePicker::Update(int deltaTime)
{
	static bool isButtonClicked = false;

	AABB collider;

	int posX = Input::Instance()->GetMousePosition().x;
	int posY = Input::Instance()->GetMousePosition().y;

	collider.SetPosition(posX, posY);

	if (Input::Instance()->IsMouseClicked())
	{
		//select a texture
		if (!isButtonClicked)
		{
			CheckCollision(collider);
			isButtonClicked = true;
		}
	}
	
	isButtonClicked = Input::Instance()->IsMouseClicked();

	for (auto it = m_textureButtons.begin(); it != m_textureButtons.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}

bool TexturePicker::Draw()
{
	m_background.Draw(m_position.x, m_position.y);

	for (auto it = m_textureButtons.begin(); it != m_textureButtons.end(); it++)
	{
		(*it)->Draw();
	}

	return true;
}

TextureButton* TexturePicker::GetTexture()
{
	return m_currentTexture;
}

bool TexturePicker::CheckCollision(AABB& collider)
{
	for (auto it = m_textureButtons.begin(); it != m_textureButtons.end(); it++)
	{
		if ((*it)->GetCollider().IsColliding(collider))
		{
			if (m_currentTexture)
			{
				m_currentTexture->SetState(Button::State::DEFAULT);
			}

			m_currentTexture = (*it);

			m_currentTexture->SetState(Button::State::ACTIVE);

			return true;
		}
	}

	return false;
}

const std::string& TexturePicker::OnClick()
{
	m_currentTexture->SetState(Button::State::ACTIVE);

	return m_currentTexture->GetID();
}

const std::map<std::string, std::string>& TexturePicker::GetTextures()
{
	return m_textures;
}


TexturePicker::~TexturePicker()
{
	for (auto it = m_textureButtons.begin(); it != m_textureButtons.end(); it++)
	{
		delete (*it);
	}

	m_textureButtons.clear();

	m_background.Unload(m_imageName);
}