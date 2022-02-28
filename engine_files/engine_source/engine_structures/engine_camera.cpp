#include "engine_structures\engine_camera.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Camera  
		// Static Declarations 
			float Camera::m_camera_zoom{ 1 };
			float Camera::m_last_camera_zoom{ -2 };
			glm::vec3 Camera::m_camera_position{ 0.0f, 0.0f,0.0f };
			float Camera::m_camera_width{ 800.0f };
			float Camera::m_camera_height{ 600.0f };
			glm::vec3 Camera::m_last_camera_position{ 0.0f };
			glm::mat4 Camera::m_perspective = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
			glm::mat4 Camera::m_camera{ glm::lookAt(
				glm::vec3(m_camera_position.x, m_camera_position.y, m_camera_zoom + 1),
				glm::vec3(m_camera_position.x, m_camera_position.y, m_camera_zoom),
				glm::vec3(0.0f, 1.0f, 0.0f)) };
			glm::vec3 Camera::m_at_vector{ glm::vec3(m_camera_position.x, m_camera_position.y, m_camera_zoom) };
			const glm::vec3 Camera::m_up_vector{ glm::vec3(0.0f, 1.0f, 0.0f) };
		// Class Members  
			const glm::mat4& Camera::Update_Camera() {
				if (m_camera_position != m_last_camera_position ||
					m_camera_zoom != m_last_camera_zoom) {

					m_camera_width = (float)cm::Engine_Constant::Window_Width();
					m_camera_height = (float)cm::Engine_Constant::Window_Height();

					m_last_camera_position = m_camera_position;

					m_last_camera_zoom = m_camera_zoom;

					m_at_vector = glm::vec3(m_camera_position.x, m_camera_position.y, cm::Engine_Constant::Inverse_Z_Tan());
					m_camera = glm::lookAt(
						glm::vec3(m_camera_position.x, m_camera_position.y, 0.0f),
						m_at_vector,
						glm::vec3(0.0f, 1.0f, 0.0f));
					return m_camera;
				}
				else {
					m_last_camera_position = m_camera_position;

					m_last_camera_zoom = m_camera_zoom;

					m_camera_width = (float)cm::Engine_Constant::Window_Width();
					m_camera_height = (float)cm::Engine_Constant::Window_Height();

					return m_camera;
				}
			}
			const glm::mat4& Camera::Update_Projection() {
				m_perspective = glm::ortho(m_camera_position.x / m_camera_zoom, ((float)cm::Engine_Constant::Window_Width() + m_camera_position.x) / m_camera_zoom,
					(m_camera_position.y + m_camera_height - (float)cm::Engine_Constant::Window_Height()) / m_camera_zoom, (m_camera_position.y + m_camera_height) / m_camera_zoom, 0.1f, 100.0f);
				return m_perspective;
			}
			void Camera::Center_Camera(const glm::vec2& p_new_center) {
				glm::vec2 v_camera_center = glm::vec2((m_camera_position.x) + (m_camera_width / 2.0f), (m_camera_position.y) + m_camera_height - (m_camera_height / 2.0f));

				glm::vec2 v_goal = p_new_center;

				v_goal.x = v_goal.x / 2.0f;
				v_goal.y = v_goal.y / 2.0f;

				glm::vec2 v_difference = v_goal - v_camera_center;

				m_camera_position.x = m_camera_position.x + v_difference.x + (m_camera_width / 4.0f);
				m_camera_position.y = m_camera_position.y + v_difference.y + (m_camera_height / 4.0f);
			}
			void Camera::Update_Position(const glm::vec3& p_new_position) {
				m_camera_position = p_new_position;
			}
			void Camera::Update_Zoom(const float& p_new_zoom) {
				m_camera_zoom = p_new_zoom;
			}
			glm::vec3 Camera::Camera_Position() {
				return glm::vec3((m_camera_position.x * 2.0f),
					(m_camera_position.y * 2.0f) + m_camera_height, m_camera_position.z);
			}
			glm::vec3 Camera::Camera_Position_Last() {
				return glm::vec3((m_last_camera_position.x * 2.0f),
					(m_last_camera_position.y * 2.0f) + m_camera_height, m_last_camera_position.z);
			}
			glm::vec2 Camera::Camera_Size() {
				return glm::vec2(m_camera_width, m_camera_height);
			}
			float Camera::Camera_Zoom() {
				return m_camera_zoom;
			}
			const glm::vec3& Camera::Up_Vector() {
				return m_up_vector;
			}
			glm::vec3& Camera::At_Vector() {
				return m_at_vector;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////