#include "engine_control\engine_file_loader.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// File_Loader               
		// Static Declarations
			glm::vec4 File_Loader::Engine_Colors[(uint32_t)Default_Colors::Color_Count]{
				//LIT_RED				#ff 80 80 
				//RED					#ff 00 00 
				//DRK_RED				#80 00 00	
				glm::vec4(	1.0f,				0.5f,				0.5f,				1.0f),
				glm::vec4(	1.0f,				0.0f,				0.0f,				1.0f),
				glm::vec4(	0.5f,				0.0f,				0.0f,				1.0f),
				//LIT_GREEN				#80 ff 80 
				//GREEN					#00 ff 00 
				//DRK_GREEN				#00 80 00 
				glm::vec4(	0.5f,				1.0f,				0.5f,				1.0f),
				glm::vec4(	0.0f,				1.0f,				0.0f,				1.0f),
				glm::vec4(	0.0f,				0.5f,				0.0f,				1.0f),
				//LIT_BLUE				#80 80 ff 
				//BLUE					#00 00 ff 
				//DRK_BLUE				#00 00 80
				glm::vec4(	0.5f,				0.5f,				1.0f,				1.0f),
				glm::vec4(	0.0f,				0.0f,				1.0f,				1.0f),
				glm::vec4(	0.0f,				0.0f,				0.5f,				1.0f),
				//LIT_YELLOW			#ff ff 80 
				//YELLOW				#ff ff 00 
				//DRK_YELLOW			#80 80 00
				glm::vec4(	1.0f,				1.0f,				0.5f,				1.0f),
				glm::vec4(	1.0f,				1.0f,				0.0f,				1.0f),
				glm::vec4(	0.5f,				0.5f,				0.0f,				1.0f),
				//LIT_PINK				#ff 80 ff 
				//PINK					#ff 00 ff 
				//DRK_PINK				#80 00 80
				glm::vec4(	1.0f,				0.5f,				1.0f,				1.0f),
				glm::vec4(	1.0f,				0.0f,				1.0f,				1.0f),
				glm::vec4(	0.5f,				0.0f,				0.5f,				1.0f),
				//LIT_CYAN				#80 ff ff 
				//CYAN					#00 ff ff 
				//DRK_CYAN				#00 80 80
				glm::vec4(	0.5f,				1.0f,				1.0f,				1.0f),
				glm::vec4(	0.0f,				1.0f,				1.0f,				1.0f),
				glm::vec4(	0.0f,				0.5f,				0.5f,				1.0f),
				//LIT_LIME				#80 ff 80 
				//LIME					#80 ff 00 
				//DRK_LIME				#40 80 00
				glm::vec4(	0.5f,				1.0f,				0.5f,				1.0f),
				glm::vec4(	0.5f,				1.0f,				0.0f,				1.0f),
				glm::vec4(	0.25f,				0.5f,				0.0f,				1.0f),
				//LIT_ORANGE			#ff bf 80 
				//ORANGE				#ff 80 00 
				//DRK_ORANGE			#cc 60 00
				glm::vec4(	1.0f,				191.0f / 255.0f,	0.5f,				1.0f),
				glm::vec4(	1.0f,				0.5f,				0.0f,				1.0f),
				glm::vec4(	204.0f / 255.0f,	96.0f / 255.0f,		0.0f,				1.0f),
				//LIT_AZURE				#80 bf ff 
				//AZURE					#00 80 ff 
				//DRK_AZURE				#00 40 80
				glm::vec4(	0.5f,				191.0f / 255.0f,	1.0f,				1.0f),
				glm::vec4(	0.0f,				0.5f,				1.0f,				1.0f),
				glm::vec4(	0.0f,				0.25f,				0.5f,				1.0f),
				//LIT_PURPLE			#bf 80 ff 
				//PURPLE				#80 00 ff 
				//DRK_PURPLE			#40 00 80
				glm::vec4(	191.0f / 255.0f,	0.5f,				1.0f,				1.0f),
				glm::vec4(	0.5f,				0.0f,				1.0f,				1.0f),
				glm::vec4(	0.25f,				0.0f,				0.5f,				1.0f),
				//LIT_BROWN				#80 5c 40 
				//BROWN					#80 40 00 
				//DRK_BROWN				#40 20 00
				glm::vec4(	0.5f,				92.0f / 255.0f,		0.25f,				1.0f),
				glm::vec4(	0.5f,				0.25f,				0.0f,				1.0f),
				glm::vec4(	0.25f,				0.125f,				0.0f,				1.0f),
				//LIT_GREY				#c0 c0 c0
				//GREY					#80 80 80 
				//DRK_GREY				#40 40 40
				glm::vec4(	192.0f / 255.0f,	192.0f / 255.0f,	192.0f / 255.0f,	1.0f),
				glm::vec4(	0.5f,				0.5f,				0.5f,				1.0f),
				glm::vec4(	0.25f,				0.25f,				0.25f,				1.0f),
				//WHITE					#ff ff ff
				//BLACK					#00 00 00
				glm::vec4(	1.0f,				1.0f,				1.0f,				1.0f),
				glm::vec4(	0.0f,				0.0f,				0.0f,				1.0f)
			};
			FIBITMAP* File_Loader::current_icon{ nullptr };

			bool File_Loader::loaded_project{ false };

			std::wstring File_Loader::animation_location{};
			std::wstring File_Loader::data_location{};
			std::wstring File_Loader::font_location{};
			std::wstring File_Loader::icon_location{};
			std::wstring File_Loader::linker_location{};
			std::wstring File_Loader::texture_location{};

			std::wstring File_Loader::engine_texture_dir{ L"engine_files/engine_resource/engine_essential/engine_textures/" };
			std::wstring File_Loader::engine_icon_dir{ L"engine_files/engine_resource/engine_essential/engine_icon/" };
			std::wstring  File_Loader::engine_animation_dir{ L"engine_files/engine_resource/engine_essential/engine_animations/" };

			std::function<void(std::wstring, bool)> File_Loader::add_scene_function{};
			std::function<void(std::wstring)> File_Loader::change_scene_function{};

			std::map<FREE_IMAGE_FORMAT, std::map<std::wstring, std::tuple<std::vector<BYTE>, uint32_t, uint32_t>>> File_Loader::texture_repository{};
			std::map<FREE_IMAGE_FORMAT, std::map<std::wstring, std::tuple<std::tuple<BYTE*, uint32_t, uint32_t>, std::tuple<float, uint32_t, uint32_t>>>> File_Loader::animation_repository{};
		// Class Members
			void File_Loader::Initialize_Loader(std::function<void(std::wstring, bool)> p_add_scene_function, std::function<void(std::wstring)> p_change_scene_function) {
				add_scene_function = p_add_scene_function;
				change_scene_function = p_change_scene_function;
			}
			st::Texture& File_Loader::Load_Texture_File(const wchar_t* file_name, bool engine_dir, const wchar_t* override_dir) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_UNKNOWN };
				// False Result
				st::Texture* texture{ nullptr };
				// First make sure the file location exists
				std::wstring file_location{ file_name };

				std::wstring v_file_name{ file_name };
				v_file_name.erase(0, OFF(v_file_name.find_last_of(L"/")));

				bool found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(override_dir == nullptr ? (engine_dir ? engine_texture_dir : texture_location) : (override_dir))) {
					// If the texture is found break
					if (found_file == true) {
						break;
					}
					// If the texture dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							std::wstring temp_file = file_finder.path().generic_wstring();
							temp_file.erase(0,temp_file.find_last_of(L"/") + 1);
							// If the texture name is correct then we found the correct path
							if (wcscmp(temp_file.c_str(), v_file_name.c_str()) == 0) {
								found_file = true;
								// Save the correct path
								file_location = file_finder.path().generic_wstring();
							}
						}
					}
				}
				if (TRY_LINE found_file == false) {
					throw er::Warning_Error(L"File Loader", std::wstring(L"Could not find file: " + std::wstring(file_name)), std::move(EXCEPTION_LINE), __FILEW__, L"recursive_directory_iterator");
				}
				std::string char_file_location = TO_STRING(file_location.c_str());

				// Get the file type of the image
				PW_FI_VOID_CALL(TRY_LINE image_type = FreeImage_GetFileType(char_file_location.c_str()));

				if (image_type == FIF_UNKNOWN) {
					PW_FI_VOID_CALL(image_type = FreeImage_GetFIFFromFilename(char_file_location.c_str()));

					if (image_type == FIF_UNKNOWN) {
						throw er::Warning_Error(L"File Loader", L"FIF_UNKNOWN, Unknown File Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_GetFileType");
					}
				}
				// Check if the file type is able to be loaded
				if (TRY_LINE FreeImage_FIFSupportsReading(image_type) == (BOOL)true) {
					switch (image_type) {
						case FIF_PNG: {
							return Load_PNG(file_location.c_str());
						}
						case FIF_BMP: {
							return Load_BMP(file_location.c_str());
						}
						case FIF_JPEG: {
							return Load_JPEG(file_location.c_str());
						}
						default: {
							throw er::Warning_Error(L"File Loader", L"Unsupported Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_FIFSupportsReading");
						}
					}
				}
				else {
					throw er::Warning_Error(L"File Loader", L"Unsupported Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_FIFSupportsReading");
				}
			}
			std::tuple<st::Texture*, st::Animation*> File_Loader::Load_Animation_File(const wchar_t* file_name, bool engine_dir, const wchar_t* override_dir) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_UNKNOWN };
				// File
				FIBITMAP* file{ nullptr };
				FIMULTIBITMAP* gif_bitmap{ nullptr };
				// Image Data
				BYTE* image_data{ nullptr };
				// Length / Width of image
				uint32_t width{ 0 };
				uint32_t height{ 0 };
				// Total frame time
				uint32_t frame_time{ 0 };
				// Result
				st::Texture* texture{ nullptr };
				st::Animation* animation{ nullptr };
				// First make sure the file location exists
				std::wstring file_location{ file_name };

				bool found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(override_dir == nullptr ? (engine_dir ? engine_animation_dir : animation_location) : (override_dir))) {
					// If the texture is found break
					if (found_file == true) {
						break;
					}
					// If the texture dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							std::wstring temp_file = file_finder.path().generic_wstring();
							temp_file.erase(0, temp_file.find_last_of(L"/") + 1);
							// If the texture name is correct then we found the correct path
							if (wcscmp(temp_file.c_str(), file_name) == 0) {
								found_file = true;
								// Save the correct path
								file_location = file_finder.path().generic_wstring();
							}
						}
					}
				}
				if (TRY_LINE found_file == false) {
					throw er::Warning_Error(L"File Loader", L"Could not find file", std::move(EXCEPTION_LINE), __FILEW__, L"recursive_directory_iterator");
				}

				std::string char_file_location = TO_STRING(file_location.c_str());

				// Get the file type of the image
				PW_FI_VOID_CALL(TRY_LINE image_type = FreeImage_GetFileType(char_file_location.c_str()));

				if (image_type == FIF_UNKNOWN) {
					PW_FI_VOID_CALL(image_type = FreeImage_GetFIFFromFilename(char_file_location.c_str()));

					if (image_type == FIF_UNKNOWN) {
						throw er::Warning_Error(L"File Loader", L"FIF_UNKNOWN, Unknown File Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_GetFileType");
					}
				}
				// Check if the file type is able to be loaded
				if (TRY_LINE FreeImage_FIFSupportsReading(image_type) == (BOOL)true) {		
						gif_bitmap = FreeImage_OpenMultiBitmap(FIF_GIF, char_file_location.c_str(), false, true);

						uint32_t frames = FreeImage_GetPageCount(gif_bitmap);

						uint32_t bytes_per_pixel = 0;

						uint32_t overall_width = 0;

						uint32_t size = 0;

						for (size_t i = 0; i < frames; i++) {
							// Open the bitmap from the gif
							FIBITMAP* bitmap = FreeImage_LockPage(gif_bitmap, TO_INT32(i));
							// Convert bitmap to RGBA with 4 bytes per pixel
							bitmap = FreeImage_ConvertTo32Bits(bitmap);
							if (i == 0) {
								bytes_per_pixel = FreeImage_GetBPP(bitmap) / TO_UINT32(8);

								image_data = pw::Engine_Memory::Allocate<BYTE>(TO_UINT64(FreeImage_GetWidth(bitmap)) * TO_UINT64(FreeImage_GetHeight(bitmap)) * frames * bytes_per_pixel);

								size = TO_UINT32(FreeImage_GetWidth(bitmap)) * TO_UINT32(FreeImage_GetHeight(bitmap)) * frames * bytes_per_pixel;

								overall_width = TO_UINT32(FreeImage_GetWidth(bitmap)) * frames * bytes_per_pixel;

								width = FreeImage_GetWidth(bitmap);
								height = FreeImage_GetHeight(bitmap);

								// Get meta data by loading
								FIBITMAP* metadata_bitmap = FreeImage_Load(FIF_GIF, char_file_location.c_str(), GIF_LOAD256);
								// Get animation meta data
								uint32_t metadata_entries{ FreeImage_GetMetadataCount(FIMD_ANIMATION, metadata_bitmap) };
								if (metadata_entries != NULL) {
									FITAG* tag{ nullptr };

									// Create a meta data to sort
									FIMETADATA* meta_data{ nullptr };

									meta_data = FreeImage_FindFirstMetadata(FIMD_ANIMATION, metadata_bitmap, &tag);

									for (size_t i = 0; i < 2; i++) {
										FreeImage_FindNextMetadata(meta_data, &tag);
										if (i == 1) {
											frame_time = std::stoi(FreeImage_TagToString(FIMD_ANIMATION, tag)) * frames;
										}
									}
									FreeImage_FindCloseMetadata(meta_data);
								}
								FreeImage_Unload(metadata_bitmap);
							}
							// Get Info
							size_t frame_width = FreeImage_GetWidth(bitmap);
							size_t frame_height = FreeImage_GetHeight(bitmap);

							BYTE* temp_pixel_data = FreeImage_GetBits(bitmap);
							// Put said pixel data into the image_data array
							for (size_t j = 0; j < frame_height; j++) {
								for (size_t k = 0; k < frame_width * bytes_per_pixel; k++) {
									image_data[k + (j * overall_width) + ((frame_width * bytes_per_pixel) * i)] = temp_pixel_data[k + (j * (frame_width * bytes_per_pixel))];
								}
							}
							FreeImage_UnlockPage(gif_bitmap, bitmap, false);
						}
						// Create Texture
						texture = pw::Engine_Memory::Allocate<st::Texture>(st::Texture(image_data, width * frames, height, GL_RGBA, GL_BGRA));

						pw::Engine_Memory::Deallocate<BYTE>(image_data);
						// Create Animation
						animation = pw::Engine_Memory::Allocate<st::Animation>(st::Animation(static_cast<float>(frame_time) / static_cast<float>(CLOCKS_PER_SEC), frames, width));

						FreeImage_Unload(file);

						FreeImage_CloseMultiBitmap(gif_bitmap);
						
						return std::tuple<st::Texture*, st::Animation*>(texture, animation);
				}
				else {
					throw er::Warning_Error(L"File Loader", L"Unsupported Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_FIFSupportsReading");
				}
			}
			GLFWimage& File_Loader::Load_Icon(const wchar_t* file_name, bool engine_dir) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_UNKNOWN };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				BYTE* image_data{ nullptr };
				// Length / Width of image / Pitch
				uint32_t width{ 0 };
				uint32_t height{ 0 };
				uint32_t pitch{ 0 };
				// Result
				GLFWimage* glfw_image{ pw::Engine_Memory::Allocate<GLFWimage>() };
				// First make sure the file location exists
				std::wstring file_location{ file_name };

				bool found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(engine_dir ? engine_icon_dir : icon_location)) {
					// If the texture is found break
					if (found_file == true) {
						break;
					}
					// If the texture dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							std::wstring temp_file = file_finder.path().generic_wstring();
							temp_file.erase(0, temp_file.find_last_of(L"/") + 1);
							// If the texture name is correct then we found the correct path
							if (wcscmp(temp_file.c_str(), file_name) == 0) {
								found_file = true;
								// Save the correct path
								file_location = file_finder.path().generic_wstring();
							}
						}
					}
				}
				if (TRY_LINE found_file == false) {
					throw er::Warning_Error(L"File Loader", L"Could not find file", std::move(EXCEPTION_LINE), __FILEW__, L"recursive_directory_iterator");
				}
				std::string char_file_location = TO_STRING(file_location.c_str());

				// Get the file type of the image
				PW_FI_VOID_CALL(TRY_LINE image_type = FreeImage_GetFileType(char_file_location.c_str()));

				if (image_type == FIF_UNKNOWN) {
					PW_FI_VOID_CALL(image_type = FreeImage_GetFIFFromFilename(char_file_location.c_str()));

					if (image_type == FIF_UNKNOWN) {
						throw er::Warning_Error(L"File Loader", L"FIF_UNKNOWN, Unknown File Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_GetFileType");
					}
				}
				// Check if the file type is able to be loaded
				if (TRY_LINE FreeImage_FIFSupportsReading(image_type) == (BOOL)true) {
					if (image_type == FIF_PNG) {
						// Load File
						PW_FI_VOID_CALL(TRY_LINE file = FreeImage_Load(image_type, char_file_location.c_str()));

						if (!file == true) {
							throw er::Warning_Error(L"File Loader", L"Unable to load", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_Load");
						}
						// If successful get data
						width = FreeImage_GetWidth(file);
						height = FreeImage_GetHeight(file);
						pitch = FreeImage_GetPitch(file);

						uint32_t bits_per_pixel = FreeImage_GetBPP(file);

						image_data = FreeImage_GetBits(file);
						
						for (size_t y = 0; y < height; y++) {
							BYTE* image_data = FreeImage_GetScanLine(file, (int32_t)y);
							for (size_t x = 0; x < width; x++) {
								BYTE temp = image_data[FI_RGBA_RED];
								image_data[FI_RGBA_RED] = image_data[FI_RGBA_BLUE];
								image_data[FI_RGBA_BLUE] = temp;
								// Go to the next pixel
								image_data += 4;
							}
						}

						// Create Texture
						glfw_image->pixels = image_data;
						glfw_image->width = width;
						glfw_image->height = height;

						current_icon = file;

						return *glfw_image;
					}
					else {
						throw er::Warning_Error(L"File Loader", L"Unsupported Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_FIFSupportsReading");
					}
				}
				else {
					throw er::Warning_Error(L"File Loader", L"Unsupported Type", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_FIFSupportsReading");
				}
			}
			void File_Loader::Unload_Icon() {
				FreeImage_Unload(current_icon);
			}
			glm::vec4 File_Loader::Default_Color(Default_Colors color) {
				return Engine_Colors[(int32_t)color];
			}
			st::Texture& File_Loader::Load_PNG(const wchar_t* file_location) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_PNG };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				BYTE* image_data{ nullptr };
				// Length / Width of image
				uint32_t width{ 0 };
				uint32_t height{ 0 };
				// Result
				st::Texture* texture{ nullptr };

				std::string char_file_location = TO_STRING(file_location);
				// Check if the texture has been loaded before
				// If it has then copy the info into the texture and send it
				// on its way.
				std::wstring processed_wstr{ file_location };
				size_t last_slash = OFF(processed_wstr.find_last_of(L'/'));
				processed_wstr.erase(0, last_slash);
				size_t period = processed_wstr.find_first_of(L".");
				processed_wstr.erase(period, processed_wstr.size() - period);
				if (texture_repository.count(FIF_PNG) > 0) {
					auto exists = texture_repository.at(FIF_PNG).find(processed_wstr);
					if (exists != texture_repository.at(FIF_PNG).end()) {
						size_t data_length = (TO_INT64(std::get<1>(texture_repository.at(FIF_PNG).at(processed_wstr))) * TO_INT64(std::get<2>(texture_repository.at(FIF_PNG).at(processed_wstr))));
						image_data = pw::Engine_Memory::Allocate<BYTE>(data_length * 4);

						std::copy(std::get<0>(texture_repository.at(FIF_PNG).at(processed_wstr)).begin(),
							std::get<0>(texture_repository.at(FIF_PNG).at(processed_wstr)).end(), image_data);

						texture = pw::Engine_Memory::Allocate<st::Texture>(st::Texture(image_data,
							std::get<1>(texture_repository.at(FIF_PNG).at(processed_wstr)),
							std::get<2>(texture_repository.at(FIF_PNG).at(processed_wstr)),
							GL_RGBA, GL_BGRA));
						pw::Engine_Memory::Deallocate<BYTE>(image_data);
						return *texture;
					}
				}

				// Load File
				PW_FI_VOID_CALL(TRY_LINE file = FreeImage_Load(image_type, char_file_location.c_str(), PNG_DEFAULT));

				if (!file == true) {
					throw er::Warning_Error(L"File Loader", L"Unable to load", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_Load");
				}
				if (TRY_LINE FreeImage_HasPixels(file) == (BOOL)true) {
					// If successful get data
					image_data = FreeImage_GetBits(file);

					width = FreeImage_GetWidth(file);
					height = FreeImage_GetHeight(file);

					// Create Texture
					texture = pw::Engine_Memory::Allocate<st::Texture>(st::Texture(image_data, width, height, GL_RGBA, GL_BGRA));

					if (texture_repository.count(FIF_PNG) > 0) {
						texture_repository.at(FIF_PNG).insert(std::make_pair(processed_wstr, std::make_tuple(std::vector<BYTE>(image_data, image_data + (TO_INT64(width) * TO_INT64(height) * TO_INT64(FreeImage_GetBPP(file) / 8))), width, height)));
					}
					else {
						std::map<std::wstring, std::tuple<std::vector<BYTE>, uint32_t, uint32_t>> map{};
						map.insert(std::make_pair(processed_wstr, std::make_tuple(std::vector<BYTE>(image_data, image_data  + (TO_INT64(width) * TO_INT64(height) * TO_INT64(FreeImage_GetBPP(file) / 8))), width, height)));
						texture_repository.insert(std::make_pair(FIF_PNG, map));
					}

					FreeImage_Unload(file);

					return *texture;
				}
				else {
					throw er::Warning_Error(L"File Loader", L"No Pixel Data", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_HasPixels");
				}
			}
			st::Texture& File_Loader::Load_BMP(const wchar_t* file_location) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_BMP };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				BYTE* image_data{ nullptr };
				// Length / Width of image
				uint32_t width{ 0 };
				uint32_t height{ 0 };
				// Result
				st::Texture* texture{ nullptr };

				std::string char_file_location = TO_STRING(file_location);

				// Load File
				PW_FI_VOID_CALL(TRY_LINE file = FreeImage_Load(image_type, char_file_location.c_str(), BMP_DEFAULT));

				if (!file == true) {
					throw er::Warning_Error(L"File Loader", L"Unable to load", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_Load");
				}
				if (TRY_LINE FreeImage_HasPixels(file) == (BOOL)true) {
					// If successful get data
					image_data = FreeImage_GetBits(file);

					width = FreeImage_GetWidth(file);
					height = FreeImage_GetHeight(file);

					// Create Texture
					texture = pw::Engine_Memory::Allocate<st::Texture>(st::Texture(image_data, width, height, GL_RGB, GL_BGR));

					FreeImage_Unload(file);

					return *texture;
				}
				else {
					throw er::Warning_Error(L"File Loader", L"No Pixel Data", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_HasPixels");
				}
			}
			st::Texture& File_Loader::Load_JPEG(const wchar_t* file_location) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_JPEG };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				BYTE* image_data{ nullptr };
				// Length / Width of image
				uint32_t width{ 0 };
				uint32_t height{ 0 };
				// Result
				st::Texture* texture{ nullptr };

				std::string char_file_location = TO_STRING(file_location);

				// Load File
				PW_FI_VOID_CALL(TRY_LINE file = FreeImage_Load(image_type, char_file_location.c_str(), JPEG_DEFAULT));

				if (!file == true) {
					throw er::Warning_Error(L"File Loader", L"Unable to load", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_Load");
				}
				if (TRY_LINE FreeImage_HasPixels(file) == (BOOL)true) {
					// If successful get data
					image_data = FreeImage_GetBits(file);

					width = FreeImage_GetWidth(file);
					height = FreeImage_GetHeight(file);

					// Create Texture
					texture = pw::Engine_Memory::Allocate<st::Texture>(st::Texture(image_data, width, height, GL_RGB, GL_BGR));

					FreeImage_Unload(file);

					return *texture;
				}
				else {
					throw er::Warning_Error(L"File Loader", L"No Pixel Data", std::move(EXCEPTION_LINE), __FILEW__, L"FreeImage_HasPixels");
				}
			}
			PW_PROJECT_FILE File_Loader::Load_Project_File(const wchar_t* file_location, std::wstring path_to_animations, std::wstring path_to_data,
				std::wstring path_to_fonts, std::wstring path_to_icon, std::wstring path_to_linker_files, std::wstring path_to_textures) {

				bool v_loaded_project{ false };
				std::string v_project_name{};
				std::string v_scene_loading{};

				std::string v_char_file_location = TO_STRING(file_location);

				io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					file_reader{ v_char_file_location.c_str() };
				file_reader.read_header(io::ignore_extra_column,
					"Project_Name", "Scene_Loading");
				while (file_reader.read_row(v_project_name, v_scene_loading)) {
					break;
				}

				v_loaded_project = true;

				loaded_project = v_loaded_project;
				
				animation_location = path_to_animations;
				data_location = path_to_data;
				font_location = path_to_fonts;
				icon_location = path_to_icon;
				linker_location = path_to_linker_files;
				texture_location = path_to_textures;

				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

				std::wstring vw_project_name{ converter.from_bytes(v_project_name) };

				std::string v_scene_name{};
				uint32_t v_set_current{ 0 };
				std::vector<std::tuple<std::wstring, bool>> v_scenes{};		
															 
				v_scene_loading.insert(0, TO_STRING(path_to_linker_files) + "/");
				v_scene_loading.append(".csv");

				io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					scene_reader{ v_scene_loading.c_str() };
				scene_reader.read_header(io::ignore_extra_column,
					"Scene_Name", "Set_Current");
				while (scene_reader.read_row(v_scene_name, v_set_current)) {
					v_scenes.push_back(std::make_tuple(converter.from_bytes(v_scene_name), (bool)v_set_current));
				}

				return std::tuple<bool, std::wstring, std::vector<std::tuple<std::wstring, bool>>>(v_loaded_project, vw_project_name, v_scenes);
			}
			st::Game_Scene* File_Loader::Load_Scene_File(const wchar_t* file_name) {
				std::string v_data_name{};
				std::string v_input_name{};
				std::string v_event_name{};
				uint32_t v_has_physics_factory{ 0 };
				float v_gravity_x{ 0.0f };
				float v_gravity_y{ 0.0f };
				uint32_t v_velocity_it{ 0 };
				uint32_t v_position_it{ 0 };

				std::string v_location{ TO_STRING(file_name) };

				v_location.insert(0, "/");
				v_location.insert(0, TO_STRING(data_location.c_str()));

				v_location.append(".csv");

				io::CSVReader<8, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					file_header_reader{ v_location.c_str() };
				file_header_reader.read_header(io::ignore_extra_column, "Data_Name","Input_Name", "Event_Name", "Has_Physics", "Gravity_x", "Gravity_y", "Velocity_It", "Position_It");
				while (file_header_reader.read_row(v_data_name, v_input_name, v_event_name, v_has_physics_factory, v_gravity_x, v_gravity_y, v_velocity_it, v_position_it)) {
					break;
				}
				std::string v_data_location{ v_location.c_str() };
				size_t v_last_slash = v_data_location.find_last_of("/");
				size_t v_last_v = v_data_location.find_last_of("v");

				std::string	v_cscene_name{ v_data_location.substr(OFF(v_last_slash), v_last_v - v_last_slash) };

				v_data_location.erase(OFF(v_last_slash), v_last_v - v_last_slash);

				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				std::wstring v_wscene_name{ converter.from_bytes(v_cscene_name) };
				st::Pysics_Factory* v_physics_factory = nullptr;
				if (v_has_physics_factory == 1) {
					v_physics_factory = pw::Engine_Memory::Allocate<st::Pysics_Factory>(st::Pysics_Factory(b2Vec2(v_gravity_x, v_gravity_y), v_velocity_it, v_position_it, 1.0f / 144.0f));
				}

				std::vector<PW_SRD_PTR(st::Scene_Model)> scene_models;
				std::vector<PW_SRD_PTR(st::Actor_Model)> v_collision_models;


				int32_t v_layer{ 0 };
				std::string v_s_id{};
				uint32_t v_is_text{ 0 };
				std::string v_font_type{};
				std::string v_texture{};
				uint32_t v_mesh_type{ 0 };
				int32_t v_color_id{ 0 };
				uint32_t v_color_r{ 0 };
				uint32_t v_color_b{ 0 };
				uint32_t v_color_g{ 0 };
				uint32_t v_color_a{ 0 };
				uint32_t v_position_x{ 0 };
				uint32_t v_position_y{ 0 };
				uint32_t v_rotation{ 0 };
				uint32_t v_size_x{ 0 };
				uint32_t v_size_y{ 0 };
				std::string v_model_type{};
				uint32_t v_is_animated{ 0 };
				uint32_t v_has_animation_extention{ 0 };
				float v_animation_length{ 0.0f };
				uint32_t v_animation_frame_count{ 0 };
				uint32_t v_animation_frame_size_x{ 0 };
				uint32_t v_has_physics{ 0 };
				std::string v_body_type{};
				uint32_t v_is_fixed{ 0 };

				std::vector<std::tuple<std::wstring, st::Actor_Model*>> v_s_id_holder{};

				v_location.erase(OFF(v_last_slash), v_last_v);
				v_location.insert(OFF(v_last_slash), v_data_name.c_str());
				v_location.append(".csv");

				io::CSVReader<25, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
					file_data_reader{ v_location.c_str() };
				file_data_reader.read_header(io::ignore_extra_column,
					"Layer", "S_ID", "Is_Text", "Font_Type", "Texture", "Mesh_Type", "Color_ID",
					"ColorR", "ColorB", "ColorG", "ColorA",
					"PositionX", "PositionY", "Rotation", "SizeX", "SizeY", "Model_Type",
					"Is_Animated", "Has_Animation_Extention", "Animation_Length", "Animation_Frame_Count", "Animation_Frame_Size_X",
					"Has_Physics", "Body_Type", "Is_Fixed");
				while (file_data_reader.read_row(v_layer, v_s_id, v_is_text, v_font_type, v_texture, v_mesh_type, v_color_id, v_color_r, v_color_b, v_color_g, v_color_a,
					v_position_x, v_position_y, v_rotation, v_size_x, v_size_y, v_model_type, v_is_animated, v_has_animation_extention,
					v_animation_length, v_animation_frame_count, v_animation_frame_size_x, v_has_physics, v_body_type, v_is_fixed)) {

					// Possible Animation cache
					std::vector<std::tuple<PW_SRD_PTR(st::Animation), st::Texture*>> v_animations{};
					std::vector<std::wstring> v_animation_ids{};
					bool v_animation_cache{ false };

					st::Texture* model_texture = nullptr;
					st::Text* v_model_text = nullptr;
					st::Font v_font_id = st::Font::PW_FONT_COUNT;


					if ((bool)v_is_text == true) {
						if (v_font_type == "CAMBRIA") {
							v_font_id = st::Font::PW_CAMBRIA;
						}
						else {
							if (v_font_type == "ARIAL") {
								v_font_id = st::Font::PW_ARIAL;
							}
							else {
								if (v_font_type == "ROBOTO") {
									v_font_id = st::Font::PW_ROBOTO;
								}
							}
						}
					}

					// Is it a static or dynamic model
					if (strcmp(v_model_type.c_str(), "s") == 0) {
						// Test for animations
						if (v_is_animated == 1) {
							PW_SRD_PTR(st::Animation) v_model_animation {};
							// Test for gif animation types
							if (v_has_animation_extention == 1) {
								std::string v_extension = v_texture.substr(v_texture.find_last_of("."), v_texture.size() - 1);
								if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
									throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", std::move(EXCEPTION_LINE), __FILEW__, L"Load_Animation_File");
								}
								else {
									// It is a gif and needs to be loaded
									std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
									std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str());
									model_texture = v_model_animation_structure._Myfirst._Val;
									v_model_animation = std::make_shared<st::Animation>(*v_model_animation_structure._Get_rest()._Myfirst._Val);
									pw::Engine_Memory::Deallocate<st::Animation>(v_model_animation_structure._Get_rest()._Myfirst._Val);
								}
							}
							else {
								// Is not a gif but a sprite-sheet of some kind
								std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
								model_texture = &co::File_Loader::Load_Texture_File(v_texture_location.c_str(), false, animation_location.c_str());

								v_model_animation = std::make_shared<st::Animation>(st::Animation(
									v_animation_length, v_animation_frame_count, v_animation_frame_size_x));
							}
							if (v_animations.size() > 0) {
								model_texture = v_animations.at(0)._Get_rest()._Myfirst._Val;
							}

							// Test for color
							if (v_color_id > -1) {
								// It has a loadable default color
								glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

								if ((bool)v_is_text == true) {
									v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_STATIC, v_font_id));
									v_size_x = TO_UINT32(v_model_text->Size().x);
								}

								PW_SRD_PTR(st::Static_Model) vs_model { pw::Engine_Memory::Allocate<st::Static_Model>() };
								*vs_model = st::Static_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
								PW_SRD_PTR(st::AAsset_Model) va_model {};
								if (v_animation_cache == true) {
									for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
										i->_Myfirst._Val.get()->Finish_Init(vs_model.get()->Model_Mesh().get()->Vertices(), vs_model.get()->Model_Mesh().get()->Vertex_Count());
									}

									va_model = PW_SRD_PTR(st::AAsset_Model)(pw::Engine_Memory::Allocate<st::AAsset_Model>(st::AAsset_Model(vs_model, v_animations, v_animation_ids, v_layer)));
								}
								else {
									v_model_animation->Finish_Init(vs_model.get()->Model_Mesh().get()->Vertices(), vs_model.get()->Model_Mesh().get()->Vertex_Count());

									va_model = PW_SRD_PTR(st::AAsset_Model)(pw::Engine_Memory::Allocate<st::AAsset_Model>(st::AAsset_Model(vs_model, v_model_animation, v_layer)));
								}
								scene_models.push_back(va_model);
							}
							else {
								if (v_color_id == -2) {
									// It is textured and has no color
									PW_SRD_PTR(st::Static_Model) vs_model { pw::Engine_Memory::Allocate<st::Static_Model>() };
									*vs_model = st::Static_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y));
									PW_SRD_PTR(st::AAsset_Model) va_model {};
									if (v_animation_cache == true) {
										for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
											i->_Myfirst._Val.get()->Finish_Init(vs_model.get()->Model_Mesh().get()->Vertices(), vs_model.get()->Model_Mesh().get()->Vertex_Count());
										}

										va_model = PW_SRD_PTR(st::AAsset_Model)(pw::Engine_Memory::Allocate<st::AAsset_Model>(st::AAsset_Model(vs_model, v_animations, v_animation_ids, v_layer)));
									}
									else {
										v_model_animation->Finish_Init(vs_model.get()->Model_Mesh().get()->Vertices(), vs_model.get()->Model_Mesh().get()->Vertex_Count());

										va_model = PW_SRD_PTR(st::AAsset_Model)(pw::Engine_Memory::Allocate<st::AAsset_Model>(st::AAsset_Model(vs_model, v_model_animation, v_layer)));
									}
									scene_models.push_back(va_model);
								}
								else {
									// It has a custom color
									glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_b / 255.0f, (float)v_color_g / 255.0f, (float)v_color_a / 255.0f);

									if ((bool)v_is_text == true) {
										v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_STATIC, v_font_id));
										v_size_x = TO_UINT32(v_model_text->Size().x);
									}

									PW_SRD_PTR(st::Static_Model) vs_model { pw::Engine_Memory::Allocate<st::Static_Model>() };
									*vs_model = st::Static_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
									PW_SRD_PTR(st::AAsset_Model) va_model {};
									if (v_animation_cache == true) {
										for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
											i->_Myfirst._Val.get()->Finish_Init(vs_model.get()->Model_Mesh().get()->Vertices(), vs_model.get()->Model_Mesh().get()->Vertex_Count());
										}

										va_model = PW_SRD_PTR(st::AAsset_Model)(pw::Engine_Memory::Allocate<st::AAsset_Model>(st::AAsset_Model(vs_model, v_animations, v_animation_ids, v_layer)));
									}
									else {
										v_model_animation->Finish_Init(vs_model.get()->Model_Mesh().get()->Vertices(), vs_model.get()->Model_Mesh().get()->Vertex_Count());

										va_model = PW_SRD_PTR(st::AAsset_Model)(pw::Engine_Memory::Allocate<st::AAsset_Model>(st::AAsset_Model(vs_model, v_model_animation, v_layer)));
									}
									scene_models.push_back(va_model);
								}
							}
						}
						else {
							if ((bool)v_is_text == false) {
								// Does not have animations
								if (strcmp(v_texture.c_str(), "D16") == 0) {
									model_texture = &co::File_Loader::Load_Texture_File(L"White.png", true, nullptr);
								}
								else {
									std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
									model_texture = &co::File_Loader::Load_Texture_File(v_texture_location.c_str(), false, nullptr);
								}
							}
							else {
								model_texture = &co::File_Loader::Load_Texture_File(L"Empty.png", true, nullptr);
							}
							// Test for color
							if (v_color_id > -1) { // Default color is > -1
								glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

								if ((bool)v_is_text == true) {
									v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_STATIC, v_font_id));
									v_size_x = TO_UINT32(v_model_text->Size().x);
								}

								PW_SRD_PTR(st::Static_Model) vs_model { pw::Engine_Memory::Allocate<st::Static_Model>() };
								*vs_model = st::Static_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
								PW_SRD_PTR(st::Asset_Model) va_model { pw::Engine_Memory::Allocate<st::Asset_Model>(st::Asset_Model(vs_model, v_model_text, v_layer)) };
								scene_models.push_back(va_model);
							}
							else {
								if (v_color_id == -2) { // No color or texture is > -2
									PW_SRD_PTR(st::Static_Model) vs_model { pw::Engine_Memory::Allocate<st::Static_Model>() };
									*vs_model = st::Static_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y));
									PW_SRD_PTR(st::Asset_Model) va_model { pw::Engine_Memory::Allocate<st::Asset_Model>(st::Asset_Model(vs_model, v_model_text, v_layer)) };
									scene_models.push_back(va_model);
								}
								else { // -3 or any other number is for a custom color
									glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_b / 255.0f, (float)v_color_g / 255.0f, (float)v_color_a / 255.0f);

									v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_STATIC, v_font_id));

									PW_SRD_PTR(st::Static_Model) vs_model { pw::Engine_Memory::Allocate<st::Static_Model>() };
									*vs_model = st::Static_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
									PW_SRD_PTR(st::Asset_Model) va_model { pw::Engine_Memory::Allocate<st::Asset_Model>(st::Asset_Model(vs_model, v_model_text, v_layer)) };
									scene_models.push_back(va_model);
								}
							}
						}
					}
					else {
						if (strcmp(v_model_type.c_str(), "d") == 0) {
							// Test for animations
							if (v_is_animated == 1) {
								PW_SRD_PTR(st::Animation) v_model_animation {};
								// Test for gif animation types
								if (v_has_animation_extention == 1) {
									std::string v_extension = v_texture.substr(v_texture.find_last_of("."), v_texture.size() - 1);
									if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
										// Test for .csv animation cache
										if (TRY_LINE strcmp(v_extension.c_str(), ".csv") != 0) {
											throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", std::move(EXCEPTION_LINE), __FILEW__, L"Load_Animation_File");
										}
										else {
											// Load the .csv file for the animation cache
											v_texture.insert(0, TO_STRING(data_location + L"/"));
											v_animation_cache = true;

											std::string v_animation_id{};
											std::string v_animation_location{};

											io::CSVReader<6, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
												animation_data_reader{ v_texture.c_str() };
											animation_data_reader.read_header(io::ignore_extra_column,
												"Animation_ID", "Animation", "Has_Animation_Extention", "Animation_Length",
												"Animation_Frame_Count", "Animation_Frame_Size_X");
											while (animation_data_reader.read_row(v_animation_id, v_animation_location, v_has_animation_extention, v_animation_length, v_animation_frame_count, v_animation_frame_size_x)) {

												if (v_has_animation_extention == 1) {
													std::string v_extension = v_animation_location.substr(v_animation_location.find_last_of("."), v_animation_location.size() - 1);
													if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
														throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", std::move(EXCEPTION_LINE), __FILEW__, L"Load_Animation_File");
													}
													else {
														// It is a gif and needs to be loaded
														std::wstring v_texture_location{ TO_WSTRING(v_animation_location.c_str()) };
														std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str());
														model_texture = v_model_animation_structure._Myfirst._Val;
														v_model_animation = std::make_shared<st::Animation>(*v_model_animation_structure._Get_rest()._Myfirst._Val);
														pw::Engine_Memory::Deallocate<st::Animation>(v_model_animation_structure._Get_rest()._Myfirst._Val);
													}
												}
												else {
													// Is not a gif but a sprite-sheet of some kind
													std::wstring v_texture_location{ TO_WSTRING(v_animation_location.c_str()) };
													model_texture = &co::File_Loader::Load_Texture_File(v_texture_location.c_str(), false, animation_location.c_str());

													v_model_animation = std::make_shared<st::Animation>(st::Animation(
														v_animation_length, v_animation_frame_count, v_animation_frame_size_x));
												}
												v_animations.push_back(std::make_tuple(v_model_animation, model_texture));
												v_animation_ids.push_back(TO_WSTRING(v_animation_id));
											}
										}
									}
									else {
										// It is a gif and needs to be loaded
										std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
										std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str());
										model_texture = v_model_animation_structure._Myfirst._Val;
										v_model_animation = std::make_shared<st::Animation>(*v_model_animation_structure._Get_rest()._Myfirst._Val);
										pw::Engine_Memory::Deallocate<st::Animation>(v_model_animation_structure._Get_rest()._Myfirst._Val);
									}
								}
								else {
									// Is not a gif but a sprite-sheet of some kind
									std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
									model_texture = &co::File_Loader::Load_Texture_File(v_texture_location.c_str(), false, animation_location.c_str());

									v_model_animation = std::make_shared<st::Animation>(st::Animation(
										v_animation_length, v_animation_frame_count, v_animation_frame_size_x));
								}
								if (v_animations.size() > 0) {
									model_texture = v_animations.at(0)._Get_rest()._Myfirst._Val;
								}
								// Test for color
								if (v_color_id > -1) {
									// It has a loadable default color
									glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

									if ((bool)v_is_text == true) {
										v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_DYNAMIC, v_font_id));
										v_size_x = TO_UINT32(v_model_text->Size().x);
									}

									PW_SRD_PTR(st::Dynamic_Model) vd_model { pw::Engine_Memory::Allocate<st::Dynamic_Model>() };
									*vd_model = st::Dynamic_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
									PW_SRD_PTR(st::AActor_Model) va_model {};
									if (v_animation_cache == true) {
										for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
											i->_Myfirst._Val.get()->Finish_Init(vd_model.get()->Model_Mesh().get()->Vertices(), vd_model.get()->Model_Mesh().get()->Vertex_Count());
										}

										va_model = PW_SRD_PTR(st::AActor_Model)(pw::Engine_Memory::Allocate<st::AActor_Model>(st::AActor_Model(vd_model, v_animations, v_animation_ids, v_layer)));
									}
									else {
										v_model_animation->Finish_Init(vd_model.get()->Model_Mesh().get()->Vertices(), vd_model.get()->Model_Mesh().get()->Vertex_Count());

										va_model = PW_SRD_PTR(st::AActor_Model)(pw::Engine_Memory::Allocate<st::AActor_Model>(st::AActor_Model(vd_model, v_model_animation, v_layer)));
									}

									if (v_s_id != "NULL") {
										std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

										std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

										v_s_id_holder.push_back(std::make_tuple(vw_s_id, &*va_model));
									}

									if (v_has_physics_factory == 1) {
										if (v_has_physics == 1) {
											if (v_body_type == "b2_staticBody") {
												v_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, vd_model.get()->Id(), v_is_fixed);
											}
											else {
												if (v_body_type == "b2_dynamicBody") {
													v_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, vd_model.get()->Id(), v_is_fixed);
													va_model.get()->Set_Poly_Body(v_physics_factory->Access_Memeber(vd_model.get()->Id())->Body());
												}
											}
										}
										v_collision_models.push_back(va_model);
									}

									scene_models.push_back(va_model);
								}
								else {
									if (v_color_id == -2) {
										// It is textured and has no color
										PW_SRD_PTR(st::Dynamic_Model) vd_model { pw::Engine_Memory::Allocate<st::Dynamic_Model>() };
										*vd_model = st::Dynamic_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y));
										PW_SRD_PTR(st::AActor_Model) va_model {};
										if (v_animation_cache == true) {
											for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
												i->_Myfirst._Val.get()->Finish_Init(vd_model.get()->Model_Mesh().get()->Vertices(), vd_model.get()->Model_Mesh().get()->Vertex_Count());
											}

											va_model = PW_SRD_PTR(st::AActor_Model)(pw::Engine_Memory::Allocate<st::AActor_Model>(st::AActor_Model(vd_model, v_animations, v_animation_ids, v_layer)));
										}
										else {
											v_model_animation->Finish_Init(vd_model.get()->Model_Mesh().get()->Vertices(), vd_model.get()->Model_Mesh().get()->Vertex_Count());

											va_model = PW_SRD_PTR(st::AActor_Model)(pw::Engine_Memory::Allocate<st::AActor_Model>(st::AActor_Model(vd_model, v_model_animation, v_layer)));
										}

										if (v_s_id != "NULL") {
											std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

											std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

											v_s_id_holder.push_back(std::make_tuple(vw_s_id, &*va_model));
										}

										if (v_has_physics_factory == 1) {
											if (v_has_physics == 1) {
												if (v_body_type == "b2_staticBody") {
													v_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, vd_model.get()->Id(), v_is_fixed);
												}
												else {
													if (v_body_type == "b2_dynamicBody") {
														v_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, vd_model.get()->Id(), v_is_fixed);
														va_model.get()->Set_Poly_Body(v_physics_factory->Access_Memeber(vd_model.get()->Id())->Body());
													}
												}
											}
											v_collision_models.push_back(va_model);
										}

										scene_models.push_back(va_model);
									}
									else {
										// It has a custom color
										glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_b / 255.0f, (float)v_color_g / 255.0f, (float)v_color_a / 255.0f);

										if ((bool)v_is_text == true) {
											v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_DYNAMIC, v_font_id));
											v_size_x = TO_UINT32(v_model_text->Size().x);
										}

										PW_SRD_PTR(st::Dynamic_Model) vd_model { pw::Engine_Memory::Allocate<st::Dynamic_Model>()};
										*vd_model = st::Dynamic_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
										PW_SRD_PTR(st::AActor_Model) va_model {};
										if (v_animation_cache == true) {
											for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
												i->_Myfirst._Val.get()->Finish_Init(vd_model.get()->Model_Mesh().get()->Vertices(), vd_model.get()->Model_Mesh().get()->Vertex_Count());
											}

											va_model = PW_SRD_PTR(st::AActor_Model)(pw::Engine_Memory::Allocate<st::AActor_Model>(st::AActor_Model(vd_model, v_animations, v_animation_ids, v_layer)));
										}
										else {
											v_model_animation->Finish_Init(vd_model.get()->Model_Mesh().get()->Vertices(), vd_model.get()->Model_Mesh().get()->Vertex_Count());

											va_model = PW_SRD_PTR(st::AActor_Model)(pw::Engine_Memory::Allocate<st::AActor_Model>(st::AActor_Model(vd_model, v_model_animation, v_layer)));
										}
										
										if (v_s_id != "NULL") {
											std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

											std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

											v_s_id_holder.push_back(std::make_tuple(vw_s_id, &*va_model));
										}

										if (v_has_physics_factory == 1) {
											if (v_has_physics == 1) {
												if (v_body_type == "b2_staticBody") {
													v_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, vd_model.get()->Id(), v_is_fixed);
												}
												else {
													if (v_body_type == "b2_dynamicBody") {
														v_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, vd_model.get()->Id(), v_is_fixed);
														va_model.get()->Set_Poly_Body(v_physics_factory->Access_Memeber(vd_model.get()->Id())->Body());
													}
												}
											}
											v_collision_models.push_back(va_model);
										}

										scene_models.push_back(va_model);
									}
								}
							}
							else {
								if ((bool)v_is_text == false) {
									// Does not have animations
									if (strcmp(v_texture.c_str(), "D16") == 0) {
										model_texture = &co::File_Loader::Load_Texture_File(L"White.png", true, nullptr);
									}
									else {
										std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
										model_texture = &co::File_Loader::Load_Texture_File(v_texture_location.c_str(), false, nullptr);
									}
								}
								else {
									model_texture = &co::File_Loader::Load_Texture_File(L"Empty.png", true, nullptr);
								}
								// Test for color
								if (v_color_id > -1) { // Default color is > -1
									glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

									if ((bool)v_is_text == true) {
										v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_DYNAMIC, v_font_id));
										v_size_x = TO_UINT32(v_model_text->Size().x);
									}

									PW_SRD_PTR(st::Dynamic_Model) vd_model { pw::Engine_Memory::Allocate<st::Dynamic_Model>() };
									*vd_model = st::Dynamic_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
									PW_SRD_PTR(st::Actor_Model) va_model { pw::Engine_Memory::Allocate<st::Actor_Model>(st::Actor_Model(vd_model, v_model_text, v_layer)) };

									if (v_s_id != "NULL") {
										std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

										std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

										v_s_id_holder.push_back(std::make_tuple(vw_s_id, &*va_model));
									}

									if (v_has_physics_factory == 1) {
										if (v_has_physics == 1) {
											if (v_body_type == "b2_staticBody") {
												v_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, vd_model.get()->Id(), v_is_fixed);
											}
											else {
												if (v_body_type == "b2_dynamicBody") {
													v_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, vd_model.get()->Id(), v_is_fixed);
													va_model.get()->Set_Poly_Body(v_physics_factory->Access_Memeber(vd_model.get()->Id())->Body());
												}
											}
										}
										v_collision_models.push_back(va_model);
									}

									scene_models.push_back(va_model);
								}
								else {
									if (v_color_id == -2) { // No color or texture is > -2
										PW_SRD_PTR(st::Dynamic_Model) vd_model { pw::Engine_Memory::Allocate<st::Dynamic_Model>() };
										*vd_model = st::Dynamic_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y));
										PW_SRD_PTR(st::Actor_Model) va_model { pw::Engine_Memory::Allocate<st::Actor_Model>(st::Actor_Model(vd_model, v_model_text, v_layer)) };

										if (v_s_id != "NULL") {
											std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

											std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

											v_s_id_holder.push_back(std::make_tuple(vw_s_id, &*va_model));
										}

										if (v_has_physics_factory == 1) {
											if (v_has_physics == 1) {
												if (v_body_type == "b2_staticBody") {
													v_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, vd_model.get()->Id(), v_is_fixed);
												}
												else {
													if (v_body_type == "b2_dynamicBody") {
														v_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, vd_model.get()->Id(), v_is_fixed);
														va_model.get()->Set_Poly_Body(v_physics_factory->Access_Memeber(vd_model.get()->Id())->Body());
													}
												}
											}
											v_collision_models.push_back(va_model);
										}

										scene_models.push_back(va_model);
									}
									else { // -3 or any other number is for a custom color
										glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_b / 255.0f, (float)v_color_g / 255.0f, (float)v_color_a / 255.0f);

										if ((bool)v_is_text == true) {
											v_model_text = pw::Engine_Memory::Allocate<st::Text>(st::Text(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, PW_DYNAMIC, v_font_id));
											v_size_x = TO_UINT32(v_model_text->Size().x);
										}

										PW_SRD_PTR(st::Dynamic_Model) vd_model { pw::Engine_Memory::Allocate<st::Dynamic_Model>()};
										*vd_model = st::Dynamic_Model((st::Mesh_Types)v_mesh_type, model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color);
										PW_SRD_PTR(st::Actor_Model) va_model { pw::Engine_Memory::Allocate<st::Actor_Model>(st::Actor_Model(vd_model, v_model_text, v_layer)) };
										
										if (v_s_id != "NULL") {
											std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

											std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

											v_s_id_holder.push_back(std::make_tuple(vw_s_id, &*va_model));
										}

										if (v_has_physics_factory == 1) {
											if (v_has_physics == 1) {
												if (v_body_type == "b2_staticBody") {
													v_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, vd_model.get()->Id(), v_is_fixed);
												}
												else {
													if (v_body_type == "b2_dynamicBody") {
														v_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, vd_model.get()->Id(), v_is_fixed);
														va_model.get()->Set_Poly_Body(v_physics_factory->Access_Memeber(vd_model.get()->Id())->Body());
													}
												}
											}
											v_collision_models.push_back(va_model);
										}

										scene_models.push_back(va_model);
									}
								}
							}
						}
					}
				}
				co::Engine_Input* v_scene_input = nullptr;

				if (v_input_name != "NULL") {

					v_scene_input = pw::Engine_Memory::Allocate<Engine_Input>();
					
					v_last_v = v_location.find_last_of("v");
					v_location.erase(OFF(v_last_slash), v_last_v);
					v_location.insert(OFF(v_last_slash), v_input_name.c_str());
					v_location.append(".csv");

					std::string v_input_type{};
					std::string v_input_event{};
					int32_t button_code{ 0 };
					std::string v_function_name{};
					int32_t v_play_once{ 0 };

					io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
						file_data_reader{ v_location.c_str() };
					file_data_reader.read_header(io::ignore_extra_column, "Input_Type", "Input_Event", "Button_Code", "Function_Name", "Play_Once");
					while (file_data_reader.read_row(v_input_type, v_input_event, button_code, v_function_name, v_play_once)) {
						if (v_input_type == "KEYBOARD") {
							if (v_input_event == "PRESS") {
								v_scene_input->Create_Event_Keyboard(GLFW_PRESS, button_code, co::Engine_Input::Access_Function(v_function_name), v_play_once);
							}
							else {
								if (v_input_event == "RELEASE") {
									v_scene_input->Create_Event_Keyboard(GLFW_RELEASE, button_code, co::Engine_Input::Access_Function(v_function_name), v_play_once);
								}
								else {
									if (v_input_event == "REPEAT") {
										v_scene_input->Create_Event_Keyboard(GLFW_REPEAT, button_code, co::Engine_Input::Access_Function(v_function_name), v_play_once);
									}
								}
							}
						}
						else {
							if (v_input_type == "MOUSE") {
								if (v_input_event == "PRESS") {
									v_scene_input->Create_Event_Mouse(GLFW_PRESS, button_code, co::Engine_Input::Access_Function(v_function_name), v_play_once);
								}
								else {
									if (v_input_event == "RELEASE") {
										v_scene_input->Create_Event_Mouse(GLFW_RELEASE, button_code, co::Engine_Input::Access_Function(v_function_name), v_play_once);
									}
									else {
										if (v_input_event == "REPEAT") {
											v_scene_input->Create_Event_Mouse(GLFW_REPEAT, button_code, co::Engine_Input::Access_Function(v_function_name), v_play_once);
										}
									}
								}
							}
							else {
								if (v_input_type == "SCROLL") {
									if (v_input_event == "FORWARD") {
										v_scene_input->Create_Event_Scroll(cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD, co::Engine_Input::Access_Function(v_function_name), v_play_once);
									}
									else {
										if (v_input_event == "BACKWARDS") {
											v_scene_input->Create_Event_Scroll(cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD, co::Engine_Input::Access_Function(v_function_name), v_play_once);
										}
									}
								}
							}
						}

					}
				}

				st::Game_Scene* scene{ pw::Engine_Memory::Allocate<st::Game_Scene, bool>(v_wscene_name.c_str(), scene_models, v_collision_models, v_scene_input, v_physics_factory) };

				for (auto i = v_s_id_holder.begin(); i != v_s_id_holder.end(); i++) {
					scene->Register_S_ID(i->_Myfirst._Val, i->_Get_rest()._Myfirst._Val);
				}
				if (v_event_name != "NULL") {
					std::string v_event_type{};
					std::string v_s_id{};
					std::string v_input_event{};
					int32_t v_button_code{};
					std::string v_function_name{};
					int32_t v_play_once{};
					std::string v_model_id{};
					std::string v_arg_1{};
					std::string v_arg_2{};

					v_last_v = v_location.find_last_of("v");
					v_location.erase(OFF(v_last_slash), v_last_v);
					v_location.insert(OFF(v_last_slash), v_event_name.c_str());
					v_location.append(".csv");													 
																														
					io::CSVReader<8, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
						file_data_reader{ v_location.c_str() };
					file_data_reader.read_header(io::ignore_extra_column, "Event_Type", "Model_S_ID", "Input_Event", "Button_Code", "Function_Name", "Play_Once", "Args_1", "Args_2");
					while (file_data_reader.read_row(v_event_type, v_s_id, v_input_event, v_button_code, v_function_name, v_play_once, v_arg_1, v_arg_2)) {

						std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

						std::wstring vw_s_id{ converter.from_bytes(v_s_id) };

						if(v_event_type == "CLICK") {
							if (v_input_event == "PRESS") {
								scene->Create_Event<void>(
									cm::Engine_Constant::PW_CLICK_EVENT, v_button_code, GLFW_PRESS,
									static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
									co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
							}
							else {
								if (v_input_event == "RELEASE") {
									scene->Create_Event<void>(
										cm::Engine_Constant::PW_CLICK_EVENT, v_button_code, GLFW_RELEASE,
										static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
										co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
								}
								else {
									if (v_input_event == "REPEAT") {
										scene->Create_Event<void>(
											cm::Engine_Constant::PW_CLICK_EVENT, v_button_code, GLFW_REPEAT,
											static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
											co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
									}
								}
							}
						}
						else {
							if (v_event_type == "HOVER") {
								scene->Create_Event<void>(
									cm::Engine_Constant::PW_HOVER_EVENT, v_button_code, GLFW_PRESS,
									static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
									co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
							}
							else {
								if (v_event_type == "COLLISION") {
									// NOT IMPLEMENTED
								}
								else {
									if (v_event_type == "KEYBOARD") {
										if (v_input_event == "PRESS") {
											if (v_function_name == "CHANGE_ANIMATION") {
												scene->Create_Event<void(pw::st::AActor_Model::*)(std::wstring, bool), st::AActor_Model, void, const std::wstring, bool>(
													cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_PRESS,
													static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)), (bool)v_play_once,
													std::mem_fn(&st::AActor_Model::Change_Animation), static_cast<st::AActor_Model&>(scene->Access_Model(vw_s_id)), std::move(std::wstring(TO_WSTRING(v_arg_1.c_str()))), (bool)std::stoi(v_arg_2));
											}
											else {
												if (v_function_name == "START_ANIMATION") {
													scene->Create_Event<void(pw::st::AActor_Model::*)(), st::AActor_Model, void>(
														cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_PRESS,
														static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)), (bool)v_play_once,
														std::mem_fn(&st::AActor_Model::Start_Animation), static_cast<st::AActor_Model&>(scene->Access_Model(vw_s_id)));
												}
												else {
													if (v_function_name == "STOP_ANIMATION") {
														scene->Create_Event<void(pw::st::AActor_Model::*)(), st::AActor_Model, void>(
															cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_PRESS,
															static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)), (bool)v_play_once,
															std::mem_fn(&st::AActor_Model::Stop_Animation), static_cast<st::AActor_Model&>(scene->Access_Model(vw_s_id)));
													}
													else {
														if (v_function_name == "ADVANCE_ANIMATION") {
															scene->Create_Event<void(pw::st::AActor_Model::*)(), st::AActor_Model, void>(
																cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_PRESS,
																static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)), (bool)v_play_once,
																std::mem_fn(&st::AActor_Model::Advance_Animation), static_cast<st::AActor_Model&>(scene->Access_Model(vw_s_id)));
														}
														else {
															if (v_function_name == "ADD_SCENE") {
																scene->Create_Event<void, const std::wstring, bool>(
																	cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_PRESS,
																	static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
																	std::make_shared<std::function<void(std::wstring, bool)>>(add_scene_function), (bool)v_play_once, std::move(std::wstring(TO_WSTRING(v_arg_1.c_str()))), (bool)std::stoi(v_arg_2));
															}
															else {
																if (v_function_name == "CHANGE_SCENE") {
																	scene->Create_Event<void, const std::wstring>(
																		cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_PRESS,
																		nullptr,
																		std::make_shared<std::function<void(std::wstring)>>(change_scene_function), (bool)v_play_once, std::move(std::wstring(TO_WSTRING(v_arg_1.c_str()))));
																}
															}
														}
													}
												}
											}
										}
										else {
											if (v_input_event == "RELEASE") {
												scene->Create_Event<void>(
													cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_RELEASE,
													static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
													co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
											}
											else {
												if (v_input_event == "REPEAT") {
													scene->Create_Event<void>(
														cm::Engine_Constant::PW_KEYBOARD_EVENT, v_button_code, GLFW_REPEAT,
														static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
														co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
												}
											}
										}
									}
									else {
										if (v_event_type == "MOUSE") {
											if (v_input_event == "PRESS") {
												scene->Create_Event<void>(
													cm::Engine_Constant::PW_MOUSE_EVENT, v_button_code, GLFW_PRESS,
													static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
													co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
											}
											else {
												if (v_input_event == "RELEASE") {
													scene->Create_Event<void>(
														cm::Engine_Constant::PW_MOUSE_EVENT, v_button_code, GLFW_RELEASE,
														static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
														co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
												}
												else {
													if (v_input_event == "REPEAT") {
														scene->Create_Event<void>(
															cm::Engine_Constant::PW_MOUSE_EVENT, v_button_code, GLFW_REPEAT,
															static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
															co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
													}
												}
											}
										}
										else {
											if (v_event_type == "SCROLL") {
												if (v_input_event == "FORWARD") {
													scene->Create_Event<void>(
														cm::Engine_Constant::PW_SCROLL_EVENT, cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD, GLFW_PRESS,
														static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
														co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
												}
												else {
													if (v_input_event == "BACKWARDS") {
														scene->Create_Event<void>(
															cm::Engine_Constant::PW_SCROLL_EVENT, cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD, GLFW_PRESS,
															static_cast<st::Actor_Model*>(&scene->Access_Model(vw_s_id)),
															co::Engine_Input::Access_Function(v_function_name), (bool)v_play_once);
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
				co::Engine_Input::Set_Scene_Event_Function(scene->Event_Callback());

				return scene;
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////