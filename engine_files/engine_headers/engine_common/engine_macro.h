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
#ifndef H_ENGINE_MACRO
#define H_ENGINE_MACRO
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <memory>
#include <stdint.h>
#include <functional>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Macros
// Standard PW Namespace
#define PW_COMMON_API
// Apart of the Engine Control Files
#define PW_CONTROL_API
// Apart of the Engine Structure Files
#define PW_STRUCTURES_API
// Apart of the Error.h header file
#define PW_ERROR_API
// Apart of the Console API
#define PW_CONSOLE_API
// Apart of the PW namespace globally
#define PW_GLOBAL_API
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
// Enable Debug Features
#ifdef _DEBUG
#define PW_DEBUG_MODE
#endif // _DEBUG
// For different function types
// An ACCESSOR function returns the function's name as a variable to the user.
// EX. int c = 0;
// int C(); <- is a ACCESSOR
// int C(); returns the c variable 
#define ACCESSOR
// An MUTATOR function changes the function's name to a variable.
// EX. int c = 0;
// void C(int new_val); <- is a MUTATOR
// void C(int new_val); changes the c variable to new_val
#define MUTATOR
// A LOADER function loads something that is the function's name.
// EX. byte_data;
// byte_data Load_Byte_Data(string location); <- is a LOADER
// byte_data Load_Byte_Data(string location); loads byte_data from a certain file location
#define LOADER
// A CORE function is a function that is within the core functionality of the engine.
// This function usually has a description of what it does and what arguments passed to it do.
#define CORE
// A ERROR_HANDLE function is purely for error reporting to the user. They handle and send important
// error related information.
#define ERROR_HANDLE
// A UTILITY function is one that preforms a certain operation that is not necessarily a necessity inside the engine.
#define UTILITY
// A CLASS_FUCNTION is a operator , deconstructor or a constructor that the class has.
#define CLASS_FUNCTION
// The user is required to overload this function
#define OVERLOAD
// This function or member is apart of the console API
#define CONSOLE
// This function is a algorithm for some mathematical purpose
#define ALGORITHM
// A function labeled with USER_INTERACTION can be used
#define USER_INTERACTION 
// A function labeled with NO_USER_INTERACTION should not be used.
#define NO_USER_INTERACTION
// A section of code that consists of only accessors
#define ACCESSORS
// A section of code that consists of only mutators
#define MUTATORS
// Lets C++ implement the function
#define LET_CPP_IMPLEMENT
// A root file is a file that does not include any other Pistonworks Engine headers
#define ROOT_FILE
// A root structure is a structure that does not include any other Pistonworks Engine structures
#define ROOT_STRUCTURE
// Memory function
#define MEMORY

#define PW_SRD_PTR(type)									std::shared_ptr<type>
#define PW_UNI_PTR(type)									std::unique_ptr<type>
#define PW_DUNI_PTR(type, deleter)							std::unique_ptr<type, deleter>
#define TO_INT16(x)											static_cast<int16_t>(x)
#define TO_UINT16(x)										static_cast<uint16_t>(x)
#define TO_INT32(x)											static_cast<int32_t>(x)
#define TO_UINT32(x)										static_cast<uint32_t>(x)
#define TO_INT64(x)											static_cast<int64_t>(x)
#define TO_UINT64(x)										static_cast<uint64_t>(x)
#define VARIABLE_NAME(x)									static_cast<const wchar_t*>(#x)
#define OFF(x)												(x + 1)
#define OFF16(x)											(TO_INT16(x) + TO_INT16(1))
#define OFF32(x)											(TO_INT32(x) + TO_INT32(1))
#define OFF64(x)											(TO_INT64(x) + TO_INT64(1))
#define COMPLEX_FUNCTION_1(x_args)							std::function<void(x_args)>
#define COMPLEX_FUNCTION_2(x_args, y_args)					std::function<void(x_args, y_args)>
#define COMPLEX_FUNCTION_3(x_args, y_args, z_args)			std::function<void(x_args, y_args, z_args)>
#define COMPLEX_FUNCTION_4(x_args, y_args, z_args, a_args)	std::function<void(x_args, y_args, z_args, a_args)>

#endif // !H_ENGINE_MACRO