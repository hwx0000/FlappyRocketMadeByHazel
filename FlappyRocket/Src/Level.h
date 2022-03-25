#pragma once
#include "Hazel.h"
#include "Player.h"

// 整个游戏区间的y坐标在[-10, 10]区间内, Player从(0,0,0)开始自动向右移动
struct Column
{
	glm::vec3 topPos;		
	glm::vec2 topScale;		// the Column can be expanded in x and y axis

	glm::vec3 bottomPos;	
	glm::vec2 bottomScale;
};

class Level
{
public:
	void Init();
	void Reset();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
	void OnImGuiRender();

	bool IsGameOver() const { return m_GameOver; }
	void SetPlayer(const Player&p) { m_Player = p; }
	Player& GetPlayer() { return m_Player; }

private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();

	void GameOver();
private:
	bool m_GameOver = false;

	float m_PillarTarget = 30.0f;
	int m_PillarIndex = 0;
	glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };
	float m_Gravity = 0.4f;

	float m_PlayerSpeed = 0.1f;
	Player m_Player;
	std::vector<Column> m_Collumns;							// 关卡信息数组
	std::shared_ptr<Hazel::Texture2D> m_TriangleTexture;    // 关卡对应的Texture2D数组
};

