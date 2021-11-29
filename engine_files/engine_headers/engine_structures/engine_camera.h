// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_ENGINE_CAMERA
#define H_ENGINE_CAMERA
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
#include "engine_common\engine_constant.h"
//////////////////////////////////
// Engine Macro Includes  
#include "engine_common\engine_error.h"
//////////////////////////////////
// Engine Macros    
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Pistonworks Engine           //
	// Created By : Darrian Corkadel//
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Camera
		// //////////////////////////////////////////////////
		// Purpose:
		//  Handles the camera function in the engine.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Camera {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Camera::Update_Camera
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used  to Used to update the camera's current look
			//  / position.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE glm::mat4& Update_Camera();
			// //////////////////////////////////////////////////
			// CORE Function: Camera::Update_Projection
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to update the current projection matrix
			//  for displaying the information on screen.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE glm::mat4& Update_Projection();
			// //////////////////////////////////////////////////
			// UTILITY Function: Camera::Scroll_Forward
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to change camera zoom in a negative
			//  direction.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY void Scroll_Forward();
			// //////////////////////////////////////////////////
			// UTILITY Function: Camera::Scroll_Backward
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to change camera zoom in a positive
			//  direction.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY void Scroll_Backward();
			// //////////////////////////////////////////////////
			// UTILITY Function: Camera::Camera_Up
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to translate the camera in the positive
			//  y direction.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY void Camera_Up();
			// //////////////////////////////////////////////////
			// UTILITY Function: Camera::Camera_Down
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to translate the camera in the negative
			//  y direction.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY void Camera_Down();
			// //////////////////////////////////////////////////
			// UTILITY Function: Camera::Camera_Left
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Use to translate the camera in the negative x
			//  direction.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY void Camera_Left();
			// //////////////////////////////////////////////////
			// UTILITY Function: Camera::Camera_Right
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to translate the camera in the positive x 
			//  direction.
			// //////////////////////////////////////////////////
			// Parameters: NONE 
			// //////////////////////////////////////////////////
			USER_INTERACTION
			static UTILITY void Camera_Right();
			// Accessors
			USER_INTERACTION
			static ACCESSOR glm::vec2 Camera_Position_Raw();
			USER_INTERACTION
			static ACCESSOR glm::vec2 Camera_Position();
			USER_INTERACTION
			static ACCESSOR glm::vec2 Camera_Position_Last();
			USER_INTERACTION
			static ACCESSOR glm::vec2 Camera_Size();
			USER_INTERACTION
			static ACCESSOR float Camera_Zoom();

		// Public Variables   
		public:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			static float camera_zoom;
			static float last_camera_zoom;

			static float camera_x_position;
			static float camera_y_position;

			static float camera_width;
			static float camera_height;

			static float last_camera_x_position;
			static float last_camera_y_position;

			static glm::mat4 perspective;
			static glm::mat4 camera;
		};
		// Functions  
		// Macros / Definitions
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_CAMERA