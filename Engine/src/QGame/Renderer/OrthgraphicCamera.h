#pragma once

#include "D:\QGameEngine\QGameEngine\Engine\vendor_src\glm\glm\glm.hpp"


namespace QGame {

	class OrthographicCamera 
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition()const { return m_Position; }
		inline float GetRotation()const { return m_Rotation; }
		void SetPosition(const glm::vec3& position) { m_Position = position;  RecalculateViewMatrix(); }
		void SetRotation(float rotation) {  m_Rotation = rotation; RecalculateViewMatrix(); }//仅仅绕Z轴的旋转(用于2D)


		const glm::mat4& GetProjectionMatrix()const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix()const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;//缓存矩阵

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};

}