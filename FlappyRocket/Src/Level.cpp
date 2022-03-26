#include "Level.h"

void Level::CreatePillar(int index, float offset)
{
}

bool Level::CollisionTest()
{
	return false;
}

void Level::GameOver()
{
}

void Level::Init()
{
}

void Level::Reset()
{
}

void Level::OnUpdate(Hazel::Timestep ts)
{
	auto pos = m_Player.GetPosition();
	glm::vec2 deltaPos = glm::vec2(1.0f * m_Player.GetVelocity().x,
		m_Player.GetForward().y * abs(m_Player.GetVelocity().y)) * ts.GetSeconds() * m_PlayerSpeed;
	pos = pos + deltaPos;
	m_Player.SetPosition(pos);

	if (m_SpacePressed)
	{
		auto p = m_Player.GetVelocity();
		p.y += m_Gravity * ts.GetSeconds();
		m_Player.SetVelocity(p);
	}
	else
	{
		auto p = m_Player.GetVelocity();
		p.y -= m_Gravity * ts.GetSeconds();
		m_Player.SetVelocity(p);
	}


}

void Level::OnRender()
{
}

void Level::OnImGuiRender()
{
}
