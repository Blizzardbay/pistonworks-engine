#include "engine_structures\engine_camera.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Camera  
		// Static Declarations 
			float Camera::camera_zoom = 0;
			float Camera::last_camera_zoom = -2;
			float Camera::camera_x_position = 0.0f;
			float Camera::camera_y_position = 0.0f;
			float Camera::camera_width = 0.0f;
			float Camera::camera_height = 0.0f;
			float Camera::last_camera_x_position = -1.0f;
			float Camera::last_camera_y_position = -1.0f;
			glm::mat4 Camera::perspective = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
			glm::mat4 Camera::camera = glm::lookAt(
				glm::vec3(camera_x_position, camera_y_position, camera_zoom + 1),
				glm::vec3(camera_x_position, camera_y_position, camera_zoom),
				glm::vec3(0.0f, 1.0f, 0.0f));
		// Class Members  
			glm::mat4& Camera::Update_Camera() {
				if (camera_x_position != last_camera_x_position ||
					camera_y_position != last_camera_y_position ||
					camera_zoom != last_camera_zoom) {

					camera_width = (float)cm::Engine_Constant::Window_Width();
					camera_height = (float)cm::Engine_Constant::Window_Height();

					last_camera_x_position = camera_x_position;
					last_camera_y_position = camera_y_position;
					last_camera_zoom = camera_zoom;
					camera = glm::lookAt(
						glm::vec3(camera_x_position, camera_y_position, camera_zoom),
						glm::vec3(camera_x_position, camera_y_position, camera_zoom + cm::Engine_Constant::Inverse_Z_Tan()),
						glm::vec3(0.0f, 1.0f, 0.0f));
					return camera;
				}
				else {
					last_camera_x_position = camera_x_position;
					last_camera_y_position = camera_y_position;
					last_camera_zoom = camera_zoom;

					camera_width = (float)cm::Engine_Constant::Window_Width();
					camera_height = (float)cm::Engine_Constant::Window_Height();

					return camera;
				}
			}
			glm::mat4& Camera::Update_Projection() {
				return perspective;
			}
			void Camera::Scroll_Forward() {
				if (camera_zoom >= -2) {
					camera_zoom -= ((32 / (float)cm::Engine_Constant::Window_Height()) * 2.0f);
				}
			}
			void Camera::Scroll_Backward() {
				if (camera_zoom <= std::abs(cm::Engine_Constant::Inverse_Z_Tan()) * 3) {
					camera_zoom += ((32 / (float)cm::Engine_Constant::Window_Height()) * 2.0f);
				}
			}
			void Camera::Camera_Up() {
				camera_y_position = camera_y_position + ((1 / (float)cm::Engine_Constant::Window_Height()) * 2.0f);
			}
			void Camera::Camera_Down() {
				camera_y_position = camera_y_position - ((1 / (float)cm::Engine_Constant::Window_Height()) * 2.0f);
			}
			void Camera::Camera_Left() {
				camera_x_position = camera_x_position - ((1 / (float)cm::Engine_Constant::Window_Width()) * 2.0f);
			}
			void Camera::Camera_Right() {
				camera_x_position = camera_x_position + ((1 / (float)cm::Engine_Constant::Window_Width()) * 2.0f);
			}
			glm::vec2 Camera::Camera_Position_Raw() {
				return glm::vec2(camera_x_position, camera_y_position);
			}
			glm::vec2 Camera::Camera_Position() {
				return glm::vec2(((camera_x_position * (float)cm::Engine_Constant::Window_Width()) / 2.0f),
					((camera_y_position * (float)cm::Engine_Constant::Window_Height()) / 2.0f) + camera_height);
			}
			glm::vec2 Camera::Camera_Position_Last() {
				return glm::vec2(((last_camera_x_position * (float)cm::Engine_Constant::Window_Width()) / 2.0f),
					((last_camera_y_position * (float)cm::Engine_Constant::Window_Height()) / 2.0f) + camera_height);
			}
			glm::vec2 Camera::Camera_Size() {
				return glm::vec2(camera_width, camera_height);
			}
			float Camera::Camera_Zoom() {
				return camera_zoom;
			}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////