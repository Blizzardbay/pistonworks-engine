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
#ifndef H_ENGINE_EVENT
#define H_ENGINE_EVENT
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
#include <queue>
#include <functional>
#include <type_traits>
#include <map>
#include <tuple>
#include <utility>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <glm\glm.hpp>
#pragma warning (pop)
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_constant.h"
//////////////////////////////////														
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
#include "engine_structures\engine_game_header.h"
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
		class Event_Base {
		// Default Class Structures
		public:
			Event_Base(const PW_BUTTON_CODE& p_button, const bool& p_play_once, const PW_INPUT_TYPE& p_trigger, const PW_INPUT_TYPE& p_resolution);

			virtual ~Event_Base();
		private:
		// Public Functions/Macros 
		public:
			virtual void Trigger_Event();

			PW_INPUT_TYPE Find_Resolution(const PW_INPUT_TYPE& p_trigger) const;
			
			const PW_INPUT_TYPE& Trigger() const;
			const PW_INPUT_TYPE& Resolution() const;
			const bool& Play_State() const;
			const PW_BUTTON_CODE& Button() const;
		// Public Variables         
		public:
		// Private Functions/Macros 
		private:
		// Private Variables    
		private:
			bool m_play_once;
			PW_BUTTON_CODE m_button;
			PW_INPUT_TYPE m_trigger;
			PW_INPUT_TYPE m_resolution;
		};
		template<class type, class ...args>
		class Event : public Event_Base {
			// Default Class Structures
		public:
			Event() :
					Event_Base{ NULL, NULL, NULL, NULL }, m_standard_callback{ nullptr },
					m_arguments{} {
			}
			explicit Event(const PW_BUTTON_CODE& p_button, const PW_INPUT_TYPE& p_trigger, const std::shared_ptr<std::function<type(args...)>>& p_trigger_function, const bool& p_play_once, args... p_arguments) :
					Event_Base{ p_button, p_play_once, p_trigger, Find_Resolution(p_trigger) }, m_standard_callback{ *p_trigger_function },
					m_arguments{ std::forward<args>(p_arguments)... } {
			}
		private:
			// Public Functions/Macros 
		public:
			void Trigger_Event() override {
				Trigger_Event(m_arguments);
			}
			// Public Variables         
		public:
			// Private Functions/Macros 
		private:
			template<typename tuple>
			void Trigger_Event(const tuple& p_tuple) {
				Trigger_Event(p_tuple, std::make_index_sequence<std::tuple_size<tuple>::value>());
			}
			template<typename tuple, std::size_t... I>
			void Trigger_Event(const tuple& p_tuple, std::index_sequence<I...>) {
				m_standard_callback(std::get<I>(p_tuple)...);
			}
			// Private Variables    
		public:
			std::function<type(args...)> m_standard_callback;
			const std::tuple<args...> m_arguments;
		};                
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_EVENT