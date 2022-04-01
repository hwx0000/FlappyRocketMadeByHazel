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
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("Resources/OpenSans-Regular.ttf", 120.0f);
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
	else if (e.GetEventType() == Hazel::EventType::MouseButtonPressed)
	{
		Hazel::MouseButtonPressedEvent* er = dynamic_cast<Hazel::MouseButtonPressedEvent*>(&e);
		if (er->GetMouseButton() == 0)
			OnMouseButtonPressed(*er);
	}
}

bool GameLayer::OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level->Reset();

	m_State = GameState::Play;
	return false;
}


void GameLayer::OnUpdate(const Hazel::Timestep& ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level->IsGameOver())
		m_State = GameState::GameOver;
	
	switch (m_State)
	{
	case GameState::Play:
	{
		m_Level->OnUpdate(ts);
		break;
	}
	}

	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	auto pos = m_Level->GetPlayer().GetPosition();
	auto angle = m_Level->GetPlayer().GetRotation();

	auto camera = m_Level->GetCameraController().GetCamera();
	auto c = camera.GetPosition();
	auto c2 = camera.GetRotation();

	// TODO: 其实Render的部分代码可以封装到Level的OnRender函数里的
	Hazel::Renderer2D::BeginScene(m_Level->GetCameraController().GetCamera());
	{
		const std::vector<Column>& columns = m_Level->GetColumns();
		std::shared_ptr<Hazel::Texture2D> triTex = m_Level->GetTriangleTex();
		
		// 绘制关卡
		// Background
		Hazel::Renderer2D::DrawQuad({ pos.x, 0.0f, -0.8f }, 0.0f, { 10.0f, 10.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });
		
		// Floor and ceiling, 在player运动的[-1, 1]范围之外绘制border即可
		Hazel::Renderer2D::DrawQuad({ pos.x, 3.5f }, 0.0f, { 50.0f, 5.0f }, m_Level->GetDynamicCollor());
		Hazel::Renderer2D::DrawQuad({ pos.x, -3.5f }, 0.0f, { 50.0f, 5.0f }, m_Level->GetDynamicCollor());


		for (size_t i = 0; i < columns.size(); i++)
		{
			// Upper triangle
			Hazel::Renderer2D::DrawQuad(columns[i].topPos, 180.0f, columns[i].scale, triTex, m_Level->GetDynamicCollor());
			
			// Lower triangle
			Hazel::Renderer2D::DrawQuad(columns[i].bottomPos, 0.0f, columns[i].scale, triTex, m_Level->GetDynamicCollor());
		}

		// 绘制Player
		Hazel::Renderer2D::DrawQuad({ pos.x, pos.y, 0.1f }, angle, { 0.2f, 0.2f }, m_Level->GetPlayer().GetTexture(), {1.0f, 1.0f, 1.0f, 1.0f});
	
		// 绘制碰撞点
		for (size_t i = 0; i < m_Level->m_DebugCollisions.size(); i++)
		{
			auto p = m_Level->m_DebugCollisions[i];
			Hazel::Renderer2D::DrawQuad({ p.x, p.y, 0.1f }, angle, { 0.025f, 0.025f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		}

		//// 绘制Player的Collider
		//for (size_t i = 0; i < 4; i++)
		//{
		//	auto p = m_Level->GetPlayer().m_CurVertices[i];
		//	Hazel::Renderer2D::DrawQuad({ p.x, p.y, 0.3f }, angle, { 0.025f, 0.025f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		//}

		//// 绘制代表关卡的三角形的顶点
		//for (size_t i = 0; i < m_Level->m_ColumnBounds.size(); i++)
		//{
		//	auto p = m_Level->m_ColumnBounds[i];
		//	Hazel::Renderer2D::DrawQuad({ p.x, p.y, 0.1f }, 0, { 0.025f, 0.025f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		//}
	}
	Hazel::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	switch (m_State)
	{
	case GameState::Play:
	{
		uint32_t playerScore = m_Level->GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		break;
	}
	case GameState::MainMenu:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Hazel::Application::Get().GetWindow().GetWindowWidth();
		auto height = Hazel::Application::Get().GetWindow().GetWindowHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
		break;
	}
	case GameState::GameOver:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Hazel::Application::Get().GetWindow().GetWindowWidth();
		auto height = Hazel::Application::Get().GetWindow().GetWindowHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

		pos.x += 200.0f;
		pos.y += 150.0f;
		uint32_t playerScore = m_Level->GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
}
