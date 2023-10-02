// BSD 3 - Clause License
//
// Copyright(c) 2021-2023, Darrian Corkadel
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
#ifndef H_MATH
#define H_MATH
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <glm\glm.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
#include "control\memory.h"
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CM_NAMESPACE_SRT
		class Math {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros 
		public:
			/*
				Returns the angle in degrees given a vector 
				Error List: PW_WIN_FUNCTION_ERROR
			*/
			static float Vector_Angle(glm::vec2 p_vector) noexcept {
				bool v_x_sign = !signbit(p_vector.x);
				bool v_y_sign = !signbit(p_vector.y);
				// In the case that p_vector.x is zero then the angle could only be
				// 90.0f or -90.0f
				if (p_vector.x == 0.0f) {
					if (v_y_sign) {
						return 90.0f;
					}
					else {
						return -90.0f;
					}
				}
				// Quadrant_1 +,+
				// Quadrant_4 +,-
				if (v_x_sign == true) {
					// Quadrant_1 +,+
					if (v_y_sign == true) {
						return glm::degrees(glm::atan(p_vector.y / p_vector.x));
					}
					// Quadrant_4 +,-
					else {
						return 360.0f - glm::degrees(glm::atan(p_vector.y / p_vector.x));
					}
				}
				// Quadrant_2 -,+
				// Quadrant_3 -,-
				else {
					// Quadrant_2 -,+
					if (v_y_sign == true) {
						return 180.0f - glm::degrees(glm::atan(p_vector.y / p_vector.x));
					}
					// Quadrant_3 -,-
					else {
						return glm::degrees(glm::atan(p_vector.y / p_vector.x)) + 180.0f;
					}
				}
			}
			// Returns the angle in degrees given a vector
			static float Vector_Angle(glm::vec2 p_point_1, glm::vec2 p_point_2) noexcept {
				return Vector_Angle(p_point_2 - p_point_1);
			}
		// Public Variables
		public:
		// Private Functions/Macros
		private:
		// Private Variables
		private:
		};
	CM_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_MATH