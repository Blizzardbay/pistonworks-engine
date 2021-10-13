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
#ifndef H_ENGINE_ANIMATION
#define H_ENGINE_ANIMATION
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers    
#include <chrono>
#include <iomanip>
#include <fstream>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers 
#include "engine_structures\engine_mesh.h"
#include "engine_structures\engine_texture.h"
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
		// PW_STRUCTURES_API Class: pw::st::Animation
		// //////////////////////////////////////////////////
		// Purpose:
		//  A base class for holding a base layout of
		//  animations within the engine.
		// //////////////////////////////////////////////////
		class PW_STRUCTURES_API Animation {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Animation::Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize animation information
			//  and data structures.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) float animation_length;
			// Purpose: 
			//  A time in seconds that the animation will last.
			// (2) uint32_t frame_count;
			// Purpose: 
			//  The total number of frames.
			// (3) uint32_t frame_size_x;
			// Purpose: 
			//  The size of one frame.
			// (4) ID_Vertex_Data* vertices;
			// Purpose:
			//  The vertices of the object.
			// (5) size_t vertices_count;
			// Purpose:
			//  The count of the vertices.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Animation(float animation_length, uint32_t frame_count, uint32_t frame_size_x, ID_Vertex_Data* vertices, size_t vertices_count);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Animation::Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize animation information
			//  and data structures. Cannot be animated.
			// //////////////////////////////////////////////////
			// Parameters: 5
			// (1) float animation_length;
			// Purpose: 
			//  A time in seconds that the animation will last.
			// (2) uint32_t frame_count;
			// Purpose: 
			//  The total number of frames.
			// (3) uint32_t frame_size_x;
			// Purpose: 
			//  The size of one frame.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Animation(float animation_length, uint32_t frame_count, uint32_t frame_size_x);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Animation::~Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to deallocate all animation information.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CLASS_FUNCTION ~Animation();
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Animation::Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  A standard copy constructor for animation
			//  information.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const Animation& copy;
			// Purpose: 
			//  The animation to be copied from.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Animation(const Animation& copy);
			// //////////////////////////////////////////////////
			// PW_STRUCTURES_API CLASS_FUNCTION: Animation::Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  A copy constructor for smart pointers.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const PW_SRD_PTR(Animation)& object;
			// Purpose: 
			//  The animation to be copied from.
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Animation(const PW_SRD_PTR(Animation)& object);
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Change_Frame
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to change the frame of the animation.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Change_Frame();
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the current animation and 
			//  all relevant data.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Delete();
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Finish_Init
			// //////////////////////////////////////////////////
			// Purpose: 
			//  If a animation is loaded from a gif or other file
			//  type, in the engine we cannot directly create a
			//  model of a known type for it so the work around
			//  is to init the animation after the model is
			//  created.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) ID_Vertex_Data* vertices;
			// Purpose:
			//  The vertices of the object.
			// (2) size_t vertices_count;
			// Purpose:
			//  The count of the vertices.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Finish_Init(ID_Vertex_Data* vertices, size_t vertices_count);
			// Accessors
			USER_INTERACTION
			ACCESSOR ID_Vertex_Data* Vertices();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Reset_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to reset that animation back to its first
			//  frame.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			CORE void Reset_Animation();
		// Private Variables 
		private:
			// Animation time between frames
			float animation_time;
			// The time at which the next frame plays
			std::clock_t activation_time;
			// The number of frames
			uint32_t frame_count;
			// The step between frames
			float animation_step;
			// This current frame
			uint32_t current_frame;

			PW_SRD_PTR(ID_Vertex_Data*) vertices_default;
			PW_SRD_PTR(ID_Vertex_Data*) animation_vertices;

			size_t vertices_count;
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_ANIMATION
