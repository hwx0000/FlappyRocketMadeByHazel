#include "ParticleSystem.h"

#include "Random.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::Emit(const ParticleProperties& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];// m_PoolIndex起始为999, 也就是从这个Pool的最后面开始用起
	particle.Active = true;
	particle.Position = particleProps.Position;// 位置是统一的
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();// 但是喷射方向是随机的

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);// x和y方向的速度都是随机变化的
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	// Size
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	// LifeTime就是单纯的赋值
	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;

	// m_PoolIndex--, 直到变为0, 再又会变成999
	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

// Update函数里, 检查所有的粒子的状态, 如果生命期到了, 则置为inActive
// 否则更新LifeTime、position和rotation
void ParticleSystem::OnUpdate(Hazel::Timestep ts, float playerSpeed)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts *  playerSpeed;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender()
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		Hazel::Renderer2D::DrawQuad({ particle.Position.x, particle.Position.y, 1.0f }, particle.Rotation,
			{ size, size }, color);
	}
}
