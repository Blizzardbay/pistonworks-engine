#include "engine_control\engine_control.h"

#include "engine_control\engine_console_manip.h"

void Print() {
	PRINT_MSG(L"User", L"Action", GAME_MSG);
}

void pw::co::Engine_Control::Init_Game() {
	Engine_Input::Register_Function("Print", std::make_shared<PW_FUNCTION>((PW_FUNCTION)Print));
}
void pw::co::Engine_Control::Before_Queue() {

}
void pw::co::Engine_Control::After_Queue() {

}