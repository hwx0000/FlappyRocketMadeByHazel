#include "GameLayer.h"
#include <filesystem>


GameLayer::GameLayer(const std::string& name)
{
	m_Level = std::make_shared<Level>();

	Hazel::Renderer2D::Init();

	std::string texturePath = std::filesystem::current_path().string() + "\\Resources\\Rocket.png";

	Player p("RocketPlayer");
	p.SetTexture(Hazel::Texture2D::Create(texturePath));

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

void GameLayer::OnEvent(Hazel::Event &e)
{
	if (e.GetEventType() == Hazel::EventType::KeyPressed)
	{
		Hazel::KeyPressedEvent* ep = dynamic_cast<Hazel::KeyPressedEvent*>(&e);
		if (ep->GetKeycode() == HZ_KEY_SPACE)
			m_Level->SetSpacePressed(true);
	}
	else if(e.GetEventType() == Hazel::EventType::KeyReleased)
	{
		Hazel::KeyReleasedEvent* er = dynamic_cast<Hazel::KeyReleasedEvent*>(&e);
		if (er->GetKeycode() == HZ_KEY_SPACE)
			m_Level->SetSpacePressed(false);
	}
}

void GameLayer::OnUpdate(const Hazel::Timestep& ts)
{
	m_Level->OnUpdate(ts);

	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	auto pos = m_Level->GetPlayer().GetPosition();
	auto angle = m_Level->GetPlayer().GetRotation();

	auto camera = m_Level->GetCameraController().GetCamera();
	auto c = camera.GetPosition();
	auto c2 = camera.GetRotation();
	Hazel::Renderer2D::BeginScene(m_Level->GetCameraController().GetCamera());
	{
		Hazel::Renderer2D::DrawQuad({ pos.x, pos.y, 0 }, angle, { 0.2f, 0.2f }, m_Level->GetPlayer().GetTexture());
	}
	Hazel::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
}
