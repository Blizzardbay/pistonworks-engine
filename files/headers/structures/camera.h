// BSD 3 - Clause License
//
// Copyright(c) 2021-2024, Darrian Corkadel
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
#ifndef H_CAMERA
#define H_CAMERA
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\constant.h"
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		class Camera {
		// Friends
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			/* Error List: NONE */
			static const glm::mat4& Update_Camera();
			/* Error List: NONE */
			static const glm::mat4& Update_Projection();
			/* Error List: NONE */
			static void Center_Camera(const glm::vec2& p_new_center);
			/* Error List: NONE */
			static void Update_Position(const glm::vec3& p_new_position);
			/* Error List: NONE */
			static void Update_Zoom(const float p_new_zoom);
			/* Error List: NONE */
			static glm::vec3 Camera_Position();
			/* Error List: NONE */
			static glm::vec3 Camera_Position_Last();
			/* Error List: NONE */
			static glm::vec2 Camera_Size();
			/* Error List: NONE */
			static const glm::vec3& Up_Vector();
			/* Error List: NONE */
			static glm::vec3& At_Vector();
			/* Error List: NONE */
			static float Camera_Zoom();
		// Public Variables   
		public:
		// Private Functions/Macros 
		private:
		// Private Variables  
		private:
			static float m_camera_zoom;
			static float m_last_camera_zoom;

			static glm::vec3 m_camera_position;

			static float m_camera_width;
			static float m_camera_height;

			static glm::vec3 m_last_camera_position;

			static glm::mat4 m_perspective;
			static glm::mat4 m_camera;
			static glm::vec3 m_at_vector;
			static const glm::vec3 m_up_vector;
		};
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_CAMERA