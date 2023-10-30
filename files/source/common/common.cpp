#include "common\constant.h"
#include "common\error.h"
#include "common\error_log.h"
#include "common\error_state.h"
#include "control\memory.h"

// Engine Constant
uint32_t pw::cm::Constant::m_window_width{ 0 };
uint32_t pw::cm::Constant::m_window_height{ 0 };
uint32_t pw::cm::Constant::m_hafe_window_width{ 0 };
uint32_t pw::cm::Constant::m_hafe_window_height{ 0 };
std::wstring pw::cm::Constant::m_window_name{ L"" };
std::unique_ptr<GLFWwindow, pw::cm::Destroy_GLFW>* pw::cm::Constant::m_current_window{ nullptr };

int32_t pw::cm::Constant::m_frames{ 0 };
int32_t pw::cm::Constant::m_last_frames{ -1 };
int32_t pw::cm::Constant::m_fps_max{ 0 };
std::vector<int32_t> pw::cm::Constant::m_fps_averager;
int32_t pw::cm::Constant::m_fps_average{ 0 };
int32_t pw::cm::Constant::m_fps_cap{ -1 };
bool pw::cm::Constant::m_vsync{ false };
int32_t pw::cm::Constant::m_refresh_rate{ 0 };

std::chrono::steady_clock::time_point pw::cm::Constant::m_start_time{};
std::chrono::steady_clock::time_point pw::cm::Constant::m_end_time{};
std::chrono::steady_clock::duration pw::cm::Constant::m_delta_time{};
std::chrono::steady_clock::duration pw::cm::Constant::m_elapsed_time{};

int32_t pw::cm::Constant::m_mouse_x_position{ 0 };
int32_t pw::cm::Constant::m_mouse_y_position{ 0 };
int32_t pw::cm::Constant::m_last_mouse_x_position{ 0 };
int32_t pw::cm::Constant::m_last_mouse_y_position{ 0 };
double pw::cm::Constant::m_mouse_x_position_raw{ 0 };
double pw::cm::Constant::m_mouse_y_position_raw{ 0 };

std::filesystem::path pw::cm::Constant::m_pistonworks_path{
	[]() ->std::filesystem::path {
		std::filesystem::path v_pistonworks_path{ std::filesystem::current_path() };

		size_t v_pistonworks_position = v_pistonworks_path.generic_string().find("Pistonworks Engine");

		if (v_pistonworks_position == std::string::npos) {
			for (const auto& v_directory_finder : std::filesystem::recursive_directory_iterator(v_pistonworks_path)) {
				if (v_directory_finder.is_directory() == true) {
					if (v_directory_finder.path().generic_string().find("Pistonworks Engine") != std::string::npos) {
						v_pistonworks_path = v_directory_finder;
						break;
					}
				}
			}

			if (v_pistonworks_path != std::filesystem::current_path()) {
				return v_pistonworks_path;
			}
			else {
				return std::filesystem::path();
			}
		}
		else {
			return v_pistonworks_path.generic_wstring().substr(0, v_pistonworks_position + 19);
		}
	}()
};
std::filesystem::path pw::cm::Constant::m_game_path{
   []() ->std::filesystem::path {
		std::filesystem::path v_game_path{ std::filesystem::current_path() };

		if (v_game_path.generic_string().find("game") == std::string::npos) {
			for (const auto& v_directory_finder : std::filesystem::recursive_directory_iterator(v_game_path)) {
				if (v_directory_finder.is_directory() == true) {
					if (v_directory_finder.path().generic_string().find("game") != std::string::npos) {
						v_game_path = v_directory_finder;
						break;
					}
				}
			}
			if (v_game_path != std::filesystem::current_path()) {
				return v_game_path;
			}
			else {
				return std::filesystem::path();
			}
		}
		else {
			return v_game_path;
		}
	}()
};

bool pw::cm::Constant::m_window_lock{ true };
const float pw::cm::Constant::m_inverse_z_tan{ -(1.0f / tan(glm::radians(45.0f / 2.0f))) };
std::chrono::steady_clock::duration pw::cm::Constant::m_expected_frame_time{ 0 };

#ifdef PW_DEBUG_MODE
pw::PW_FUNCTION pw::cm::Constant::m_debug_info{};
#endif
// Engine Error
uint64_t pw::er::Error::m_line{ 0 };
std::wstring pw::er::Error::m_file{};
// Error Log
std::string pw::er::Error_Log::m_console_log_name{
	#ifdef PW_DEBUG_MODE
		[](const std::filesystem::path& p_pistonworks_path) ->std::string {
		size_t v_count = 1;
		for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_pistonworks_path.generic_wstring() + L"/files/resource/log")) {
			if (v_file_finder.exists()) {
				v_count = v_count + 1;
			}
		}

		std::string v_temp = std::string(__TIME__ + std::string("_console_log_") + std::to_string(v_count) + std::string(".txt"));

		size_t v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');
		v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');

		return v_temp;
	}(pw::cm::Constant::Pistonworks_Path())
	#else
		std::string()
	#endif // PW_DEBUG_MODE
};
std::string pw::er::Error_Log::m_error_log_name{
	#ifdef PW_DEBUG_MODE
		[](const std::filesystem::path& p_pistonworks_path) ->std::string {
		size_t v_count = 1;
		for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_pistonworks_path.generic_wstring() + L"/files/resource/log")) {
			if (v_file_finder.exists()) {
				v_count = v_count + 1;
			}
		}

		std::string v_temp = std::string(__TIME__ + std::string("_error_log_") + std::to_string(v_count) + std::string(".txt"));

		size_t v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');
		v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');

		return v_temp;
	}(pw::cm::Constant::Pistonworks_Path())
	#else
		std::string()
	#endif // PW_DEBUG_MODE
};
std::function<std::wstring()> pw::er::Error_Log::m_error_state_value_callback{};
// Engine Error State
uint64_t pw::er::Error_State::m_error_line{ 0 };
uint32_t pw::er::Error_State::m_error_state{ 0 };
bool pw::er::Error_State::m_warning_error{ false };
bool pw::er::Error_State::m_severe_error{ false };
pw::er::Warning_Error pw::er::Error_State::m_werror_info{};
pw::er::Severe_Error pw::er::Error_State::m_serror_info{};
std::function<void(const pw::er::Warning_Error&)> pw::er::Error_State::m_warning_handler{};
std::function<void(const pw::er::Severe_Error&)> pw::er::Error_State::m_severe_handler{};