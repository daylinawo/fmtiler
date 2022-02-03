#include "EditorMenu.h"
#include "Input.h"
#include "Debug.h"

EditorMenu::EditorMenu(int xPos, int yPos)
{

	m_position = { xPos, yPos };
	m_menuOptionChoice = -1;

}

void EditorMenu::AddMenuItem(const std::string& text)
{

	m_buttons.push_back(new UtilityButton("Assets/Images/Buttons/UIButton_128x52.png", text, m_buttons.size(), BUTTON_WIDTH, 
									  BUTTON_HEIGHT, m_position.x, m_position.y + (m_buttons.size() * BUTTON_HEIGHT)));

}

int EditorMenu::GetMenuOption()
{
	return m_menuOptionChoice;
}

void EditorMenu::Reset()
{
	m_menuOptionChoice = -1;
}

void EditorMenu::Update(int deltaTime)
{
	static bool isButtonClicked = false;

	if (Input::Instance()->IsMouseClicked() && !isButtonClicked)
	{
		//instantiate a box collider at point of mouse click
		AABB collider;

		int xPos = Input::Instance()->GetMousePosition().x;
		int yPos = Input::Instance()->GetMousePosition().y;

		collider.SetPosition(xPos, yPos);

		for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
		{
			(*it)->Update(deltaTime);
		
			if ((*it)->GetCollider().IsColliding(collider))
			{
				m_menuOptionChoice = (*it)->GetID();
			}
		}
	}

	isButtonClicked = Input::Instance()->IsMouseClicked();

}

bool EditorMenu::Draw()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
	{
		(*it)->Draw();
	}

	return true;
}

EditorMenu::~EditorMenu()
{
}