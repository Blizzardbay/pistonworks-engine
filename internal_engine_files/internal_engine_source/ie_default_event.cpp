#include "internal_engine_headers\ie_default_event.h"
namespace pw {
	/* Engine_Queue             */
	/* Static Declarations      */
	void (*IE_Default_Event::function_arr[(int)Default_Functions::DEFAULT_FUCNTION_COUNT])();
	float IE_Default_Event::move_increment = 120;
	/* Class Members            */
	void IE_Default_Event::Init_Default_Input_Callbacks() {
		function_arr[(int)Default_Functions::MOVE_RIGHT] = IE_Default_Event::Move_Right;
		function_arr[(int)Default_Functions::MOVE_LEFT] = IE_Default_Event::Move_Left;
		function_arr[(int)Default_Functions::MOVE_UP] = IE_Default_Event::Move_Up;
		function_arr[(int)Default_Functions::MOVE_DOWN] = IE_Default_Event::Move_Down;
		function_arr[(int)Default_Functions::CHANGE_SCENE] = IE_Default_Event::Change_Scene;
	}
	void IE_Default_Event::Move_Right() {
		IE_Player::Set_Player_X_Position(IE_Player::Player_X_Position() + move_increment * (Engine_Constant::Delta_Time().count() / 1000));
	}
	void IE_Default_Event::Move_Left() {
		IE_Player::Set_Player_X_Position(IE_Player::Player_X_Position() - move_increment * (Engine_Constant::Delta_Time().count() / 1000));
	}
	void IE_Default_Event::Move_Up() {
		IE_Player::Set_Player_Y_Position(IE_Player::Player_Y_Position() + move_increment * (Engine_Constant::Delta_Time().count() / 1000));
	}
	void IE_Default_Event::Move_Down() {
		IE_Player::Set_Player_Y_Position(IE_Player::Player_Y_Position() - move_increment * (Engine_Constant::Delta_Time().count() / 1000));
	}
	void IE_Default_Event::Change_Scene() {
		Engine_Queue::Change_Scene(Engine_Queue::Scene_Index() + 1);
	}
}