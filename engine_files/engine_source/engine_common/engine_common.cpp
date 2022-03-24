#include "engine_common\engine_constant.h"
#include "engine_common\engine_error.h"
#include "engine_common\engine_error_log.h"
#include "engine_common\engine_exception.h"
#include "engine_common\engine_memory.h"

// Engine Constant
int32_t pw::cm::Engine_Constant::m_window_width{ 0 };
int32_t pw::cm::Engine_Constant::m_window_height{ 0 };
int32_t pw::cm::Engine_Constant::m_hafe_window_width{ 0 };
int32_t pw::cm::Engine_Constant::m_hafe_window_height{ 0 };
std::wstring pw::cm::Engine_Constant::m_window_name{ L"" };
std::unique_ptr<GLFWwindow, pw::cm::Destroy_GLFW>* pw::cm::Engine_Constant::m_current_window{ nullptr };

int32_t pw::cm::Engine_Constant::m_frames{ 0 };
int32_t pw::cm::Engine_Constant::m_last_frames{ -1 };
int32_t pw::cm::Engine_Constant::m_fps_max{ 0 };
std::vector<int32_t> pw::cm::Engine_Constant::m_fps_averager;
float pw::cm::Engine_Constant::m_fps_average{ 0.0f };
int32_t pw::cm::Engine_Constant::m_fps_cap{ -1 };
bool pw::cm::Engine_Constant::m_vsync{ false };
int32_t pw::cm::Engine_Constant::m_refresh_rate{ 0 };

std::chrono::system_clock::time_point pw::cm::Engine_Constant::m_start_time{};
std::chrono::system_clock::time_point pw::cm::Engine_Constant::m_end_time{};
std::chrono::system_clock::duration pw::cm::Engine_Constant::m_delta_time{};
std::chrono::system_clock::duration pw::cm::Engine_Constant::m_elapsed_time{};

int32_t pw::cm::Engine_Constant::m_mouse_x_position{ 0 };
int32_t pw::cm::Engine_Constant::m_mouse_y_position{ 0 };
int32_t pw::cm::Engine_Constant::m_last_mouse_x_position{ 0 };
int32_t pw::cm::Engine_Constant::m_last_mouse_y_position{ 0 };
double pw::cm::Engine_Constant::m_mouse_x_position_raw{ 0 };
double pw::cm::Engine_Constant::m_mouse_y_position_raw{ 0 };

std::filesystem::path pw::cm::Engine_Constant::m_pistonworks_path{
	[]() ->std::filesystem::path {
		std::filesystem::path v_pistonworks_path{ std::filesystem::current_path() };

		if (v_pistonworks_path.generic_string().find("Pistonworks Engine") == std::string::npos) {
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
			return v_pistonworks_path;
		}
		
	}()
};
std::filesystem::path pw::cm::Engine_Constant::m_game_path{
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

bool pw::cm::Engine_Constant::m_window_lock{ true };
const float pw::cm::Engine_Constant::m_inverse_z_tan{ -(1.0f / tan(glm::radians(45.0f / 2.0f))) };

#ifdef PW_DEBUG_MODE
pw::PW_FUNCTION pw::cm::Engine_Constant::m_debug_info{};
#endif
// Engine Error
int32_t pw::er::Engine_Error::PW_LINE_ = 0;
std::wstring pw::er::Engine_Error::PW_FILE_{};
// Error Log
// Static Declarations
std::string pw::er::Error_Log::m_console_log_name{
	#ifdef PW_DEBUG_MODE
		[](const std::filesystem::path& p_pistonworks_path) ->std::string {
		size_t v_count = 1;
		for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_pistonworks_path.generic_wstring() + L"/engine_files/engine_resource/engine_log")) {
			v_file_finder;
			v_count = v_count + 1;
		}

		std::string v_temp = std::string(__TIME__ + std::string("_console_log_") + std::to_string(v_count) + std::string(".txt"));

		size_t v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');
		v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');

		return v_temp;
	}(pw::cm::Engine_Constant::Pistonworks_Path())
	#else
		std::string()
	#endif // PW_DEBUG_MODE
};
std::string pw::er::Error_Log::m_error_log_name{
	#ifdef PW_DEBUG_MODE
		[](const std::filesystem::path& p_pistonworks_path) ->std::string {
		size_t v_count = 1;
		for (const auto& v_file_finder : std::filesystem::recursive_directory_iterator(p_pistonworks_path.generic_wstring() + L"/engine_files/engine_resource/engine_log")) {
			v_file_finder;
			v_count = v_count + 1;
		}

		std::string v_temp = std::string(__TIME__ + std::string("_error_log_") + std::to_string(v_count) + std::string(".txt"));

		size_t v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');
		v_colon = v_temp.find(L':', 0);
		v_temp.erase(v_colon, 1);
		v_temp.insert(v_colon, 1, L'_');

		return v_temp;
	}(pw::cm::Engine_Constant::Pistonworks_Path())
	#else
		std::string()
	#endif // PW_DEBUG_MODE
};
// Engine Exception
uint64_t pw::er::Engine_Exception::m_exception_line{ 0 };
// Engine Memory
uint64_t pw::Engine_Memory::m_heap_memory{ 0 };
uint64_t pw::Engine_Memory::m_high_heap_memory{ 0 };
uint64_t pw::Engine_Memory::m_allocations{ 0 };
std::set<pw::Engine_Memory::Memory>* pw::Engine_Memory::m_memory_pointers{};