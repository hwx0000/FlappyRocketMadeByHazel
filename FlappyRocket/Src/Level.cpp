#include "Level.h"
#include <filesystem>

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

Level::Level() :m_OrthoCameraController(1.7778f, 1.0f)
{
	Column c1;
	c1.topPos = {0, 1.0f, 0};
	c1.topScale = {0.8f, 0.8f};
	c1.bottomPos = {0, -1.0f, 0};
	c1.bottomScale = {1.5f, 1.5f};
	m_Collumns.push_back(c1);

	std::string texturePath = std::filesystem::current_path().string() + "\\Resources\\Triangle.png";
	m_TriangleTexture = Hazel::Texture2D::Create(texturePath);
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
