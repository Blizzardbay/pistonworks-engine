#include "structures\sound.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		// Sound  
		// Static Declarations
		// Class Members
		Sound::Sound() :
				m_audio_source_id{ 0 }, m_position{}, m_center_calculator{}, m_source_state{ AL_INITIAL }, m_loop{ false },
				m_start{ true }, m_end{ false }, m_natural_stop{ false } {
		}
		Sound::Sound(const uint32_t p_source_id, const bool p_loop) :
				m_audio_source_id { p_source_id }, m_position{}, m_center_calculator{}, m_source_state{ AL_INITIAL }, m_loop{ p_loop },
				m_start{ true }, m_end{ false }, m_natural_stop{ false } {
			if (TRY_LINE alIsSource(m_audio_source_id) != AL_TRUE) {
				SET_ERROR_STATE(PW_NO_AUDIO_SOURCE_ERROR);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Sound", L"Loaded audio source not found.", ERROR_LINE, __FILEW__, L"alIsSource"));
				return;
			}
			else {
				PW_AL_VOID_CALL(alSourcefv(m_audio_source_id, AL_POSITION, &m_position[0]), true);
				PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state), false);
			}
		}
		Sound::~Sound() {
			PW_AL_VOID_CALL(alDeleteSources(1, &m_audio_source_id), false);
		}
		void Sound::Update() {
			// If m_center_calculator has the same position as last
			// time it will return a false value that we can check for
			if (m_source_state == AL_PLAYING) {
				if (m_center_calculator != nullptr) {
					m_position = m_center_calculator();
					// We need to update the position of the sound every frame 
					PW_AL_VOID_CALL(alSourcefv(m_audio_source_id, AL_POSITION, &m_position[0]), true);
				}
			}
			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state), true);

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

			PW_AL_VOID_CALL(alSourcefv(m_audio_source_id, AL_POSITION, &m_position[0]), true);

			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state), true);
			if (m_source_state == AL_INITIAL) {
				m_start = true;
				m_natural_stop = false;
				PW_AL_VOID_CALL(alSourcePlay(m_audio_source_id), true);
			}
			else {
				if (m_source_state == AL_PAUSED) {
					m_natural_stop = false;
					PW_AL_VOID_CALL(alSourcePlay(m_audio_source_id), true);
				}
				else {
					if (m_source_state == AL_STOPPED) {
						// Since this is sound is looped we need to reset it so it can
						// be played again
						// Reset and Replay
						if (p_reset_play == true) {
							PW_CALL(Reset(), true);
							PW_CALL(Play(false), false);
						}
						else {
							PW_CALL(Reset(), false);
						}
					}
				}
				m_start = false;
			}
		}
		void Sound::Pause() {
			m_start = false;
			m_end = false;

			PW_AL_VOID_CALL(alSourcePause(m_audio_source_id), true);
		}
		void Sound::Stop() {
			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state), true);
			if (m_source_state != AL_INITIAL && m_source_state != AL_STOPPED) {
				m_start = false;
				m_end = true;

				// "Fake" stop
				m_natural_stop = true;

				PW_AL_VOID_CALL(alSourceStop(m_audio_source_id), true);
			}
		}
		void Sound::Reset() {
			PW_AL_VOID_CALL(alGetSourcei(m_audio_source_id, AL_SOURCE_STATE, &m_source_state), true);
			if (m_source_state != AL_INITIAL) {
				m_start = false;
				if (m_source_state != AL_STOPPED) {
					m_end = true;
				}
				// "Fake" stop
				m_natural_stop = true;

				PW_AL_VOID_CALL(alSourceStop(m_audio_source_id), true);
				PW_AL_VOID_CALL(alSourceRewind(m_audio_source_id), true);
			}
		}
		void Sound::Set_Volume(const float p_new_gain, const bool p_windows_style) {
			if (p_windows_style == true) {
				PW_AL_VOID_CALL(alSourcef(m_audio_source_id, AL_GAIN, p_new_gain / 100.0f), false);
			}
			else {
				PW_AL_VOID_CALL(alSourcef(m_audio_source_id, AL_GAIN, p_new_gain), false);
			}
		}
		void Sound::Attach(const std::function<glm::vec2()>& p_center_calculator) {
			m_center_calculator = p_center_calculator;
		}
		const bool Sound::Start() {
			return m_start;
		}
		const bool Sound::End() {
			return m_end;
		}
		const int32_t& Sound::State() const {
			return m_source_state;
		}
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
				SET_ERROR_STATE(PW_SOUND_ID_SIZE_MISMATCH);
				SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::st::Sound_Structure", L"Sound count does not equal id count. Every sound must have an id.", ERROR_LINE, __FILEW__, L"Sound_Structure"));
				return;
			}
		}
		Sound_Structure::~Sound_Structure() {
			for (auto i = m_sounds.begin(); i != m_sounds.end(); i++) {
				if (pw::co::Memory::Deallocate<st::Sound>(i->second) == false) {
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
	ST_NAMESPACE_END
PW_NAMESPACE_END