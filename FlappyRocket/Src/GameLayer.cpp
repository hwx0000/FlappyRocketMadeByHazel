#include "GameLayer.h"

// 默认正交相机的radio为16:9, zoom为1
GameLayer::GameLayer(const std::string& name): m_OrthoCameraController(1.7778f, 1.0f)
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
}

void GameLayer::OnDettach()
{
}

void GameLayer::OnEvent(Hazel::Event &)
{
}

void GameLayer::OnUpdate(const Hazel::Timestep &)
{
}

void GameLayer::OnImGuiRender()
{
}
