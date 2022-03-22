#include "engine_structures\engine_event.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
		// Event Base
		// Static Declarations
		// Class Members
		Event_Base::Event_Base(const PW_BUTTON_CODE& p_button, const bool& p_play_once, const PW_INPUT_TYPE& p_trigger, const PW_INPUT_TYPE& p_resolution) :
				m_play_once{ p_play_once }, m_trigger{ p_trigger }, m_resolution{ p_resolution }, m_button{ p_button } {
		}
		Event_Base::~Event_Base() {
		}
		void Event_Base::Trigger_Event() {
		}
		PW_INPUT_TYPE Event_Base::Find_Resolution(const PW_INPUT_TYPE& p_trigger) const {
			switch (p_trigger) {
				case GLFW_PRESS: {
					return GLFW_RELEASE;
				}
				case GLFW_RELEASE: {
					return GLFW_PRESS;
				}
				case GLFW_REPEAT: {
					return GLFW_PRESS | GLFW_RELEASE;
				}
				default: {
					return NULL;
				}
			}
		}
		const PW_INPUT_TYPE& Event_Base::Trigger() const {
			return m_trigger;
		}
		const PW_INPUT_TYPE& Event_Base::Resolution() const {
			return m_resolution;
		}
		const bool& Event_Base::Play_State() const {
			return m_play_once;
		}
		const PW_BUTTON_CODE& Event_Base::Button() const {
			return m_button;
		}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////