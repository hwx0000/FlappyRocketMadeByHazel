#pragma once
#include "Hazel.h"

class Player
{
public:
	Player(const char* name = "Default Player") : m_Name(name) {};

	//void LoadAssets();
	//void OnUpdate(Hazel::Timestep ts);
	//void OnRender();
	//void OnImGuiRender();
	//void Reset();

	void SetTexture(std::shared_ptr <Hazel::Texture2D> tex) { m_RocketTexture = tex; }
	std::shared_ptr<Hazel::Texture2D> GetTexture() { return m_RocketTexture; }

	float GetRotation() 
	{
		if (m_Velocity.y * 8.0f - 90.0f < -180)
			m_Velocity.y = -90.0f / 8.0f;

		if (m_Velocity.y * 8.0f - 90.0f > 0)
			m_Velocity.y = 90.0f / 8.0f;

		return m_Velocity.y * 8.0f - 90.0f; 
	}
	const glm::vec2& GetPosition() const { return m_Position; } 
	void SetPosition(glm::vec2 pos) { m_Position = pos; }

	glm::vec4 GetForward() { return glm::rotate(glm::mat4(1.0f), glm::radians(m_Velocity.y * 8.0f), { 0, 0, 1 }) * glm::vec4(1, 0, 0, 0); }
	glm::vec2 GetVelocity() { return m_Velocity; }
	void SetVelocity(const glm::vec2& p) { m_Velocity = p; }
	uint32_t GetScore() const { return (uint32_t)((m_Position.x + 10.0f) / 10.0f); }
private:
	glm::vec2 m_Position = { 0.0f, 0.0f };
	glm::vec2 m_Velocity = { 10.0f, 0.0f };

	float m_EnginePower = 0.5f;

	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	//ParticleProps m_SmokeParticle, m_EngineParticle;
	//ParticleSystem m_ParticleSystem;
	//
	std::shared_ptr<Hazel::Texture2D> m_RocketTexture;
	std::string m_Name;
};

