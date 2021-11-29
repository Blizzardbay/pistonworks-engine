#include "engine_control\engine_queue.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// Engine_Queue
		// Static Declarations
		// Class Members
			void Engine_Queue::Pre_Queue() {
				if (current_scene != nullptr) {
					scene_directory.at(*current_scene)->Pre_Render();
				}
			}
			void Engine_Queue::Run_Queue() {
				if (current_scene != nullptr) {
					scene_directory.at(*current_scene)->Render();
				}
			}
			void Engine_Queue::Refresh_Queue() {
				if (current_scene != nullptr) {
					scene_directory.at(*current_scene)->Refresh_Scene();
				}
			}
			void Engine_Queue::Load_From_Dir(const wchar_t* directory, st::Shader& shader, PW_DUNI_PTR(GLFWwindow, cm::Engine_Constant::Destroy_GLFW)& main_window, PW_SRD_PTR(PW_FUNCTION) state_function) {

				co::File_Loader::Initialize_Loader(&Engine_Queue::Add_Scene, &Engine_Queue::Set_Current_Scene);

				// Set debug function if in debug mode
				#ifdef PW_DEBUG_MODE
					cm::Engine_Constant::Set_Debug_Function(Print_Debug_Stats);
				#endif

				// Find if the directory exist
				std::wstring v_str_directory = directory;

				std::filesystem::path v_path_to_animations{ v_str_directory + std::wstring(L"animations") };
				std::filesystem::path v_path_to_data{ v_str_directory + std::wstring(L"data") };
				std::filesystem::path v_path_to_fonts{ v_str_directory + std::wstring(L"fonts") };
				std::filesystem::path v_path_to_icon{ v_str_directory + std::wstring(L"icon") };
				std::filesystem::path v_path_to_linker_files{ v_str_directory + std::wstring(L"linker_files") };
				std::filesystem::path v_path_to_textures{ v_str_directory + std::wstring(L"textures") };

				if (TRY_LINE std::filesystem::exists(v_path_to_animations) == false) {
					PW_PRINT_ERROR(pw::er::Warning_Error(L"Pistonworks Engine", L"Could not find \"animations\" directory", std::move(EXCEPTION_LINE), __FILEW__, L"std::filesystem::exists"));
				}
				else {
					if (TRY_LINE std::filesystem::exists(v_path_to_data) == false) {
						PW_PRINT_ERROR(pw::er::Warning_Error(L"Pistonworks Engine", L"Could not find \"data\" directory", std::move(EXCEPTION_LINE), __FILEW__, L"std::filesystem::exists"));
					}
					else {
						if (TRY_LINE std::filesystem::exists(v_path_to_fonts) == false) {
							PW_PRINT_ERROR(pw::er::Warning_Error(L"Pistonworks Engine", L"Could not find \"fonts\" directory", std::move(EXCEPTION_LINE), __FILEW__, L"std::filesystem::exists"));
						}
						else {
							if (TRY_LINE std::filesystem::exists(v_path_to_icon) == false) {
								PW_PRINT_ERROR(pw::er::Warning_Error(L"Pistonworks Engine", L"Could not find \"icon\" directory", std::move(EXCEPTION_LINE), __FILEW__, L"std::filesystem::exists"));
							}
							else {
								if (TRY_LINE std::filesystem::exists(v_path_to_linker_files) == false) {
									PW_PRINT_ERROR(pw::er::Warning_Error(L"Pistonworks Engine", L"Could not find \"linker_files\" directory", std::move(EXCEPTION_LINE), __FILEW__, L"std::filesystem::exists"));
								}
								else {
									if (TRY_LINE std::filesystem::exists(v_path_to_textures) == false) {
										PW_PRINT_ERROR(pw::er::Warning_Error(L"Pistonworks Engine", L"Could not find \"textures\" directory", std::move(EXCEPTION_LINE), __FILEW__, L"std::filesystem::exists"));
									}
									else {
										// First make sure the file location exists
										std::wstring project_location = std::wstring();

										bool found_file = false;

										for (const auto& file_finder : std::filesystem::recursive_directory_iterator(v_path_to_linker_files)) {
											// If the .pwproject is found break
											if (found_file == true) {
												break;
											}
											// If the .pwproject dir exists then search for the file
											if (TRY_LINE file_finder.exists() == true) {
												// If the path is empty 
												if (file_finder.path().empty() == false) {
													// Get rid of the path and only find the name
													std::wstring temp_file_extention = file_finder.path().generic_wstring();
													temp_file_extention.erase(0, temp_file_extention.find_last_of(L".") + 1);
													// If the pwproject name is correct then we found the correct path
													if (wcscmp(temp_file_extention.c_str(), L"csv") == 0) {
														found_file = true;
														// Save the correct path
														project_location = file_finder.path().generic_wstring();
													}
												}
											}
										}
										if (found_file == false) {
											PW_PRINT_ERROR(er::Warning_Error(L"Pistonworks Engine", L"Could not find project file.", std::move(EXCEPTION_LINE), __FILEW__, L"recursive_directory_iterator"));
										}
										else {
											// Create loading animation
											std::tuple<st::Texture*, st::Animation*> v_animation = co::File_Loader::Load_Animation_File(L"Loading_Bar.gif", true);
											st::Static_Model v_model = st::Static_Model(st::Mesh_Types::SQUARE, v_animation._Myfirst._Val, glm::vec2(0.0f, cm::Engine_Constant::Window_Height()), 0.0f, glm::vec2(cm::Engine_Constant::Window_Width(), cm::Engine_Constant::Window_Height()));
											v_animation._Get_rest()._Myfirst._Val->Finish_Init(v_model.Model_Mesh().get()->Vertices(), v_model.Model_Mesh().get()->Vertex_Count());
											st::AAsset_Model v_loading_bar = st::AAsset_Model(
												std::make_shared<st::Static_Model>(v_model),
												std::make_shared<st::Animation>(*v_animation._Get_rest()._Myfirst._Val)
											);
											v_animation = co::File_Loader::Load_Animation_File(L"Loading_PW_Logo.gif", true);
											v_model = st::Static_Model(st::Mesh_Types::SQUARE, v_animation._Myfirst._Val, glm::vec2(637.0f, 163.0f), 0.0f, glm::vec2(163.0f, 163.0f));
											v_animation._Get_rest()._Myfirst._Val->Finish_Init(v_model.Model_Mesh().get()->Vertices(), v_model.Model_Mesh().get()->Vertex_Count());
											st::AAsset_Model v_loading_icon = st::AAsset_Model(
												std::make_shared<st::Static_Model>(v_model),
												std::make_shared<st::Animation>(*v_animation._Get_rest()._Myfirst._Val)
											);

											// Load the .pwproject file
											PW_PROJECT_FILE project = std::async(std::launch::async, [](
												std::wstring project_location, std::wstring path_to_animations, std::wstring path_to_data,
												std::wstring path_to_fonts, std::wstring path_to_icon, std::wstring path_to_linker_files, std::wstring path_to_textures) -> PW_PROJECT_FILE {
													return co::File_Loader::Load_Project_File(project_location.c_str(),
														path_to_animations, path_to_data, path_to_fonts,
														path_to_icon, path_to_linker_files, path_to_textures);
												}, project_location, v_path_to_animations.generic_wstring(),
													v_path_to_data.generic_wstring(), v_path_to_fonts.generic_wstring(),
													v_path_to_icon.generic_wstring(), v_path_to_linker_files.generic_wstring(),
													v_path_to_textures.generic_wstring()).get();

											v_loading_bar.Stop_Animation();
											v_loading_bar.Advance_Animation();
											while (true) {
												// Calculate needed time constants
												cm::Engine_Constant::Calc_Elapsed_Time(main_window.get());
												cm::Engine_Constant::Calc_Delta_Time();

												// Engine Input
												PW_GLFW_VOID_CALL(glfwPollEvents());
												// Engine Frame / Shader
												PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
												PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
												// Update the projection information for the vertex shader / fragment shader
												shader.Update_Projection();

												v_loading_bar.Render();
												v_loading_icon.Render();

												// Swap Open GL Buffers
												(*state_function.get())();
												// Wait until the next frame should run
												cm::Engine_Constant::Wait();

												if (project._Myfirst._Val == true) {
													break;
												}
											}
											float v_loaded = 0;
											std::wstring v_first_scene{};
											float v_quarter = 0.25f;

											for (auto i = std::get<2>(project).begin(); i != std::get<2>(project).end(); i++) {
												if (std::get<1>(*i) == true) {
													v_first_scene = std::get<0>(*i);
												}
												Add_Scene(std::get<0>(*i));

												v_loaded = ((float)std::distance(std::get<2>(project).begin(), i) + 1.0f) / (float)std::get<2>(project).size();
												{
													// Calculate needed time constants
													cm::Engine_Constant::Calc_Elapsed_Time(main_window.get());
													cm::Engine_Constant::Calc_Delta_Time();

													// Engine Input
													PW_GLFW_VOID_CALL(glfwPollEvents());
													// Engine Frame / Shader
													PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
													PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
													// Update the projection information for the vertex shader / fragment shader
													shader.Update_Projection();
													if (v_loaded > v_quarter && v_quarter <= 1.0f) {
														v_loading_bar.Advance_Animation();
														v_quarter = v_quarter + 0.25f;
													}
													v_loading_bar.Render();
													v_loading_icon.Render();

													// Swap Open GL Buffers
													(*state_function.get())();
													// Wait until the next frame should run
													cm::Engine_Constant::Wait();
												}
											}
											v_loading_bar.Delete();
											v_loading_icon.Delete();

											Set_Current_Scene(v_first_scene.c_str());
										}
									}
								}
							}
						}
					}
				}
			}
			CORE void Engine_Queue::Print_Debug_Stats() {
				PRINT_INFO(L"HM    ", pw::Engine_Memory::Memory_String(pw::Engine_Memory::Heap_Memory()), 0);
				PRINT_INFO(L"HHM   ", pw::Engine_Memory::Memory_String(pw::Engine_Memory::High_Heap_Memory()), 1);
				PRINT_INFO(L"FPS   ", std::to_wstring(pw::cm::Engine_Constant::FPS()), 2);
				PRINT_INFO(L"FPSLST", std::to_wstring(pw::cm::Engine_Constant::Last_FPS()), 3);
				PRINT_INFO(L"FPSMAX", std::to_wstring(pw::cm::Engine_Constant::FPS_Max()), 4);

				std::wstring v_fps_average = std::to_wstring(pw::cm::Engine_Constant::FPS_Average());

				uint16_t v_period = v_fps_average.find(L".");
				if (v_period != std::string::npos) {
					uint16_t v_decimal_count = v_fps_average.size() - OFF64(v_period);
					if (v_decimal_count > 2) {
						v_decimal_count = v_decimal_count - 2;
						v_fps_average.erase(OFF64(v_period) + 2, v_decimal_count);
					}
				}

				PRINT_INFO(L"FPSAVG", v_fps_average, 5);
				PRINT_INFO(L"MODELS", std::to_wstring(st::Model::model_counter), 6);
				size_t v_render_count = 0;
				if (current_scene != nullptr) {
					v_render_count = scene_directory.at(*current_scene)->Last_Render_Count();
				}
				PRINT_INFO(L"RNDCNT", std::to_wstring(v_render_count), 7);

				std::wstring v_camera_position_x = std::to_wstring(st::Camera::Camera_Position().x);

				v_period = v_camera_position_x.find(L".");
				if (v_period != std::string::npos) {
					uint16_t v_decimal_count = v_camera_position_x.size() - OFF64(v_period);
					if (v_decimal_count > 2) {
						v_decimal_count = v_decimal_count - 2;
						v_camera_position_x.erase(OFF64(v_period) + 2, v_decimal_count);
					}
				}

				PRINT_INFO(L"CAMXPS", v_camera_position_x, 8);

				std::wstring v_camera_position_y = std::to_wstring(st::Camera::Camera_Position().y);

				v_period = v_camera_position_y.find(L".");
				if (v_period != std::string::npos) {
					uint16_t v_decimal_count = v_camera_position_y.size() - OFF64(v_period);
					if (v_decimal_count > 2) {
						v_decimal_count = v_decimal_count - 2;
						v_camera_position_y.erase(OFF64(v_period) + 2, v_decimal_count);
					}
				}

				PRINT_INFO(L"CAMYPS", v_camera_position_y, 9);
			}
			st::Game_Scene* Engine_Queue::Current_Scene() {
				return scene_directory.at(*current_scene);
			}
			void Engine_Queue::Clear_Queue() {
				for (auto i = scene_directory.begin(); i != scene_directory.end(); i++) {
					i->second->Delete();
					pw::Engine_Memory::Deallocate<st::Game_Scene>(i->second);
				}
				scene_directory.clear();
			}
			void Engine_Queue::Add_Scene(std::wstring scene_name, bool set_current) {
				auto v_found = scene_directory.find(scene_name);
				// Can't load the same scene twice in once instance
				if (v_found == scene_directory.end()) {
					// Load scene
					st::Game_Scene* v_scene = co::File_Loader::Load_Scene_File(scene_name.c_str());

					scene_directory.insert(std::make_pair(scene_name, v_scene));
					if (set_current == true) {
						Set_Current_Scene(scene_name.c_str());
					}
				}
			}
			void Engine_Queue::Set_Current_Scene(std::wstring name_id) {
				auto v_found = scene_directory.find(name_id);
				// Check if the scene exists first
				if (v_found != scene_directory.end()) {
					if (current_scene == nullptr) {
						current_scene = pw::Engine_Memory::Allocate<std::wstring>(name_id.c_str());
						co::Engine_Input::Set_Current_Input(scene_directory.at(*current_scene)->Input());
						co::Engine_Input::Set_Refresh_Function(scene_directory.at(*current_scene)->Refresh_Scene_Callback());
						co::Engine_Input::Set_Scene_Event_Function(scene_directory.at(*current_scene)->Event_Callback());
						scene_directory.at(*current_scene)->Re_Render();
					}
					else {
						scene_directory.at(*current_scene)->Capture_Instance(st::Camera::Camera_Position());

						pw::Engine_Memory::Deallocate<std::wstring>(current_scene);
						current_scene = pw::Engine_Memory::Allocate<std::wstring>(name_id.c_str());
						co::Engine_Input::Set_Current_Input(scene_directory.at(*current_scene)->Input());
						co::Engine_Input::Set_Refresh_Function(scene_directory.at(*current_scene)->Refresh_Scene_Callback());
						co::Engine_Input::Set_Scene_Event_Function(scene_directory.at(*current_scene)->Event_Callback());
						scene_directory.at(*current_scene)->Re_Render();
					}
				}
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////