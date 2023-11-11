#include "Text.h"
#include "Camera.h"

Text::Text(Actor* actor)
    : Component(actor), m_offset(Vector::zero)
{

}

Text::Text(Actor* actor, std::string str) : Component(actor)
{
    SetText(str);
}

Text::~Text()
{
}

void Text::Update(const UpdateInfo&)
{
}

void Text::Render(const RenderInfo& ri)
{
    IVector v = Camera::WorldToScreen(GetActor()->GetTransform()->GetPosition() + m_offset, ri);

    SetBkMode(ri.hdc, TRANSPARENT);
    TextOut(ri.hdc, v.x, v.y, m_str.data(), m_str.length());
}

void Text::SetText(std::string str) { m_str = str; }

void Text::SetOffset(const Vector& offset)
{
    m_offset = offset;
}
