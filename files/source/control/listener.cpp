#include "control\listener.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Listener  
		// Static Declarations
			bool Listener::m_created_listener{ false };
			glm::vec2 Listener::m_position{ st::Camera::At_Vector() };
			glm::vec3 Listener::m_up_vector{};
			glm::vec3& Listener::m_at_vector{ st::Camera::At_Vector() };
			ALCdevice* Listener::m_current_device{ nullptr };
			ALCcontext* Listener::m_context{ nullptr };
			std::function<glm::vec2()> Listener::m_position_calculator{};
		// Class Members
			void Listener::Create_Listener(const glm::vec3& p_up_vector, glm::vec3& p_at_vector) {
				if (m_created_listener != true) {
					m_created_listener = true;

					m_up_vector = p_up_vector;

					m_at_vector = p_at_vector;

					// Finds the default output device for the computer
					TRY_LINE m_current_device = alcOpenDevice(NULL);

					if (m_current_device != NULL) {
						m_context = alcCreateContext(m_current_device, NULL);
						alcMakeContextCurrent(m_context);
					}
					else {
						SET_ERROR_STATE(PW_AUDIO_SOURCE_NOT_FOUND);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Listener", L"Unable to find default audio device.", ERROR_LINE, __FILEW__, L"Create_Listener"));
						return;
					}

					PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]), true);

					float listener_orientation[6];

					listener_orientation[0] = m_at_vector.x;
					listener_orientation[1] = m_at_vector.y;
					listener_orientation[2] = m_at_vector.z;
					listener_orientation[3] = m_up_vector.x;
					listener_orientation[4] = m_up_vector.y;
					listener_orientation[5] = m_up_vector.z;

					PW_AL_VOID_CALL(alListenerfv(AL_ORIENTATION, listener_orientation), false);
				}
			}
			void Listener::Create_Listener(const std::function<glm::vec2()>& p_position_tie, const glm::vec3& p_up_vector, glm::vec3& p_at_vector) {
				if (m_created_listener == true) {
					Change_Bound_Listener(p_position_tie);
				}
				else {
					m_created_listener = true;

					m_position = p_position_tie();
					m_position_calculator = p_position_tie;

					m_up_vector = p_up_vector;

					m_at_vector = p_at_vector;

					// Finds the default output device for the computer
					TRY_LINE m_current_device = alcOpenDevice(NULL);

					if (m_current_device != NULL) {
						m_context = alcCreateContext(m_current_device, NULL);
						alcMakeContextCurrent(m_context);
					}
					else {
						SET_ERROR_STATE(PW_AUDIO_SOURCE_NOT_FOUND);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Listener", L"Unable to find default audio device.", ERROR_LINE, __FILEW__, L"Create_Listener"));
						return;
					}

					PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]), true);

					float listener_orientation[6];

					listener_orientation[0] = m_at_vector.x;
					listener_orientation[1] = m_at_vector.y;
					listener_orientation[2] = m_at_vector.z;
					listener_orientation[3] = m_up_vector.x;
					listener_orientation[4] = m_up_vector.y;
					listener_orientation[5] = m_up_vector.z;

					PW_AL_VOID_CALL(alListenerfv(AL_ORIENTATION, listener_orientation), false);
				}
			}
			void Listener::Update() {
				if (m_created_listener == true) {
					// If m_center_calculator has the same position as last
					// time it will return a false value that we can check for
					if (m_position_calculator != nullptr) {
						m_position = m_position_calculator();
						// We need to update the position of the sound every frame
						PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]), false);
					}
				}
			}
			void Listener::Release() {
				if (m_created_listener == true) {
					m_context = alcGetCurrentContext();
					m_current_device = alcGetContextsDevice(m_context);
					alcMakeContextCurrent(NULL);
					alcDestroyContext(m_context);
					alcCloseDevice(m_current_device);
				}
			}
			void Listener::Change_Bound_Listener(const std::function<glm::vec2()>& p_new_position_tie) {
				if (m_created_listener == true) {
					if (p_new_position_tie != nullptr) {
						m_position = p_new_position_tie();

						PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]), false);
					}
				}
			}
			void Listener::Set_Volume(const float& p_new_gain, const bool& p_windows_style) {
				if (m_created_listener == true) {
					if (p_windows_style == true) {
						PW_AL_VOID_CALL(alListenerf(AL_GAIN, p_new_gain / 100.0f), false);
					}
					else {
						PW_AL_VOID_CALL(alListenerf(AL_GAIN, p_new_gain), false);
					}
				}
			}
			void Listener::Set_Device(const std::wstring& p_device_name) {
				if (m_created_listener == true) {
					TRY_LINE m_current_device = alcOpenDevice(TO_STRING(p_device_name).c_str());
					if (m_current_device == NULL) {
						SET_ERROR_STATE(PW_AUDIO_SOURCE_NOT_FOUND);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Listener", TO_WSTRING(alGetString(alGetError())), ERROR_LINE, __FILEW__, L"Set_Device"));
						return;
					}
				}
			}
			std::vector<std::wstring> Listener::Get_Device_List() {
				if (m_created_listener == true) {
					const char* v_device_list = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
					int32_t v_terminator = 0;
					uint64_t v_index = 0;

					std::wstring v_temp_str{};

					std::vector<std::wstring> v_device_list_holder{};
					// This device list str is terminated by two null terminators '\0' '\0'
					while (v_terminator != 2) {
						if (v_device_list[v_index] == '\0') {
							v_terminator = v_terminator + 1;
						}
						else {
							if (v_terminator > 0) {
								// We failed at finding the end so 
								// add the string we created to the vector
								// and go on creating more
								v_device_list_holder.push_back(v_temp_str);
								v_temp_str.clear();
								v_terminator = v_terminator - 1;
							}
							v_temp_str.append(TO_WSTRING(v_device_list[v_index]));
							v_index = v_index + 1;
						}
					}
					v_device_list_holder.push_back(v_temp_str);

					return v_device_list_holder;
				}
				else {
					return std::vector<std::wstring>();
				}
			}
			std::wstring Listener::Device_Name() {
				if (m_created_listener == true) {
					return TO_WSTRING(alcGetString(m_current_device, ALC_DEVICE_SPECIFIER));
				}
				else {
					return std::wstring();
				}
			}
	CO_NAMESPACE_END
PW_NAMESPACE_END