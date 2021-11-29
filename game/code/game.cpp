#include "engine_control\engine_control.h"

#include "engine_control\engine_console_manip.h"

void Print() {
	PRINT_MSG(L"User", L"Action", GAME_MSG);
}
void Print1() {
	PRINT_MSG(L"User", L"De_Action", GAME_MSG);
}
void Print2() {
	PRINT_MSG(L"User", L"Changed_Correctly", GAME_MSG);
}

void pw::co::Engine_Control::Init_Game() {
	Engine_Input::Register_Function("Print", std::make_shared<PW_FUNCTION>((PW_FUNCTION)Print));
	Engine_Input::Register_Function("Print1", std::make_shared<PW_FUNCTION>((PW_FUNCTION)Print1));
	Engine_Input::Register_Function("Print2", std::make_shared<PW_FUNCTION>((PW_FUNCTION)Print2));
}
void pw::co::Engine_Control::Before_Queue() {

}
void pw::co::Engine_Control::After_Queue() {

}