#include "internal_engine_headers\ie_camera.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		// Camera  
		// Static Declarations 
		PW_INT ie::Camera::camera_zoom = -1;
		PW_INT ie::Camera::last_camera_zoom = -2;
		PW_FLOAT ie::Camera::camera_x_position = 0.0f;
		PW_FLOAT ie::Camera::camera_y_position = 0.0f;
		PW_FLOAT ie::Camera::last_camera_x_position = -1.0f;
		PW_FLOAT ie::Camera::last_camera_y_position = -1.0f;
		glm::mat4 ie::Camera::perspective = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
		glm::mat4 ie::Camera::camera = glm::lookAt(
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
					glm::vec3(camera_x_position, camera_y_position, camera_zoom + 1),
					glm::vec3(camera_x_position, camera_y_position, camera_zoom),
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
		PW_VOID Camera::Scroll_Forward() {
			if (camera_zoom >= -2) {
				camera_zoom -= 1;
			}
		}
		PW_VOID Camera::Scroll_Backward() {
			if (camera_zoom <= 3) {
				camera_zoom += 1;
			}
		}
		PW_VOID Camera::Camera_Up() {
			camera_y_position = camera_y_position + 0.01f;
		}
		PW_VOID Camera::Camera_Down() {
			camera_y_position = camera_y_position - 0.01f;
		}
		PW_VOID Camera::Camera_Left() {
			camera_x_position = camera_x_position - 0.01f;
		}
		PW_VOID Camera::Camera_Right() {
			camera_x_position = camera_x_position + 0.01f;
		}
		// End of Class Members
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////