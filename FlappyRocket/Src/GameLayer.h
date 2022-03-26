#pragma once
#include "Hazel.h"
#include "Level.h"

class GameLayer : public Hazel::Layer
{
public:
	GameLayer(const std::string& name = "Layer");
	~GameLayer();
	void OnAttach() override;  //当layer添加到layer stack的时候会调用此函数，相当于Init函数
	void OnDettach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
	void OnEvent(Hazel::Event&) override;
	void OnUpdate(const Hazel::Timestep&) override;
	void OnImGuiRender() override;

private:
	std::shared_ptr<Level> m_Level;

	glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);

	// 添加一个数组, 每个数组元素代表每个Timer的结果
	//std::vector<Hazel::ProfileResult> m_ProfileResults;
};