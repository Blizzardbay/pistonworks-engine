#include "engine_structures\engine_camera.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Camera  
		// Static Declarations 
			int32_t Camera::camera_zoom = 0;
			int32_t Camera::last_camera_zoom = -2;
			float Camera::camera_x_position = 0.0f;
			float Camera::camera_y_position = 0.0f;
			float Camera::last_camera_x_position = -1.0f;
			float Camera::last_camera_y_position = -1.0f;
			glm::mat4 Camera::perspective = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
			glm::mat4 Camera::camera = glm::lookAt(
				glm::vec3(camera_x_position, camera_y_position, camera_zoom + 1),
				glm::vec3(camera_x_position, camera_y_position, camera_zoom),
				glm::vec3(0.0f, 1.0f, 0.0f));
		// Class Members  
			glm::mat4 Camera::Update_Camera() {
				if (camera_x_position != last_camera_x_position ||
					camera_y_position != last_camera_y_position ||
					camera_zoom != last_camera_zoom) {
					last_camera_x_position = camera_x_position;
					last_camera_y_position = camera_y_position;
					last_camera_zoom = camera_zoom;
					camera = glm::lookAt(
						glm::vec3(camera_x_position, camera_y_position, camera_zoom),
						glm::vec3(camera_x_position, camera_y_position, camera_zoom - 1),
						glm::vec3(0.0f, 1.0f, 0.0f));
					return camera;
				}
				else {
					last_camera_x_position = camera_x_position;
					last_camera_y_position = camera_y_position;
					last_camera_zoom = camera_zoom;
					return camera;
				}
			}
			glm::mat4 Camera::Update_Projection() {
				return perspective;
			}
			void Camera::Scroll_Forward() {
				if (camera_zoom >= -1) {
					camera_zoom -= 1;
				}
			}
			void Camera::Scroll_Backward() {
				if (camera_zoom <= 10) {
					camera_zoom += 1;
				}
			}
			void Camera::Camera_Up() {
				camera_y_position = camera_y_position + 0.01f;
			}
			void Camera::Camera_Down() {
				camera_y_position = camera_y_position - 0.01f;
			}
			void Camera::Camera_Left() {
				camera_x_position = camera_x_position - 0.01f;
			}
			void Camera::Camera_Right() {
				camera_x_position = camera_x_position + 0.01f;
			}
			glm::vec2 Camera::Camera_Position() {
				return glm::vec2(camera_x_position, camera_y_position);
			}
			int32_t Camera::Camera_Zoom() {
				return camera_zoom;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////