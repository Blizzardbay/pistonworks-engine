#include "main_menu\main_menu.h"

//////////////////////////////////
DU_NAMESPACE_SRT
//////////////////////////////////
	// Main_Menu
	// Static Declarations
		pw::st::Actor* Main_Menu::m_text{ nullptr };
		pw::st::Actor* Main_Menu::m_slider{ nullptr };
		bool Main_Menu::m_above_slider{ false };
	// Class Members
		void Main_Menu::Init_Menu() {
			m_text = pw::co::Engine_Queue::Current_Scene()->Access_Model(L"Volume_Percent");
			m_slider = pw::co::Engine_Queue::Current_Scene()->Access_Model(L"Volume_Slider");
		}
		void Main_Menu::Hovering_Over_Slider() {
			m_above_slider = true;
		}
		void Main_Menu::Move_Slider() {
			if (m_above_slider == true) {
				float v_mouse_x_coord = TO_FLOAT(pw::cm::Engine_Constant::Mouse_X_Coord());

				if (v_mouse_x_coord < 241 && v_mouse_x_coord > 47) {
					m_slider->Model()->Set_Position(glm::vec3((v_mouse_x_coord - m_slider->Model()->Position().x) + m_slider->Model()->Position().x - 16, m_slider->Model()->Position().y, 0.0f));

					// Calculate new volume%
					int32_t v_percent = TO_INT32((m_slider->Model()->Position().x / 192.0f) * 100.0f) - 16;

					m_text->Set_Text(std::to_wstring(v_percent) + L"%");

					pw::st::Listener::Set_Volume((float)v_percent, true);
				}
			}
			m_above_slider = false;
		}
	// End of Class Members
//////////////////////////////////
DU_NAMESPACE_END
//////////////////////////////////