#include "Level.h"
#include "Random.h"
#include <filesystem>

bool Level::CollisionTest()
{
	return false;
}

void Level::UpdateColumns()
{
	// 从第一个Column开始, Player每走三分之一个屏幕宽度, 就Update最左边的Columns
	float currentPosX = m_Player.GetPosition().x;
	float columnIntervelX = 4.0f / 3.0f;

	int last = int(m_LastPlayerPosX / columnIntervelX);
	int now = int(currentPosX / columnIntervelX);

	if (now > last && now != 1)
	{
		m_Collumns[0] = m_Collumns[1];
		m_Collumns[1] = m_Collumns[2];
		m_Collumns[2] = m_Collumns[3];
		m_Collumns[3] = m_Collumns[4];
		m_Collumns[4].bottomPos.x += columnIntervelX;
		m_Collumns[4].topPos.x += columnIntervelX;

		m_Collumns[4].bottomScale = { Random::Float() * 1.5f + 0.5f, Random::Float() * 1.5f + 0.5f };
		m_Collumns[4].topScale = { Random::Float() * 1.5f + 0.5f, Random::Float() * 1.5f + 0.5f };
	}
}

void Level::GameOver()
{
}

Level::Level() :m_OrthoCameraController(1.7778f, 1.0f)
{
	// 因为我们的屏幕一般是16:9，或者16:10的，所以这里的横向区间比纵向区间一般要是这个比例，所以我现在把横轴长度改成4，纵轴长度改成了4/16 * 9 = 2.25
	m_OrthoCameraController.GetCamera() = Hazel::OrthographicCamera(-2.0f, 2.0f, -1.225f, 1.225f);

	float columnIntervelX = 4.0f / 3;
	for (size_t i = 0; i < 5; i++)
	{
		Column c;
		c.topPos = { i * columnIntervelX, 1.0f, 0 };
		c.topScale =  { Random::Float() * 1.5f + 0.5f, Random::Float() * 1.5f + 0.5f };
		c.bottomPos = { i * columnIntervelX, -1.0f, 0 };
		c.bottomScale = { Random::Float() * 1.5f + 0.5f, Random::Float() * 1.5f + 0.5f };
		m_Collumns.push_back(c);
	}

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

	m_LastPlayerPosX = m_Player.GetPosition().x;
	m_Player.SetPosition(pos);


	// Camera跟随Player
	auto s = m_OrthoCameraController.GetCamera().GetPosition();
	s.x = s.x + deltaPos.x;
	s.y = s.y + deltaPos.y;
	m_OrthoCameraController.GetCamera().SetPosition(s);


	if (m_SpacePressed)
	{
		auto p = m_Player.GetVelocity();
		p.y += m_UpAcceleration * ts.GetSeconds();
		m_Player.SetVelocity(p);
	}
	else
	{
		auto p = m_Player.GetVelocity();
		p.y -= m_Gravity * ts.GetSeconds();
		m_Player.SetVelocity(p);
	}

	UpdateColumns();
}

void Level::OnRender()
{
}

void Level::OnImGuiRender()
{
}
