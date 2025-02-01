#include "Transform.h"

namespace ECS
{
	Transform::Transform(float x, float y) : m_Position({x, y})
	{
	
	}

	Transform::Transform(float scalar) : m_Position(scalar)
	{

	}

	Transform::Transform(const glm::vec2& vec2) : m_Position(vec2)
	{
		
	}

	Transform::Transform(glm::vec2&& vec2) : m_Position(std::move(vec2))
	{

	}
	
	Transform::Transform(Transform&& other) noexcept : m_Position(std::move(other.m_Position))
	{

	}
	
	Transform::Transform(const Transform& other) : m_Position(other.m_Position)
	{
		
	}

	glm::vec2& Transform::GetPosition()
	{
		return m_Position;
	}
	
	void Transform::SetPosition(glm::vec2&& vec2) noexcept
	{
		m_Position = std::move(vec2);
	}
	void Transform::SetPosition(const glm::vec2& vec2)
	{
	}
	Transform& Transform::operator=(const Transform& other)
	{
		m_Position = other.m_Position;
		return *this;
	}
	Transform& Transform::operator=(Transform&& other) noexcept
	{
		m_Position = std::move(other.m_Position);
		return *this;
	}
}