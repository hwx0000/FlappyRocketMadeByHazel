#include "GameLayer.h"
#include <filesystem>

// 默认正交相机的radio为16:9, zoom为1
GameLayer::GameLayer(const std::string& name): m_OrthoCameraController(1.7778f, 1.0f)
{
	Hazel::Renderer2D::Init();

	std::string texturePath = std::filesystem::current_path().string() + "\\Resources\\Rocket.png";

	Player p("RocketPlayer");
	p.SetTexture(Hazel::Texture2D::Create(texturePath));

	m_Level = std::make_shared<Level>();
	m_Level->SetPlayer(p);
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

void GameLayer::OnUpdate(const Hazel::Timestep& ts)
{
	m_Level->OnUpdate(ts);

	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	auto pos = m_Level->GetPlayer().GetPosition();
	auto angle = m_Level->GetPlayer().GetRotation();
	Hazel::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
	{
		Hazel::Renderer2D::DrawQuad({ pos.x, pos.y, 0 }, angle, { 0.2f, 0.2f }, m_Level->GetPlayer().GetTexture());
	}
	Hazel::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
}
