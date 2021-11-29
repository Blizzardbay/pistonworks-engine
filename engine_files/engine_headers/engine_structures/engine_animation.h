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
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CLASS_FUNCTION Animation();
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
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Advance_Frame
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Forces the animation to the next frame.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Advance_Frame();
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Start_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Makes the animation start to animate.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Start_Animation();
			// //////////////////////////////////////////////////
			// CORE Function: Animation::Stop_Animation
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Stops the animation from animating. Can still be
			//  advanced manually.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			USER_INTERACTION
			CORE void Stop_Animation();
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
			// Accessors
			USER_INTERACTION
			ACCESSOR ID_Vertex_Data* Vertices();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
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

			bool keep_animating;
		};
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API Class Name: pw::st::Animation_Structure
		// //////////////////////////////////////////////////
		// Purpose:
		//  A strcture that hold animation information.
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API Animation_Structure {
		// Default Class Structures 
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Animation_Structure::Animation_Structure
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the class structures.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) PW_SRD_PTR(st::Animation) p_animation;
			// Purpose:
			//  Sets the structure so it only has a single
			//  animation.
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Animation_Structure(PW_SRD_PTR(st::Animation) p_animation);
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Actor_Model::Actor_Model
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to initialize the animation structure.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) std::vector<PW_SRD_PTR(st::Animation)> p_animations;
			// Purpose:
			//  The animations to go into the structure.
			// (2) std::vector<std::wstring> p_animation_ids;
			// Purpose:
			//  The id's of the animation in the order of the
			//  animations.
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Animation_Structure(std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> p_animations, std::vector<std::wstring> p_animation_ids);
		private:
		// Public Functions/Macros 
		public:
			// //////////////////////////////////////////////////
			// CORE Function: Animation_Structure::Delete
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Used to delete the class structure's and models.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
				CORE void Delete();
			// Accessors
			// If the structure only has one animation it will return a shared ptr to the animation else a nullptr
			const ACCESSOR std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>& Animation() const;
			const ACCESSOR std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>& Animation(const std::wstring&& p_animation_id);
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			bool m_single_animation;
			std::map<std::wstring, std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> m_animations;
			st::Texture* m_current_access;
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
