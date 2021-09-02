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
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Headers
#include "internal_engine_headers\ie_game_scene.h"
//////////////////////////////////
// Engine Macro Includes
#include "engine_headers\engine_error.h"
//////////////////////////////////
// Engine Macros
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	// Classes

	//////////////////////////////////
	// Class Name: pw::Engine_Queue
	//
	// Purpose: For handling all engine events and switching
	//    from editor mode to game state.
	//
	class PW_ENGINE_API Engine_Queue {
	// Default Class Structures
	public:
	private:
	// Public Functions/Macros
	public:
		// Function: Engine_Queue::Run_Queue
		//
		// Purpose: Runs the game engine rendering. 
		//
		static PW_VOID Run_Queue();
		// Function: Engine_Queue::Refresh_Queue
		//
		// Purpose: Refreshes the models in the queue after event. 
		//
		static PW_VOID Refresh_Queue();
		// Function: Engine_Queue::Load_From_Dir
		//
		// Purpose: Loads a project from a directory.
		//
		static PW_VOID Load_From_Dir(PW_CSTRING directory);
		// Function: Engine_Queue::Current_Scene
		//
		// Purpose: Returns the current scene being drawn.
		//
		static ie::Game_Scene* Current_Scene();
		// Function: Engine_Queue::Clear_Queue
		//
		// Purpose: Clears the queue of all of its members.
		//
		static PW_VOID Clear_Queue();
		// Function: Engine_Queue::Load_Scene
		//
		// Purpose: Loads a scene from a file location.
		//
		static PW_VOID Load_Scene(PW_CSTRING scene_location);
		// Function: Engine_Queue::Set_Current_Scene
		//
		// Purpose: Sets the current scene to be rendered.
		//
		static PW_VOID Set_Current_Scene(PW_CSTRING name_id);
	// Public Variables      
	public:
	// Private Functions/Macros
	private:
	// Private Variables       
	private:
		// Has the pwproject file been loaded
		static PW_FLAG loaded_project;
		// Data to be loaded from the game
		static PW_STRING project_name;

		static PW_STRING data_location;
		static PW_STRING texture_location;
		static PW_STRING animation_location;
		static PW_STRING font_location;
		static PW_STRING icon_location;

		static PW_NAME_ID* current_scene;

		static std::map<PW_NAME_ID, ie::Game_Scene*> scene_directory;
	};
	// Functions
	// Macros / Definitions   
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_QUEUE