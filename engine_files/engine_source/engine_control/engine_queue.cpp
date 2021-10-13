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
			void Engine_Queue::Run_Queue() {
				if (current_scene != nullptr) {
					scene_directory.at(*current_scene)->Render();
				}
			}
			void Engine_Queue::Load_From_Dir(const wchar_t* directory) {
				// Find if the directory exist
				std::wstring v_str_directory = directory;

				std::filesystem::path v_path_to_animations{ v_str_directory + std::wstring(L"animations") };
				std::filesystem::path v_path_to_data{ v_str_directory + std::wstring(L"data") };
				std::filesystem::path v_path_to_fonts{ v_str_directory + std::wstring(L"fonts") };
				std::filesystem::path v_path_to_icon{ v_str_directory + std::wstring(L"icon") };
				std::filesystem::path v_path_to_linker_files{ v_str_directory + std::wstring(L"linker_files") };
				std::filesystem::path v_path_to_textures{ v_str_directory + std::wstring(L"textures") };

				if (std::filesystem::exists(v_path_to_animations) == false) {
					PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find \"animations\" directory");
				}
				else {
					if (std::filesystem::exists(v_path_to_data) == false) {
						PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find \"data\" directory");
					}
					else {
						if (std::filesystem::exists(v_path_to_fonts) == false) {
							PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find \"fonts\" directory");
						}
						else {
							if (std::filesystem::exists(v_path_to_icon) == false) {
								PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find \"icon\" directory");
							}
							else {
								if (std::filesystem::exists(v_path_to_linker_files) == false) {
									PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find \"linker_files\" directory");
								}
								else {
									if (std::filesystem::exists(v_path_to_textures) == false) {
										PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find \"textures\" directory");
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
											if (file_finder.exists() == true) {
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
											PW_PRINT_ERROR(L"Pistonworks Engine", L"Could not find project file");
										}
										else {
											// Load the .pwproject file
											PW_PROJECT_FILE project = co::File_Loader::Load_Project_File(project_location.c_str(),
												v_path_to_animations.generic_wstring(), v_path_to_data.generic_wstring(), v_path_to_fonts.generic_wstring(),
												v_path_to_icon.generic_wstring(), v_path_to_linker_files.generic_wstring(), v_path_to_textures.generic_wstring());
											// Load first scene
											scene_directory.insert(std::make_pair(project._Get_rest()._Get_rest()._Myfirst._Val, co::File_Loader::Load_Scene_File(project._Get_rest()._Get_rest()._Myfirst._Val.c_str())));
											Set_Current_Scene(project._Get_rest()._Get_rest()._Myfirst._Val.c_str());
										}
									}
								}
							}
						}
					}
				}
			}
			st::Game_Scene* Engine_Queue::Current_Scene() {
				return scene_directory.at(*current_scene);
			}
			void Engine_Queue::Clear_Queue() {
				for (auto i = scene_directory.begin(); i != scene_directory.end(); i++) {
					i->second->Delete();
				}
				scene_directory.clear();
			}
			void Engine_Queue::Set_Current_Scene(const wchar_t* name_id) {
				if (current_scene == nullptr) {
					current_scene = new std::wstring(name_id);
					co::Engine_Input::Set_Current_Input(scene_directory.at(*current_scene)->Input());
					co::Engine_Input::Set_Refresh_Function(scene_directory.at(*current_scene)->Refresh_Scene_Callback());
				}
				else {
					delete current_scene;
					current_scene = new std::wstring(name_id);
					co::Engine_Input::Set_Current_Input(scene_directory.at(*current_scene)->Input());
				}
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////