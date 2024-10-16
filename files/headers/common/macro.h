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
#ifndef H_MACRO
#define H_MACRO
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <memory>
#include <stdint.h>
#include <functional>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////

// Standard PW Namespace
#define PW_NAMESPACE_SRT namespace pw {
#define PW_NAMESPACE_END }
// Standard Common Namespace
#define CM_NAMESPACE_SRT namespace cm {
#define CM_NAMESPACE_END }
// Standard Control Namespace
#define CO_NAMESPACE_SRT namespace co {
#define CO_NAMESPACE_END }
// Standard Structure Namespace
#define ST_NAMESPACE_SRT namespace st {
#define ST_NAMESPACE_END }
// Error namespace
#define ER_NAMESPACE_SRT namespace er {
#define ER_NAMESPACE_END }
// Console namespace
#define CN_NAMESPACE_SRT namespace cn {
#define CN_NAMESPACE_END }
// Utility namespace
#define UTIL_NAMESPACE_SRT namespace util {
#define UTIL_NAMESPACE_END }
// Extensions namespace
#define EX_NAMESPACE_SRT namespace ex {
#define EX_NAMESPACE_END }

#define TO_INT16(x)											static_cast<int16_t>(x)
#define TO_INT32(x)											static_cast<int32_t>(x)
#define TO_INT64(x)											static_cast<int64_t>(x)
#define TO_UINT16(x)										static_cast<uint16_t>(x)
#define TO_UINT32(x)										static_cast<uint32_t>(x)
#define TO_UINT64(x)										static_cast<uint64_t>(x)
#define TO_BOOL(x)											static_cast<bool>(x)
#define TO_FLOAT(x)											static_cast<float>(x)
#define TO_DOUBLE(x)										static_cast<double>(x)
#define VARIABLE_NAME(x)									(#x)
#define OFF(x)												(x + 1)
#define OFF_INT16(x)										TO_INT16(TO_INT16(x) + TO_INT16(1))
#define OFF_INT32(x)										TO_INT32(TO_INT32(x) + TO_INT32(1))
#define OFF_INT64(x)										TO_INT64(TO_INT64(x) + TO_INT64(1))
#define OFF_UINT16(x)										TO_UINT16(TO_UINT16(x) + TO_UINT16(1))
#define OFF_UINT32(x)										TO_UINT32(TO_UINT32(x) + TO_UINT32(1))
#define OFF_UINT64(x)										TO_UINT64(TO_UINT64(x) + TO_UINT64(1))
#define INC(x)												(x + 1)
#define INC_INT16(x)										TO_INT16(TO_INT16(x) + TO_INT16(1))
#define INC_INT32(x)										TO_INT32(TO_INT32(x) + TO_INT32(1))
#define INC_INT64(x)										TO_INT64(TO_INT64(x) + TO_INT64(1))
#define INC_UINT16(x)										TO_UINT16(TO_UINT16(x) + TO_UINT16(1))
#define INC_UINT32(x)										TO_UINT32(TO_UINT32(x) + TO_UINT32(1))
#define INC_UINT64(x)										TO_UINT64(TO_UINT64(x) + TO_UINT64(1))
#define ADD_INT16(x, y)										TO_INT16(TO_INT16(x) + TO_INT16(y))
#define ADD_INT32(x, y)										TO_INT32(TO_INT32(x) + TO_INT32(y))
#define ADD_INT64(x, y)										TO_INT64(TO_INT64(x) + TO_INT64(y))
#define ADD_UINT16(x, y)									TO_UINT16(TO_UINT16(x) + TO_UINT16(y))
#define ADD_UINT32(x, y)									TO_UINT32(TO_UINT32(x) + TO_UINT32(y))
#define ADD_UINT64(x, y)									TO_UINT64(TO_UINT64(x) + TO_UINT64(y))
#define SUB_INT16(x, y)										TO_INT16(TO_INT16(x) - TO_INT16(y))
#define SUB_INT32(x, y)										TO_INT32(TO_INT32(x) - TO_INT32(y))
#define SUB_INT64(x, y)										TO_INT64(TO_INT64(x) - TO_INT64(y))
#define SUB_UINT16(x, y)									TO_UINT16(TO_UINT16(x) - TO_UINT16(y))
#define SUB_UINT32(x, y)									TO_UINT32(TO_UINT32(x) - TO_UINT32(y))
#define SUB_UINT64(x, y)									TO_UINT64(TO_UINT64(x) - TO_UINT64(y))
#define MUL_INT16(x, y)										TO_INT16(TO_INT16(x) * TO_INT16(y))
#define MUL_INT32(x, y)										TO_INT32(TO_INT32(x) * TO_INT32(y))
#define MUL_INT64(x, y)										TO_INT64(TO_INT64(x) * TO_INT64(y))
#define MUL_UINT16(x, y)									TO_UINT16(TO_UINT16(x) * TO_UINT16(y))
#define MUL_UINT32(x, y)									TO_UINT32(TO_UINT32(x) * TO_UINT32(y))
#define MUL_UINT64(x, y)									TO_UINT64(TO_UINT64(x) * TO_UINT64(y))
#define COMPLEX_FUNCTION_0									std::function<void()>
#define COMPLEX_FUNCTION_1(x_args)							std::function<void(x_args)>
#define COMPLEX_FUNCTION_2(x_args, y_args)					std::function<void(x_args, y_args)>
#define COMPLEX_FUNCTION_3(x_args, y_args, z_args)			std::function<void(x_args, y_args, z_args)>
#define COMPLEX_FUNCTION_4(x_args, y_args, z_args, a_args)	std::function<void(x_args, y_args, z_args, a_args)>
#define UNUSED(x)											x;
#define EXPRESSION_STRING(x)								#x
#define EXPRESSION_WSTRING(x)								_CRT_WIDE(#x)
#define EXPRESSION_TO_WSTRING(x)							_CRT_WIDE(x)

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Control;
	CO_NAMESPACE_END
PW_NAMESPACE_END

#define GIVE_ACCESS(class_type) friend class class_type

#endif // !H_MACRO