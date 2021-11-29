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
		Event_Base::Event_Base(bool p_play_once, PW_INPUT_TYPE p_trigger, PW_INPUT_TYPE p_resolution) :
				m_play_once{ p_play_once }, m_trigger{ p_trigger }, m_resolution{ p_resolution } {
		}
		void Event_Base::Trigger_Event() {
		}
		PW_INPUT_TYPE Event_Base::Find_Resolution(PW_INPUT_TYPE trigger) {
			if (trigger == cm::Engine_Constant::PW_CONDIONAL_EVENT) {
				return cm::Engine_Constant::PW_ACONDIONAL_EVENT;
			}
			switch (trigger) {
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
		// Accessors
		PW_INPUT_TYPE Event_Base::Trigger() {
			return m_trigger;
		}
		PW_INPUT_TYPE Event_Base::Resolution() {
			return m_resolution;
		}
		bool Event_Base::Play_State() {
			return m_play_once;
		}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////