#ifndef H_IE_PLAYER
#define H_IE_PLAYER

//(HEADER_ONLY)

/* C++ Headers              */
/* Project Headers          */
/* Engine Headers           */
#include "internal_engine_headers\ie_model.h"
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
	//
	/* ############################# */
	/* Internal Engine               */
	/* Created By : Darrian Corkadel */
	/* ############################# */
	namespace ie {
	/* Classes                  */
	//
		/*                                             */
		/*[ (IE_Player)                                 ]
		 For handling the player object within the
		 engine.
		*/
		class Player {
	/* Default Class Structures */
		public:
		private:
	/* Public Functions/Macros  */
		public:
			static PW_VOID Init_Player(Dynamic_Model init_player_model) {
				player_model = init_player_model;
			}

			static PW_VOID Draw_Player() {
				if (player_model.Model_Type() != Dynamic_Model::Model_Types::UNINIT) {
					player_model.Render();
				}
			}
			static PW_VOID Delete_Player() { player_model.Delete(); }

			static PW_FLOAT Player_X_Position() { return player_model.Position().x; }
			static PW_FLOAT Player_Y_Position() { return player_model.Position().y; }

			static PW_VOID Set_Player_X_Position(PW_FLOAT x_pos) { player_model.Update_Position(x_pos, Player::Player_Y_Position()); }
			static PW_VOID Set_Player_Y_Position(PW_FLOAT y_pos) { player_model.Update_Position(Player::Player_X_Position(), y_pos); }

			static Dynamic_Model& Get_Model() { return player_model; }

			static PW_VOID Refresh_Player() { player_model.Refresh_Model(); }
	/* Public Variables         */
		public:
	/* Private Functions/Macros */
		private:
	/* Private Variables        */
		private:
			static Dynamic_Model player_model;
		};
	/* Functions                */
	/* Macros                   */
	}
}
#endif // !H_IE_PLAYER
