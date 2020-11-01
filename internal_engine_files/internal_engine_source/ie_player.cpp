#include "internal_engine_headers\ie_player.h"

namespace pw {
	/* Engine_Queue             */
	/* Static Declarations      */
	IE_Model IE_Player::player_model = IE_Model();
	/* Class Members            */
	void IE_Player::Draw_Player(IE_Shader shader) {
		if (player_model.Get_Model_Type() != IE_Model::Model_Types::UNINIT) {
			player_model.Render(shader);
		}
	}
	void IE_Player::Init_Player(IE_Model init_player_model) {
		player_model = init_player_model;
	}
}