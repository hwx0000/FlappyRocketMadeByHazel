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

// 对于整个关卡区间的y值: 
// [-1, 1]为玩家的竖直活动区间
// [-Infinity, -1]和[1, Infinity]区间为关卡的上下边界
// 但是由于正交Camera是紧跟Player的, Camera的显示范围为横轴长度为4, 纵轴长度为2.25(16:9)
class Level
{
public:
	// 默认正交相机的radio为16:9, zoom为1
	Level();
	void Init();
	void Reset();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
	void OnImGuiRender();

	bool IsGameOver() const { return m_GameOver; }

	Hazel::OrthographicCameraController& GetCameraController() { return m_OrthoCameraController; }

	void SetPlayer(const Player&p) { m_Player = p; }
	Player& GetPlayer() { return m_Player; }

	void SetSpacePressed(bool pressed) { m_SpacePressed = pressed; }
	std::vector<Column>& GetColumns() { return m_Collumns; }

	std::shared_ptr<Hazel::Texture2D> GetTriangleTex() { return m_TriangleTexture; }
private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();

	void GameOver();
private:
	bool m_GameOver = false;

	float m_PillarTarget = 30.0f;
	int m_PillarIndex = 0;
	glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };
	float m_Gravity = 20.0f;
	float m_PlayerSpeed = 0.05f;

	Player m_Player;
	std::vector<Column> m_Collumns;							// 关卡信息数组
	std::shared_ptr<Hazel::Texture2D> m_TriangleTexture;    // 关卡对应的Texture2D数组
	bool m_SpacePressed = false;
	Hazel::OrthographicCameraController m_OrthoCameraController;
};