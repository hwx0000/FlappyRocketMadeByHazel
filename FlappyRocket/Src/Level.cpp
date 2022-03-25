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
	auto  s = ts.GetSeconds();
	pos += m_Player.GetVelocity() * ts.GetSeconds();
	m_Player.SetPosition(pos);
}

void Level::OnRender()
{
}

void Level::OnImGuiRender()
{
}
