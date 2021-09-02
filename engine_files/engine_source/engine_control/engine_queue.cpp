#include "engine_headers\engine_queue.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	// Engine_Queue
	// Static Declarations
	// Class Members
		PW_VOID Engine_Queue::Run_Queue() {

		}
		PW_VOID Engine_Queue::Refresh_Queue() {

		}
		PW_VOID Engine_Queue::Load_From_Dir(PW_CSTRING directory) {
			// Find if the directory exist
			PW_STRING str_directory = directory;

			std::filesystem::path path_to_directory = std::filesystem::path(str_directory);

			// Store file information
			PW_STRING project_data = PW_STRING();

			PW_STRING first_scene = PW_STRING();

			if (std::filesystem::exists(path_to_directory) == false) {
				PW_PRINT_ERROR("Pistonworks Engine", "Could not find directory");
			}
			else {
				// First make sure the file location exists
				PW_STRING project_location = PW_STRING();

				PW_BOOL found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(str_directory)) {
					// If the .pwproject is found break
					if (found_file == true) {
						break;
					}
					// If the .pwproject dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							PW_STRING temp_file_extention = file_finder.path().generic_string();
							temp_file_extention.erase(0, temp_file_extention.find_last_of(".") + 1);
							// If the .pwproject name is correct then we found the correct path
							if (strcmp(temp_file_extention.c_str(), "pwproject") == 0) {
								found_file = true;
								// Save the correct path
								project_location = file_finder.path().generic_string();
							}
						}
					}
				}
				if (found_file == false) {
					PW_PRINT_ERROR("Pistonworks Engine", "Could not find project file");
				}
				else {
					// Load the .pwproject file
					std::ifstream file_loader = std::ifstream();
					// Open file
					file_loader.open(project_location, std::ios_base::in);
				   // Test for fail
					if (file_loader.is_open() == true) {
						// While the file is still readable dump information into a string
						// Get a line of characters
						PW_STRING file_line = PW_STRING();
						while (file_loader.eof() == false) {
							std::getline(file_loader, file_line);
							project_data.append(file_line);
						}
						file_loader.close();
					}
					else {
						PW_PRINT_ERROR("Pistonworks Engine", "Could not open project file");
					}
					// Interpret the project data
					PW_INT place = 0;
					PW_INT place_off = 0;
					PW_INT data_off = 0;
					// Used for syntax
					PW_STRING test_str = PW_STRING();
					// Used for data / data testing
					PW_STRING data_str = PW_STRING();
					// "project_name"
					place = project_data.find('{');
					data_off = std::strlen("{HEADER}/PROJECT_NAME(");
					test_str = project_data.substr(place, data_off);
					if (std::strcmp(test_str.c_str(), "{HEADER}/PROJECT_NAME(") != false) {
						PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 1 & line 2");
					}
					else {
						// Get data
						place = project_data.find('"', place);
						place_off = project_data.find('"', OFF(place));
						data_str = project_data.substr(OFF(place), place_off - OFF(place));

						project_name = data_str.c_str();
						data_str.clear();

						Engine_Constant::Set_Window_Name(project_name.c_str());
						// Check the end of the line
						place = project_data.find(')');
						data_off = std::strlen(");");
						test_str = project_data.substr(place, data_off);
						if (std::strcmp(test_str.c_str(), ");") != false) {
							PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 2");
						}
						else {
							// "First Scene"
							place = project_data.find('{', place);
							data_off = std::strlen("{STRUCTURE}/ONLOAD_SCENE(");
							test_str = project_data.substr(place, data_off);
							if (std::strcmp(test_str.c_str(), "{STRUCTURE}/ONLOAD_SCENE(") != false) {
								PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 3 & 4");
							}
							else {
								// Get data
								place = project_data.find('"', place);
								place_off = project_data.find('"', OFF(place));
								data_str = project_data.substr(OFF(place), place_off - OFF(place));
								first_scene = data_str;
								// Check the end of the line
								place = project_data.find(')', place);
								data_off = std::strlen(");");
								test_str = project_data.substr(place, data_off);
								if (std::strcmp(test_str.c_str(), ");") != false) {
									PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 4");
								}
								else {
									// "data_location"
									place = project_data.find('{', place);
									data_off = std::strlen("{FILES}/DATALOC(");
									test_str = project_data.substr(place, data_off);
									if (std::strcmp(test_str.c_str(), "{FILES}/DATALOC(") != false) {
										PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 5 & 6");
									}
									else {
										// Get data
										place = project_data.find('"', place);
										place_off = project_data.find('"', OFF(place));
										data_str = project_data.substr(OFF(place), place_off - OFF(place));
										data_location = data_str;
										data_location.insert(0, "engine_files/engine_resource/");
										data_str.clear();
										// Check the end of the line
										place = project_data.find(')', place);
										data_off = std::strlen(");");
										test_str = project_data.substr(place, data_off);
										if (std::strcmp(test_str.c_str(), ");") != false) {
											PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 6");
										}
										else {
											// "texture_location"
											place = project_data.find('{', place);
											data_off = std::strlen("{TEXTURES}/TEXTURELOC(");
											test_str = project_data.substr(place, data_off);
											if (std::strcmp(test_str.c_str(), "{TEXTURES}/TEXTURELOC(") != false) {
												PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 7 & 8");
											}
											else {
												// Get data
												place = project_data.find('"', place);
												place_off = project_data.find('"', OFF(place));
												data_str = project_data.substr(OFF(place), place_off - OFF(place));
												texture_location = data_str;
												texture_location.insert(0, "engine_files/engine_resource/");
												data_str.clear();
												// Check the end of the line
												place = project_data.find(')', place);
												data_off = std::strlen(");");
												test_str = project_data.substr(place, data_off);
												if (std::strcmp(test_str.c_str(), ");") != false) {
													PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 8");
												}
												else {
													// "animation_location"
													place = project_data.find('{', place);
													data_off = std::strlen("{ANIMATIONS}/ANIMATIONLOC(");
													test_str = project_data.substr(place, data_off);
													if (std::strcmp(test_str.c_str(), "{ANIMATIONS}/ANIMATIONLOC(") != false) {
														PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 9 & 10");
													}
													else {
														// Get data
														place = project_data.find('"', place);
														place_off = project_data.find('"', OFF(place));
														data_str = project_data.substr(OFF(place), place_off - OFF(place));
														animation_location = data_str;
														animation_location.insert(0, "engine_files/engine_resource/");
														data_str.clear();
														// Check the end of the line
														place = project_data.find(')', place);
														data_off = std::strlen(");");
														test_str = project_data.substr(place, data_off);
														if (std::strcmp(test_str.c_str(), ");") != false) {
															PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 10");
														}
														else {
															// "font_location"
															place = project_data.find('{', place);
															data_off = std::strlen("{FONT}/FONTLOC(");
															test_str = project_data.substr(place, data_off);
															if (std::strcmp(test_str.c_str(), "{FONT}/FONTLOC(") != false) {
																PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 11 & 12");
															}
															else {
																// Get data
																place = project_data.find('"', place);
																place_off = project_data.find('"', OFF(place));
																data_str = project_data.substr(OFF(place), place_off - OFF(place));
																font_location = data_str;
																font_location.insert(0, "engine_files/engine_resource/");
																data_str.clear();
																// Check the end of the line
																place = project_data.find(')', place);
																data_off = std::strlen(");");
																test_str = project_data.substr(place, data_off);
																if (std::strcmp(test_str.c_str(), ");") != false) {
																	PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 12");
																}
																else {
																	// "icon_location"
																	place = project_data.find('{', place);
																	data_off = std::strlen("{ICON}/ICONLOC(");
																	test_str = project_data.substr(place, data_off);
																	if (std::strcmp(test_str.c_str(), "{ICON}/ICONLOC(") != false) {
																		PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 13 & 14");
																	}
																	else {
																		// Get data
																		place = project_data.find('"', place);
																		place_off = project_data.find('"', OFF(place));
																		data_str = project_data.substr(OFF(place), place_off - OFF(place));
																		icon_location = data_str;
																		icon_location.insert(0, "engine_files/engine_resource/");
																		data_str.clear();
																		// Check the end of the line
																		place = project_data.find(')', place);
																		data_off = std::strlen(");");
																		test_str = project_data.substr(place, data_off);
																		if (std::strcmp(test_str.c_str(), ");") != false) {
																			PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 14");
																		}
																		else {
																			place = project_data.find('{', place);
																			data_off = std::strlen("{END_OF_FILE}");
																			test_str = project_data.substr(place, data_off);
																			if (std::strcmp(test_str.c_str(), "{END_OF_FILE}") != false) {
																				PW_PRINT_ERROR("Pistonworks Engine", "Project File: Invalid Syntax : line 15");
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
					// Find if scene exist
					PW_BOOL found_file = false;

					// If the scene has no extension, give it one
					if (first_scene.find('.', 0) == std::string::npos) {
						first_scene.append(".pwsf");
					}

					for (const auto& file_finder : std::filesystem::recursive_directory_iterator(data_location)) {
						// If the .pwproject is found break
						if (found_file == true) {
							break;
						}
						// If the .pwproject dir exists then search for the file
						if (file_finder.exists() == true) {
							// If the path is empty 
							if (file_finder.path().empty() == false) {
								// Get rid of the path and only find the name
								PW_STRING temp_file_extention = file_finder.path().generic_string();
								temp_file_extention.erase(0, temp_file_extention.find_last_of("/") + 1);
								// If the name of the file is equal to name of the scene, we have found the file
								if (temp_file_extention == first_scene) {
									found_file = true;
									// Save the correct path
									first_scene = file_finder.path().generic_string();
								}
							}
						}
					}
					if (found_file == false) {
						PW_PRINT_ERROR("Pistonworks Engine", "Could not find project file");
					}
					else {
						// Load first scene
						Load_Scene(first_scene.c_str());


					}
				}
			}

		}
		ie::Game_Scene* Engine_Queue::Current_Scene() {
			return scene_directory.at(*current_scene);
		}
		PW_VOID Engine_Queue::Clear_Queue() {
			for (auto i = scene_directory.begin(); i != scene_directory.end(); i++) {
				i->second->Delete();
			}
			scene_directory.clear();
		}
		PW_VOID Engine_Queue::Load_Scene(PW_CSTRING scene_location) {
			PW_STRING scene_data{};

			// Load the .pwproject file
			std::ifstream file_loader = std::ifstream();
			// Open file
			file_loader.open(scene_location, std::ios_base::in);
			// Test for fail
			if (file_loader.is_open() == true) {
				// While the file is still readable dump information into a string
				// Get a line of characters
				PW_STRING file_line = PW_STRING();
				while (file_loader.eof() == false) {
					std::getline(file_loader, file_line);
					scene_data.append(file_line);
				}
				file_loader.close();
			}
			else {
				PW_PRINT_ERROR("Pistonworks Engine", "Could not open scene file");
			}
			// Interpret the scene data
			PW_INT place = 0;
			PW_INT place_off = 0;
			PW_INT data_off = 0;
			// Used for syntax
			PW_STRING test_str = PW_STRING();
			// Used for data / data testing
			PW_STRING data_str = PW_STRING();



		}
		PW_VOID Engine_Queue::Set_Current_Scene(PW_CSTRING name_id) {
			Engine_Input::Set_Current_Input(scene_directory.at(*current_scene)->Input());
			current_scene = &name_id;
		}
	// End of Class Members
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////