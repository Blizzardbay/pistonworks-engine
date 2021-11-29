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
#ifndef H_ENGINE_QUEUE
#define H_ENGINE_QUEUE
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <iostream>
#include <filesystem>
#include <fstream>
#include <corecrt_wstring.h>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers
#include "engine_control\engine_file_loader.h"
#include "engine_structures\engine_shader.h"
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
	CO_NAMESPACE_SRT
	//////////////////////////////////
		//////////////////////////////////
		// Classes

		// //////////////////////////////////////////////////
		// PW_CONTROL_API Class Name: pw::Engine_Queue
		// //////////////////////////////////////////////////
		// Purpose:
		//  For handling all engine events and switching
		//  from editor mode to game state.
		// //////////////////////////////////////////////////
		class PW_CONTROL_API Engine_Queue : protected cm::Engine_Constant {
		// Default Class Structures
		public:
		private:
		// Public Functions/Macros
		public:
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Pre_Queue
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Gets rendering information ready for scene render
			// .
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Pre_Queue();
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Run_Queue
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Runs the game engine rendering.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Run_Queue();
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Refresh_Queue
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Refreshes the models in the queue after event.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Refresh_Queue();
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Load_From_Dir
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Loads a project from a directory.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const wchar_t* directory; 
			// Purpose:
			//  The directory in which the project file resides.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Load_From_Dir(const wchar_t* directory, st::Shader& shader, PW_DUNI_PTR(GLFWwindow, cm::Engine_Constant::Destroy_GLFW)& main_window,
				PW_SRD_PTR(PW_FUNCTION) state_function);
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Print_Debug_Stats
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Prints out debug stats about the engine.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			static CORE void Print_Debug_Stats();
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Clear_Queue
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Clears the queue of all of its members.
			// //////////////////////////////////////////////////
			// Parameters: NONE
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Clear_Queue();
			// //////////////////////////////////////////////////
			// CORE FUNCTION: Engine_Queue::Add_Scene
			// //////////////////////////////////////////////////
			// Purpose: 
			//  Adds a scene to the total queue.
			// //////////////////////////////////////////////////
			// Parameters: 2
			// (1) std::wstring scene_name;
			// Purpose:
			//  The name of the scene to be added and loaded.
			// (2) bool set_current = false;
			// Purpose:
			//  Do we set this to the current scene.
			// //////////////////////////////////////////////////
			NO_USER_INTERACTION
			static CORE void Add_Scene(std::wstring scene_name, bool set_current = false);
			// Mutator
			USER_INTERACTION
			static MUTATOR void Set_Current_Scene(std::wstring name_id);
			// Accessors
			NO_USER_INTERACTION
			static ACCESSOR st::Game_Scene* Current_Scene();
		// Public Variables      
		public:
		// Private Functions/Macros
		private:
		// Private Variables       
		private:
			// Has the pwproject file been loaded
			static bool loaded_project;
			// Data to be loaded from the game
			static std::wstring project_name;

			static std::wstring* current_scene;

			static std::map<std::wstring, st::Game_Scene*> scene_directory;
		};
		// Functions
		// Macros / Definitions
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////   
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_QUEUE