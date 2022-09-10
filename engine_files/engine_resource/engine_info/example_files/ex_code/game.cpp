#include "engine_control\engine_control.h"

#include "engine_control\engine_console_manip.h"
#include "engine_structures\engine_game_scene.h"
#include "engine_common\engine_math.h"

#include "game_structures\game_headers\structure_headers\player.h"
#include "game_structures\game_headers\main_menu\main_menu.h"

void Print() {
	PRINT_MSG(L"Game", L"This is a mouse event", GAME_MSG);
}

void pw::co::Engine_Control::Pre_Scene_Load(const std::wstring& p_scene) {
}
void pw::co::Engine_Control::Pre_Scene_Change(const std::wstring& p_scene) {
}
void pw::co::Engine_Control::Pre_Scene_Removal(const std::wstring& p_scene) {
}
void pw::co::Engine_Control::Post_Scene_Load(const std::wstring& p_scene) {
}
void pw::co::Engine_Control::Post_Scene_Change(const std::wstring& p_scene) {
}
void pw::co::Engine_Control::Post_Scene_Removal(const std::wstring& p_scene) {
}
void pw::co::Engine_Control::Pre_Load() {
	pw::co::Engine_Input::Register_Function(L"Hovering_Over_Slider", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Main_Menu::Hovering_Over_Slider));
	pw::co::Engine_Input::Register_Function(L"Move_Slider", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Main_Menu::Move_Slider));

	pw::co::Engine_Input::Register_Function(L"Move_Left", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::Move_Left));
	pw::co::Engine_Input::Register_Function(L"Move_Right", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::Move_Right));
	pw::co::Engine_Input::Register_Function(L"Move_Up", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::Move_Up));
	pw::co::Engine_Input::Register_Function(L"Move_Down", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::Move_Down));
	pw::co::Engine_Input::Register_Function(L"End_Move_Left", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::End_Move_Left));
	pw::co::Engine_Input::Register_Function(L"End_Move_Right", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::End_Move_Right));
	pw::co::Engine_Input::Register_Function(L"End_Move_Up", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::End_Move_Up));
	pw::co::Engine_Input::Register_Function(L"End_Move_Down", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::End_Move_Down));

	pw::co::Engine_Input::Register_Function(L"Interact", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::Interact));
	pw::co::Engine_Input::Register_Function(L"Attack", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)du::Player::Attack));

	pw::co::Engine_Input::Register_Function(L"Print", std::make_shared<pw::PW_FUNCTION>((pw::PW_FUNCTION)Print));
}
void pw::co::Engine_Control::Initialize_Game() {
	du::Main_Menu::Init_Menu();
	du::Player::Init_Player(pw::co::Engine_Queue::Get_Scene(L"Zone_1"));
	du::Bush::Init(pw::co::Engine_Queue::Get_Scene(L"Zone_1"));
}
void pw::co::Engine_Control::Before_Queue() {
	du::Player::Set_Zone(pw::co::Engine_Queue::Current_Scene()->Scene_Name());
	du::Player::Choose_Zone(pw::co::Engine_Queue::Current_Scene()->Scene_Name(), du::Player::Engine_Queue_State::BEFORE);
}
void pw::co::Engine_Control::After_Queue() {
	du::Player::Choose_Zone(pw::co::Engine_Queue::Current_Scene()->Scene_Name(), du::Player::Engine_Queue_State::AFTER);
}
void pw::co::Engine_Control::Release_Game() {
	du::Player::Delete_Player();
}
USE_PISTONWORKS_ENGINE(800, 600, true);



/*
object->Render();
if (sword->Render_Toggle()) {
	sword->Render();
}
sword->Render();
sword->Set_Render_Toggle(false);
sword->Model().Set_Model_Color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
object->Model().Set_Model_Color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
//glm::vec3 v_player_center = player->Model().Calculate_Center();


if (sword->Test_Collision(object)) {
	sword->Model().Set_Model_Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	object->Model().Set_Model_Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//PRINT_MSG(L"Hit", L"", GAME_MSG);
}
else {
	sword->Model().Set_Model_Color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	//PRINT_MSG(L"Miss", L"", GAME_MSG);
}
/*float v_mouse_angle = pw::cm::Engine_Math::Vector_Angle(v_player_center, pw::cm::Engine_Constant::Mouse_Coord());

glm::vec2 v_new_sword_position{0.0f};

v_new_sword_position.x = v_player_center.x + 16.0f * glm::cos(glm::radians(v_mouse_angle));
v_new_sword_position.y = v_player_center.y + 16.0f * glm::sin(glm::radians(v_mouse_angle));

glm::vec3 v_sword_center = sword->Model().Calculate_Center();

sword->Model().Set_Position(glm::vec3(glm::vec2(v_new_sword_position.x + (sword->Model().Position().x - v_sword_center.x),
	v_new_sword_position.y + (sword->Model().Position().y - v_sword_center.y)),
	0.0f), true);

sword->Model().Set_Rotation(v_mouse_angle, sword->Body()); */
/*
player = pw::Engine_Memory::Allocate<pw::st::Actor, bool>(std::shared_ptr<pw::st::Model>(new pw::st::Model(
	pw::st::Geometry_Types::SQUARE, &pw::co::File_Loader::Load_Texture_File(L"White.png", true), glm::vec2(32.0f, 160.0f), 0.0f, glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))));
sword = pw::Engine_Memory::Allocate<pw::st::Actor, bool>(std::shared_ptr<pw::st::Model>(new pw::st::Model(
	pw::st::Geometry_Types::SQUARE, &pw::co::File_Loader::Load_Texture_File(L"White.png", true), glm::vec2(32.0f, 96.0f), 0.0f, glm::vec2(96.0f, 32.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f))));
//sword->Model().Attach_To(player->Model().Position_Reference());
//sword->Model().Set_Offset(glm::vec2(10.0f, 0.0f));

object = pw::Engine_Memory::Allocate<pw::st::Actor, bool>(std::shared_ptr<pw::st::Model>(new pw::st::Model(
	pw::st::Geometry_Types::SQUARE, &pw::co::File_Loader::Load_Texture_File(L"White.png", true), glm::vec2(128.0f, 96.0f), 0.0f, glm::vec2(32.0f, 32.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))));

pw::co::Engine_Queue::Current_Scene()->Input()->Create_Event_Keyboard(GLFW_PRESS, GLFW_KEY_W, std::make_shared<PW_FUNCTION>((PW_FUNCTION)Move_Up), false);
pw::co::Engine_Queue::Current_Scene()->Input()->Create_Event_Keyboard(GLFW_PRESS, GLFW_KEY_S, std::make_shared<PW_FUNCTION>((PW_FUNCTION)Move_Down), false);
pw::co::Engine_Queue::Current_Scene()->Input()->Create_Event_Keyboard(GLFW_PRESS, GLFW_KEY_A, std::make_shared<PW_FUNCTION>((PW_FUNCTION)Move_Left), false);
pw::co::Engine_Queue::Current_Scene()->Input()->Create_Event_Keyboard(GLFW_PRESS, GLFW_KEY_D, std::make_shared<PW_FUNCTION>((PW_FUNCTION)Move_Right), false);


pw::co::Engine_Queue::Current_Scene()->Scene_Physics()->Add_Object(std::make_shared<pw::st::Model>(sword->Model()), b2BodyType::b2_dynamicBody, sword->Model().Id(), false);
sword->Set_Physics_Object(pw::co::Engine_Queue::Current_Scene()->Scene_Physics()->Access_Memeber(sword->Model().Id()));
pw::co::Engine_Queue::Current_Scene()->Scene_Physics()->Add_Object(std::make_shared<pw::st::Model>(object->Model()), b2BodyType::b2_dynamicBody, object->Model().Id(), false);
object->Set_Physics_Object(pw::co::Engine_Queue::Current_Scene()->Scene_Physics()->Access_Memeber(object->Model().Id()));;

//sword->Model().Set_Rotation(45.0f, sword->Body());

pw::co::Engine_Queue::Current_Scene()->Add_Model(player);
sword->Set_Render_Toggle(false);
//sword->Set_Render_Toggle(true);
if (sword->Test_Collision(object)) {
	sword->Model().Set_Model_Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	object->Model().Set_Model_Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//PRINT_MSG(L"Hit", L"", GAME_MSG);
}
else {
	sword->Model().Set_Model_Color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	//PRINT_MSG(L"Miss", L"", GAME_MSG);
}						 */