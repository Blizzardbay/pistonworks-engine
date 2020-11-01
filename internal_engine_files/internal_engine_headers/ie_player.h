#ifndef H_IE_PLAYER
#define H_IE_PLAYER

//(DUAL_FILE)

/* C++ Headers              */
/* Project Headers          */
/* Engine Headers           */
#include "ie_model.h"
/* Engine Macro Includes    */
#include "engine_headers\engine_error.h"
/* Engine Macros            */
/****************************/
namespace pw {
/* Classes                  */
//
	/*                                             */
	/*[ (IE_Player)                                 ]
	 For handling the player object within the
	 engine.
	*/
	class IE_Player {
/* Default Class Structures */
	public:
	private:
/* Public Functions/Macros  */
	public:
		static void Init_Player(IE_Model player_model);

		static void Draw_Player(IE_Shader shader);
		static void Delete_Player() { player_model.Delete(); }

		static int Get_Player_X_Position() { return player_model.Get_IPosition_X(); }
		static int Get_Player_Y_Position() { return player_model.Get_IPosition_Y(); }

		static void Set_Player_X_Position(int x_pos) { player_model.Update_Position((float)x_pos, (float)IE_Player::Get_Player_Y_Position()); }
		static void Set_Player_Y_Position(int y_pos) { player_model.Update_Position((float)IE_Player::Get_Player_X_Position(), (float)y_pos); }
/* Public Variables         */
	public:
/* Private Functions/Macros */
	private:
/* Private Variables        */
	private:
		static IE_Model player_model;
	};
/* Functions                */
/* Macros                   */
}
#endif // !H_IE_PLAYER
