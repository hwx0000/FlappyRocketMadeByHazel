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
	// 因为我们的屏幕一般是16:9，或者16:10的，所以这里的横向区间比纵向区间一般要是这个比例，所以我现在把横轴长度改成4，纵轴长度改成了4/16 * 9 = 2.25
	m_OrthoCameraController.GetCamera() = Hazel::OrthographicCamera(-2.0f, 2.0f, -1.225f, 1.225f);

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

	// 高度限制在[-1, 1]区间
	if (pos.y > 1.f)
	{
		pos.y = 1.0f;
		deltaPos.y = 0.0f;
	}
	if (pos.y < -1.f)
	{
		pos.y = -1.0f;
		deltaPos.y = 0.0f;
	}

	m_Player.SetPosition(pos);


	// Camera跟随Player
	auto s = m_OrthoCameraController.GetCamera().GetPosition();
	s.x = s.x + deltaPos.x;
	s.y = s.y + deltaPos.y;
	m_OrthoCameraController.GetCamera().SetPosition(s);


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
