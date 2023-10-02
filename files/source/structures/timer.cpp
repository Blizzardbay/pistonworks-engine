#include "structures\timer.h"

PW_NAMESPACE_SRT
	ST_NAMESPACE_SRT
		// Time_Constant
		// Static Declarations
			std::map<std::string, std::wstring>* Time_Constant::m_time_total{ nullptr };
			std::map<std::string, std::wstring>* Time_Constant::m_time_postfix{ nullptr };
		// Class Members
			void Time_Constant::Initialize() {
				// Template arguments do not work inside proper macros *PW_CALL*
				typedef std::map<std::string, std::wstring> TIME_TOTAL;
				PW_CALL(m_time_total = pw::co::Memory::Allocate<TIME_TOTAL>({
					std::make_pair(typeid(std::chrono::nanoseconds).name(), L"nanoseconds"),
					std::make_pair(typeid(std::chrono::microseconds).name(), L"microseconds"),
					std::make_pair(typeid(std::chrono::milliseconds).name(), L"milliseconds"),
					std::make_pair(typeid(std::chrono::seconds).name(), L"seconds"),
					std::make_pair(typeid(std::chrono::minutes).name(), L"minutes"),
					std::make_pair(typeid(std::chrono::hours).name(), L"hours"),
					std::make_pair(typeid(std::chrono::days).name(), L"days"),
					std::make_pair(typeid(std::chrono::months).name(), L"months"),
					std::make_pair(typeid(std::chrono::years).name(), L"years")
				}), true);
				typedef std::map<std::string, std::wstring> TIME_POSTFIX;
				PW_CALL(m_time_postfix = pw::co::Memory::Allocate<TIME_POSTFIX>({
					std::make_pair(typeid(std::chrono::nanoseconds).name(), L"ns"),
					std::make_pair(typeid(std::chrono::microseconds).name(), L"us"),
					std::make_pair(typeid(std::chrono::milliseconds).name(), L"ms"),
					std::make_pair(typeid(std::chrono::seconds).name(), L"s"),
					std::make_pair(typeid(std::chrono::minutes).name(), L"min"),
					std::make_pair(typeid(std::chrono::hours).name(), L"hrs"),
					std::make_pair(typeid(std::chrono::days).name(), L"dys"),
					std::make_pair(typeid(std::chrono::months).name(), L"mhs"),
					std::make_pair(typeid(std::chrono::years).name(), L"yrs")
				}), false);

				if (m_time_postfix == nullptr) {
					if (pw::co::Memory::Deallocate<std::map<std::string, std::wstring>>(m_time_total) == false) {
						if (m_time_total != nullptr) {
							delete m_time_total;
							m_time_total = nullptr;
						}
					}
				}
			}
			void Time_Constant::Release() {
				if (pw::co::Memory::Deallocate<std::map<std::string, std::wstring>>(m_time_total) == false) {
					if (m_time_total != nullptr) {
						delete m_time_total;
						m_time_total = nullptr;
					}
				}
				if (pw::co::Memory::Deallocate<std::map<std::string, std::wstring>>(m_time_postfix) == false) {
					if (m_time_postfix != nullptr) {
						delete m_time_postfix;
						m_time_postfix = nullptr;
					}
				}
			}
		// Time
			template class Time<std::chrono::nanoseconds>;
			template class Time<std::chrono::microseconds>;
			template class Time<std::chrono::milliseconds>;
			template class Time<std::chrono::seconds>;
			template class Time<std::chrono::minutes>;
			template class Time<std::chrono::hours>;
			template class Time<std::chrono::days>;
			template class Time<std::chrono::months>;
			template class Time<std::chrono::years>;
		// Static Declarations
		// Class Members
			template<class duration>
			std::wstring Time<duration>::Total() {
				auto v_found = this->m_time_total->find(typeid(duration).name());
				if (v_found != this->m_time_total->end()) {
					return v_found->second;
				}
				else {
					return std::wstring();
				}
			}
			template<class duration>
			std::wstring Time<duration>::Postfix() {
				auto v_found = this->m_time_postfix->find(typeid(duration).name());
				if (v_found != this->m_time_postfix->end()) {
					return v_found->second;
				}
				else {
					return std::wstring();
				}
			}
		// Manual_Timer
			template class Manual_Timer<std::chrono::nanoseconds>;
			template class Manual_Timer<std::chrono::microseconds>;
			template class Manual_Timer<std::chrono::milliseconds>;
			template class Manual_Timer<std::chrono::seconds>;
			template class Manual_Timer<std::chrono::minutes>;
			template class Manual_Timer<std::chrono::hours>;
			template class Manual_Timer<std::chrono::days>;
			template class Manual_Timer<std::chrono::months>;
			template class Manual_Timer<std::chrono::years>;
		// Static Declarations
		// Class Members
			template<class duration>
			_NODISCARD Manual_Timer<duration>::Manual_Timer(const uint64_t& p_timer_length, const bool& p_start_ready, const bool& p_reset) noexcept :
					Time<duration>{}, m_activation_time{},
					m_timer_length{ p_timer_length }, m_start_ready{ p_start_ready }, m_should_reset{ p_reset }, m_reseted{ false } {
			}
			template<class duration>
			_NODISCARD bool Manual_Timer<duration>::Use() noexcept {
				if (m_start_ready == true) {
					m_start_ready = false;
					return true;
				}
				if (m_activation_time >= cm::Constant::Current_Time() && m_reseted == true) {
					return false;
				}
				if (m_should_reset == false) {
					m_reseted = false;
					return true;
				}
				m_reseted = true;
				m_activation_time = cm::Constant::Current_Time() + duration(m_timer_length);
				return true;
			}
			template<class duration>
			void Manual_Timer<duration>::Reset() noexcept {
				m_reseted = true;
				m_activation_time = cm::Constant::Current_Time() + duration(m_timer_length);
			}
			template<class duration>
			_NODISCARD const float Manual_Timer<duration>::Time_Left() const noexcept {
				std::chrono::steady_clock::duration v_activation_time = m_activation_time.time_since_epoch();
				if (m_activation_time.time_since_epoch() != duration(0)) {
					return glm::clamp(TO_FLOAT(cm::Constant::Current_Time().time_since_epoch() / m_activation_time.time_since_epoch()), 0.0f, 1.0f);
				}
				else {
					return 0.0f;
				}
			}
			template<class duration>
			template<class precision>
			_NODISCARD const precision& Manual_Timer<duration>::Timer_Length() noexcept {
				auto v_temp = std::chrono::duration_cast<
					std::chrono::duration<precision, duration::period>
				>(m_timer_length);
				return v_temp.count();
			}
			template<class duration>
			_NODISCARD const bool& Manual_Timer<duration>::Start_Ready() noexcept {
				return m_start_ready;
			}
			template<class duration>
			_NODISCARD const bool& Manual_Timer<duration>::Should_Reset() noexcept {
				return m_should_reset;
			}
			template<class duration>
			_NODISCARD const bool& Manual_Timer<duration>::Reseted() noexcept {
				return m_reseted;
			}
			template<class duration>
			_NODISCARD const std::chrono::steady_clock::time_point& Manual_Timer<duration>::Activation_Time() noexcept {
				return m_activation_time;
			}
		// Scope_Timer
			template class Scope_Timer<std::chrono::nanoseconds, int64_t>;
			template class Scope_Timer<std::chrono::microseconds, int64_t>;
			template class Scope_Timer<std::chrono::milliseconds, int64_t>;
			template class Scope_Timer<std::chrono::seconds, int64_t>;
			template class Scope_Timer<std::chrono::minutes, int64_t>;
			template class Scope_Timer<std::chrono::hours, int64_t>;
			template class Scope_Timer<std::chrono::days, int64_t>;
			template class Scope_Timer<std::chrono::months, int64_t>;
			template class Scope_Timer<std::chrono::years, int64_t>;

			template class Scope_Timer<std::chrono::nanoseconds, float>;
			template class Scope_Timer<std::chrono::microseconds, float>;
			template class Scope_Timer<std::chrono::milliseconds, float>;
			template class Scope_Timer<std::chrono::seconds, float>;
			template class Scope_Timer<std::chrono::minutes, float>;
			template class Scope_Timer<std::chrono::hours, float>;
			template class Scope_Timer<std::chrono::days, float>;
			template class Scope_Timer<std::chrono::months, float>;
			template class Scope_Timer<std::chrono::years, float>;

			template class Scope_Timer<std::chrono::nanoseconds, double>;
			template class Scope_Timer<std::chrono::microseconds, double>;
			template class Scope_Timer<std::chrono::milliseconds, double>;
			template class Scope_Timer<std::chrono::seconds, double>;
			template class Scope_Timer<std::chrono::minutes, double>;
			template class Scope_Timer<std::chrono::hours, double>;
			template class Scope_Timer<std::chrono::days, double>;
			template class Scope_Timer<std::chrono::months, double>;
			template class Scope_Timer<std::chrono::years, double>;
		// Static Declarations
		// Class Members
			template<class duration, class precision>
			Scope_Timer<duration, precision>::Scope_Timer(const pw::co::cn::Msg_Types& p_msg_type) noexcept :
					Time<duration>{}, m_msg_type{ p_msg_type }, m_start_time{ std::chrono::steady_clock::now() } {
			}
			template<class duration, class precision>
			Scope_Timer<duration, precision>::~Scope_Timer() noexcept {
				#ifdef PW_DEBUG_MODE
					auto v_temp = std::chrono::duration_cast<
						std::chrono::duration<precision, duration::period>
					>(std::chrono::steady_clock::now() - m_start_time);
					PW_CALL(PRINT_MSG(L"", std::to_wstring(v_temp.count()) + this->Postfix(), m_msg_type), false);
				#endif // PW_DEBUG_MODE
			}
	ST_NAMESPACE_END
PW_NAMESPACE_END