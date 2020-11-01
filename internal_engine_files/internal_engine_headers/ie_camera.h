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
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (IE_Camera)                                 ]
	 Handles the camera function in the engine.
	*/
	class IE_Camera {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		IE_Camera(glm::vec3 init_camera_position, glm::vec3 camera_yaw, GLfloat yaw_change,
			GLfloat pitch_change, GLfloat movement_speed, GLfloat turn_speed) :
			camera_position(init_camera_position), camera_yaw(camera_yaw), yaw_change(yaw_change),
			pitch_change(pitch_change), camera_front(0.0f, 0.0f, 0.0f), camera_pitch(0.0f, 0.0f, 0.0f),
			up_direction(0.0f, 0.0f, 0.0f) {

		}
		glm::mat4 Update_Camera() {
			return glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		static glm::mat4 Update_Projection() {
			return glm::perspective(glm::radians(45.0f),1.0f,0.1f, 100.0f);
		}
		void SetCameraPosition(glm::vec3 new_camera_position) { camera_position = new_camera_position; }

		float Get_Camera_Position_X() { return camera_position.x; }
		float Get_Camera_Position_Y() { return camera_position.y; }
		float Get_Camera_Position_Z() { return camera_position.z; }	
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static glm::vec3 camera_temp_vec;

		glm::vec3 camera_position;
		glm::vec3 camera_front;
		glm::vec3 camera_yaw;
		glm::vec3 camera_pitch;

		glm::vec3 up_direction;

		float yaw_change;
		float pitch_change;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_CAMERA