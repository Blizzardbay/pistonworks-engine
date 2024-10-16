#include "control\queue.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Engine_Queue
		// Static Declarations
		std::wstring co::Engine_Queue::m_project_name{};

		std::wstring co::Engine_Queue::m_current_scene{};
		std::map<std::wstring, st::Game_Scene*>* co::Engine_Queue::m_scene_directory{ nullptr };

		std::function<void(const std::wstring&)> co::Engine_Queue::m_pre_scene_add{ nullptr };
		std::function<void(const std::wstring&)> co::Engine_Queue::m_post_scene_add{ nullptr };

		std::function<void(const std::wstring&)> co::Engine_Queue::m_pre_scene_change{ nullptr };
		std::function<void(const std::wstring&)> co::Engine_Queue::m_post_scene_change{ nullptr };

		std::function<void(const std::wstring&)> co::Engine_Queue::m_pre_scene_remove{ nullptr };
		std::function<void(const std::wstring&)> co::Engine_Queue::m_post_scene_remove{ nullptr };
		std::function<void()> co::Engine_Queue::m_user_debug_function{ nullptr };
		// Class Members
			void Engine_Queue::Pre_Queue() {
				if (m_current_scene.empty() != true) {
					PW_CALL(m_scene_directory->at(m_current_scene)->Pre_Render(), false);
				}
			}
			void Engine_Queue::Run_Queue() {
				if (m_current_scene.empty() != true) {
					PW_CALL(m_scene_directory->at(m_current_scene)->Render(), false);
				}
			}
			void Engine_Queue::Initialize() {
				typedef std::map<std::wstring, st::Game_Scene*> SCENE_DIRECTORY;

				PW_CALL(m_scene_directory = pw::co::Memory::Allocate<SCENE_DIRECTORY>(), false);
			}
			void Engine_Queue::Release() {
				auto i = m_scene_directory->begin();
				while (i != m_scene_directory->end()) {
					PW_CALL(Remove_Scene(i->first), true);
					i = m_scene_directory->begin();
				}
				if (pw::co::Memory::Deallocate<std::map<std::wstring, st::Game_Scene*>>(m_scene_directory) == false) {
					if (m_scene_directory != nullptr) {
						delete m_scene_directory;
						m_scene_directory = nullptr;
					}
				}

				m_current_scene.~basic_string();

				m_project_name.~basic_string();
			}
			void Engine_Queue::Print_Debug_Stats() {
				PRINT_INFO(L"HM    ", pw::co::Memory::Memory_String(pw::co::Memory::Heap_Memory()), TO_UINT16(0));
				PRINT_INFO(L"HHM   ", pw::co::Memory::Memory_String(pw::co::Memory::High_Heap_Memory()), TO_UINT16(1));
				PRINT_INFO(L"MEMCNT", std::to_wstring(pw::co::Memory::Allocations()), TO_UINT16(2));
				PRINT_INFO(L"FPS   ", std::to_wstring(pw::cm::Constant::FPS()), TO_UINT16(3));
				PRINT_INFO(L"FPSLST", std::to_wstring(pw::cm::Constant::Last_FPS()), TO_UINT16(4));
				PRINT_INFO(L"FPSMAX", std::to_wstring(pw::cm::Constant::FPS_Max()), TO_UINT16(5));

				std::wstring v_fps_average{ std::to_wstring(pw::cm::Constant::FPS_Average()) };

				uint64_t v_period{ v_fps_average.find(L".") };
				if (v_period != std::string::npos) {
					uint64_t v_decimal_count{ v_fps_average.size() - OFF_UINT64(v_period) };
					if (v_decimal_count > 2) {
						v_decimal_count = SUB_UINT64(v_decimal_count, 2);
						v_fps_average.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);
					}
				}

				PRINT_INFO(L"FPSAVG", v_fps_average, TO_UINT16(6));
				PRINT_INFO(L"MODELS", std::to_wstring(st::Model::m_model_counter), TO_UINT16(7));
				uint64_t v_render_count{ 0 };
				if (m_current_scene.empty() != true) {
					v_render_count = m_scene_directory->at(m_current_scene)->Last_Render_Count();
				}
				PRINT_INFO(L"RNDCNT", std::to_wstring(v_render_count), TO_UINT16(8));

				std::wstring v_camera_position_x{ std::to_wstring(st::Camera::Camera_Position().x) };

				v_period = v_camera_position_x.find(L".");
				if (v_period != std::string::npos) {
					size_t v_decimal_count{ v_camera_position_x.size() - OFF_UINT64(v_period) };
					if (v_decimal_count > 2) {
						v_decimal_count = SUB_UINT64(v_decimal_count, 2);
						v_camera_position_x.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);
					}
				}

				PRINT_INFO(L"CAMXPS", v_camera_position_x, TO_UINT16(9));

				std::wstring v_camera_position_y = std::to_wstring(st::Camera::Camera_Position().y);

				v_period = v_camera_position_y.find(L".");
				if (v_period != std::string::npos) {
					size_t v_decimal_count{ v_camera_position_y.size() - OFF_UINT64(v_period) };
					if (v_decimal_count > 2) {
						v_decimal_count = SUB_UINT64(v_decimal_count, 2);
						v_camera_position_y.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);
					}
				}

				PRINT_INFO(L"CAMYPS", v_camera_position_y, TO_UINT16(10));

				if (m_user_debug_function != nullptr) {
					PW_CALL(m_user_debug_function(), true);
				}
			}
			void Engine_Queue::Load_From_Dir(std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>& p_main_window, std::shared_ptr<PW_FUNCTION> p_state_function) {
				co::File_Loader::Initialize_Loader(&Engine_Queue::Add_Scene, &Engine_Queue::Set_Current_Scene, &Engine_Queue::Remove_Scene, &Engine_Queue::Set_Sub_Scene_Render);

				// Find if the directory exist
				std::filesystem::path v_game_path = pw::cm::Constant::Game_Path();
				if (TRY_LINE v_game_path.empty() == true) {
					SET_ERROR_STATE(PW_GAME_PATH_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"game path\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::path.empty()"));
					return;
				}
				std::wstring v_wstr_directory = v_game_path.generic_wstring();

				std::filesystem::path v_path_to_animations{ v_wstr_directory + std::wstring(L"/animations") };
				std::filesystem::path v_path_to_data{ v_wstr_directory + std::wstring(L"/data") };
				std::filesystem::path v_path_to_fonts{ v_wstr_directory + std::wstring(L"/fonts") };
				std::filesystem::path v_path_to_icon{ v_wstr_directory + std::wstring(L"/icon") };
				std::filesystem::path v_path_to_linker_files{ v_wstr_directory + std::wstring(L"/linker_files") };
				std::filesystem::path v_path_to_textures{ v_wstr_directory + std::wstring(L"/textures") };
				std::filesystem::path v_path_to_sounds{ v_wstr_directory + std::wstring(L"/sounds") };

				if (TRY_LINE std::filesystem::exists(v_path_to_animations) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"animations\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				if (TRY_LINE std::filesystem::exists(v_path_to_data) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"data\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				if (TRY_LINE std::filesystem::exists(v_path_to_fonts) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"fonts\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				if (TRY_LINE std::filesystem::exists(v_path_to_icon) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"icon\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				if (TRY_LINE std::filesystem::exists(v_path_to_linker_files) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"linker_files\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				if (TRY_LINE std::filesystem::exists(v_path_to_textures) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"textures\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				if (TRY_LINE std::filesystem::exists(v_path_to_sounds) == false) {
					SET_ERROR_STATE(PW_DIRECTORY_NOT_FOUND);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"Pistonworks Engine", L"Could not find \"sounds\" directory", ERROR_LINE, __FILEW__, L"std::filesystem::exists"));
					return;
				}
				// First make sure the file location exists
				PW_CALL(std::filesystem::path v_project_location = co::File_Finder::Find_File(v_path_to_linker_files.generic_string(), "PWProject", ".csv"), true);

				// Load the .pwproject file
				PW_PROJECT_FILE v_project = std::async(std::launch::async, [](
					const std::filesystem::path& p_project_location, const std::wstring& p_path_to_animations, const std::wstring& p_path_to_data,
					const std::wstring& p_path_to_fonts, const std::wstring& p_path_to_icon, const std::wstring& p_path_to_linker_files,
					const std::wstring& p_path_to_textures, const std::wstring& p_path_to_sounds) -> PW_PROJECT_FILE {
						return co::File_Loader::Load_Project_File(p_project_location,
							p_path_to_animations, p_path_to_data, p_path_to_fonts,
							p_path_to_icon, p_path_to_linker_files, p_path_to_textures, p_path_to_sounds);
					}, v_project_location, v_path_to_animations.generic_wstring(),
						v_path_to_data.generic_wstring(), v_path_to_fonts.generic_wstring(),
						v_path_to_icon.generic_wstring(), v_path_to_linker_files.generic_wstring(),
						v_path_to_textures.generic_wstring(), v_path_to_sounds.generic_wstring()).get();

				// Create loading animation
				std::tuple<st::Texture*, st::Animation*> v_animation{};
				PW_CALL(v_animation = co::File_Loader::Load_Animation_File(L"Loading_Bar.gif", false, true, false, true), true);
				PW_CALL(st::Model * v_model = pw::co::Memory::Allocate_Args<st::Model>(st::Geometry_Types::SQUARE, v_animation._Myfirst._Val, glm::vec2(-TO_FLOAT(cm::Constant::Hafe_Window_Width()), cm::Constant::Hafe_Window_Height()), 0.0f, glm::vec2(cm::Constant::Window_Width(), cm::Constant::Window_Height())), true);
				PW_CALL(v_animation._Get_rest()._Myfirst._Val->Finish_Init(v_model->Mesh()->Vertices(), v_model->Mesh()->Vertex_Count()), true);
				st::Actor v_loading_bar = st::Actor(v_model, v_animation._Get_rest()._Myfirst._Val);

				PW_CALL(v_animation = co::File_Loader::Load_Animation_File(L"Loading_PW_Logo.gif", false, true, false, true), true);
				PW_CALL(v_model = pw::co::Memory::Allocate_Args<st::Model>(st::Geometry_Types::SQUARE, v_animation._Myfirst._Val, glm::vec2(TO_FLOAT(cm::Constant::Hafe_Window_Width()) - 163.0f, -TO_FLOAT(cm::Constant::Hafe_Window_Height()) + 163.0f), 0.0f, glm::vec2(163.0f, 163.0f)), true);
				PW_CALL(v_animation._Get_rest()._Myfirst._Val->Finish_Init(v_model->Mesh()->Vertices(), v_model->Mesh()->Vertex_Count()), true);
				st::Actor v_loading_icon = st::Actor(v_model, v_animation._Get_rest()._Myfirst._Val, 1);
				v_model = nullptr;

				v_loading_bar.Stop_Animation();
				PW_CALL(v_loading_bar.Advance_Animation(), true);
				while (true) {
					PW_CALL(pw::co::Shader::Use(), true);
					// Calculate needed time constants
					PW_CALL(cm::Constant::Calc_Elapsed_Time(&*p_main_window), true);

					// Engine Input
					PW_GLFW_VOID_CALL(glfwPollEvents(), true);
					// Engine Frame / Shader
					PW_GL_VOID_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f), true, false);
					PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), true, false);
					// Update the projection information for the vertex shader / fragment shader
					PW_CALL(pw::co::Shader::Update_Projection(), true);

					// Send Draws
					PW_CALL(v_loading_bar.Render(), true);
					PW_CALL(v_loading_icon.Render(), true);

					// Render
					PW_CALL(pw::st::Model::Draw(), true);
					PW_CALL(pw::st::Model::Draw_Transparent(), true);

					// Swap Open GL Buffers
					PW_CALL((*p_state_function)(), true);
					// Wait until the next frame should run
					cm::Constant::Wait();

					if (v_project._Myfirst._Val == true) {
						PW_AFTER_CALL(L"Load_Project_File", true);
						break;
					}
				}
				PW_GLFW_VOID_CALL(glfwSetWindowTitle(&*p_main_window, TO_STRING(std::get<1>(v_project)).c_str()), true);
				PW_GLFW_VOID_CALL(glfwSetWindowSize(&*p_main_window, TO_INT32(cm::Constant::Window_Width()), TO_INT32(cm::Constant::Window_Height())), true);

				// Load font
				PW_CALL(std::filesystem::path v_file_location = co::File_Finder::Find_File(v_path_to_linker_files.generic_wstring(), TO_WSTRING(std::get<3>(v_project)), L".csv"), true);

				std::vector<std::wstring> v_font_ids{};
				std::vector<std::wstring> v_font_names{};

				std::string v_font_id{};
				std::string v_font_name{};


				io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					v_font_reader{ v_file_location.generic_string().c_str() };
				v_font_reader.read_header(io::ignore_extra_column,
					"Font_Id", "Font_Name");
				while (v_font_reader.read_row(v_font_id, v_font_name)) {
					PW_CALL(v_font_ids.push_back(TO_WSTRING(v_font_id)), true);
					PW_CALL(v_font_names.push_back(TO_WSTRING(v_font_name)), true);
				}

				PW_CALL(Text_Renderer::Load_Engine_Fonts(v_path_to_fonts.generic_wstring(), v_font_ids, v_font_names), true);

				// Load Icon
				PW_CALL(GLFWimage* v_icon = pw::co::File_Loader::Load_Icon(TO_WSTRING(std::get<4>(v_project)), false), true);

				PW_GLFW_VOID_CALL(glfwSetWindowIcon(&*p_main_window, 1, v_icon), true);

				pw::co::File_Loader::Unload_Icon();

				if (pw::co::Memory::Deallocate<GLFWimage>(v_icon) == false) {
					if (v_icon != nullptr) {
						delete v_icon;
						v_icon = nullptr;
					}
				}
				// Lock Window

				pw::cm::Constant::Set_Window_Lock((bool)std::get<5>(v_project));

				float v_loaded = 0;
				std::wstring v_first_scene{};
				float v_quarter = 0.25f;

				for (auto i = std::get<2>(v_project).begin(); i != std::get<2>(v_project).end(); i++) {
					if (std::get<1>(*i) == true) {
						v_first_scene = std::get<0>(*i);
					}
					{
						PW_CALL(pw::co::Shader::Use(), true);
						// Calculate needed time constants
						PW_CALL(cm::Constant::Calc_Elapsed_Time(&*p_main_window), true);

						// Engine Input
						PW_GLFW_VOID_CALL(glfwPollEvents(), true);
						// Engine Frame / Shader
						PW_GL_VOID_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f), true, false);
						PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), true, false);
						// Update the projection information for the vertex shader / fragment shader
						PW_CALL(pw::co::Shader::Update_Projection(), true);
						if (v_loaded > v_quarter && v_quarter <= 1.0f) {
							PW_CALL(v_loading_bar.Advance_Animation(), true);
							v_quarter = v_quarter + 0.25f;
						}
						// Send Draws
						PW_CALL(v_loading_bar.Render(), true);
						PW_CALL(v_loading_icon.Render(), true);

						// Render
						PW_CALL(pw::st::Model::Draw(), true);
						PW_CALL(pw::st::Model::Draw_Transparent(), true);

						// Swap Open GL Buffers
						PW_CALL((*p_state_function)(), true);
						// Wait until the next frame should run
						cm::Constant::Wait();
					}
					PW_CALL(Add_Scene(std::get<0>(*i)), true);

					v_loaded = ((float)std::distance(std::get<2>(v_project).begin(), i) + 1.0f) / (float)std::get<2>(v_project).size();
					{
						PW_CALL(pw::co::Shader::Use(), true);
						// Calculate needed time constants
						PW_CALL(cm::Constant::Calc_Elapsed_Time(&*p_main_window), true);

						// Engine Input
						PW_GLFW_VOID_CALL(glfwPollEvents(), true);
						// Engine Frame / Shader
						PW_GL_VOID_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f), true, false);
						PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT), true, false);
						// Update the projection information for the vertex shader / fragment shader
						PW_CALL(pw::co::Shader::Update_Projection(), true);
						if (v_loaded > v_quarter && v_quarter <= 1.0f) {
							PW_CALL(v_loading_bar.Advance_Animation(), true);
							v_quarter = v_quarter + 0.25f;
						}
						// Send Draws
						PW_CALL(v_loading_bar.Render(), true);
						PW_CALL(v_loading_icon.Render(), true);

						// Render
						PW_CALL(pw::st::Model::Draw(), true);
						PW_CALL(pw::st::Model::Draw_Transparent(), true);

						// Swap Open GL Buffers
						PW_CALL((*p_state_function)(), true);
						// Wait until the next frame should run
						cm::Constant::Wait();
					}
				}
				PW_CALL(Set_Current_Scene(v_first_scene.c_str()), true);
			}
			void Engine_Queue::Add_Scene(const std::wstring& p_scene_name, const bool p_set_current) {
				auto v_found = m_scene_directory->find(p_scene_name);
				// Can't load the same scene twice in once instance
				if (v_found == m_scene_directory->end()) {
					if (m_pre_scene_add != nullptr) {
						PW_CALL(m_pre_scene_add(p_scene_name), true);
					}

					// Load scene
					PW_CALL(st::Game_Scene* v_scene = co::File_Loader::Load_Scene_File(p_scene_name.c_str()), true);

					m_scene_directory->insert(std::make_pair(p_scene_name, v_scene));
					if (p_set_current == true) {
						PW_CALL(Set_Current_Scene(p_scene_name.c_str()), true);
					}
					if (m_post_scene_add != nullptr) {
						PW_CALL(m_post_scene_add(p_scene_name), true);
					}
				}
			}
			void Engine_Queue::Set_Current_Scene(const std::wstring& p_scene_name) {
				auto v_found = m_scene_directory->find(p_scene_name);
				// Check if the scene exists first
				if (v_found != m_scene_directory->end()) {
					if (m_pre_scene_change != nullptr) {
						PW_CALL(m_pre_scene_change(p_scene_name), true);
					}

					if (m_current_scene.empty() == true) {
						m_current_scene = p_scene_name;
						co::Input::Set_Current_Input(m_scene_directory->at(m_current_scene)->Input());
						co::Input::Set_Scene_Event_Function(m_scene_directory->at(m_current_scene)->Event_Callback());
						m_scene_directory->at(m_current_scene)->Re_Render();
					}
					else {
						m_scene_directory->at(m_current_scene)->Capture_Instance(st::Camera::Camera_Position());

						PW_CALL(m_scene_directory->at(m_current_scene)->Stop_All_Sounds(), true);

						m_current_scene = p_scene_name;
						co::Input::Set_Current_Input(m_scene_directory->at(m_current_scene)->Input());
						co::Input::Set_Scene_Event_Function(m_scene_directory->at(m_current_scene)->Event_Callback());
						m_scene_directory->at(m_current_scene)->Re_Render();
					}

					if (m_post_scene_change != nullptr) {
						PW_CALL(m_post_scene_change(p_scene_name), true);
					}
				}
			}
			void Engine_Queue::Remove_Scene(std::wstring p_scene_name) {
				auto v_found = m_scene_directory->find(p_scene_name);
				// Can't load the same scene twice in once instance
				if (v_found != m_scene_directory->end()) {
					if (m_pre_scene_remove != nullptr) {
						PW_CALL(m_pre_scene_remove(p_scene_name), true);
					}

					if (m_current_scene.empty() != true) {
						if (v_found->first == m_current_scene) {
							m_current_scene = std::wstring();
						}
					}

					if (pw::co::Memory::Deallocate<pw::st::Game_Scene>(v_found->second) == false) {
						if (v_found->second != nullptr) {
							delete v_found->second;
							v_found->second = nullptr;
						}
					}

					m_scene_directory->erase(v_found->first);


					if (m_post_scene_remove != nullptr) {
						PW_CALL(m_post_scene_remove(p_scene_name), true);
					}
				}
			}
			void Engine_Queue::Set_Scene_Functions(
					const std::function<void(const std::wstring&)>& p_pre_add,
					const std::function<void(const std::wstring&)>& p_post_add,
					const std::function<void(const std::wstring&)>& p_pre_change,
					const std::function<void(const std::wstring&)>& p_post_change,
					const std::function<void(const std::wstring&)>& p_pre_remove,
					const std::function<void(const std::wstring&)>& p_post_remove) {

				m_pre_scene_add = p_pre_add;
				m_post_scene_add = p_post_add;
				m_pre_scene_change = p_pre_change;
				m_post_scene_change = p_post_change;
				m_pre_scene_remove = p_pre_remove;
				m_post_scene_remove = p_post_remove;
			}
			void Engine_Queue::Set_User_Debug_Function(const std::function<void()>& p_debug_function) {
				m_user_debug_function = p_debug_function;
			}
			void Engine_Queue::Set_Sub_Scene_Render(const std::wstring& p_base_scene, const std::wstring& p_sub_scene, const bool p_state) {
				auto v_found = m_scene_directory->find(p_base_scene);
				if (v_found != m_scene_directory->end()) {
					v_found->second->Set_Sub_Scene_State(p_sub_scene, p_state);
				}
			}
			st::Game_Scene* Engine_Queue::Get_Scene(const std::wstring& p_scene_name) {
				auto v_found = m_scene_directory->find(p_scene_name);
				if (v_found != m_scene_directory->end()) {
					return v_found->second;
				}
				else {
					return nullptr;
				}
			}
			st::Game_Scene* Engine_Queue::Current_Scene() {
				auto v_found = m_scene_directory->find(m_current_scene);
				if (v_found != m_scene_directory->end()) {
					return v_found->second;
				}
				else {
					return nullptr;
				}
			}
	CO_NAMESPACE_END
PW_NAMESPACE_END