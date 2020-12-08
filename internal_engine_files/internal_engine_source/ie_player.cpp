#include "internal_engine_headers\ie_player.h"

namespace pw {
	/* Engine_Queue             */
	/* Static Declarations      */
	IE_Dynamic_Model IE_Player::player_model = IE_Dynamic_Model();
	/* Class Members            */
	void IE_Player::Draw_Player() {
		if (player_model.Model_Type() != IE_Dynamic_Model::Model_Types::UNINIT) {
			player_model.Render();
		}
	}
	void IE_Player::Init_Player(IE_Dynamic_Model init_player_model) {
		player_model = init_player_model;
	}
}