#include "control\multi_scope_timer.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
	// Time_Controller
		template const int64_t Multi_Scope_Timer::End<std::chrono::nanoseconds, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::microseconds, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::milliseconds, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::seconds, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::minutes, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::hours, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::days, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::months, int64_t>(const std::wstring& p_identifier);
		template const int64_t Multi_Scope_Timer::End<std::chrono::years, int64_t>(const std::wstring& p_identifier);

		template const float Multi_Scope_Timer::End<std::chrono::nanoseconds, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::microseconds, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::milliseconds, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::seconds, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::minutes, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::hours, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::days, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::months, float>(const std::wstring& p_identifier);
		template const float Multi_Scope_Timer::End<std::chrono::years, float>(const std::wstring& p_identifier);

		template const double Multi_Scope_Timer::End<std::chrono::nanoseconds, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::microseconds, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::milliseconds, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::seconds, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::minutes, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::hours, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::days, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::months, double>(const std::wstring& p_identifier);
		template const double Multi_Scope_Timer::End<std::chrono::years, double>(const std::wstring& p_identifier);

		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::nanoseconds, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::microseconds, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::milliseconds, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::seconds, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::minutes, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::hours, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::days, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::months, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<int64_t> Multi_Scope_Timer::Print_End<std::chrono::years, int64_t>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);

		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::nanoseconds, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::microseconds, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::milliseconds, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::seconds, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::minutes, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::hours, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::days, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::months, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<float> Multi_Scope_Timer::Print_End<std::chrono::years, float>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);

		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::nanoseconds, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::microseconds, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::milliseconds, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::seconds, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::minutes, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::hours, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::days, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::months, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
		template const std::optional<double> Multi_Scope_Timer::Print_End<std::chrono::years, double>(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time);
	// Static Declarations
		std::map<std::wstring, std::chrono::steady_clock::time_point>* Multi_Scope_Timer::m_timer_pool{ nullptr };
	// Class Members
		Multi_Scope_Timer::Multi_Scope_Timer() {
		}
		Multi_Scope_Timer::Multi_Scope_Timer(const std::wstring& p_identifier) {
			if (m_timer_pool != nullptr) {
				m_timer_pool->insert(std::make_pair(p_identifier, std::chrono::steady_clock::now()));
			}
		}
		Multi_Scope_Timer::~Multi_Scope_Timer() {}
		void Multi_Scope_Timer::Initialize() {
			typedef std::map<std::wstring, std::chrono::steady_clock::time_point> TIMER_POOL;
			PW_CALL(m_timer_pool = pw::co::Memory::Allocate<TIMER_POOL>(), false);
		}
		void Multi_Scope_Timer::Release() {
			if (pw::co::Memory::Deallocate<std::map<std::wstring, std::chrono::steady_clock::time_point>>(m_timer_pool) == false) {
				if (m_timer_pool != nullptr) {
					delete m_timer_pool;
					m_timer_pool = nullptr;
				}
			}
		}
		template<class duration, class precision>
		const precision Multi_Scope_Timer::End(const std::wstring& p_identifier) {
			auto v_found = m_timer_pool->find(p_identifier);
			if (v_found != m_timer_pool->end()) {
				auto v_temp = std::chrono::duration_cast<
					std::chrono::duration<precision, duration::period>
				>(std::chrono::steady_clock::now() - v_found->second);

				m_timer_pool->erase(p_identifier);

				return v_temp.count();
			}
			else {
				return precision(0);
			}
		}
		template<class duration, class precision>
		const std::optional<precision> Multi_Scope_Timer::Print_End(const std::wstring& p_identifier, const pw::co::cn::Console_Msg& p_msg, bool p_return_time) {
			auto v_found = m_timer_pool->find(p_identifier);
			if (v_found != m_timer_pool->end()) {
				auto v_temp = std::chrono::duration_cast<
					std::chrono::duration<precision, duration::period>
				>(std::chrono::steady_clock::now() - v_found->second);

				m_timer_pool->erase(p_identifier);

				#ifdef PW_DEBUG_MODE
					PW_CALL(PRINT_MSG(p_msg.From(), std::wstring(p_msg.Msg()) + std::to_wstring(v_temp.count()) + pw::st::Time<duration>().Postfix(), p_msg.Type()), false);

					if (pw::er::Error_State::Get() > PW_NO_ERROR) {
						return std::optional<precision>();
					}
				#endif // PW_DEBUG_MODE

				if (p_return_time == true) {
					return v_temp.count();
				}
				else {
					return std::optional<precision>();
				}
			}
			else {
				#ifdef PW_DEBUG_MODE
					PW_CALL(PRINT_MSG(p_msg.From(), p_identifier + L" , Not Found.", p_msg.Type()), false);

					if (pw::er::Error_State::Get() > PW_NO_ERROR) {
						return std::optional<precision>();
					}
				#endif // PW_DEBUG_MODE

				if (p_return_time == true) {
					return precision(0);
				}
				else {
					return std::optional<precision>();
				}
			}
		}
	CO_NAMESPACE_END
PW_NAMESPACE_END