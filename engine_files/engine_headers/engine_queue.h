#ifndef H_ENGINE_QUEUE
#define H_ENGINE_QUEUE

//(DUAL_FILE)

/* C++ Headers              */
#include <iostream>
#include <filesystem>
/* Project Headers          */
/* Engine Headers           */
#include "internal_engine_headers\ie_game_scene.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
//
/* ############################# */
/* Pistonworks Engine            */
/* Created By : Darrian Corkadel */
/* ############################# */
namespace pw {
/* Classes                  */
//
	/* -Engine_Queue
	 For handling all engine events and switching
	 from editor mode to game state.
	*/
	class Engine_Queue {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static PW_VOID Run_Queue();

		static PW_VOID Refresh_Queue();

		static PW_VOID Load_From_Dir(PW_CSTRING dir);
		
		static PW_VOID Add_Game_Scene(ie::Game_Scene scene);

		static PW_VOID Change_Scene(PW_UINT new_index) { index = new_index; }
		static PW_UINT Scene_Index() { return index; }

		static PW_VOID Clear_Queue();
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		static PW_VOID Insertion_Sort();
/* Private Variables        */
	private:
		static PW_UINT index;
		static std::vector<ie::Game_Scene> scene_vector;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_ENGINE_QUEUE