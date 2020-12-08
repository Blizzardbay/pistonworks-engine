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
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (Engine_Queue)                              ]
	 For handling all engine events and switching
	 from editor mode to game state.
	*/
	class Engine_Queue {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static void Run_Queue();

		static void Load_From_Dir(const char* dir);
		
		static void Add_Game_Scene(IE_Game_Scene scene);

		static void Change_Scene(size_t new_index) { index = new_index; }
		static size_t Scene_Index() { return index; }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
		static void Insertion_Sort();
/* Private Variables        */
	private:
		static size_t index;
		static std::vector<IE_Game_Scene> scene_vector;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_ENGINE_QUEUE