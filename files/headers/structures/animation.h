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
#ifndef H_ANIMATION
#define H_ANIMATION
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers  
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <chrono>
#include <iomanip>
#include <fstream>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\error.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "structures\timer.h"
#include "structures\mesh.h"
#include "structures\texture.h"
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		class Animation {
		// Friends
		// Default Class Structures
		public:
			/* Error List: NONE */
			Animation();
			/* Error List: PW_FUNCTION_ERROR */
			Animation(const float p_animation_length, const uint32_t p_frame_count, const uint32_t p_frame_size_x, Vertex_Data* p_vertices, const size_t& p_vertices_count, const bool p_is_async);
			/* Error List: NONE */
			Animation(const float p_animation_length, const uint32_t p_frame_count, const uint32_t p_frame_size_x, const bool p_is_async);
			/* Error List: NONE */
			~Animation();
			/* Error List: NONE */
			Animation(const Animation& p_copy);
			/* Error List: NONE */
			Animation(const std::shared_ptr<Animation>& p_object);
		private:
		// Public Functions/Macros
		public:
			/* Error List: PW_NULL_PARAMETER_W */
			void Change_Frame(bool p_render_call = true);
			/* Error List: PW_FUNCTION_ERROR */
			void Finish_Init(Vertex_Data* p_vertices, size_t p_vertices_count);
			/* Error List: PW_NULL_PARAMETER_W */
			void Advance_Frame();
			/* Error List: NONE */
			void Start_Animation();
			/* Error List: NONE */
			void Stop_Animation();
			/* Error List: NONE */
			void Reset_Animation();
			/* Error List: NONE */
			Vertex_Data* Vertices();
			// Returns true if we are at the start
			// Error List: NONE 
			const bool Start();
			// Returns true if we are at the end
			// Error List: NONE
			const bool End();
			// Returns if the animation should be updated
			// Error List: NONE
			const bool Is_Async();
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

			st::Manual_Timer<std::chrono::milliseconds> m_frame_timer;
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
			/* Error List: NONE */
			Animation_Structure(st::Animation* p_animation);
			/* Error List: PW_ANIMATION_ID_SIZE_MISMATCH */
			Animation_Structure(const std::vector<std::tuple<st::Animation*, st::Texture*>>& p_animations, const std::vector<std::wstring>& p_animation_ids);
			/* Error List: NONE */
			~Animation_Structure();
		private:
		// Public Functions/Macros 
		public:
			// If the structure only has one animation it will return a shared ptr to the animation else a nullptr
			// Error List: NONE
			std::tuple<st::Animation*, st::Texture*> Animation() const;
			/* Error List: NONE */
			std::tuple<st::Animation*, st::Texture*> Animation(const std::wstring& p_animation_id);
			/* Error List: NONE */
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
	ST_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_IE_ANIMATION
