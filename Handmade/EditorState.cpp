#include "Debug.h"
#include "EndState.h"
#include "Game.h"
#include "Input.h"
#include "MenuState.h"
#include "EditorState.h"
#include "Screen.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
EditorState::EditorState()
{
	m_grid = nullptr;
	m_image = nullptr;
	m_editorMenu = nullptr;
	m_texturePicker = nullptr;
}
//------------------------------------------------------------------------------------------------------
//function that creates all game objects for the state
//------------------------------------------------------------------------------------------------------
bool EditorState::OnEnter()
{
	SDL_Point resolution = Screen::Instance()->GetResolution();

	m_image = new Background("Assets/Images/Backgrounds/Editor_1280x720.png", "Assets/Music/Play.ogg");

	m_texturePicker = new TexturePicker();
	m_texturePicker->CreateButtons();
	
	m_grid = new Grid();
	m_grid->Create();

	m_editorMenu = new EditorMenu(50, 50);
	m_editorMenu->AddMenuItem("NEW");
	m_editorMenu->AddMenuItem("SAVE");
	m_editorMenu->AddMenuItem("SAVE AS");
	m_editorMenu->AddMenuItem("LOAD");
	m_editorMenu->AddMenuItem("UNDO");
	m_editorMenu->AddMenuItem("QUIT");

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that reads key presses, mouse clicks and updates all game objects in scene
//------------------------------------------------------------------------------------------------------
GameState* EditorState::Update(int deltaTime)
{
	TextureButton* currentTexture = m_texturePicker->GetTexture();

	if (currentTexture != nullptr)
	{
		m_grid->SetTextureID(currentTexture->GetID());
	}

	if (m_editorMenu->GetMenuOption() == static_cast<int>(MenuOption::NEW))
	{
		m_grid->Clear();
		m_grid->Create();
	}

	if (m_editorMenu->GetMenuOption() == static_cast<int>(MenuOption::SAVE))
	{
		m_grid->Save(m_texturePicker->GetTextures());
	}

	if (m_editorMenu->GetMenuOption() == static_cast<int>(MenuOption::SAVEAS))
	{
		m_grid->SaveAs(m_texturePicker->GetTextures());
	}

	if (m_editorMenu->GetMenuOption() == static_cast<int>(MenuOption::LOAD))
	{
		m_grid->Load();
	}

	if (m_editorMenu->GetMenuOption() == static_cast<int>(MenuOption::UNDO))
	{
		m_grid->Undo();
	}

	if (m_editorMenu->GetMenuOption() == static_cast<int>(MenuOption::QUIT))
	{
		return nullptr;
	}	
	
	m_editorMenu->Reset();

	m_grid->Update(deltaTime);
	m_editorMenu->Update(deltaTime);
	m_texturePicker->Update(deltaTime);

	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}
//------------------------------------------------------------------------------------------------------
//function that renders all game objects in scene
//------------------------------------------------------------------------------------------------------
bool EditorState::Draw()
{

	//render the background image
	m_image->Draw();
	m_grid->Draw();
	m_editorMenu->Draw();
	m_texturePicker->Draw();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void EditorState::OnExit()
{
	//destroy all individual game objects

	delete m_grid;
	delete m_image;
	delete m_texturePicker;
	delete m_editorMenu;

}