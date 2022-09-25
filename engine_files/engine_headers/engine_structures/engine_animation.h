// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
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
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers  
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <chrono>
#include <iomanip>
#include <fstream>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_error.h"
#include "engine_common\engine_timer.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_mesh.h"
#include "engine_structures\engine_texture.h"
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
		class Animation {
		// Default Class Structures
		public:
			Animation();

			Animation(const float& p_animation_length, const uint32_t& p_frame_count, const uint32_t& p_frame_size_x, Vertex_Data* p_vertices, const size_t& p_vertices_count, const bool& p_is_async);
			
			Animation(const float& p_animation_length, const uint32_t& p_frame_count, const uint32_t& p_frame_size_x, const bool& p_is_async);
			
			~Animation();
			
			Animation(const Animation& p_copy);
			
			Animation(const std::shared_ptr<Animation>& p_object);
		private:
		// Public Functions/Macros
		public:
			void Change_Frame(bool p_render_call = true);
			
			void Finish_Init(Vertex_Data* p_vertices, size_t p_vertices_count);
			
			void Advance_Frame();
			
			void Start_Animation();
			void Stop_Animation();
			void Reset_Animation();
			
			Vertex_Data* Vertices();
			// Returns true if we are at the start
			const bool& Start();
			// Returns true if we are at the end
			const bool& End();
			// Returns if the animation should be updated
			const bool& Is_Async();
		// Public Variables
		public:
		// Private Functions/Macros 
		private:
		// Private Variables 
		private:
			bool m_start;
			bool m_end;

			bool m_keep_animating;
			// Do we keep running the animation
			// as long as the scene is still being played
			bool m_is_async;

			cm::Engine_Timer m_frame_timer;
			// The number of frames
			uint32_t m_frame_count;
			// The step between frames
			float m_animation_step;
			// This current frame
			uint32_t m_current_frame;

			Vertex_Data* m_vertices_default;
			Vertex_Data* m_animation_vertices;

			size_t m_vertices_count;
		};
		struct Animation_Structure {
		// Default Class Structures 
		public:
			Animation_Structure(st::Animation* p_animation);
			Animation_Structure(const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids);

			~Animation_Structure();
		private:
		// Public Functions/Macros 
		public:
			// If the structure only has one animation it will return a shared ptr to the animation else a nullptr
			std::tuple<st::Animation*, st::Texture*> Animation() const;
			std::tuple<st::Animation*, st::Texture*> Animation(const std::wstring& p_animation_id);
			std::map<std::wstring, std::tuple<st::Animation*, st::Texture*>>& Animations();
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables        
		private:
			bool m_single_animation;
			std::map<std::wstring, std::tuple<st::Animation*, st::Texture*>> m_animations;
			st::Texture* m_current_access;
		};
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_IE_ANIMATION
