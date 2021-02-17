#ifndef H_IE_CAMERA
#define H_IE_CAMERA

//(HEADER_ONLY)

/* C++ Headers              */
/* Project Headers          */
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
/* Engine Headers           */
#include "engine_headers\engine_constant.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
	/* Classes                  */
	//
		/* -Camera
		 Handles the camera function in the engine.
		*/
		class Camera {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static glm::mat4 Update_Camera() {
				return glm::lookAt(glm::vec3(camera_x_position, camera_y_position, camera_zoom + 1), glm::vec3(camera_x_position, camera_y_position, camera_zoom), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			static glm::mat4 Update_Projection() {
				return glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
			}

			static PW_VOID Scroll_Forward() {
				if (camera_zoom >= -2) {
					camera_zoom -= 1;
				}
			}
			static PW_VOID Scroll_Backward() {
				if (camera_zoom <= 3) {
					camera_zoom += 1;
				}
			}
			static PW_VOID Camera_Up() {
				camera_y_position = camera_y_position + 0.01f;
			}
			static PW_VOID Camera_Down() {
				camera_y_position = camera_y_position - 0.01f;
			}
			static PW_VOID Camera_Left() {
				camera_x_position = camera_x_position - 0.01f;
			}
			static PW_VOID Camera_Right() {
				camera_x_position = camera_x_position + 0.01f;
			}
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static PW_INT camera_zoom;
			static PW_FLOAT camera_x_position;
			static PW_FLOAT camera_y_position;
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_CAMERA