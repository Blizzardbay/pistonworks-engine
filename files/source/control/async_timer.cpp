#include "control\async_timer.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Async_Timer
		// Static Declarations
			std::map<std::wstring, std::pair<pw::st::Manual_Timer<std::chrono::milliseconds>*, pw::st::Event_Base*>>* Async_Timer::m_timers{ nullptr };
		// Class Members
			void Async_Timer::Initialize() {
				m_timers = pw::co::Memory::Allocate<std::map<std::wstring, std::pair<pw::st::Manual_Timer<std::chrono::milliseconds>*, pw::st::Event_Base*>>>();
			}
			void Async_Timer::Release() {
				for (auto i = m_timers->begin(); i != m_timers->end(); i++) {
					if (pw::co::Memory::Deallocate<pw::st::Manual_Timer<std::chrono::milliseconds>>(i->second.first) == false) {
						if (i->second.first != nullptr) {
							delete i->second.first;
							i->second.first = nullptr;
						}
					}
					if (pw::co::Memory::Deallocate<pw::st::Event_Base>(i->second.second) == false) {
						if (i->second.second != nullptr) {
							delete i->second.second;
							i->second.second = nullptr;
						}
					}
				}
				if (pw::co::Memory::Deallocate<std::map<std::wstring, std::pair<pw::st::Manual_Timer<std::chrono::milliseconds>*, pw::st::Event_Base*>>>(m_timers) == false) {
					if (m_timers != nullptr) {
						delete m_timers;
						m_timers = nullptr;
					}
				}
			}
			void Async_Timer::Poll() {
				for (auto i = m_timers->begin(); i != m_timers->end(); i++) {
					// Guaranteed not to be nullptr
					if (i->second.first->Use() == true) {
						i->second.second->Trigger_Event();
					}
				}
			}
			void Async_Timer::Add(const std::wstring& p_timer_id, pw::st::Manual_Timer<std::chrono::milliseconds>* p_timer, pw::st::Event_Base* p_callback) {
				if (p_timer_id.empty() == true) {
					return;
				}
				if (p_timer == nullptr) {
					return;
				}
				if (p_callback == nullptr) {
					return;
				}
				auto v_found_id = m_timers->find(p_timer_id);

				if (v_found_id == m_timers->end()) {
					m_timers->insert(std::make_pair(p_timer_id, std::make_pair(p_timer, p_callback)));
				}
			}
			void Async_Timer::Remove(const std::wstring& p_timer_id) {
				if (p_timer_id.empty() == true) {
					return;
				}
				auto v_found_id = m_timers->find(p_timer_id);

				if (v_found_id != m_timers->end()) {
					m_timers->erase(v_found_id);
				}
			}
	CO_NAMESPACE_END
PW_NAMESPACE_END