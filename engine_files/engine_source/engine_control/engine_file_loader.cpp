#include "engine_control\engine_file_loader.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// File_Loader               
		// Static Declarations
			FIBITMAP* File_Loader::m_current_icon{ nullptr };

			bool File_Loader::m_loaded_project{ false };

			std::wstring File_Loader::m_animation_location{};
			std::wstring File_Loader::m_data_location{};
			std::wstring File_Loader::m_font_location{};
			std::wstring File_Loader::m_icon_location{};
			std::wstring File_Loader::m_linker_location{};
			std::wstring File_Loader::m_texture_location{};
			std::wstring File_Loader::m_sound_location{};

			std::wstring File_Loader::m_engine_texture_dir{ L"/engine_files/engine_resource/engine_essential/engine_textures" };
			std::wstring File_Loader::m_engine_icon_dir{ L"/engine_files/engine_resource/engine_essential/engine_icon" };
			std::wstring File_Loader::m_engine_animation_dir{ L"/engine_files/engine_resource/engine_essential/engine_animations" };

			std::function<void(const std::wstring&, const bool&)> File_Loader::m_add_scene_function{};
			std::function<void(const std::wstring&)> File_Loader::m_change_scene_function{};
			std::function<void(const std::wstring&)> File_Loader::m_remove_scene_function{};
			std::function<void(const std::wstring&, const std::wstring&, const bool&)> File_Loader::m_sub_scene_render{};

			std::map<std::wstring, st::Texture*>* File_Loader::m_texture_repository{ nullptr };

			glm::vec4 File_Loader::m_engine_colors[(uint32_t)Default_Colors::Color_Count]{
				//LIT_RED				#ff 80 80 
				//RED					#ff 00 00 
				//DRK_RED				#80 00 00	
				glm::vec4(1.0f,				0.5f,				0.5f,				1.0f),
				glm::vec4(1.0f,				0.0f,				0.0f,				1.0f),
				glm::vec4(0.5f,				0.0f,				0.0f,				1.0f),
				//LIT_GREEN				#80 ff 80 
				//GREEN					#00 ff 00 
				//DRK_GREEN				#00 80 00 
				glm::vec4(0.5f,				1.0f,				0.5f,				1.0f),
				glm::vec4(0.0f,				1.0f,				0.0f,				1.0f),
				glm::vec4(0.0f,				0.5f,				0.0f,				1.0f),
				//LIT_BLUE				#80 80 ff 
				//BLUE					#00 00 ff 
				//DRK_BLUE				#00 00 80
				glm::vec4(0.5f,				0.5f,				1.0f,				1.0f),
				glm::vec4(0.0f,				0.0f,				1.0f,				1.0f),
				glm::vec4(0.0f,				0.0f,				0.5f,				1.0f),
				//LIT_YELLOW			#ff ff 80 
				//YELLOW				#ff ff 00 
				//DRK_YELLOW			#80 80 00
				glm::vec4(1.0f,				1.0f,				0.5f,				1.0f),
				glm::vec4(1.0f,				1.0f,				0.0f,				1.0f),
				glm::vec4(0.5f,				0.5f,				0.0f,				1.0f),
				//LIT_PINK				#ff 80 ff 
				//PINK					#ff 00 ff 
				//DRK_PINK				#80 00 80
				glm::vec4(1.0f,				0.5f,				1.0f,				1.0f),
				glm::vec4(1.0f,				0.0f,				1.0f,				1.0f),
				glm::vec4(0.5f,				0.0f,				0.5f,				1.0f),
				//LIT_CYAN				#80 ff ff 
				//CYAN					#00 ff ff 
				//DRK_CYAN				#00 80 80
				glm::vec4(0.5f,				1.0f,				1.0f,				1.0f),
				glm::vec4(0.0f,				1.0f,				1.0f,				1.0f),
				glm::vec4(0.0f,				0.5f,				0.5f,				1.0f),
				//LIT_LIME				#80 ff 80 
				//LIME					#80 ff 00 
				//DRK_LIME				#40 80 00
				glm::vec4(0.5f,				1.0f,				0.5f,				1.0f),
				glm::vec4(0.5f,				1.0f,				0.0f,				1.0f),
				glm::vec4(0.25f,			0.5f,				0.0f,				1.0f),
				//LIT_ORANGE			#ff bf 80 
				//ORANGE				#ff 80 00 
				//DRK_ORANGE			#cc 60 00
				glm::vec4(1.0f,				191.0f / 255.0f,	0.5f,				1.0f),
				glm::vec4(1.0f,				0.5f,				0.0f,				1.0f),
				glm::vec4(204.0f / 255.0f,	96.0f / 255.0f,		0.0f,				1.0f),
				//LIT_AZURE				#80 bf ff 
				//AZURE					#00 80 ff 
				//DRK_AZURE				#00 40 80
				glm::vec4(0.5f,				191.0f / 255.0f,	1.0f,				1.0f),
				glm::vec4(0.0f,				0.5f,				1.0f,				1.0f),
				glm::vec4(0.0f,				0.25f,				0.5f,				1.0f),
				//LIT_PURPLE			#bf 80 ff 
				//PURPLE				#80 00 ff 
				//DRK_PURPLE			#40 00 80
				glm::vec4(191.0f / 255.0f,	0.5f,				1.0f,				1.0f),
				glm::vec4(0.5f,				0.0f,				1.0f,				1.0f),
				glm::vec4(0.25f,			0.0f,				0.5f,				1.0f),
				//LIT_BROWN				#80 5c 40 
				//BROWN					#80 40 00 
				//DRK_BROWN				#40 20 00
				glm::vec4(0.5f,				92.0f / 255.0f,		0.25f,				1.0f),
				glm::vec4(0.5f,				0.25f,				0.0f,				1.0f),
				glm::vec4(0.25f,			0.125f,				0.0f,				1.0f),
				//LIT_GREY				#c0 c0 c0
				//GREY					#80 80 80 
				//DRK_GREY				#40 40 40
				glm::vec4(192.0f / 255.0f,	192.0f / 255.0f,	192.0f / 255.0f,	1.0f),
				glm::vec4(0.5f,				0.5f,				0.5f,				1.0f),
				glm::vec4(0.25f,			0.25f,				0.25f,				1.0f),
				//WHITE					#ff ff ff
				//BLACK					#00 00 00
				glm::vec4(1.0f,				1.0f,				1.0f,				1.0f),
				glm::vec4(0.0f,				0.0f,				0.0f,				1.0f)
			};
		// Class Members
			void File_Loader::Initialize_Loader() {
				m_engine_texture_dir = pw::cm::Engine_Constant::Pistonworks_Path().generic_wstring() + m_engine_texture_dir;
				m_engine_icon_dir = pw::cm::Engine_Constant::Pistonworks_Path().generic_wstring() + m_engine_icon_dir;
				m_engine_animation_dir = pw::cm::Engine_Constant::Pistonworks_Path().generic_wstring() + m_engine_animation_dir;

				m_texture_repository = pw::Engine_Memory::Allocate<std::map<std::wstring, st::Texture*>>();
			}
			void File_Loader::Initialize_Loader(const std::function<void(const std::wstring&, const bool&)>& p_add_scene_function,
					const std::function<void(const std::wstring&)>& p_change_scene_function,
					const std::function<void(const std::wstring&)>& p_remove_scene_function,
					const std::function<void(const std::wstring&, const std::wstring&, const bool&)>& p_sub_scene_render) {
				m_add_scene_function = p_add_scene_function;
				m_change_scene_function = p_change_scene_function;
				m_remove_scene_function = p_remove_scene_function;
				m_sub_scene_render = p_sub_scene_render;
			}
			void File_Loader::Release_Loader() {
				m_animation_location.~basic_string();
				m_data_location.~basic_string();
				m_font_location.~basic_string();
				m_icon_location.~basic_string();
				m_linker_location.~basic_string();
				m_texture_location.~basic_string();
				m_sound_location.~basic_string();

				m_engine_texture_dir.~basic_string();
				m_engine_icon_dir.~basic_string();
				m_engine_animation_dir.~basic_string();

				if (pw::Engine_Memory::Deallocate<std::map<std::wstring, st::Texture*>>(m_texture_repository) == false) {
					if (m_texture_repository != nullptr) {
						delete m_texture_repository;
						m_texture_repository = nullptr;
					}
				}
			}
			st::Texture* File_Loader::Load_Texture_File(const std::wstring& p_file_name, const bool& p_repeat, const bool& p_linear, const bool& p_engine_dir, std::wstring* p_override_dir) {
				// File Type
				FREE_IMAGE_FORMAT v_image_type{ FREE_IMAGE_FORMAT::FIF_UNKNOWN };
				// First make sure the file location exists
				std::filesystem::path v_location = co::File_Finder::Find_File((p_override_dir == nullptr ?
					(p_engine_dir ? File_Loader::m_engine_texture_dir : File_Loader::m_texture_location) : (*p_override_dir)), p_file_name);

				// Get the file type of the image
				PW_FI_VOID_CALL(TRY_LINE v_image_type = FreeImage_GetFileType(v_location.generic_string().c_str()));

				if (v_image_type == FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					PW_FI_VOID_CALL(v_image_type = FreeImage_GetFIFFromFilename(v_location.generic_string().c_str()));

					if (v_image_type == FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
						throw er::Warning_Error(L"File Loader", L"FIF_UNKNOWN, Unknown File Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_GetFileType");
					}
				}
				// Check if the file type is able to be loaded
				if (TRY_LINE FreeImage_FIFSupportsReading(v_image_type) == (BOOL)true) {
					switch (v_image_type) {
						case FREE_IMAGE_FORMAT::FIF_PNG: {
							return Load_PNG(v_location, p_repeat, p_linear);
						}
						case FREE_IMAGE_FORMAT::FIF_BMP: {
							return Load_BMP(v_location, p_repeat, p_linear);
						}
						case FREE_IMAGE_FORMAT::FIF_JPEG: {
							return Load_JPEG(v_location, p_repeat, p_linear);
						}
						default: {
							throw er::Warning_Error(L"File Loader", L"Unsupported Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_FIFSupportsReading");
						}
					}
				}
				else {
					throw er::Warning_Error(L"File Loader", L"Unsupported Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_FIFSupportsReading");
				}
			}
			std::tuple<st::Texture*, st::Animation*> File_Loader::Load_Animation_File(const std::wstring& p_file_name, const bool& p_repeat, const bool& p_linear, const bool& p_is_async, const bool& p_engine_dir, std::wstring* p_override_dir) {
				// File Type
				FREE_IMAGE_FORMAT v_image_type{ FREE_IMAGE_FORMAT::FIF_UNKNOWN };
				// File
				FIBITMAP* v_file{ nullptr };
				FIMULTIBITMAP* v_gif_bitmap{ nullptr };
				// Image Data
				BYTE* v_image_data{ nullptr };
				// Length / Width of image
				uint32_t v_width{ 0 };
				uint32_t v_height{ 0 };
				// Total frame time
				uint32_t v_frame_time{ 0 };
				// Result
				st::Texture* v_texture{ nullptr };
				st::Animation* v_animation{ nullptr };
				// First make sure the file location exists
				std::filesystem::path v_file_location = co::File_Finder::Find_File((p_override_dir == nullptr ?
					(p_engine_dir ? File_Loader::m_engine_animation_dir : File_Loader::m_animation_location) : (*p_override_dir)), p_file_name);

				// Get the file type of the image
				PW_FI_VOID_CALL(TRY_LINE v_image_type = FreeImage_GetFileType(v_file_location.generic_string().c_str()));

				if (v_image_type == FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					PW_FI_VOID_CALL(v_image_type = FreeImage_GetFIFFromFilename(v_file_location.generic_string().c_str()));

					if (v_image_type == FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
						throw er::Warning_Error(L"File Loader", L"FIF_UNKNOWN, Unknown File Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_GetFileType");
					}
				}
				// Check if the file type is able to be loaded
				if (TRY_LINE FreeImage_FIFSupportsReading(v_image_type) == (BOOL)true) {
					v_gif_bitmap = FreeImage_OpenMultiBitmap(FREE_IMAGE_FORMAT::FIF_GIF, v_file_location.generic_string().c_str(), false, true);

						uint32_t v_frames = FreeImage_GetPageCount(v_gif_bitmap);

						uint32_t v_bytes_per_pixel = 0;

						uint32_t v_overall_width = 0;

						uint32_t v_size = 0;

						for (size_t i = 0; i < v_frames; i++) {
							// Open the bitmap from the gif
							FIBITMAP* v_bitmap = FreeImage_LockPage(v_gif_bitmap, TO_INT32(i));
							// Convert bitmap to RGBA with 4 bytes per pixel
							v_bitmap = FreeImage_ConvertTo32Bits(v_bitmap);
							if (i == 0) {
								v_bytes_per_pixel = FreeImage_GetBPP(v_bitmap) / TO_UINT32(8);

								v_image_data = pw::Engine_Memory::Allocate<BYTE>(TO_UINT64(FreeImage_GetWidth(v_bitmap)) * TO_UINT64(FreeImage_GetHeight(v_bitmap)) * v_frames * v_bytes_per_pixel);

								v_size = TO_UINT32(FreeImage_GetWidth(v_bitmap)) * TO_UINT32(FreeImage_GetHeight(v_bitmap)) * v_frames * v_bytes_per_pixel;

								v_overall_width = TO_UINT32(FreeImage_GetWidth(v_bitmap)) * v_frames * v_bytes_per_pixel;

								v_width = FreeImage_GetWidth(v_bitmap);
								v_height = FreeImage_GetHeight(v_bitmap);

								// Get meta data by loading
								FIBITMAP* v_metadata_bitmap = FreeImage_Load(FREE_IMAGE_FORMAT::FIF_GIF, v_file_location.generic_string().c_str());
								// Get animation meta data
								uint32_t v_metadata_entries{ FreeImage_GetMetadataCount(FIMD_ANIMATION, v_metadata_bitmap) };
								if (v_metadata_entries != NULL) {
									FITAG* v_tag{ nullptr };

									// Create a meta data to sort
									FIMETADATA* v_meta_data{ nullptr };

									v_meta_data = FreeImage_FindFirstMetadata(FIMD_ANIMATION, v_metadata_bitmap, &v_tag);

									for (size_t j = 0; j < 2; j++) {
										FreeImage_FindNextMetadata(v_meta_data, &v_tag);
										if (j == 1) {
											v_frame_time = std::stoi(FreeImage_TagToString(FIMD_ANIMATION, v_tag)) * v_frames;
										}
									}
									FreeImage_FindCloseMetadata(v_meta_data);
								}
								FreeImage_Unload(v_metadata_bitmap);
							}
							// Get Info
							size_t v_frame_width = FreeImage_GetWidth(v_bitmap);
							size_t v_frame_height = FreeImage_GetHeight(v_bitmap);

							BYTE* v_temp_pixel_data = FreeImage_GetBits(v_bitmap);
							// Put said pixel data into the image_data array
							for (size_t j = 0; j < v_frame_height; j++) {
								for (size_t k = 0; k < v_frame_width * v_bytes_per_pixel; k++) {
									v_image_data[k + (j * v_overall_width) + ((v_frame_width * v_bytes_per_pixel) * i)] = v_temp_pixel_data[k + (j * (v_frame_width * v_bytes_per_pixel))];
								}
							}
							FreeImage_UnlockPage(v_gif_bitmap, v_bitmap, false);
						}
						// Create Texture
						v_texture = pw::Engine_Memory::Allocate<st::Texture, bool>(v_image_data, v_width * v_frames, v_height, GL_RGBA, GL_BGRA, p_repeat, p_linear);
						// Create Animation
						v_animation = pw::Engine_Memory::Allocate<st::Animation, bool>(static_cast<float>(v_frame_time) / static_cast<float>(CLOCKS_PER_SEC), v_frames, v_width, p_is_async);

						FreeImage_Unload(v_file);

						FreeImage_CloseMultiBitmap(v_gif_bitmap);
						
						return std::tuple<st::Texture*, st::Animation*>(v_texture, v_animation);
				}
				else {
					throw er::Warning_Error(L"File Loader", L"Unsupported Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_FIFSupportsReading");
				}
			}
			GLFWimage* File_Loader::Load_Icon(const std::wstring& p_file_name, const bool& p_engine_dir) {
				// File Type
				FREE_IMAGE_FORMAT v_image_type{ FREE_IMAGE_FORMAT::FIF_UNKNOWN };
				// File
				FIBITMAP* v_file{ nullptr };
				// Image Data
				BYTE* v_image_data{ nullptr };
				// Length / Width of image / Pitch
				uint32_t v_width{ 0 };
				uint32_t v_height{ 0 };
				uint32_t v_pitch{ 0 };
				// Result
				GLFWimage* v_glfw_image{ pw::Engine_Memory::Allocate<GLFWimage>() };
				// First make sure the file location exists
				std::filesystem::path v_file_location = co::File_Finder::Find_File((p_engine_dir ? m_engine_icon_dir : m_icon_location), p_file_name);

				// Get the file type of the image
				PW_FI_VOID_CALL(TRY_LINE v_image_type = FreeImage_GetFileType(v_file_location.generic_string().c_str()));

				if (v_image_type == FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
					PW_FI_VOID_CALL(v_image_type = FreeImage_GetFIFFromFilename(v_file_location.generic_string().c_str()));

					if (v_image_type == FREE_IMAGE_FORMAT::FIF_UNKNOWN) {
						throw er::Warning_Error(L"File Loader", L"FIF_UNKNOWN, Unknown File Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_GetFileType");
					}
				}
				// Check if the file type is able to be loaded
				if (TRY_LINE FreeImage_FIFSupportsReading(v_image_type) == (BOOL)true) {
					if (v_image_type == FREE_IMAGE_FORMAT::FIF_PNG) {
						// Load File
						PW_FI_VOID_CALL(TRY_LINE v_file = FreeImage_Load(v_image_type, v_file_location.generic_string().c_str()));

						if (!v_file == true) {
							throw er::Warning_Error(L"File Loader", L"Unable to load", EXCEPTION_LINE, __FILEW__, L"FreeImage_Load");
						}
						// If successful get data
						v_width = FreeImage_GetWidth(v_file);
						v_height = FreeImage_GetHeight(v_file);
						v_pitch = FreeImage_GetPitch(v_file);

						v_image_data = FreeImage_GetBits(v_file);
						
						for (size_t y = 0; y < v_height; y++) {
							BYTE* image_data_scan_line = FreeImage_GetScanLine(v_file, (int32_t)y);
							for (size_t x = 0; x < v_width; x++) {
								// BGR -> RGB conversion
								BYTE temp = image_data_scan_line[FI_RGBA_RED];
								image_data_scan_line[FI_RGBA_RED] = image_data_scan_line[FI_RGBA_BLUE];
								image_data_scan_line[FI_RGBA_BLUE] = temp;
								// Go to the next pixel
								image_data_scan_line += 4;
							}
						}

						// Create Texture
						v_glfw_image->pixels = v_image_data;
						v_glfw_image->width = v_width;
						v_glfw_image->height = v_height;

						m_current_icon = v_file;

						return v_glfw_image;
					}
					else {
						throw er::Warning_Error(L"File Loader", L"Unsupported Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_FIFSupportsReading");
					}
				}
				else {
					throw er::Warning_Error(L"File Loader", L"Unsupported Type", EXCEPTION_LINE, __FILEW__, L"FreeImage_FIFSupportsReading");
				}
			}
			void File_Loader::Unload_Icon() {
				FreeImage_Unload(m_current_icon);
			}
			glm::vec4 File_Loader::Default_Color(const Default_Colors& color) {
				return m_engine_colors[(int32_t)color];
			}
			st::Texture* File_Loader::Load_PNG(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear) {
				// File Type
				FREE_IMAGE_FORMAT v_image_type{ FREE_IMAGE_FORMAT::FIF_PNG };
				// File
				FIBITMAP* v_file{ nullptr };
				// Image Data
				BYTE* v_image_data{ nullptr };
				// Length / Width of image
				uint32_t v_width{ 0 };
				uint32_t v_height{ 0 };
				// Result
				st::Texture* v_texture{ nullptr };

				auto v_found = m_texture_repository->find(p_file_location.filename().wstring());
				if (v_found == m_texture_repository->end()) {
					// Load File
					PW_FI_VOID_CALL(TRY_LINE v_file = FreeImage_Load(v_image_type, p_file_location.generic_string().c_str(), PNG_DEFAULT));

					if (!v_file == true) {
						throw er::Warning_Error(L"File Loader", L"Unable to load", EXCEPTION_LINE, __FILEW__, L"FreeImage_Load");
					}

					if (TRY_LINE FreeImage_HasPixels(v_file) == (BOOL)true) {
						// If successful get data
						v_image_data = FreeImage_GetBits(v_file);

						v_width = FreeImage_GetWidth(v_file);
						v_height = FreeImage_GetHeight(v_file);

						// Create Texture
						v_texture = pw::Engine_Memory::Allocate<st::Texture, bool>(v_image_data, v_width, v_height, GL_RGBA, GL_BGRA, p_repeat, p_linear);

						m_texture_repository->insert(std::make_pair(p_file_location.filename().wstring(), v_texture));

						FreeImage_Unload(v_file);

						return v_texture;
					}
					else {
						throw er::Warning_Error(L"File Loader", L"No Pixel Data", EXCEPTION_LINE, __FILEW__, L"FreeImage_HasPixels");
					}
				}
				else {
					return pw::Engine_Memory::Allocate<st::Texture, bool>(*v_found->second);
				}
			}
			st::Texture* File_Loader::Load_BMP(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear) {
				// File Type
				FREE_IMAGE_FORMAT v_image_type{ FREE_IMAGE_FORMAT::FIF_BMP };
				// File
				FIBITMAP* v_file{ nullptr };
				// Image Data
				BYTE* v_image_data{ nullptr };
				// Length / Width of image
				uint32_t v_width{ 0 };
				uint32_t v_height{ 0 };
				// Result
				st::Texture* v_texture{ nullptr };

				// Load File
				PW_FI_VOID_CALL(TRY_LINE v_file = FreeImage_Load(v_image_type, p_file_location.generic_string().c_str(), BMP_DEFAULT));

				if (!v_file == true) {
					throw er::Warning_Error(L"File Loader", L"Unable to load", EXCEPTION_LINE, __FILEW__, L"FreeImage_Load");
				}
				if (TRY_LINE FreeImage_HasPixels(v_file) == (BOOL)true) {
					// If successful get data
					v_image_data = FreeImage_GetBits(v_file);

					v_width = FreeImage_GetWidth(v_file);
					v_height = FreeImage_GetHeight(v_file);

					// Create Texture
					v_texture = pw::Engine_Memory::Allocate<st::Texture, bool>(v_image_data, v_width, v_height, GL_RGB, GL_BGR, p_repeat, p_linear);

					FreeImage_Unload(v_file);

					return v_texture;
				}
				else {
					throw er::Warning_Error(L"File Loader", L"No Pixel Data", EXCEPTION_LINE, __FILEW__, L"FreeImage_HasPixels");
				}
			}
			st::Texture* File_Loader::Load_JPEG(const std::filesystem::path& p_file_location, const bool& p_repeat, const bool& p_linear) {
				// File Type
				FREE_IMAGE_FORMAT v_image_type{ FREE_IMAGE_FORMAT::FIF_JPEG };
				// File
				FIBITMAP* v_file{ nullptr };
				// Image Data
				BYTE* v_image_data{ nullptr };
				// Length / Width of image
				uint32_t v_width{ 0 };
				uint32_t v_height{ 0 };
				// Result
				st::Texture* v_texture{ nullptr };

				// Load File
				PW_FI_VOID_CALL(TRY_LINE v_file = FreeImage_Load(v_image_type, p_file_location.generic_string().c_str(), JPEG_DEFAULT));

				if (!v_file == true) {
					throw er::Warning_Error(L"File Loader", L"Unable to load", EXCEPTION_LINE, __FILEW__, L"FreeImage_Load");
				}
				if (TRY_LINE FreeImage_HasPixels(v_file) == (BOOL)true) {
					// If successful get data
					v_image_data = FreeImage_GetBits(v_file);

					v_width = FreeImage_GetWidth(v_file);
					v_height = FreeImage_GetHeight(v_file);

					// Create Texture
					v_texture = pw::Engine_Memory::Allocate<st::Texture, bool>(v_image_data, v_width, v_height, GL_RGB, GL_BGR, p_repeat, p_linear);

					FreeImage_Unload(v_file);

					return v_texture;
				}
				else {
					throw er::Warning_Error(L"File Loader", L"No Pixel Data", EXCEPTION_LINE, __FILEW__, L"FreeImage_HasPixels");
				}
			}
			PW_PROJECT_FILE File_Loader::Load_Project_File(const std::filesystem::path& p_file_location, const std::wstring& p_path_to_animations,
					const std::wstring& p_path_to_data, const std::wstring& p_path_to_fonts, const std::wstring& p_path_to_icon, const std::wstring& p_path_to_linker_files,
					const std::wstring& p_path_to_textures, const std::wstring& p_path_to_sounds) {

				bool v_loaded_project{ false };
				std::string v_project_name{};
				std::string v_scene_loading{};
				std::string v_font_repository{};
				std::string v_icon_location{};
				int32_t v_fps_cap{ 0 };
				uint32_t v_has_vsync{ false };
				int32_t v_window_x{ 1 };
				int32_t v_window_y{ 1 };

				uint32_t v_is_locked{ false };

				io::CSVReader<9, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					v_file_reader{ p_file_location.generic_string().c_str() };
				v_file_reader.read_header(io::ignore_extra_column,
					"Project_Name", "Scene_Loading", "Font_Loading", "Icon", "FPS_Cap", "Vsync", "Window_Size_X", "Window_Size_Y", "Lock_Window");
				while (v_file_reader.read_row(v_project_name, v_scene_loading, v_font_repository, v_icon_location, v_fps_cap, v_has_vsync, v_window_x, v_window_y, v_is_locked)) {
					break;
				}
				cm::Engine_Constant::Set_Window_Width(TO_UINT32(v_window_x));
				cm::Engine_Constant::Set_Window_Height(TO_UINT32(v_window_y));
				v_window_x = TO_INT32(ceilf((float)v_window_x / 2));
				cm::Engine_Constant::Set_Hafe_Window_Width(TO_UINT32(v_window_x));
				v_window_y = TO_INT32(ceilf((float)v_window_y / 2));
				cm::Engine_Constant::Set_Hafe_Window_Height(TO_UINT32(v_window_y));

				cm::Engine_Constant::Set_FPS_Info(v_fps_cap, TO_BOOL(v_has_vsync));

				v_loaded_project = true;

				m_loaded_project = v_loaded_project;
				
				m_animation_location = p_path_to_animations;
				m_data_location = p_path_to_data;
				m_font_location = p_path_to_fonts;
				m_icon_location = p_path_to_icon;
				m_linker_location = p_path_to_linker_files;
				m_texture_location = p_path_to_textures;
				m_sound_location = p_path_to_sounds;

				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> v_converter;

				std::wstring vw_project_name{ v_converter.from_bytes(v_project_name) };

				std::string v_scene_name{};
				uint32_t v_set_current{ 0 };
				std::vector<std::tuple<std::wstring, bool>> v_scenes{};		

				std::filesystem::path v_file_location = co::File_Finder::Find_File(m_linker_location, TO_WSTRING(v_scene_loading), L".csv");

				io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					v_scene_reader{ v_file_location.generic_string().c_str() };
				v_scene_reader.read_header(io::ignore_extra_column,
					"Scene_Name", "Set_Current");
				while (v_scene_reader.read_row(v_scene_name, v_set_current)) {
					v_scenes.push_back(std::make_tuple(v_converter.from_bytes(v_scene_name), (bool)v_set_current));
				}

				return std::tuple<bool, std::wstring, std::vector<std::tuple<std::wstring, bool>>, std::wstring, std::wstring, uint32_t>(
					v_loaded_project, vw_project_name, v_scenes, TO_WSTRING(v_font_repository), TO_WSTRING(v_icon_location), v_is_locked);
			}
			st::Game_Scene* File_Loader::Load_Scene_File(const std::wstring& p_file_name) {
				// First load the scene data 
				std::string v_data_name{};
				std::string v_input_repository{};
				std::string v_event_repository{};
				std::string v_listener_id{};
				uint32_t v_has_physics_factory{ 0 };
				float v_gravity_x{ 0.0f };
				float v_gravity_y{ 0.0f };
				uint32_t v_velocity_it{ 0 };
				uint32_t v_position_it{ 0 };

				std::filesystem::path v_location = co::File_Finder::Find_File(m_data_location, p_file_name, L".csv");

				io::CSVReader<9, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_line_comment<'#'>>
					v_file_header_reader{ v_location.generic_string().c_str() };
				v_file_header_reader.read_header(io::ignore_extra_column, "Data_Name", "Input_Name", "Event_Name", "Listener_ID", "Has_Physics", "Gravity_x", "Gravity_y", "Velocity_It", "Position_It");
				while (v_file_header_reader.read_row(v_data_name, v_input_repository, v_event_repository, v_listener_id, v_has_physics_factory, v_gravity_x, v_gravity_y, v_velocity_it, v_position_it)) {
					break;
				}

				size_t v_last_slash = v_location.generic_string().find_last_of("/");
				size_t v_last_v = v_location.generic_string().find_last_of("v");

				std::string	v_cscene_name{ v_location.generic_string().substr(OFF(v_last_slash), v_last_v - v_last_slash) };

				std::wstring v_wscene_name{ TO_WSTRING(v_cscene_name) };
				st::Physics_Factory* v_physics_factory = nullptr;
				if (v_has_physics_factory == 1) {
					v_physics_factory = pw::Engine_Memory::Allocate<st::Physics_Factory, bool>(b2Vec2(v_gravity_x, v_gravity_y), v_velocity_it, v_position_it);
				}
				// End of scene loading
				// Next load the scene / sub-scene locations
				
				v_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_data_name), L".csv");

				std::string v_temp_identifier_scene{};
				std::string v_main_scene;
				uint32_t v_is_main{ 0 };
				std::vector<std::string> v_sub_scenes{};

				io::CSVReader<2, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
					v_file_data_scene_reader{ v_location.generic_string().c_str() };
				v_file_data_scene_reader.read_header(io::ignore_extra_column, "Scene_Data", "Main_Scene");
				while (v_file_data_scene_reader.read_row(v_temp_identifier_scene, v_is_main)) {
					if ((bool)v_is_main != true) {
						v_sub_scenes.push_back(v_temp_identifier_scene);
					}
					else {
						v_main_scene = v_temp_identifier_scene;
					}
				}
				// End of scene / sub-scene finding
				// Load the main scene and then the sub-scenes
				std::vector<st::Actor*> v_scene_models;
				std::vector<st::Actor*> v_collision_models;
				std::vector<std::tuple<std::wstring, st::Actor*, int32_t>> v_s_id_holder{};
				std::map<std::wstring, st::Sub_Scene_Structure*> v_sub_scene_structures{};
				std::vector<std::tuple<std::wstring, st::Actor*, glm::vec2>> v_model_attachments{};
				// Create context for the sounds
				st::Listener::Create_Listener();

				Load_Data_File(v_scene_models, v_collision_models, v_s_id_holder,
					v_sub_scene_structures, v_location, v_has_physics_factory, v_physics_factory, v_main_scene, v_sub_scenes, v_model_attachments);
				// Start loading of standard input
				std::map<std::wstring, co::Engine_Input*> v_scene_input{};
				co::Engine_Input* v_temp_input = nullptr;

				std::string v_input_id{};
				std::string v_current_input{};
				std::string v_input_name{};
				uint32_t v_is_current_input{};

				v_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_input_repository), L".csv");

				io::CSVReader<3, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
					v_input_data_reader{ v_location.generic_string().c_str() };
				v_input_data_reader.read_header(io::ignore_extra_column, "Input_ID", "Input", "Is_Current");
				while (v_input_data_reader.read_row(v_input_id, v_input_name, v_is_current_input)) {

					if ((bool)v_is_current_input == true) {
						v_current_input = v_input_id;
					}

					v_temp_input = pw::Engine_Memory::Allocate<Engine_Input>();

					v_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_input_name), L".csv");

					std::string v_input_type{};
					std::string v_input_event{};
					int32_t v_button_code{ 0 };
					std::string v_function_name{};
					int32_t v_play_once{ 0 };

					io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
						v_file_data_reader{ v_location.generic_string().c_str() };
					v_file_data_reader.read_header(io::ignore_extra_column, "Input_Type", "Input_Event", "Button_Code", "Function_Name", "Play_Once");
					while (v_file_data_reader.read_row(v_input_type, v_input_event, v_button_code, v_function_name, v_play_once)) {
						if (v_input_type == "KEYBOARD") {
							if (v_input_event == "PRESS") {
								v_temp_input->Create_Event_Keyboard(GLFW_PRESS, v_button_code, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
							}
							else {
								if (v_input_event == "RELEASE") {
									v_temp_input->Create_Event_Keyboard(GLFW_RELEASE, v_button_code, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
								}
								else {
									if (v_input_event == "REPEAT") {
										v_temp_input->Create_Event_Keyboard(GLFW_REPEAT, v_button_code, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
									}
								}
							}
						}
						else {
							if (v_input_type == "MOUSE") {
								if (v_input_event == "PRESS") {
									v_temp_input->Create_Event_Mouse(GLFW_PRESS, v_button_code, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
								}
								else {
									if (v_input_event == "RELEASE") {
										v_temp_input->Create_Event_Mouse(GLFW_RELEASE, v_button_code, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
									}
									else {
										if (v_input_event == "REPEAT") {
											v_temp_input->Create_Event_Mouse(GLFW_REPEAT, v_button_code, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
										}
									}
								}
							}
							else {
								if (v_input_type == "SCROLL") {
									if (v_input_event == "FORWARD") {
										v_temp_input->Create_Event_Scroll(cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
									}
									else {
										if (v_input_event == "BACKWARDS") {
											v_temp_input->Create_Event_Scroll(cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD, co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), v_play_once);
										}
									}
								}
							}
						}
					}
					v_scene_input.insert(std::make_pair(TO_WSTRING(v_input_id), v_temp_input));
					v_temp_input = nullptr;
				}
				// End of loading for standard input

				v_wscene_name.erase(v_wscene_name.begin() + v_wscene_name.find_last_of(L"."), v_wscene_name.end());

				st::Game_Scene* v_scene{ pw::Engine_Memory::Allocate<st::Game_Scene, bool>(
					v_wscene_name, v_scene_models, v_collision_models, v_scene_input, v_physics_factory, v_sub_scene_structures, TO_WSTRING(v_listener_id)) };

				for (auto i = v_s_id_holder.begin(); i != v_s_id_holder.end(); i++) {
					v_scene->Register_S_ID(i->_Myfirst._Val, i->_Get_rest()._Myfirst._Val);
				}
				
				auto function_picker = [](
					const std::wstring& p_event_id, const std::wstring& p_sound_id, st::Game_Scene* p_scene,
					std::map<std::wstring, st::Sub_Scene_Structure*> p_sub_scene_structure,
					uint32_t p_event_type, const std::wstring& p_function_name,
					int32_t p_button_code, int32_t p_press_type, st::Actor* p_main_actor, st::Actor* p_test_actor,
					bool p_play_once, std::string& p_arg_1, std::string& p_arg_2, std::string& p_arg_3, std::string& p_arg_4, std::string& p_arg_5) {
						switch (p_event_type) {
							case pw::cm::Engine_Constant::PW_SOUND_START_EVENT:
							case pw::cm::Engine_Constant::PW_SOUND_END_EVENT: {
								if (co::Engine_Input::Access_Function(p_function_name) != nullptr) {
									p_scene->Create_Event<void>(
										p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
										co::Engine_Input::Access_Function(p_function_name), p_play_once);
								}
								else {
									if (p_function_name == L"CHANGE_ANIMATION") {
										p_scene->Create_Event<void>(
											p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
											std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
												std::bind(static_cast<void(st::Actor::*)(std::wstring, bool)>(&st::Actor::Change_Animation), p_main_actor, std::placeholders::_1, std::placeholders::_2))),
											p_play_once, TO_WSTRING(p_arg_2), (bool)std::stoi(p_arg_3));
									}
									else {
										if (p_function_name == L"START_ANIMATION") {
											p_scene->Create_Event<void>(
												p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
												std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
													std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Start_Animation), p_main_actor))),
												p_play_once);
										}
										else {
											if (p_function_name == L"STOP_ANIMATION") {
												p_scene->Create_Event<void>(
													p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
													std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
														std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Stop_Animation), p_main_actor))),
													p_play_once);
											}
											else {
												if (p_function_name == L"ADVANCE_ANIMATION") {
													p_scene->Create_Event<void>(
														p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type,
														p_main_actor,
														std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
															std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Advance_Animation), p_main_actor))),
														p_play_once);
												}
												else {
													if (p_function_name == L"ADD_SCENE") {
														p_scene->Create_Event<void>(
															p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
															std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																m_add_scene_function)),
															p_play_once, TO_WSTRING(p_arg_2), (bool)std::stoi(p_arg_3));
													}
													else {
														if (p_function_name == L"CHANGE_SCENE") {
															p_scene->Create_Event<void>(
																p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																	m_change_scene_function)),
																p_play_once, TO_WSTRING(p_arg_2));
														}
														else {
															if (p_function_name == L"REMOVE_SCENE") {
																p_scene->Create_Event<void>(
																	p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																	std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																		m_remove_scene_function)),
																	p_play_once, TO_WSTRING(p_arg_2));
															}
															else {
																if (p_function_name == L"SET_TEXTURE") {
																	p_scene->Create_Event<void>(
																		p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																		std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																			std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Set_Texture), p_main_actor, std::placeholders::_1))),
																		p_play_once, TO_WSTRING(p_arg_2));
																}
																else {
																	if (p_function_name == L"SET_SRENDER") {
																		auto v_found_sub_structure = p_sub_scene_structure.find(TO_WSTRING(p_arg_2));
																		if (v_found_sub_structure != p_sub_scene_structure.end()) {
																			p_scene->Create_Event<void, bool>(
																				p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																				std::make_shared<COMPLEX_FUNCTION_1(bool)>(COMPLEX_FUNCTION_1(bool)(
																					std::bind(static_cast<void(st::Sub_Scene_Structure::*)(bool)>(&st::Sub_Scene_Structure::Set_Render_Toggle), &*v_found_sub_structure->second, std::placeholders::_1))),
																				p_play_once, (bool)std::stoi(p_arg_2));
																		}
																	}
																	else {
																		if (p_function_name == L"SET_OSRENDER") {
																			p_scene->Create_Event<void>(
																				p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																				std::make_shared<COMPLEX_FUNCTION_3(std::wstring, std::wstring, bool)>(COMPLEX_FUNCTION_3(std::wstring, std::wstring, bool)(
																					m_sub_scene_render)),
																				p_play_once, TO_WSTRING(p_arg_2), TO_WSTRING(p_arg_3), (bool)std::stoi(p_arg_4));
																		}
																		else {
																			if (p_function_name == L"PLAY_SOUND") {
																				p_scene->Create_Event<void>(
																					p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																					std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																						std::bind(static_cast<void(st::Actor::*)(std::wstring, bool)>(&st::Actor::Play_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1, std::placeholders::_2))),
																					p_play_once, TO_WSTRING(p_arg_2), (bool)std::stoi(p_arg_3));
																			}
																			else {
																				if (p_function_name == L"PAUSE_SOUND") {
																					p_scene->Create_Event<void>(
																						p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																						std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																							std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Pause_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1))),
																						p_play_once, TO_WSTRING(p_arg_2));
																				}
																				else {
																					if (p_function_name == L"STOP_SOUND") {
																						p_scene->Create_Event<void>(
																							p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																							std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																								std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Stop_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1))),
																							p_play_once, TO_WSTRING(p_arg_2));
																					}
																					else {
																						if (p_function_name == L"RESET_SOUND") {
																							p_scene->Create_Event<void>(
																								p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																								std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																									std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Reset_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1))),
																								p_play_once, TO_WSTRING(p_arg_2));
																						}
																						else {
																							if (p_function_name == L"CHANGE_VOLUME") {
																								p_scene->Create_Event<void>(
																									p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																									std::make_shared<COMPLEX_FUNCTION_3(std::wstring, float, bool)>(COMPLEX_FUNCTION_3(std::wstring, float, bool)(
																										std::bind(static_cast<void(st::Actor::*)(std::wstring, float, bool)>(&st::Actor::Change_Volume), p_scene->Access_Model(p_sound_id),
																											std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))),
																									p_play_once, TO_WSTRING(p_arg_2), std::stof(p_arg_3), (bool)std::stoi(p_arg_4));
																							}
																							else {
																								if (p_function_name == L"SET_ACTIVE_INPUT") {
																									p_scene->Create_Event<void>(
																										p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																										std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																											std::bind(static_cast<void(st::Game_Scene::*)(std::wstring)>(&st::Game_Scene::Set_Active_Input), p_scene, std::placeholders::_1))),
																										p_play_once, TO_WSTRING(p_arg_2));
																								}
																								else {
																									if (p_function_name == L"TOGGLE_RENDER") {
																										p_scene->Create_Event<void>(
																											p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																											std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																												std::bind(static_cast<void(st::Game_Scene::*)(std::wstring)>(&st::Game_Scene::Toggle_Render), p_scene, std::placeholders::_1))),
																											p_play_once, TO_WSTRING(p_arg_2));
																									}
																									else {
																										if (p_function_name == L"SET_TEXT") {
																											p_scene->Create_Event<void>(
																												p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																												std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																													std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Set_Text), p_main_actor,
																														std::placeholders::_1))),
																												p_play_once, TO_WSTRING(p_arg_2));
																										}
																										else {
																											if (p_function_name == L"SET_TEXT_COLOR") {
																												p_scene->Create_Event<void>(
																													p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																													std::make_shared<COMPLEX_FUNCTION_1(glm::vec4)>(COMPLEX_FUNCTION_1(glm::vec4)(
																														std::bind(static_cast<void(st::Actor::*)(glm::vec4)>(&st::Actor::Set_Text_Color), p_main_actor, std::placeholders::_1))),
																													p_play_once, glm::vec4(std::stof(p_arg_2) / 255.0f, std::stof(p_arg_3) / 255.0f, std::stof(p_arg_4) / 255.0f, std::stof(p_arg_5) / 255.0f));
																											}
																											else {
																												if (p_function_name == L"SET_COLOR") {
																													p_scene->Create_Event<void>(
																														p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																														std::make_shared<COMPLEX_FUNCTION_1(glm::vec4)>(COMPLEX_FUNCTION_1(glm::vec4)(
																															std::bind(static_cast<void(st::Actor::*)(glm::vec4)>(&st::Actor::Set_Color), p_main_actor, std::placeholders::_1))),
																														p_play_once, glm::vec4(std::stof(p_arg_2) / 255.0f, std::stof(p_arg_3) / 255.0f, std::stof(p_arg_4) / 255.0f, std::stof(p_arg_5) / 255.0f));
																												}
																												else {
																													if (p_function_name == L"CLOSE_ENGINE") {
																														p_scene->Create_Event<void>(
																															p_event_id, TO_WSTRING(p_arg_1), p_event_type, p_press_type, p_main_actor,
																															std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(&cm::Engine_Constant::Close_Engine)),
																															p_play_once);
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
														}
													}
												}
											}
										}
									}
								}
								break;
							}
							default: {
								if (co::Engine_Input::Access_Function(p_function_name) != nullptr) {
									p_scene->Create_Event<void>(
										p_event_id, p_event_type, p_button_code, p_press_type,
										p_test_actor, p_main_actor,
										co::Engine_Input::Access_Function(p_function_name), p_play_once);
								}
								else {
									if (p_function_name == L"CHANGE_ANIMATION") {
										p_scene->Create_Event<void>(
											p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
											std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
												std::bind(static_cast<void(st::Actor::*)(std::wstring, bool)>(&st::Actor::Change_Animation), p_main_actor, std::placeholders::_1, std::placeholders::_2))),
											p_play_once, TO_WSTRING(p_arg_1), (bool)std::stoi(p_arg_2));
									}
									else {
										if (p_function_name == L"START_ANIMATION") {
											p_scene->Create_Event<void>(
												p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
												std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
													std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Start_Animation), p_main_actor))),
												p_play_once);
										}
										else {
											if (p_function_name == L"STOP_ANIMATION") {
												p_scene->Create_Event<void>(
													p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
													std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
														std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Stop_Animation), p_main_actor))),
													p_play_once);
											}
											else {
												if (p_function_name == L"ADVANCE_ANIMATION") {
													p_scene->Create_Event<void>(
														p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
														std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
															std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Advance_Animation), p_main_actor))),
														p_play_once);
												}
												else {
													if (p_function_name == L"ADD_SCENE") {
														p_scene->Create_Event<void>(
															p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
															std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																m_add_scene_function)),
															p_play_once, TO_WSTRING(p_arg_1), (bool)std::stoi(p_arg_2));
													}
													else {
														if (p_function_name == L"CHANGE_SCENE") {
															p_scene->Create_Event<void>(
																p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																	m_change_scene_function)),
																p_play_once, TO_WSTRING(p_arg_1));
														}
														else {
															if (p_function_name == L"REMOVE_SCENE") {
																p_scene->Create_Event<void>(
																	p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																	std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																		m_remove_scene_function)),
																	p_play_once, TO_WSTRING(p_arg_1));
															}
															else {
																if (p_function_name == L"SET_TEXTURE") {
																	p_scene->Create_Event<void>(
																		p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																		std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																			std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Set_Texture), p_main_actor, std::placeholders::_1))),
																		p_play_once, TO_WSTRING(p_arg_1));
																}
																else {
																	if (p_function_name == L"SET_SRENDER") {
																		auto v_found_sub_structure = p_sub_scene_structure.find(TO_WSTRING(p_arg_1));
																		if (v_found_sub_structure != p_sub_scene_structure.end()) {
																			p_scene->Create_Event<void, bool>(
																				p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																				std::make_shared<COMPLEX_FUNCTION_1(bool)>(COMPLEX_FUNCTION_1(bool)(
																					std::bind(static_cast<void(st::Sub_Scene_Structure::*)(bool)>(&st::Sub_Scene_Structure::Set_Render_Toggle), &*v_found_sub_structure->second, std::placeholders::_1))),
																				p_play_once, (bool)std::stoi(p_arg_2));
																		}
																	}
																	else {
																		if (p_function_name == L"SET_OSRENDER") {
																			p_scene->Create_Event<void>(
																				p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																				std::make_shared<COMPLEX_FUNCTION_3(std::wstring, std::wstring, bool)>(COMPLEX_FUNCTION_3(std::wstring, std::wstring, bool)(
																					m_sub_scene_render)),
																				p_play_once, TO_WSTRING(p_arg_1), TO_WSTRING(p_arg_2), (bool)std::stoi(p_arg_3));
																		}
																		else {
																			if (p_function_name == L"PLAY_SOUND") {
																				p_scene->Create_Event<void>(
																					p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																					std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																						std::bind(static_cast<void(st::Actor::*)(std::wstring, bool)>(&st::Actor::Play_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1, std::placeholders::_2))),
																					p_play_once, TO_WSTRING(p_arg_1), (bool)std::stoi(p_arg_2));
																			}
																			else {
																				if (p_function_name == L"PAUSE_SOUND") {
																					p_scene->Create_Event<void>(
																						p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																						std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																							std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Pause_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1))),
																						p_play_once, TO_WSTRING(p_arg_1));
																				}
																				else {
																					if (p_function_name == L"STOP_SOUND") {
																						p_scene->Create_Event<void>(
																							p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																							std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																								std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Stop_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1))),
																							p_play_once, TO_WSTRING(p_arg_1));
																					}
																					else {
																						if (p_function_name == L"RESET_SOUND") {
																							p_scene->Create_Event<void>(
																								p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																								std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																									std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Reset_Sound), p_scene->Access_Model(p_sound_id), std::placeholders::_1))),
																								p_play_once, TO_WSTRING(p_arg_1));
																						}
																						else {
																							if (p_function_name == L"CHANGE_VOLUME") {
																								p_scene->Create_Event<void>(
																									p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																									std::make_shared<COMPLEX_FUNCTION_3(std::wstring, float, bool)>(COMPLEX_FUNCTION_3(std::wstring, float, bool)(
																										std::bind(static_cast<void(st::Actor::*)(std::wstring, float, bool)>(&st::Actor::Change_Volume), p_scene->Access_Model(p_sound_id),
																											std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))),
																									p_play_once, TO_WSTRING(p_arg_1), std::move(std::stof(p_arg_2)), (bool)std::stoi(p_arg_3));
																							}
																							else {
																								if (p_function_name == L"SET_ACTIVE_INPUT") {
																									p_scene->Create_Event<void>(
																										p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																										std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																											std::bind(static_cast<void(st::Game_Scene::*)(std::wstring)>(&st::Game_Scene::Set_Active_Input), p_scene, std::placeholders::_1))),
																										p_play_once, TO_WSTRING(p_arg_1));
																								}
																								else {
																									if (p_function_name == L"TOGGLE_RENDER") {
																										p_scene->Create_Event<void>(
																											p_event_id, p_event_type, p_button_code, p_press_type, p_test_actor, p_main_actor,
																											std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																												std::bind(static_cast<void(st::Game_Scene::*)(std::wstring)>(&st::Game_Scene::Toggle_Render), p_scene, std::placeholders::_1))),
																											p_play_once, TO_WSTRING(p_arg_1));
																									}
																									else {
																										if (p_function_name == L"SET_TEXT") {
																											p_scene->Create_Event<void>(
																												p_event_id, p_event_type, p_button_code, p_press_type,
																												p_test_actor, p_main_actor,
																												std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																													std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Set_Text), p_main_actor, std::placeholders::_1))),
																												p_play_once, TO_WSTRING(p_arg_1));
																										}
																										else {
																											if (p_function_name == L"SET_TEXT_COLOR") {
																												p_scene->Create_Event<void>(
																													p_event_id, p_event_type, p_button_code, p_press_type,
																													p_test_actor, p_main_actor,
																													std::make_shared<COMPLEX_FUNCTION_1(glm::vec4)>(COMPLEX_FUNCTION_1(glm::vec4)(
																														std::bind(static_cast<void(st::Actor::*)(glm::vec4)>(&st::Actor::Set_Text_Color), p_main_actor, std::placeholders::_1))),
																													p_play_once, glm::vec4(std::stof(p_arg_1) / 255.0f, std::stof(p_arg_2) / 255.0f, std::stof(p_arg_3) / 255.0f, std::stof(p_arg_4) / 255.0f));
																											}
																											else {
																												if (p_function_name == L"SET_COLOR") {
																													p_scene->Create_Event<void>(
																														p_event_id, p_event_type, p_button_code, p_press_type,
																														p_test_actor, p_main_actor,
																														std::make_shared<COMPLEX_FUNCTION_1(glm::vec4)>(COMPLEX_FUNCTION_1(glm::vec4)(
																															std::bind(static_cast<void(st::Actor::*)(glm::vec4)>(&st::Actor::Set_Color), p_main_actor, std::placeholders::_1))),
																														p_play_once, glm::vec4(std::stof(p_arg_1) / 255.0f, std::stof(p_arg_2) / 255.0f, std::stof(p_arg_3) / 255.0f, std::stof(p_arg_4) / 255.0f));
																												}
																												else {
																													if (p_function_name == L"CLOSE_ENGINE") {
																														p_scene->Create_Event<void>(
																															p_event_id, p_event_type, p_button_code, p_press_type,
																															p_test_actor, p_main_actor,
																															std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(&cm::Engine_Constant::Close_Engine)),
																															p_play_once);
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
														}
													}
												}
											}
										}
									}
								}
								break;
							}
						}
				};

				// Start loading event / custom input
				std::string v_current_event{};
				std::string v_event_name{};
				uint32_t v_is_current_event{};

				v_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_event_repository), L".csv");

				io::CSVReader<3, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
					v_event_data_reader{ v_location.generic_string().c_str() };
				v_event_data_reader.read_header(io::ignore_extra_column, "Input_ID", "Event", "Is_Current");
				while (v_event_data_reader.read_row(v_input_id, v_event_name, v_is_current_event)) {

					if ((bool)v_is_current_event == true) {
						v_current_event = v_input_id;
					}

					std::string v_event_type{};
					std::string v_s_id{};
					std::string v_input_event{};
					int32_t v_button_code{};
					std::string v_function_name{};
					int32_t v_play_once{};
					std::string v_model_id{};
					std::string v_object_id{}; 
					std::string v_sound_id{};
					std::string v_arg_1{};
					std::string v_arg_2{};
					std::string v_arg_3{};
					std::string v_arg_4{};
					std::string v_arg_5{};

					v_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_event_name), L".csv");

					io::CSVReader<13, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
						v_file_data_reader{ v_location.generic_string().c_str() };
					v_file_data_reader.read_header(io::ignore_extra_column, "Event_Type", "Model_S_ID", "Sound_S_ID", "Input_Event", "Button_Code", "Function_Name", "Play_Once", "Other_S_ID", "Args_1", "Args_2", "Args_3", "Args_4", "Args_5");
					while (v_file_data_reader.read_row(v_event_type, v_s_id, v_sound_id, v_input_event, v_button_code, v_function_name, v_play_once, v_object_id, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5)) {
						std::wstring v_ws_id{ TO_WSTRING(v_s_id) };
						std::wstring v_wsound_id{ TO_WSTRING(v_sound_id) };

						std::vector<st::Actor*> v_actor_list{};

						st::Actor* v_main_actor{ nullptr };

						for (auto i = v_s_id_holder.begin(); i != v_s_id_holder.end(); i++) {
							if (v_ws_id == std::get<0>(*i) || v_wsound_id == std::get<0>(*i)) {
								if (std::get<2>(*i) == 1) {
									v_main_actor = std::get<1>(*i);
								}
								v_actor_list.push_back(std::get<1>(*i));
							}

						}

						if (v_actor_list.size() == 0) {
							if (v_event_type == "KEYBOARD") {
								if (v_input_event == "PRESS") {
									function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_KEYBOARD_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
								}
								else {
									if (v_input_event == "RELEASE") {
										function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_KEYBOARD_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
									}
									else {
										if (v_input_event == "REPEAT") {
											function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_KEYBOARD_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_REPEAT, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
										}
									}
								}
							}
							else {
								if (v_event_type == "MOUSE") {
									if (v_input_event == "PRESS") {
										function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_MOUSE_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
									}
									else {
										if (v_input_event == "RELEASE") {
											function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_MOUSE_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
										}
										else {
											if (v_input_event == "REPEAT") {
												function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_MOUSE_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_REPEAT, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
											}
										}
									}
								}
								else {
									if (v_event_type == "SCROLL") {
										if (v_input_event == "FORWARD") {
											function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_SCROLL_EVENT, TO_WSTRING(v_function_name), cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD, GLFW_PRESS, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
										}
										else {
											if (v_input_event == "BACKWARDS") {
												function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_SCROLL_EVENT, TO_WSTRING(v_function_name), cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD, GLFW_PRESS, v_main_actor, nullptr, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
											}
										}
									}
								}
							}
						}
						else {
							if (v_object_id != "NULL") {
								if (v_event_type == "CLICK") {
									if (v_input_event == "PRESS") {
										function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_CLICK_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_scene->Access_Model(TO_WSTRING(v_object_id)), v_main_actor, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
									}
									else {
										if (v_input_event == "RELEASE") {
											function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_CLICK_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_scene->Access_Model(TO_WSTRING(v_object_id)), v_main_actor, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
										}
										else {
											if (v_input_event == "REPEAT") {
												function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_CLICK_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_REPEAT, v_scene->Access_Model(TO_WSTRING(v_object_id)), v_main_actor, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
											}
										}
									}
								}
								else {
									if (v_event_type == "HOVER") {
										if (v_input_event == "PRESS") {
											function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_HOVER_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_scene->Access_Model(TO_WSTRING(v_object_id)), v_main_actor, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
										}
										else {
											if (v_input_event == "RELEASE") {
												function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_HOVER_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_scene->Access_Model(TO_WSTRING(v_object_id)), v_main_actor, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
											}
										}
									}
								}
							}
							else {
								for (auto i = v_actor_list.begin(); i != v_actor_list.end(); i++) {
									if (v_event_type == "CLICK") {
										if (v_input_event == "PRESS") {
											function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_CLICK_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
										}
										else {
											if (v_input_event == "RELEASE") {
												function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_CLICK_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
											}
											else {
												if (v_input_event == "REPEAT") {
													function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_CLICK_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_REPEAT, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
												}
											}
										}
									}
									else {
										if (v_event_type == "HOVER") {
											if (v_input_event == "PRESS") {
												function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_HOVER_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
											}
											else {
												if (v_input_event == "RELEASE") {
													function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_HOVER_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
												}
											}
										}
										else {
											if (v_event_type == "COLLISION") {
												if (co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)) != nullptr) {
													v_scene->Create_Event<void>(TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
														co::Engine_Input::Access_Function(TO_WSTRING(v_function_name)), (bool)v_play_once);
												}
												else {
													if (v_function_name == "CHANGE_ANIMATION") {
														v_scene->Create_Event<void, std::wstring, bool>(
															TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
															std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																std::bind(static_cast<void(st::Actor::*)(std::wstring, bool)>(&st::Actor::Change_Animation), v_scene->Access_Model(v_ws_id), std::placeholders::_1, std::placeholders::_2))),
															(bool)v_play_once, TO_WSTRING(v_arg_1), (bool)std::stoi(v_arg_2));
													}
													else {
														if (v_function_name == "START_ANIMATION") {
															v_scene->Create_Event<void>(
																TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
																	std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Start_Animation), v_scene->Access_Model(v_ws_id)))),
																(bool)v_play_once);
														}
														else {
															if (v_function_name == "STOP_ANIMATION") {
																v_scene->Create_Event<void>(
																	TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																	std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
																		std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Stop_Animation), v_scene->Access_Model(v_ws_id)))),
																	(bool)v_play_once);
															}
															else {
																if (v_function_name == "ADVANCE_ANIMATION") {
																	v_scene->Create_Event<void>(
																		TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																		std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(
																			std::bind(static_cast<void(st::Actor::*)()>(&st::Actor::Advance_Animation), v_scene->Access_Model(v_ws_id)))),
																		(bool)v_play_once);
																}
																else {
																	if (v_function_name == "ADD_SCENE") {
																		v_scene->Create_Event<void, std::wstring, bool>(
																			TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																			std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																				m_add_scene_function)),
																			(bool)v_play_once, TO_WSTRING(v_arg_1), (bool)std::stoi(v_arg_2));
																	}
																	else {
																		if (v_function_name == "CHANGE_SCENE") {
																			v_scene->Create_Event<void, std::wstring>(
																				TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																				std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																					m_change_scene_function)),
																				(bool)v_play_once, TO_WSTRING(v_arg_1));
																		}
																		else {
																			if (v_function_name == "REMOVE_SCENE") {
																				v_scene->Create_Event<void, std::wstring>(
																					TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																					std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																						m_remove_scene_function)),
																					(bool)v_play_once, TO_WSTRING(v_arg_1));
																			}
																			else {
																				if (v_function_name == "SET_TEXTURE") {
																					v_scene->Create_Event<void, std::wstring>(
																						TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																						std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																							std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Set_Texture), v_scene->Access_Model(v_ws_id), std::placeholders::_1))),
																						(bool)v_play_once, TO_WSTRING(v_arg_1));
																				}
																				else {
																					auto vv_found_sub_structure = v_sub_scene_structures.find(TO_WSTRING(v_arg_1));
																					if (v_function_name == "SET_SRENDER") {
																						v_scene->Create_Event<void, bool>(
																							TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																							std::make_shared<COMPLEX_FUNCTION_1(bool)>(COMPLEX_FUNCTION_1(bool)(
																								std::bind(static_cast<void(st::Sub_Scene_Structure::*)(bool)>(&st::Sub_Scene_Structure::Set_Render_Toggle), vv_found_sub_structure->second, std::placeholders::_1))),
																							v_play_once, (bool)std::stoi(v_arg_2));
																					}
																					else {
																						if (v_function_name == "SET_OSRENDER") {
																							v_scene->Create_Event<void>(
																								TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																								std::make_shared<COMPLEX_FUNCTION_3(std::wstring, std::wstring, bool)>(COMPLEX_FUNCTION_3(std::wstring, std::wstring, bool)(
																									m_sub_scene_render)),
																								(bool)v_play_once, TO_WSTRING(v_arg_1), TO_WSTRING(v_arg_2), (bool)std::stoi(v_arg_3));
																						}
																						else {
																							if (v_function_name == "PLAY_SOUND") {
																								v_scene->Create_Event<void, std::wstring>(
																									TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																									std::make_shared<COMPLEX_FUNCTION_2(std::wstring, bool)>(COMPLEX_FUNCTION_2(std::wstring, bool)(
																										std::bind(static_cast<void(st::Actor::*)(std::wstring, bool)>(&st::Actor::Play_Sound), v_scene->Access_Model(TO_WSTRING(v_sound_id)), std::placeholders::_1, std::placeholders::_2))),
																									(bool)v_play_once, std::move(TO_WSTRING(v_arg_1)), (bool)std::stoi(v_arg_2));
																							}
																							else {
																								if (v_function_name == "PAUSE_SOUND") {
																									v_scene->Create_Event<void, std::wstring>(
																										TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																										std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																											std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Pause_Sound), v_scene->Access_Model(TO_WSTRING(v_sound_id)), std::placeholders::_1))),
																										(bool)v_play_once, std::move(TO_WSTRING(v_arg_1)));
																								}
																								else {
																									if (v_function_name == "STOP_SOUND") {
																										v_scene->Create_Event<void, std::wstring>(
																											TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																											std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																												std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Stop_Sound), v_scene->Access_Model(TO_WSTRING(v_sound_id)), std::placeholders::_1))),
																											(bool)v_play_once, std::move(TO_WSTRING(v_arg_1)));
																									}
																									else {
																										if (v_function_name == "RESET_SOUND") {
																											v_scene->Create_Event<void, std::wstring>(
																												TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																												std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																													std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Reset_Sound), v_scene->Access_Model(TO_WSTRING(v_sound_id)), std::placeholders::_1))),
																												(bool)v_play_once, std::move(TO_WSTRING(v_arg_1)));
																										}
																										else {
																											if (v_function_name == "CHANGE_VOLUME") {
																												v_scene->Create_Event<void, std::wstring, float, bool>(
																													TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																													std::make_shared<COMPLEX_FUNCTION_3(std::wstring, float, bool)>(COMPLEX_FUNCTION_3(std::wstring, float, bool)(
																														std::bind(static_cast<void(st::Actor::*)(std::wstring, float, bool)>(&st::Actor::Change_Volume), v_scene->Access_Model(TO_WSTRING(v_sound_id)),
																															std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))),
																													(bool)v_play_once, TO_WSTRING(v_arg_1), std::stof(v_arg_2), (bool)std::stoi(v_arg_3));
																											}
																											else {
																												if (v_function_name == "SET_ACTIVE_INPUT") {
																													v_scene->Create_Event<void, std::wstring>(
																														TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																														std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																															std::bind(static_cast<void(st::Game_Scene::*)(std::wstring)>(&st::Game_Scene::Set_Active_Input), v_scene, std::placeholders::_1))),
																														(bool)v_play_once, TO_WSTRING(v_arg_1));
																												}
																												else {
																													if (v_function_name == "TOGGLE_RENDER") {
																														v_scene->Create_Event<void, std::wstring>(
																															TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																															std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																																std::bind(static_cast<void(st::Game_Scene::*)(std::wstring)>(&st::Game_Scene::Toggle_Render), v_scene, std::placeholders::_1))),
																															(bool)v_play_once, TO_WSTRING(v_arg_1));
																													}
																													else {
																														if (v_function_name == "SET_TEXT") {
																															v_scene->Create_Event<void, std::wstring>(
																																TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																																std::make_shared<COMPLEX_FUNCTION_1(std::wstring)>(COMPLEX_FUNCTION_1(std::wstring)(
																																	std::bind(static_cast<void(st::Actor::*)(std::wstring)>(&st::Actor::Set_Text), v_scene->Access_Model(v_ws_id), std::placeholders::_1))),
																																(bool)v_play_once, TO_WSTRING(v_arg_1));
																														}
																														else {
																															if (v_function_name == "SET_TEXT_COLOR") {
																																v_scene->Create_Event<void, glm::vec4>(
																																	TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																																	std::make_shared<COMPLEX_FUNCTION_1(glm::vec4)>(COMPLEX_FUNCTION_1(glm::vec4)(
																																		std::bind(static_cast<void(st::Actor::*)(glm::vec4)>(&st::Actor::Set_Text_Color), v_scene->Access_Model(v_ws_id), std::placeholders::_1))),
																																	(bool)v_play_once, glm::vec4(std::stof(v_arg_1) / 255.0f, std::stof(v_arg_2) / 255.0f, std::stof(v_arg_3) / 255.0f, std::stof(v_arg_4) / 255.0f));
																															}
																															else {
																																if (v_function_name == "SET_COLOR") {
																																	v_scene->Create_Event<void, glm::vec4>(
																																		TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																																		std::make_shared<COMPLEX_FUNCTION_1(glm::vec4)>(COMPLEX_FUNCTION_1(glm::vec4)(
																																			std::bind(static_cast<void(st::Actor::*)(glm::vec4)>(&st::Actor::Set_Color), v_scene->Access_Model(v_ws_id), std::placeholders::_1))),
																																		(bool)v_play_once, glm::vec4(std::stof(v_arg_1) / 255.0f, std::stof(v_arg_2) / 255.0f, std::stof(v_arg_3) / 255.0f, std::stof(v_arg_4) / 255.0f));
																																}
																																else {
																																	if (v_function_name == "CLOSE_ENGINE") {
																																		v_scene->Create_Event<void>(
																																			TO_WSTRING(v_input_id), v_ws_id, TO_WSTRING(v_object_id),
																																			std::make_shared<COMPLEX_FUNCTION_0>(COMPLEX_FUNCTION_0(&cm::Engine_Constant::Close_Engine)),
																																			(bool)v_play_once);
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
																		}
																	}
																}
															}
														}
													}
												}
											}
											else {
												if (v_event_type == "KEYBOARD") {
													if (v_input_event == "PRESS") {
														function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_KEYBOARD_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
													}
													else {
														if (v_input_event == "RELEASE") {
															function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_KEYBOARD_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
														}
														else {
															if (v_input_event == "REPEAT") {
																function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_KEYBOARD_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_REPEAT, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
															}
														}
													}
												}
												else {
													if (v_event_type == "MOUSE") {
														if (v_input_event == "PRESS") {
															function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_MOUSE_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_PRESS, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
														}
														else {
															if (v_input_event == "RELEASE") {
																function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_MOUSE_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_RELEASE, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
															}
															else {
																if (v_input_event == "REPEAT") {
																	function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_MOUSE_EVENT, TO_WSTRING(v_function_name), v_button_code, GLFW_REPEAT, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
																}
															}
														}
													}
													else {
														if (v_event_type == "SCROLL") {
															if (v_input_event == "FORWARD") {
																function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_SCROLL_EVENT, TO_WSTRING(v_function_name), cm::Engine_Constant::PW_SCROLL_WHEEL_FORWARD, GLFW_PRESS, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
															}
															else {
																if (v_input_event == "BACKWARDS") {
																	function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_SCROLL_EVENT, TO_WSTRING(v_function_name), cm::Engine_Constant::PW_SCROLL_WHEEL_BACKWARD, GLFW_PRESS, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
																}
															}
														}
														else {
															if (v_event_type == "ANIM_START") {
																function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_ANIMATION_START_EVENT, TO_WSTRING(v_function_name), NULL, NULL, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
															}
															else {
																if (v_event_type == "ANIM_END") {
																	function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_ANIMATION_END_EVENT, TO_WSTRING(v_function_name), NULL, NULL, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
																}
																else {
																	v_ws_id = TO_WSTRING(v_sound_id);

																	if (v_event_type == "SOUND_START") {
																		function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_SOUND_START_EVENT, TO_WSTRING(v_function_name), NULL, NULL, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
																	}
																	else {
																		if (v_event_type == "SOUND_END") {
																			function_picker(TO_WSTRING(v_input_id), TO_WSTRING(v_sound_id), v_scene, v_sub_scene_structures, cm::Engine_Constant::PW_SOUND_END_EVENT, TO_WSTRING(v_function_name), NULL, NULL, v_main_actor, *i, (bool)v_play_once, v_arg_1, v_arg_2, v_arg_3, v_arg_4, v_arg_5);
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
				co::Engine_Input::Set_Scene_Event_Function(v_scene->Event_Callback());
				// End of loading event inputs
				if (v_current_event == v_current_input) {
					v_scene->Set_Active_Input(TO_WSTRING(v_current_input));
				}

				for (auto i = v_model_attachments.begin(); i != v_model_attachments.end(); i++) {
					if (v_scene->Access_Model(std::get<0>(*i)) != nullptr) {
						if (std::get<1>(*i) != nullptr) {
							std::get<1>(*i)->Model()->Attach_To(v_scene->Access_Model(std::get<0>(*i))->Model()->Position_Reference());
							std::get<1>(*i)->Model()->Set_Offset(std::get<2>(*i));
						}
					}
				}

				return v_scene;
			}
			void File_Loader::Load_Data_File(std::vector<st::Actor*>& p_scene_models,
				std::vector<st::Actor*>& p_collision_models,
				std::vector<std::tuple<std::wstring, st::Actor*, int32_t>>& p_s_id_holder,
				std::map<std::wstring, st::Sub_Scene_Structure*>& p_sub_scene_structures,
				std::filesystem::path& p_location, uint32_t& p_has_physics_factory, st::Physics_Factory* p_physics_factory,
				std::string& p_main_scene, std::vector<std::string>& p_sub_scenes, std::vector<std::tuple<std::wstring, st::Actor*, glm::vec2>>& p_model_attachments) {

				int32_t v_layer{ 0 };
				std::string v_s_id{};
				uint32_t v_is_main_s_id{ 0 };
				uint32_t v_is_text{ 0 };
				std::string v_font_type{};
				std::string v_texture{};
				uint32_t v_repeats{ 0 };
				uint32_t v_mesh_type{ 0 };
				int32_t v_color_id{ 0 };
				uint32_t v_color_r{ 0 };
				uint32_t v_color_b{ 0 };
				uint32_t v_color_g{ 0 };
				uint32_t v_color_a{ 0 };
				int32_t v_position_x{ 0 };
				int32_t v_position_y{ 0 };
				uint32_t v_rotation{ 0 };
				uint32_t v_size_x{ 0 };
				uint32_t v_size_y{ 0 };
				uint32_t v_is_animated{ 0 };
				uint32_t v_has_animation_extention{ 0 };
				float v_animation_length{ 0.0f };
				uint32_t v_animation_frame_count{ 0 };
				uint32_t v_animation_frame_size_x{ 0 };
				uint32_t v_is_async_animation{ 0 };
				uint32_t v_has_physics{ 0 };
				std::string v_body_type{};
				uint32_t v_is_fixed{ 0 };
				float v_friction{ 0.0f };
				float v_restitution{ 0.0f };
				float v_density{ 0.0f };
				std::string v_sound_structure{};

				uint32_t v_is_attached{ 0 };
				std::string v_attachment_id{};
				float v_offset_x{ 0.0f };
				float v_offset_y{ 0.0f };

				uint32_t v_is_linear{ 0 };

				std::string v_body_shape{};
				uint32_t v_fixed_rotation{ 0 };

				uint32_t v_is_sensor{ 0 };

				p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(p_main_scene), L".csv");

				io::CSVReader<39, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
					v_file_data_reader{ p_location.generic_string().c_str() };
				v_file_data_reader.read_header(io::ignore_extra_column,
					"Layer", "S_ID", "Is_Main_ID_Actor", "Is_Attached", "Attachment_ID", "Offset_X", "Offset_Y", "Is_Text", "Font_Type", "Texture", "Texture_Repeats", "Is_Linear",
					"Mesh_Type", "Color_ID", "ColorR", "ColorG", "ColorB", "ColorA",
					"PositionX", "PositionY", "Rotation", "SizeX", "SizeY",
					"Is_Animated", "Has_Animation_Extention", "Animation_Length", "Animation_Frame_Count", "Animation_Frame_Size_X", "Is_Async_Animation",
					"Has_Physics", "Is_Sensor", "Body_Type", "Shape", "Fixed_Rot", "Is_Fixed", "Friction", "Restitution", "Density", "Sound_Structure");
				while (v_file_data_reader.read_row(v_layer, v_s_id, v_is_main_s_id, v_is_attached, v_attachment_id, v_offset_x, v_offset_y, v_is_text, v_font_type, v_texture, v_repeats, v_is_linear,
					v_mesh_type, v_color_id, v_color_r, v_color_g, v_color_b, v_color_a,
					v_position_x, v_position_y, v_rotation, v_size_x, v_size_y, v_is_animated, v_has_animation_extention,
					v_animation_length, v_animation_frame_count, v_animation_frame_size_x, v_is_async_animation,
					v_has_physics, v_is_sensor, v_body_type, v_body_shape, v_fixed_rotation, v_is_fixed, v_friction,
					v_restitution, v_density, v_sound_structure)) {

					// Possible Animation cache
					std::vector<std::tuple<st::Animation*, st::Texture*>> v_animations{};
					std::vector<std::wstring> v_animation_ids{};
					bool v_animation_cache{ false };

					st::Texture* v_model_texture = nullptr;
					st::Text* v_model_text = nullptr;
					st::Texture_Structure* v_texture_structure = nullptr;
					st::Sound_Structure* v_sound_structure_container = nullptr;
					std::wstring v_font_id = TO_WSTRING(v_font_type);

					if (v_sound_structure != "NULL") {
						p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_sound_structure), L".csv");

						std::vector<std::wstring> v_sound_ids{};
						std::vector<st::Sound*> v_sound_holder{};

						std::string v_sound_id{};
						std::string v_sound_name{};
						uint32_t v_is_looping{ 0 };
						float v_volume{ 0.0f };
						uint32_t v_windows_style{ 0 };

						io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
							v_sound_data_reader{ p_location.generic_string().c_str() };
						v_sound_data_reader.read_header(io::ignore_extra_column,
							"Sound_ID", "Sound_Name", "Is_Looping", "Volume", "Windows_Style");
						while (v_sound_data_reader.read_row(v_sound_id, v_sound_name, v_is_looping, v_volume, v_windows_style)) {
							v_sound_ids.push_back(TO_WSTRING(v_sound_id));

							v_sound_holder.push_back(Load_Audio_File(TO_WSTRING(v_sound_name).c_str(), (bool)v_is_looping, v_volume, (bool)v_windows_style));
						}
						v_sound_structure_container = pw::Engine_Memory::Allocate<st::Sound_Structure, bool>(v_sound_holder, v_sound_ids);
					}
					if (v_is_animated == 1) {
						st::Animation* v_model_animation {};
						// Test for gif animation types
						if (v_has_animation_extention == 1) {
							std::string v_extension = v_texture.substr(v_texture.find_last_of("."), v_texture.size() - 1);
							if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
								// Test for .csv animation cache
								if (TRY_LINE strcmp(v_extension.c_str(), ".csv") != 0) {
									throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", EXCEPTION_LINE, __FILEW__, L"Load_Animation_File");
								}
								else {
									// Load the .csv file for the animation cache
									p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_texture));
									v_animation_cache = true;

									std::string v_animation_id{};
									std::string v_animation_location{};

									io::CSVReader<7, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
										v_animation_data_reader{ p_location.generic_string().c_str() };
									v_animation_data_reader.read_header(io::ignore_extra_column,
										"Animation_ID", "Animation", "Has_Animation_Extention", "Animation_Length",
										"Animation_Frame_Count", "Animation_Frame_Size_X", "Is_Async_Animation");
									while (v_animation_data_reader.read_row(v_animation_id, v_animation_location, v_has_animation_extention,
										v_animation_length, v_animation_frame_count, v_animation_frame_size_x, v_is_async_animation)) {
										try {
											if (v_has_animation_extention == 1) {
												v_extension = v_animation_location.substr(v_animation_location.find_last_of("."), v_animation_location.size() - 1);
												if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
													throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", EXCEPTION_LINE, __FILEW__, L"Load_Animation_File");
												}
												else {
													// It is a gif and needs to be loaded
													std::wstring v_texture_location{ TO_WSTRING(v_animation_location.c_str()) };
													std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, (bool) v_is_async_animation);
													v_model_texture = v_model_animation_structure._Myfirst._Val;
													v_model_animation = v_model_animation_structure._Get_rest()._Myfirst._Val;
													v_model_animation_structure._Get_rest()._Myfirst._Val = nullptr;
												}
											}
											else {
												// Is not a gif but a sprite-sheet of some kind
												std::wstring v_texture_location{ TO_WSTRING(v_animation_location.c_str()) };
												v_model_texture = co::File_Loader::Load_Texture_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, false, &m_animation_location);

												v_model_animation = pw::Engine_Memory::Allocate<st::Animation, bool>(v_animation_length, v_animation_frame_count, v_animation_frame_size_x, (bool)v_is_async_animation);
											}
											v_animations.push_back(std::make_tuple(v_model_animation, v_model_texture));
											v_animation_ids.push_back(TO_WSTRING(v_animation_id));
										}
										catch (const er::Warning_Error& v_error) {
											PW_PRINT_ERROR(v_error);

											er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
										}
									}
								}
							}
							else {
								try {
									// It is a gif and needs to be loaded
									std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
									std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, (bool)v_is_async_animation);
									v_model_texture = v_model_animation_structure._Myfirst._Val;
									v_model_animation = v_model_animation_structure._Get_rest()._Myfirst._Val;
									v_model_animation_structure._Get_rest()._Myfirst._Val = nullptr;
								}
								catch (const er::Warning_Error& v_error) {
									PW_PRINT_ERROR(v_error);

									er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
								}
							}
						}
						else {
							try {
								// Is not a gif but a sprite-sheet of some kind
								std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
								v_model_texture = co::File_Loader::Load_Texture_File(v_texture_location.c_str(), (bool)v_repeats, false, &m_animation_location);

								v_model_animation = pw::Engine_Memory::Allocate<st::Animation, bool>(v_animation_length, v_animation_frame_count, v_animation_frame_size_x, (bool)v_is_async_animation);
							}
							catch (const er::Warning_Error& v_error) {
								PW_PRINT_ERROR(v_error);

								er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
							}
						}
						if (v_animations.size() > 0) {
							v_model_texture = v_animations.at(0)._Get_rest()._Myfirst._Val;
						}
						// If this is true then do not create the model
						if (v_model_texture == nullptr) {
							continue;
						}
						// Test for color
						if (v_color_id > -1) {
							// It has a loadable default color
							glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

							if ((bool)v_is_text == true) {
								v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
								v_size_x = TO_UINT32(v_model_text->Size().x);
								v_size_y = TO_UINT32(v_model_text->Size().y);

								v_position_y = TO_INT32(v_model_text->Position().y + 1);
							}

							st::Model* vd_model{ pw::Engine_Memory::Allocate<st::Model, bool>((
								st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y), (float)v_rotation,
								glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats, (bool)v_fixed_rotation) };
							st::Actor* va_model {};
							if (v_animation_cache == true) {
								for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
									i->_Myfirst._Val->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());
								}

								if (v_sound_structure_container != nullptr) {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_sound_structure_container, v_layer);
								}
								else {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_layer);
								}
							}
							else {
								v_model_animation->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());

								if (v_sound_structure_container != nullptr) {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_sound_structure_container, v_layer);
								}
								else {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_layer);
								}
							}

							if (v_s_id != "NULL") {
								std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

								p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
							}
							if (v_is_attached == 1) {
								p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
							}

							if (p_has_physics_factory == 1) {
								if (v_has_physics == 1) {
									if (v_body_type == "b2_staticBody") {
										if (v_body_shape == "POLYGON") {
											p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
										}
										else {
											if (v_body_shape == "CIRCLE") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
										}
										va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
									}
									else {
										if (v_body_type == "b2_dynamicBody") {
											if (v_body_shape == "POLYGON") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
											else {
												if (v_body_shape == "CIRCLE") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
											}
											va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
										}
									}
									p_collision_models.push_back(va_model);
								}
							}

							p_scene_models.push_back(va_model);
						}
						else {
							if (v_color_id == -2) {
								// It is textured and has no color
								st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
									(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
									(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), (bool)v_repeats, (bool)v_fixed_rotation) };
								st::Actor* va_model {};
								if (v_animation_cache == true) {
									for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
										i->_Myfirst._Val->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());
									}

									if (v_sound_structure_container != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_layer);
									}
								}
								else {
									v_model_animation->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());

									if (v_sound_structure_container != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_layer);
									}
								}

								if (v_s_id != "NULL") {
									std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

									p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
								}

								if (v_is_attached == 1) {
									p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
								}

								if (p_has_physics_factory == 1) {
									if (v_has_physics == 1) {
										if (v_body_type == "b2_staticBody") {
											if (v_body_shape == "POLYGON") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
											else {
												if (v_body_shape == "CIRCLE") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
											}
											va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
										}
										else {
											if (v_body_type == "b2_dynamicBody") {
												if (v_body_shape == "POLYGON") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
												else {
													if (v_body_shape == "CIRCLE") {
														p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
													}
												}
												va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
											}
										}
										p_collision_models.push_back(va_model);
									}
								}

								p_scene_models.push_back(va_model);
							}
							else {
								// It has a custom color
								glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_g / 255.0f, (float)v_color_b / 255.0f, (float)v_color_a / 255.0f);

								if ((bool)v_is_text == true) {
									v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
									v_size_x = TO_UINT32(v_model_text->Size().x);
									v_size_y = TO_UINT32(v_model_text->Size().y);

									v_position_y = TO_INT32(v_model_text->Position().y + 1);
								}

								st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
									(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
									(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats, (bool)v_fixed_rotation) };
								st::Actor* va_model {};
								if (v_animation_cache == true) {
									for (auto i = v_animations.begin(); i != v_animations.end(); i++) {
										i->_Myfirst._Val->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());
									}

									if (v_sound_structure_container != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_layer);
									}
								}
								else {
									v_model_animation->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());

									if (v_sound_structure_container != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_layer);
									}
								}

								if (v_s_id != "NULL") {
									std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

									p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
								}

								if (v_is_attached == 1) {
									p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
								}

								if (p_has_physics_factory == 1) {
									if (v_has_physics == 1) {
										if (v_body_type == "b2_staticBody") {
											if (v_body_shape == "POLYGON") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
											else {
												if (v_body_shape == "CIRCLE") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
											}
											va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
										}
										else {
											if (v_body_type == "b2_dynamicBody") {
												if (v_body_shape == "POLYGON") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
												else {
													if (v_body_shape == "CIRCLE") {
														p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
													}
												}
												va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
											}
										}
										p_collision_models.push_back(va_model);
									}
								}

								p_scene_models.push_back(va_model);
							}
						}
					}
					else {
						if ((bool)v_is_text == false) {
							// Does not have animations
							if (strcmp(v_texture.c_str(), "D16") == 0) {
								try {
									v_model_texture = co::File_Loader::Load_Texture_File(L"White.png", (bool)v_repeats, (bool)v_is_linear, true, nullptr);
								}
								catch (const er::Warning_Error& v_error) {
									PW_PRINT_ERROR(v_error);

									er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
								}
							}
							else {
								std::string v_extension = v_texture.substr(v_texture.find_last_of("."), v_texture.size() - 1);
								if (TRY_LINE strcmp(v_extension.c_str(), ".csv") != 0) {
									try {
										std::wstring v_texture_location{ TO_WSTRING(v_texture) };
										v_model_texture = co::File_Loader::Load_Texture_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, false, nullptr);
									}
									catch (const er::Warning_Error& v_error) {
										PW_PRINT_ERROR(v_error);

										er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
									}
								}
								else {
									// It is a multi texture then load it
									p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_texture));
									io::CSVReader<3, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
										v_multi_texture_data_reader{ p_location.generic_string().c_str() };
									v_multi_texture_data_reader.read_header(io::ignore_extra_column,
										"Texture_ID", "Texture_Name", "Set_Current");

									std::string v_texture_id{};
									std::string v_temp_texture_location{};
									uint32_t v_set_current_texture{};

									std::vector<st::Texture*> v_textures;
									std::vector<std::wstring> v_texture_ids;

									while (v_multi_texture_data_reader.read_row(v_texture_id, v_temp_texture_location, v_set_current_texture)) {
										try {
											v_textures.push_back(co::File_Loader::Load_Texture_File(TO_WSTRING(v_temp_texture_location).c_str(), (bool)v_repeats, (bool)v_is_linear));
											v_texture_ids.push_back(TO_WSTRING(v_texture_id));
											if ((bool)v_set_current_texture == true) {
												v_model_texture = v_textures.back();
											}
										}
										catch (const er::Warning_Error& v_error) {
											PW_PRINT_ERROR(v_error);

											er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
										}
									}
									v_texture_structure = pw::Engine_Memory::Allocate<st::Texture_Structure, bool>(v_textures, v_texture_ids);
								}
							}
						}
						else {
							try {
								v_model_texture = co::File_Loader::Load_Texture_File(L"Empty.png", (bool)v_repeats, (bool)v_is_linear, true, nullptr);
							}
							catch (const er::Warning_Error& v_error) {
								PW_PRINT_ERROR(v_error);

								er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
							}
						}
						// If this is true then do not create the model
						if (v_model_texture == nullptr) {
							continue;
						}
						// Test for color
						if (v_color_id > -1) { // Default color is > -1
							glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

							if ((bool)v_is_text == true) {
								v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
								v_size_x = TO_UINT32(v_model_text->Size().x);
								v_size_y = TO_UINT32(v_model_text->Size().y);

								v_position_y = TO_INT32(v_model_text->Position().y + 1);
							}

							st::Model* vd_model{ pw::Engine_Memory::Allocate<st::Model, bool>(
								(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
								(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats, (bool)v_fixed_rotation) };
							st::Actor* va_model {};

							if (v_sound_structure_container != nullptr) {
								if (v_texture_structure != nullptr) {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_sound_structure_container, v_layer);
								}
								else {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_sound_structure_container, v_layer);
								}
							}
							else {
								if (v_texture_structure != nullptr) {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_layer);
								}
								else {
									va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_layer);
								}
							}

							if (v_s_id != "NULL") {
								std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

								p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
							}

							if (v_is_attached == 1) {
								p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
							}

							if (p_has_physics_factory == 1) {
								if (v_has_physics == 1) {
									if (v_body_type == "b2_staticBody") {
										if (v_body_shape == "POLYGON") {
											p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
										}
										else {
											if (v_body_shape == "CIRCLE") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
										}
										va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
									}
									else {
										if (v_body_type == "b2_dynamicBody") {
											if (v_body_shape == "POLYGON") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
											else {
												if (v_body_shape == "CIRCLE") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
											}
											va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
										}
									}
									p_collision_models.push_back(va_model);
								}
							}

							p_scene_models.push_back(va_model);
						}
						else {
							if (v_color_id == -2) { // No color or texture is > -2
								st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
									(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
									(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), (bool)v_repeats, (bool)v_fixed_rotation) };
								st::Actor* va_model {};

								if (v_sound_structure_container != nullptr) {
									if (v_texture_structure != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_sound_structure_container, v_layer);
									}
								}
								else {
									if (v_texture_structure != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_layer);
									}
								}


								if (v_s_id != "NULL") {
									std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

									p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
								}

								if (v_is_attached == 1) {
									p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
								}

								if (p_has_physics_factory == 1) {
									if (v_has_physics == 1) {
										if (v_body_type == "b2_staticBody") {
											if (v_body_shape == "POLYGON") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
											else {
												if (v_body_shape == "CIRCLE") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
											}
											va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
										}
										else {
											if (v_body_type == "b2_dynamicBody") {
												if (v_body_shape == "POLYGON") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
												else {
													if (v_body_shape == "CIRCLE") {
														p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
													}
												}
												va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
											}
										}
										p_collision_models.push_back(va_model);
									}
								}

								p_scene_models.push_back(va_model);
							}
							else { // -3 or any other number is for a custom color
								glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_g / 255.0f, (float)v_color_b / 255.0f, (float)v_color_a / 255.0f);

								if ((bool)v_is_text == true) {
									v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
									v_size_x = TO_UINT32(v_model_text->Size().x);
									v_size_y = TO_UINT32(v_model_text->Size().y);

									v_position_y = TO_INT32(v_model_text->Position().y + 1);
								}

								st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
									(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
									(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats, (bool)v_fixed_rotation) };
								st::Actor* va_model {};

								if (v_sound_structure_container != nullptr) {
									if (v_texture_structure != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_sound_structure_container, v_layer);
									}
								}
								else {
									if (v_texture_structure != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_layer);
									}
								}

								if (v_s_id != "NULL") {
									std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

									p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
								}

								if (v_is_attached == 1) {
									p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
								}

								if (p_has_physics_factory == 1) {
									if (v_has_physics == 1) {
										if (v_body_type == "b2_staticBody") {
											if (v_body_shape == "POLYGON") {
												p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
											}
											else {
												if (v_body_shape == "CIRCLE") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_staticBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
											}
											va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
										}
										else {
											if (v_body_type == "b2_dynamicBody") {
												if (v_body_shape == "POLYGON") {
													p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::POLYGON, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
												}
												else {
													if (v_body_shape == "CIRCLE") {
														p_physics_factory->Add_Object(vd_model, b2BodyType::b2_dynamicBody, st::Physics_Object::Object_Type::CIRCLE, v_is_sensor, vd_model->Id(), v_is_fixed, v_friction, v_restitution, v_density);
													}
												}
												va_model->Set_Physics_Object(p_physics_factory->Access_Memeber(vd_model->Id()));
											}
										}
										p_collision_models.push_back(va_model);
									}
								}

								p_scene_models.push_back(va_model);
							}
						}
					}
				}
				// End of main scene loading
				// Starting loading each sub-scene

				for (auto i = p_sub_scenes.begin(); i != p_sub_scenes.end(); i++) {
					// A vector to hold the model information
					std::vector<st::Actor*> v_sub_scene_models;
					// Since the scene is not the main scene then it need a
					// explicit event to trigger it	to render
					bool v_should_render = false;

					p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(*i), L".csv");
					// Notes on sub structure
					// Does not have physics involved
					// It could but setting all of the things would 
					// Be tiresome at the moment so for now no
					// Same loading as the main scene data accept no physics 
					io::CSVReader<30, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
						v_file_sub_data_reader{ p_location.generic_string().c_str() };
					v_file_sub_data_reader.read_header(io::ignore_extra_column,
						"Layer", "S_ID", "Is_Main_ID_Actor", "Is_Attached", "Attachment_ID", "Offset_X", "Offset_Y", "Is_Text", "Font_Type", "Texture", "Texture_Repeats", "Is_Linear",
						"Mesh_Type", "Color_ID", "ColorR", "ColorG", "ColorB", "ColorA",
						"PositionX", "PositionY", "Rotation", "SizeX", "SizeY",
						"Is_Animated", "Has_Animation_Extention", "Animation_Length", "Animation_Frame_Count", "Animation_Frame_Size_X", "Is_Async_Animation", "Sound_Structure");
					while (v_file_sub_data_reader.read_row(v_layer, v_s_id, v_is_main_s_id, v_is_attached, v_attachment_id, v_offset_x, v_offset_y, v_is_text, v_font_type, v_texture, v_repeats, v_is_linear,
						v_mesh_type, v_color_id, v_color_r, v_color_g, v_color_b, v_color_a,
						v_position_x, v_position_y, v_rotation, v_size_x, v_size_y, v_is_animated, v_has_animation_extention,
						v_animation_length, v_animation_frame_count, v_animation_frame_size_x, v_is_async_animation, v_sound_structure)) {

						// Possible Animation cache
						std::vector<std::tuple<st::Animation*, st::Texture*>> v_animations{};
						std::vector<std::wstring> v_animation_ids{};
						bool v_animation_cache{ false };

						st::Texture* v_model_texture = nullptr;
						st::Text* v_model_text = nullptr;
						st::Texture_Structure* v_texture_structure = nullptr;
						st::Sound_Structure* v_sound_structure_container = nullptr;
						std::wstring v_font_id = TO_WSTRING(v_font_type);

						if (v_sound_structure != "NULL") {
							p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_sound_structure), L".csv");

							std::vector<std::wstring> v_sound_ids{};
							std::vector<st::Sound*> v_sound_holder{};

							std::string v_sound_id{};
							std::string v_sound_name{};
							uint32_t v_is_looping{ 0 };
							float v_volume{ 0.0f };
							uint32_t v_windows_style{ 0 };

							io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
								v_sound_data_reader{ p_location.generic_string().c_str() };
							v_sound_data_reader.read_header(io::ignore_extra_column,
								"Sound_ID", "Sound_Name", "Is_Looping", "Volume", "Windows_Style");
							while (v_sound_data_reader.read_row(v_sound_id, v_sound_name, v_is_looping, v_volume, v_windows_style)) {
								v_sound_ids.push_back(TO_WSTRING(v_sound_id));

								v_sound_holder.push_back(Load_Audio_File(TO_WSTRING(v_sound_name).c_str(), (bool)v_is_looping, v_volume, (bool)v_windows_style));
							}
							v_sound_structure_container = pw::Engine_Memory::Allocate<st::Sound_Structure, bool>(v_sound_holder, v_sound_ids);
						}
						// Test for animations
						if (v_is_animated == 1) {
							st::Animation* v_model_animation {};
							// Test for gif animation types
							if (v_has_animation_extention == 1) {
								std::string v_extension = v_texture.substr(v_texture.find_last_of("."), v_texture.size() - 1);
								if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
									// Test for .csv animation cache
									if (TRY_LINE strcmp(v_extension.c_str(), ".csv") != 0) {
										throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", EXCEPTION_LINE, __FILEW__, L"Load_Animation_File");
									}
									else {
										// Load the .csv file for the animation cache
										p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_texture));
										v_animation_cache = true;

										std::string v_animation_id{};
										std::string v_animation_location{};

										io::CSVReader<6, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
											v_animation_data_reader{ p_location.generic_string().c_str() };
										v_animation_data_reader.read_header(io::ignore_extra_column,
											"Animation_ID", "Animation", "Has_Animation_Extention", "Animation_Length",
											"Animation_Frame_Count", "Animation_Frame_Size_X");
										while (v_animation_data_reader.read_row(v_animation_id, v_animation_location, v_has_animation_extention, v_animation_length, v_animation_frame_count, v_animation_frame_size_x)) {
											try {
												if (v_has_animation_extention == 1) {
													v_extension = v_animation_location.substr(v_animation_location.find_last_of("."), v_animation_location.size() - 1);
													if (TRY_LINE strcmp(v_extension.c_str(), ".gif") != 0) {
														throw er::Warning_Error(L"File Loader", L"Unknown animation file type.", EXCEPTION_LINE, __FILEW__, L"Load_Animation_File");
													}
													else {
														// It is a gif and needs to be loaded
														std::wstring v_texture_location{ TO_WSTRING(v_animation_location.c_str()) };
														std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, (bool)v_is_async_animation);
														v_model_texture = v_model_animation_structure._Myfirst._Val;
														v_model_animation = v_model_animation_structure._Get_rest()._Myfirst._Val;
														v_model_animation_structure._Get_rest()._Myfirst._Val = nullptr;
													}
												}
												else {
													// Is not a gif but a sprite-sheet of some kind
													std::wstring v_texture_location{ TO_WSTRING(v_animation_location.c_str()) };
													v_model_texture = co::File_Loader::Load_Texture_File(v_texture_location.c_str(), (bool)v_repeats, false, &m_animation_location);

													v_model_animation = pw::Engine_Memory::Allocate<st::Animation, bool>(v_animation_length, v_animation_frame_count, v_animation_frame_size_x, (bool)v_is_async_animation);
												}
												v_animations.push_back(std::make_tuple(v_model_animation, v_model_texture));
												v_animation_ids.push_back(TO_WSTRING(v_animation_id));
											}
											catch (const er::Warning_Error& v_error) {
												PW_PRINT_ERROR(v_error);

												er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
											}
										}
									}
								}
								else {
									try {
										// It is a gif and needs to be loaded
										std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
										std::tuple<st::Texture*, st::Animation*> v_model_animation_structure = co::File_Loader::Load_Animation_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, (bool)v_is_async_animation);
										v_model_texture = v_model_animation_structure._Myfirst._Val;
										v_model_animation = v_model_animation_structure._Get_rest()._Myfirst._Val;
										v_model_animation_structure._Get_rest()._Myfirst._Val = nullptr;
									}
									catch (const er::Warning_Error& v_error) {
										PW_PRINT_ERROR(v_error);

										er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
									}
								}
							}
							else {
								try {
									// Is not a gif but a sprite-sheet of some kind
									std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
									v_model_texture = co::File_Loader::Load_Texture_File(v_texture_location.c_str(), (bool)v_repeats, false, &m_animation_location);

									v_model_animation = pw::Engine_Memory::Allocate<st::Animation, bool>(v_animation_length, v_animation_frame_count, v_animation_frame_size_x, (bool)v_is_async_animation);
								}
								catch (const er::Warning_Error& v_error) {
									PW_PRINT_ERROR(v_error);

									er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
								}
							}
							if (v_animations.size() > 0) {
								v_model_texture = v_animations.at(0)._Get_rest()._Myfirst._Val;
							}
							// If this is true then do not create the model
							if (v_model_texture == nullptr) {
								continue;
							}
							// Test for color
							if (v_color_id > -1) {
								// It has a loadable default color
								glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

								if ((bool)v_is_text == true) {
									v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
									v_size_x = TO_UINT32(v_model_text->Size().x);
									v_size_y = TO_UINT32(v_model_text->Size().y);

									v_position_y = TO_INT32(v_model_text->Position().y + 1);
								}

								st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
									(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
									(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats) };
								st::Actor* va_model {};
								if (v_animation_cache == true) {
									for (auto j = v_animations.begin(); j != v_animations.end(); j++) {
										j->_Myfirst._Val->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());
									}

									if (v_sound_structure_container != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_layer);
									}
								}
								else {
									v_model_animation->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());

									if (v_sound_structure_container != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_layer);
									}
								}

								if (v_s_id != "NULL") {
									std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

									p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
								}

								if (v_is_attached == 1) {
									p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
								}

								v_sub_scene_models.push_back(va_model);
							}
							else {
								if (v_color_id == -2) {
									// It is textured and has no color
									st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
										(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
										(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), (bool)v_repeats) };
									st::Actor* va_model {};
									if (v_animation_cache == true) {
										for (auto j = v_animations.begin(); j != v_animations.end(); j++) {
											j->_Myfirst._Val->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());
										}

										if (v_sound_structure_container != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_sound_structure_container, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_layer);
										}
									}
									else {
										v_model_animation->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());

										if (v_sound_structure_container != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_sound_structure_container, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_layer);
										}
									}

									if (v_s_id != "NULL") {
										std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

										p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
									}

									if (v_is_attached == 1) {
										p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
									}

									v_sub_scene_models.push_back(va_model);
								}
								else {
									// It has a custom color
									glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_g / 255.0f, (float)v_color_b / 255.0f, (float)v_color_a / 255.0f);

									if ((bool)v_is_text == true) {
										v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
										v_size_x = TO_UINT32(v_model_text->Size().x);
										v_size_y = TO_UINT32(v_model_text->Size().y);

										v_position_y = TO_INT32(v_model_text->Position().y + 1);
									}

									st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
										(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
										(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats) };
									st::Actor* va_model {};
									if (v_animation_cache == true) {
										for (auto j = v_animations.begin(); j != v_animations.end(); j++) {
											j->_Myfirst._Val->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());
										}

										if (v_sound_structure_container != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_sound_structure_container, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_animations, v_animation_ids, v_layer);
										}
									}
									else {
										v_model_animation->Finish_Init(vd_model->Mesh()->Vertices(), vd_model->Mesh()->Vertex_Count());

										if (v_sound_structure_container != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_sound_structure_container, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_animation, v_layer);
										}
									}

									if (v_s_id != "NULL") {
										std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

										p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
									}

									if (v_is_attached == 1) {
										p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
									}

									v_sub_scene_models.push_back(va_model);
								}
							}
						}
						else {
							if ((bool)v_is_text == false) {
								// Does not have animations
								if (strcmp(v_texture.c_str(), "D16") == 0) {
									try {
										v_model_texture = co::File_Loader::Load_Texture_File(L"White.png", (bool)v_repeats, (bool)v_is_linear, true, nullptr);
									}
									catch (const er::Warning_Error& v_error) {
										PW_PRINT_ERROR(v_error);

										er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
									}
								}
								else {
									std::string v_extension = v_texture.substr(v_texture.find_last_of("."), v_texture.size() - 1);
									if (TRY_LINE strcmp(v_extension.c_str(), ".csv") != 0) {
										try {
											std::wstring v_texture_location{ TO_WSTRING(v_texture.c_str()) };
											v_model_texture = co::File_Loader::Load_Texture_File(v_texture_location.c_str(), (bool)v_repeats, (bool)v_is_linear, false, nullptr);
										}
										catch (const er::Warning_Error& v_error) {
											PW_PRINT_ERROR(v_error);

											er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
										}
									}
									else {
										// It is a multi texture then load it
										p_location = co::File_Finder::Find_File(m_data_location, TO_WSTRING(v_texture));

										io::CSVReader<3, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::ignore_overflow, io::single_line_comment<'#'>>
											v_multi_texture_data_reader{ p_location.generic_string().c_str() };
										v_multi_texture_data_reader.read_header(io::ignore_extra_column,
											"Texture_ID", "Texture_Name", "Set_Current");

										std::string v_texture_id{};
										std::string v_temp_texture_location{};
										uint32_t v_set_current_texture{};

										std::vector<st::Texture*> v_textures;
										std::vector<std::wstring> v_texture_ids;

										while (v_multi_texture_data_reader.read_row(v_texture_id, v_temp_texture_location, v_set_current_texture)) {
											try {
												v_textures.push_back(co::File_Loader::Load_Texture_File(TO_WSTRING(v_temp_texture_location).c_str(), (bool)v_repeats, (bool)v_is_linear));
												v_texture_ids.push_back(TO_WSTRING(v_texture_id));
												if ((bool)v_set_current_texture == true) {
													v_model_texture = v_textures.back();
												}
											}
											catch (const er::Warning_Error& v_error) {
												PW_PRINT_ERROR(v_error);

												er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
											}
										}
										v_texture_structure = pw::Engine_Memory::Allocate<st::Texture_Structure, bool>(v_textures, v_texture_ids);
									}
								}
							}
							else {
								try {
									v_model_texture = co::File_Loader::Load_Texture_File(L"Empty.png", (bool)v_repeats, (bool)v_is_linear, true, nullptr);
								}
								catch (const er::Warning_Error& v_error) {
									PW_PRINT_ERROR(v_error);

									er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);
								}
							}
							// If this is true then do not create the model
							if (v_model_texture == nullptr) {
								continue;
							}
							// Test for color
							if (v_color_id > -1) { // Default color is > -1
								glm::vec4 v_color = co::File_Loader::Default_Color((co::File_Loader::Default_Colors)v_color_id);

								if ((bool)v_is_text == true) {
									v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
									v_size_x = TO_UINT32(v_model_text->Size().x);
									v_size_y = TO_UINT32(v_model_text->Size().y);

									v_position_y = TO_INT32(v_model_text->Position().y + 1);
								}

								st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
									(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
									(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats) };
								st::Actor* va_model {};

								if (v_sound_structure_container != nullptr) {
									if (v_texture_structure != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_sound_structure_container, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_sound_structure_container, v_layer);
									}
								}
								else {
									if (v_texture_structure != nullptr) {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_layer);
									}
									else {
										va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_layer);
									}
								}

								if (v_s_id != "NULL") {
									std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

									p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
								}

								if (v_is_attached == 1) {
									p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
								}

								v_sub_scene_models.push_back(va_model);
							}
							else {
								if (v_color_id == -2) { // No color or texture is > -2
									st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
										(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
										(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), (bool)v_repeats) };
									st::Actor* va_model {};

									if (v_sound_structure_container != nullptr) {
										if (v_texture_structure != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_sound_structure_container, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_sound_structure_container, v_layer);
										}
									}
									else {
										if (v_texture_structure != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_layer);
										}
									}

									if (v_s_id != "NULL") {
										std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

										p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
									}

									if (v_is_attached == 1) {
										p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
									}

									v_sub_scene_models.push_back(va_model);
								}
								else { // -3 or any other number is for a custom color
									glm::vec4 v_color = glm::vec4((float)v_color_r / 255.0f, (float)v_color_g / 255.0f, (float)v_color_b / 255.0f, (float)v_color_a / 255.0f);

									if ((bool)v_is_text == true) {
										v_model_text = pw::Engine_Memory::Allocate<st::Text, bool>(TO_WSTRING(v_texture), glm::ivec2(v_position_x, v_position_y), glm::ivec2(v_size_x, v_size_y), v_color, v_font_id);
										v_size_x = TO_UINT32(v_model_text->Size().x);
										v_size_y = TO_UINT32(v_model_text->Size().y);

										v_position_y = TO_INT32(v_model_text->Position().y + 1);
									}

									st::Model* vd_model { pw::Engine_Memory::Allocate<st::Model, bool>(
										(st::Geometry_Types)v_mesh_type, v_model_texture, glm::vec2((float)v_position_x, (float)v_position_y),
										(float)v_rotation, glm::vec2((float)v_size_x, (float)v_size_y), v_color, (bool)v_repeats) };
									st::Actor* va_model {};

									if (v_sound_structure_container != nullptr) {
										if (v_texture_structure != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_sound_structure_container, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_sound_structure_container, v_layer);
										}
									}
									else {
										if (v_texture_structure != nullptr) {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_texture_structure, v_layer);
										}
										else {
											va_model = pw::Engine_Memory::Allocate<st::Actor, bool>(vd_model, v_model_text, v_layer);
										}
									}

									if (v_s_id != "NULL") {
										std::wstring vw_s_id{ TO_WSTRING(v_s_id) };

										p_s_id_holder.push_back(std::make_tuple(vw_s_id, va_model, v_is_main_s_id));
									}

									if (v_is_attached == 1) {
										p_model_attachments.push_back(std::make_tuple(TO_WSTRING(v_attachment_id), va_model, glm::vec2(v_offset_x, v_offset_y)));
									}

									v_sub_scene_models.push_back(va_model);
								}
							}
						}
					}
					// Allocate for the new structure
					st::Sub_Scene_Structure* v_sub_scene_structure = pw::Engine_Memory::Allocate<st::Sub_Scene_Structure, bool>(TO_WSTRING(*i), v_sub_scene_models, v_should_render);

					auto v_found = p_sub_scene_structures.find(TO_WSTRING(*i));
					if (v_found == p_sub_scene_structures.end()) {
						p_sub_scene_structures.insert(std::make_pair(TO_WSTRING(*i), v_sub_scene_structure));
					}
				}
				// End of loading each sub-scene
			}
			st::Sound* File_Loader::Load_Audio_File(const std::wstring& p_file_name, const bool& p_loops, const float& p_volume, const bool& p_windows_style) {
				// First make sure the file location exists
				std::filesystem::path v_location = co::File_Finder::Find_File(m_sound_location, p_file_name);
				// File information
				BYTE* v_file_buffer = nullptr;
				int32_t v_file_format = 0;
				int32_t v_buffer_size = 0;
				float v_frequency = 0;
				// Buffer
				uint32_t v_buffer_id = 0;
				// Source
				uint32_t v_source_id = 0;

				v_file_buffer = (BYTE*)alutLoadMemoryFromFile(v_location.string().c_str(), &v_file_format, &v_buffer_size, &v_frequency);

				PW_AL_VOID_CALL(alGenBuffers(1, &v_buffer_id));
				PW_AL_VOID_CALL(alBufferData(v_buffer_id, v_file_format, v_file_buffer, v_buffer_size, static_cast<int32_t>(v_frequency)));

				PW_AL_VOID_CALL(alGenSources(1, &v_source_id));
				PW_AL_VOID_CALL(alSourcei(v_source_id, AL_BUFFER, v_buffer_id));

				delete[] v_file_buffer;
				v_file_buffer = nullptr;

				if (p_loops == true) {
					PW_AL_VOID_CALL(alSourcei(v_source_id, AL_LOOPING, AL_TRUE));
				}
				if (p_windows_style == true) {
					PW_AL_VOID_CALL(alSourcef(v_source_id, AL_GAIN, p_volume / 100.0f));
				}
				else {
					PW_AL_VOID_CALL(alSourcef(v_source_id, AL_GAIN, p_volume));
				}

				return pw::Engine_Memory::Allocate<st::Sound, bool>(v_source_id, p_loops);
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////