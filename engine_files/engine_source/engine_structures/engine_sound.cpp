#include "engine_structures\engine_sound.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	ST_NAMESPACE_SRT
	//////////////////////////////////
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
					throw pw::er::Severe_Error(L"Engine Sound", L"Unable to find default audio device.", pw::er::Engine_Exception::Exception_Line(), __FILEW__, L"alcOpenDevice");
				}

				PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]));

				float listener_orientation[6];

				listener_orientation[0] = m_at_vector.x;
				listener_orientation[1] = m_at_vector.y;
				listener_orientation[2] = m_at_vector.z;
				listener_orientation[3] = m_up_vector.x;
				listener_orientation[4] = m_up_vector.y;
				listener_orientation[5] = m_up_vector.z;

				PW_AL_VOID_CALL(alListenerfv(AL_ORIENTATION, listener_orientation));
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
					throw pw::er::Severe_Error(L"Engine Sound", L"Unable to find default audio device.", pw::er::Engine_Exception::Exception_Line(), __FILEW__, L"alcOpenDevice");
				}

				PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]));

				float listener_orientation[6];

				listener_orientation[0] = m_at_vector.x;
				listener_orientation[1] = m_at_vector.y;
				listener_orientation[2] = m_at_vector.z;
				listener_orientation[3] = m_up_vector.x;
				listener_orientation[4] = m_up_vector.y;
				listener_orientation[5] = m_up_vector.z;

				PW_AL_VOID_CALL(alListenerfv(AL_ORIENTATION, listener_orientation));
			}
		}
		void Listener::Change_Bound_Listener(const std::function<glm::vec2()>& p_new_position_tie) {
			if (m_created_listener == true) {
				if (p_new_position_tie != nullptr) {
					m_position = p_new_position_tie();

					PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]));
				}
			}
		}
		void Listener::Update() {
			if (m_created_listener == true) {
				// If m_center_calculator has the same position as last
				// time it will return a false value that we can check for
				if (m_position_calculator != nullptr) {
					m_position = m_position_calculator();
					// We need to update the position of the sound every frame
					PW_AL_VOID_CALL(alListenerfv(AL_POSITION, &m_position[0]));
				}
			}
		}
		void Listener::Release_Listener() {
			if (m_created_listener == true) {
				m_context = alcGetCurrentContext();
				m_current_device = alcGetContextsDevice(m_context);
				alcMakeContextCurrent(NULL);
				alcDestroyContext(m_context);
				alcCloseDevice(m_current_device);
			}
		}
		void Listener::Set_Volume(const float& p_new_gain, const bool& p_windows_style) {
			if (m_created_listener == true) {
				if (p_windows_style == true) {
					PW_AL_VOID_CALL(alListenerf(AL_GAIN, p_new_gain / 100.0f));
				}
				else {
					PW_AL_VOID_CALL(alListenerf(AL_GAIN, p_new_gain));
				}
			}
		}
		void Listener::Set_Device(const std::wstring& p_device_name) {
			if (m_created_listener == true) {
				TRY_LINE m_current_device = alcOpenDevice(TO_STRING(p_device_name).c_str());
				if (m_current_device == NULL) {
					throw pw::er::Warning_Error(L"Engine Sound", TO_WSTRING(alGetString(alGetError())), pw::er::Engine_Exception::Exception_Line(), __FILEW__, L"alcOpenDevice");
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
							v_terminator = v_terminator - 1;
						}
						v_temp_str.append(TO_WSTRING(v_device_list[v_index]));
						v_index = v_index + 1;
					}
				}
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
		// End of Class Members
		// Sound  
		// Static Declarations
		// Class Members
		Sound::Sound() :
				m_audio_source_id{ 0 }, m_position{}, m_center_calculator{}, m_source_state{ AL_INITIAL }, m_loop{ false },
				m_start{ true }, m_end{ false }, m_natural_stop{ false } {
		}
		Sound::Sound(const uint32_t& p_source_id, const bool& p_loop) :
				m_audio_source_id { p_source_id }, m_position{}, m_center_calculator{}, m_source_state{ AL_INITIAL }, m_loop{ p_loop },
				m_start{ true }, m_end{ false }, m_natural_stop{ false } {
			if (TRY_LINE alIsSource(m_audio_source_id) != AL_TRUE) {
				throw pw::er::Warning_Error(L"Engine Sound", L"Loaded audio source not found.", pw::er::Engine_Exception::Exception_Line(), __FILEW__, L"alIsSource");
			}
			else {
				PW_AL_VOID_CALL(alSourcefv(m_audio_source_id, AL_POSITION, &m_position[0]));
				PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state));
			}
		}
		Sound::~Sound() {
			PW_AL_VOID_CALL(alDeleteSources(1, &m_audio_source_id));
		}
		void Sound::Update() {
			// If m_center_calculator has the same position as last
			// time it will return a false value that we can check for
			if (m_source_state == AL_PLAYING) {
				if (m_center_calculator != nullptr) {
					m_position = m_center_calculator();
					// We need to update the position of the sound every frame 
					PW_AL_VOID_CALL(alSourcefv(m_audio_source_id, AL_POSITION, &m_position[0]));
				}
			}
			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state));

			m_start = false;

			if (m_source_state == AL_STOPPED) {
				if (m_natural_stop == false) {
					m_natural_stop = true;
					m_end = true;
				}
				else {
					m_end = false;
				}
			}
			else {
				m_end = false;
			}
		}
		void Sound::Play(bool p_reset_play) {
			m_position = m_center_calculator();

			PW_AL_VOID_CALL(alSourcefv(m_audio_source_id, AL_POSITION, &m_position[0]));

			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state));
			if (m_source_state == AL_INITIAL) {
				m_start = true;
				m_natural_stop = false;
				PW_AL_VOID_CALL(alSourcePlay(m_audio_source_id));
			}
			else {
				if (m_source_state == AL_PAUSED) {
					m_natural_stop = false;
					PW_AL_VOID_CALL(alSourcePlay(m_audio_source_id));
				}
				else {
					if (m_source_state == AL_STOPPED) {
						// Since this is sound is looped we need to reset it so it can
						// be played again
						// Reset and Replay
						if (p_reset_play == true) {
							Reset();
							Play(false);
						}
						else {
							Reset();
						}
					}
				}
				m_start = false;
			}
		}
		void Sound::Pause() {
			m_start = false;
			m_end = false;

			PW_AL_VOID_CALL(alSourcePause(m_audio_source_id));
		}
		void Sound::Stop() {
			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state));
			if (m_source_state != AL_INITIAL && m_source_state != AL_STOPPED) {
				m_start = false;
				m_end = true;

				// "Fake" stop
				m_natural_stop = true;

				PW_AL_VOID_CALL(alSourceStop(m_audio_source_id));
			}
		}
		void Sound::Reset() {
			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state));
			if (m_source_state != AL_INITIAL) {
				m_start = false;
				if (m_source_state != AL_STOPPED) {
					m_end = true;
				}
				// "Fake" stop
				m_natural_stop = true;

				PW_AL_VOID_CALL(alSourceStop(m_audio_source_id));
				PW_AL_VOID_CALL(alSourceRewind(m_audio_source_id));
			}
		}
		void Sound::Set_Volume(const float& p_new_gain, const bool& p_windows_style) {
			if (p_windows_style == true) {
				PW_AL_VOID_CALL(alSourcef(m_audio_source_id, AL_GAIN, p_new_gain / 100.0f));
			}
			else {
				PW_AL_VOID_CALL(alSourcef(m_audio_source_id, AL_GAIN, p_new_gain));
			}
		}
		void Sound::Attach(const std::function<glm::vec2()>& p_center_calculator) {
			m_center_calculator = p_center_calculator;
		}
		const bool& Sound::Start() {
			return m_start;
		}
		const bool& Sound::End() {
			return m_end;
		}
		const int32_t& Sound::State() const {
			return m_source_state;
		}
		// End of Class Members
		// Sound_Structure  
		// Static Declarations
		// Class Members
		Sound_Structure::Sound_Structure(st::Sound* p_sound) :
				m_single_sound{ true }, m_sounds{}, m_current_access{ nullptr } {
			m_sounds.insert(std::make_pair(L"SINGLE", p_sound));
		}
		Sound_Structure::Sound_Structure(const std::vector<st::Sound*>& p_sounds, const std::vector<std::wstring>& p_sound_ids) :
				m_single_sound{ false }, m_sounds{}, m_current_access{ p_sounds.size() > 0 ? p_sounds.at(0) : nullptr } {
			if (TRY_LINE p_sounds.size() == p_sound_ids.size()) {
				for (size_t i = 0; i < p_sounds.size(); i++) {
					m_sounds.insert(std::make_pair(p_sound_ids.at(i), p_sounds.at(i)));
				}
			}
			else {
				throw pw::er::Warning_Error(L"Sound_Structure", L"Sound count does not equal id count. Every sound must have an id.", EXCEPTION_LINE, __FILEW__, L"Sound_Structure");
			}
		}
		Sound_Structure::~Sound_Structure() {
			for (auto i = m_sounds.begin(); i != m_sounds.end(); i++) {
				if (pw::Engine_Memory::Deallocate<st::Sound>(i->second) == false) {
					if (i->second != nullptr) {
						delete i->second;
						i->second = nullptr;
					}
				}
			}
		}
		st::Sound* Sound_Structure::Sound() const {
			if (m_single_sound == true) {
				return m_sounds.at(L"SINGLE");
			}
			else {
				return m_sounds.begin()->second;
			}
		}
		st::Sound* Sound_Structure::Sound(const std::wstring& p_sound_id) {
			auto v_found = m_sounds.find(p_sound_id);
			if (v_found != m_sounds.end()) {
				m_current_access = m_sounds.at(p_sound_id);
				return m_sounds.at(p_sound_id);
			}
			else {
				return nullptr;
			}
		}
		std::map<std::wstring, st::Sound*>* Sound_Structure::All_Sounds() {
			return &m_sounds;
		}
		// End of Class Members
	//////////////////////////////////
	ST_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////