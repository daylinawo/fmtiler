#include "UtilityButton.h"
#include "Screen.h"

UtilityButton::UtilityButton(const std::string& imageFilename, const std::string& text, int ID, int width, int height, int xPos, int yPos)
{

    //load font resource into memory
    static bool isLoaded = false;

    m_image.Load(imageFilename, imageFilename);

    if (!isLoaded)
    {
        Text::Load("Assets/Fonts/Righteous-Regular.ttf", "UtilityButton_Font", Text::FontSize::SMALL);
        isLoaded = true;
    }

    m_image.SetImage(imageFilename);
    m_image.SetSpriteDimension(width, height);
    m_image.SetImageDimension(1, 1, width, height);

    m_text.SetFont("UtilityButton_Font");
    m_text.SetColor(255, 255, 255);
    m_text.SetSize(text.size() * BUTTON_TEXT_CHAR_W, BUTTON_TEXT_CHAR_H);
    m_text.SetText(text);

    m_position = { xPos, yPos };
    m_boxCollider.SetDimension(width, height);
    m_boxCollider.SetPosition(xPos, yPos);

    m_ID = ID;
    m_imageName = imageFilename;

}

void UtilityButton::Update(int deltaTime)
{
}

bool UtilityButton::Draw()
{
    m_image.Draw(m_position.x, m_position.y);

    m_text.Draw(m_position.x + m_image.GetSpriteDimension().x / 2 - m_text.GetSize().x / 2,
                m_position.y + m_image.GetSpriteDimension().y / 2 - m_text.GetSize().y / 2);

    return true;
}

int UtilityButton::GetID()
{
    return m_ID;
}

UtilityButton::~UtilityButton()
{
    m_image.Unload(m_imageName);

    static bool isUnloaded = false;
    
    if (!isUnloaded)
    {
        m_text.Unload("UtilityButton_Font");
        isUnloaded = true;
    }
}