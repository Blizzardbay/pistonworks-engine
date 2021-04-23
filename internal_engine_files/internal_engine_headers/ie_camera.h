#ifndef H_IE_CAMERA
#define H_IE_CAMERA
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
//////////////////////////////////
// Engine Headers       
#include "engine_headers\engine_constant.h"
//////////////////////////////////
// Engine Macro Includes  
#include "engine_headers\engine_error.h"
//////////////////////////////////
// Engine Macros    
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Internal Engine              //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	IE_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		//////////////////////////////////
		// Class Name: pw::ie::Camera
		//
		// Purpose: Handles the camera function in the engine.
		//
		class Camera {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// Function: Camera::Update_Camera
			//
			// Purpose: Used  to Used to update the camera's current look / position.
			//
			static glm::mat4 Update_Camera();
			// Function: Camera::Update_Projection
			//
			// Purpose: Used to update the current projection matrix
			//  for displaying the information on screen.
			//
			static glm::mat4 Update_Projection();
			// Function: Camera::Scroll_Forward
			//
			// Purpose: Used to change camera zoom in a negative direction.
			//
			static PW_VOID Scroll_Forward();
			// Function: Camera::Scroll_Backward
			//
			// Purpose: Used to change camera zoom in a positive direction.
			//
			static PW_VOID Scroll_Backward();
			// Function: Camera::Camera_Up
			//
			// Purpose:  Used to translate the camera in the positive y direction.
			//
			static PW_VOID Camera_Up();
			// Function: Camera::Camera_Down
			//
			// Purpose: Used to translate the camera in the negative y direction.
			//
			static PW_VOID Camera_Down();
			// Function: Camera::Camera_Left
			//
			// Purpose: Use to translate the camera in the negative x direction..
			//
			static PW_VOID Camera_Left();
			// Function: Camera::Camera_Right
			//
			// Purpose: Used to translate the camera in the positive x direction.
			//
			static PW_VOID Camera_Right();
		// Public Variables   
		public:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			static PW_INT camera_zoom;
			static PW_INT last_camera_zoom;

			static PW_FLOAT camera_x_position;
			static PW_FLOAT camera_y_position;

			static PW_FLOAT last_camera_x_position;
			static PW_FLOAT last_camera_y_position;

			static glm::mat4 perspective;
			static glm::mat4 camera;
		};
		// Functions  
		// Macros
	//////////////////////////////////
	IE_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_CAMERA