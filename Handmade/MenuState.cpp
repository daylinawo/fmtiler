#include <time.h>
#include "Input.h"
#include "Game.h"
#include "MenuState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
MenuState::MenuState()
{

	m_menu = nullptr;
	m_image = nullptr;
	
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::OnEnter()
{

	m_menu = new MainMenu;
	m_menu->SetMenuText("Play game");
	m_menu->SetMenuText("Quit game");

	m_image = new Background("Assets/Images/Menu_1280x720.png", "Assets/Music/Menu.ogg");

	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
GameState* MenuState::Update(int deltaTime)
{

	//play the background music associated with the image
	//when the state transitions to the next state stop it
	//m_image->PlayMusic();

	//update the main menu to determine which menu choice was made
	m_menu->Update(deltaTime);

	//if player chose to play game, go into main playing state 
	if (m_menu->GetMenuOption() == static_cast<int>(MenuOption::PLAY))
	{
		//m_image->StopMusic();
		//return new PlayState;
	}

	//if player chose to exit the game then quit altogether
	if (m_menu->GetMenuOption() == static_cast<int>(MenuOption::QUIT))
	{
		//m_image->StopMusic();
		return nullptr;
	}

	//otherwise return reference to self
	//so that we stay in this game state
	return this;

}
//------------------------------------------------------------------------------------------------------
//function that renders the background splash image and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::Draw()
{

	m_image->Draw();
	m_menu->Draw();

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void MenuState::OnExit()
{

	delete m_image;
	delete m_menu;

}