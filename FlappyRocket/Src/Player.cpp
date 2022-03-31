#include "Player.h"

void Player::SetPosition(const glm::vec2& pos)
{
	m_Position = pos;

	// Update Bound Vertices
	for (size_t i = 0; i < 4; i++)
	{
		auto trans = glm::scale(glm::mat4(1.0f), { 0.2f, 0.2f, 1.0f });
		trans = glm::rotate(trans, glm::radians(m_Velocity.y * 3.0f), { 0, 0, 1 });

		auto translation = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f });
		trans = translation * trans;
		
		m_CurVertices[i] = trans * m_MeshVertices[i];
	}
}