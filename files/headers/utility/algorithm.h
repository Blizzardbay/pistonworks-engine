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
#ifndef H_ALGORITHM
#define H_ALGORITHM
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
//////////////////////////////////
// Project Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <glm\ext\vector_float2.hpp>
#pragma warning(pop)
//////////////////////////////////
// Engine Common Headers
#include "common\macro.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Header
#include "structures\model.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////

// Algorithm namespace
#define ALG_NAMESPACE_SRT namespace alg {
#define ALG_NAMESPACE_END }

PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		ALG_NAMESPACE_SRT
			extern bool Line_Intersection(glm::vec2 p_point_1, glm::vec2 p_point_2, glm::vec2 p_point_3, glm::vec2 p_point_4);
			extern bool Line_Intersection(float p_x1, float p_y1, float p_x2, float p_y2, float p_x3, float p_y3, float p_x4, float p_y4);

			extern bool Point_In_Shape(glm::vec2 p_point, st::Model* p_shape);
			extern bool Point_In_Shape(float p_x, float p_y, st::Model* p_shape);
		ALG_NAMESPACE_END
	UTIL_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_ALGORITHM