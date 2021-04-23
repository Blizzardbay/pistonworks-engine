#ifndef H_ENGINE_QUEUE
#define H_ENGINE_QUEUE
//////////////////////////////////
// #FILE_INFO#
// +(DUAL_FILE)
//////////////////////////////////
// C++ Headers
#include <iostream>
#include <filesystem>
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
		// Purpose: Loads a scene from a dir.
		//
		static PW_VOID Load_From_Dir(PW_CSTRING dir);
		// Function: Engine_Queue::Add_Game_Scene
		//
		// Purpose: Add a scene to the global queue. 
		//
		static PW_VOID Add_Game_Scene(PW_SRD_PTR(ie::Game_Scene) scene);
		// Function: Engine_Queue::Change_Scene
		//
		// Purpose: Changes the scene to a specific member. 
		//
		static PW_VOID Change_Scene(PW_UINT new_index);
		// Function: Engine_Queue::Scene_Index
		//
		// Purpose: Returns the current index.
		//
		static PW_UINT Scene_Index();
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
	// Public Variables      
	public:
	// Private Functions/Macros
	private:
		// Function: Engine_Queue::Insertion_Sort
		//
		// Purpose: Sorts a list of scene very fast. 
		//
		static PW_VOID Insertion_Sort();
	// Private Variables       
	private:
		static PW_UINT index;
		static std::vector<PW_SRD_PTR(ie::Game_Scene)> scene_vector;
	};
	// Functions   
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_QUEUE