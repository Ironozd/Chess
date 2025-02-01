#pragma once

#include <glm/vec2.hpp>

namespace ECS
{
	/*
	 * @brief Transform Component
	 */
	class Transform
	{
	public:
		Transform(float x, float y);
		Transform(float scalar);
		Transform(const glm::vec2& vec2);
		Transform(glm::vec2&& vec2);
		Transform(Transform&& other) noexcept;
		Transform(const Transform& other);

		glm::vec2& GetPosition();
		void SetPosition(glm::vec2&& vec2) noexcept;
		void SetPosition(const glm::vec2& vec2);

		Transform& operator=(const Transform& other);
		Transform& operator=(Transform&& other) noexcept;
	private:
		glm::vec2 m_Position;
	};
}