#include "FlappyRocketApp.h"
#include "GameLayer.h"


FlappyRocketApp::FlappyRocketApp()
{
	HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");

	m_Window = std::unique_ptr<Hazel::Window>(Hazel::Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	m_ImGuiLayer = new Hazel::ImGuiLayer();
	m_LayerStack.PushOverlay(m_ImGuiLayer);
	
	m_LayerStack.PushLayer(new GameLayer());

	//m_Window->SetVSync(true);
}

Hazel::Application* Hazel::CreateApplication() 
{
	FlappyRocketApp *s = new FlappyRocketApp();
	return s;
}
