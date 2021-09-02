#include "engine_control\engine_file_loader.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// File_Loader               
		// Static Declarations
			glm::vec4 File_Loader::Engine_Colors[(PW_UINT)Default_Colors::Color_Count]{
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
			PW_CSTRING File_Loader::texture_dir{ "internal_engine_files/internal_engine_resource/textures/" };
			PW_CSTRING File_Loader::icon_dir{ "internal_engine_files/internal_engine_resource/icons/" };
		// Class Members
			Texture& File_Loader::Load_Texture_File(PW_CSTRING file_name) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_UNKNOWN };
				// False Result
				Texture* texture{ nullptr };
				// First make sure the file location exists
				PW_STRING file_location{ file_name };

				PW_BOOL found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(texture_dir)) {
					// If the texture is found break
					if (found_file == true) {
						break;
					}
					// If the texture dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							PW_STRING temp_file = file_finder.path().generic_string();
							temp_file.erase(0,temp_file.find_last_of("/") + 1);
							// If the texture name is correct then we found the correct path
							if (strcmp(temp_file.c_str(), file_name) == 0) {
								found_file = true;
								// Save the correct path
								file_location = file_finder.path().generic_string();
							}
						}
					}
				}
				if (found_file == false) {
					PW_PRINT_ERROR("Pistonworks Engine", "Could not find file");
					return *texture;
				}
				// Get the file type of the image
				PW_FI_VOID_CALL(image_type = FreeImage_GetFileType(file_location.c_str()));

				if (image_type == FIF_UNKNOWN) {
					PW_FI_VOID_CALL(image_type = FreeImage_GetFIFFromFilename(file_location.c_str()));

					if (image_type == FIF_UNKNOWN) {
						PW_PRINT_ERROR("FreeImage_GetFileType", "FIF_UNKNOWN");
						return *texture;
					}
				}
				// Check if the file type is able to be loaded
				if (FreeImage_FIFSupportsReading(image_type) == (BOOL)true) {
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
							PW_PRINT_ERROR("Pistonworks Engine", "Unsupported Type");
							return *texture;
						}
					}
				}
				else {
					PW_PRINT_ERROR("FreeImage_FIFSupportsReading", "Unsupported Type");
					return *texture;
				}
			}
			std::tuple<Texture*, Animation*> File_Loader::Load_Animation_File(PW_CSTRING file_name) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_UNKNOWN };
				// File
				FIBITMAP* file{ nullptr };
				FIMULTIBITMAP* gif_bitmap{ nullptr };
				// Image Data
				PW_BYTE* image_data{ nullptr };
				// Length / Width of image
				PW_UINT width{ 0 };
				PW_UINT height{ 0 };
				// Total frame time
				PW_UINT frame_time{ 0 };
				// Result
				Texture* texture{ nullptr };
				Animation* animation{ nullptr };
				// First make sure the file location exists
				PW_STRING file_location{ file_name };

				PW_BOOL found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(texture_dir)) {
					// If the texture is found break
					if (found_file == true) {
						break;
					}
					// If the texture dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							PW_STRING temp_file = file_finder.path().generic_string();
							temp_file.erase(0, temp_file.find_last_of("/") + 1);
							// If the texture name is correct then we found the correct path
							if (strcmp(temp_file.c_str(), file_name) == 0) {
								found_file = true;
								// Save the correct path
								file_location = file_finder.path().generic_string();
							}
						}
					}
				}
				if (found_file == false) {
					PW_PRINT_ERROR("Pistonworks Engine", "Could not find file");
					return std::tuple<Texture*, Animation*>(texture, animation);
				}
				// Get the file type of the image
				PW_FI_VOID_CALL(image_type = FreeImage_GetFileType(file_location.c_str()));

				if (image_type == FIF_UNKNOWN) {
					PW_FI_VOID_CALL(image_type = FreeImage_GetFIFFromFilename(file_location.c_str()));

					if (image_type == FIF_UNKNOWN) {
						PW_PRINT_ERROR("FreeImage_GetFileType", "FIF_UNKNOWN");
						return std::tuple<Texture*, Animation*>(texture, animation);
					}
				}
				// Check if the file type is able to be loaded
				if (FreeImage_FIFSupportsReading(image_type) == (BOOL)true) {		
						gif_bitmap = FreeImage_OpenMultiBitmap(FIF_GIF, file_location.c_str(), false, true);

						PW_UINT frames = FreeImage_GetPageCount(gif_bitmap);

						PW_UINT bytes_per_pixel = 0;

						PW_UINT overall_width = 0;

						PW_UINT size = 0;


						for (PW_SIZE i = 0; i < frames; i++) {
							// Open the bitmap from the gif
							FIBITMAP* bitmap = FreeImage_LockPage(gif_bitmap, TO_INT(i));
							// Convert bitmap to RGBA with 4 bytes per pixel
							bitmap = FreeImage_ConvertTo32Bits(bitmap);
							if (i == 0) {
								bytes_per_pixel = FreeImage_GetBPP(bitmap) / TO_UINT(8);

								image_data = new BYTE[TO_UINT(FreeImage_GetWidth(bitmap)) * TO_UINT(FreeImage_GetHeight(bitmap)) * frames * bytes_per_pixel];

								size = TO_UINT(FreeImage_GetWidth(bitmap)) * TO_UINT(FreeImage_GetHeight(bitmap)) * frames * bytes_per_pixel;

								overall_width = TO_UINT(FreeImage_GetWidth(bitmap)) * frames * bytes_per_pixel;

								width = FreeImage_GetWidth(bitmap);
								height = FreeImage_GetHeight(bitmap);

								// Get meta data by loading
								FIBITMAP* metadata_bitmap = FreeImage_Load(FIF_GIF, file_location.c_str(), GIF_LOAD256);
								// get animation meta data
								PW_UINT metadata_entries{ FreeImage_GetMetadataCount(FIMD_ANIMATION, metadata_bitmap) };
								if (metadata_entries != NULL) {
									FITAG* tag{ nullptr };

									// create a meta data to sort
									FIMETADATA* meta_data{ nullptr };

									meta_data = FreeImage_FindFirstMetadata(FIMD_ANIMATION, metadata_bitmap, &tag);

									for (PW_SIZE i = 0; i < 2; i++) {
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
							PW_UINT frame_width = FreeImage_GetWidth(bitmap);
							PW_UINT frame_height = FreeImage_GetHeight(bitmap);

							PW_BYTE* temp_pixel_data = FreeImage_GetBits(bitmap);
							// Put said pixel data into the image_data array
							for (PW_UINT j = 0; j < frame_height; j++) {
								for (PW_UINT k = 0; k < frame_width * bytes_per_pixel; k++) {
									image_data[k + (j * overall_width) + ((frame_width * bytes_per_pixel) * i)] = temp_pixel_data[k + (j * (frame_width * bytes_per_pixel))];
								}
							}
							FreeImage_UnlockPage(gif_bitmap, bitmap, false);
						}
						// Create Texture
						texture = new Texture(image_data, width * frames, height, GL_RGBA, GL_BGRA);

						delete[] image_data;
						// Create Animation
						animation = new Animation(static_cast<PW_FLOAT>(frame_time) / static_cast<PW_FLOAT>(CLOCKS_PER_SEC), frames, width);

						FreeImage_Unload(file);

						FreeImage_CloseMultiBitmap(gif_bitmap);

						return std::tuple<Texture*, Animation*>(texture, animation);
				}
				else {
					PW_PRINT_ERROR("FreeImage_FIFSupportsReading", "Unsupported Type");
					return std::tuple<Texture*, Animation*>(texture, animation);
				}
			}
			GLFWimage& File_Loader::Load_Icon(PW_CSTRING file_name) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_UNKNOWN };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				PW_BYTE* image_data{ nullptr };
				// Length / Width of image / Pitch
				PW_UINT width{ 0 };
				PW_UINT height{ 0 };
				PW_UINT pitch{ 0 };
				// Result
				GLFWimage* glfw_image{ new GLFWimage() };
				// First make sure the file location exists
				PW_STRING file_location{ file_name };

				PW_BOOL found_file = false;

				for (const auto& file_finder : std::filesystem::recursive_directory_iterator(icon_dir)) {
					// If the texture is found break
					if (found_file == true) {
						break;
					}
					// If the texture dir exists then search for the file
					if (file_finder.exists() == true) {
						// If the path is empty 
						if (file_finder.path().empty() == false) {
							// Get rid of the path and only find the name
							PW_STRING temp_file = file_finder.path().generic_string();
							temp_file.erase(0, temp_file.find_last_of("/") + 1);
							// If the texture name is correct then we found the correct path
							if (strcmp(temp_file.c_str(), file_name) == 0) {
								found_file = true;
								// Save the correct path
								file_location = file_finder.path().generic_string();
							}
						}
					}
				}
				if (found_file == false) {
					PW_PRINT_ERROR("Pistonworks Engine", "Could not find file");
					return *glfw_image;
				}
				// Get the file type of the image
				PW_FI_VOID_CALL(image_type = FreeImage_GetFileType(file_location.c_str()));

				if (image_type == FIF_UNKNOWN) {
					PW_FI_VOID_CALL(image_type = FreeImage_GetFIFFromFilename(file_location.c_str()));

					if (image_type == FIF_UNKNOWN) {
						PW_PRINT_ERROR("FreeImage_GetFileType", "FIF_UNKNOWN");
						return *glfw_image;
					}
				}
				// Check if the file type is able to be loaded
				if (FreeImage_FIFSupportsReading(image_type) == (BOOL)true) {
					if (image_type == FIF_PNG) {
						// Load File
						PW_FI_VOID_CALL(file = FreeImage_Load(image_type, file_location.c_str()));

						if (!file == true) {
							PW_PRINT_ERROR("FreeImage_Load", "Unable to load");
							return *glfw_image;
						}
						// If successful get data
						width = FreeImage_GetWidth(file);
						height = FreeImage_GetHeight(file);
						pitch = FreeImage_GetPitch(file);

						PW_UINT bits_per_pixel = FreeImage_GetBPP(file);

						image_data = FreeImage_GetBits(file);
						
						for (PW_SIZE y = 0; y < height; y++) {
							BYTE* image_data = FreeImage_GetScanLine(file, (PW_INT)y);
							for (PW_SIZE x = 0; x < width; x++) {
								BYTE temp = image_data[FI_RGBA_RED];
								image_data[FI_RGBA_RED] = image_data[FI_RGBA_BLUE];
								image_data[FI_RGBA_BLUE] = temp;
								// Got to the next pixel
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
						PW_PRINT_ERROR("Pistonworks Engine", "Unsupported Type");
						return *glfw_image;
					}
				}
				else {
					PW_PRINT_ERROR("FreeImage_FIFSupportsReading", "Unsupported Type");
					return *glfw_image;
				}
			}
			PW_VOID File_Loader::Unload_Icon() {
				FreeImage_Unload(current_icon);
			}
			glm::vec4 File_Loader::Default_Color(Default_Colors color) {
				return Engine_Colors[(PW_INT)color];
			}
			Texture& File_Loader::Load_PNG(PW_CSTRING file_location) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_PNG };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				PW_BYTE* image_data{ nullptr };
				// Length / Width of image
				PW_UINT width{ 0 };
				PW_UINT height{ 0 };
				// Result
				Texture* texture{ nullptr };

				// Load File
				PW_FI_VOID_CALL(file = FreeImage_Load(image_type, file_location, PNG_DEFAULT));

				if (!file == true) {
					PW_PRINT_ERROR("FreeImage_Load", "Unable to load");
					return *texture;
				}
				if (FreeImage_HasPixels(file) == (BOOL)true) {
					// If successful get data
					image_data = FreeImage_GetBits(file);

					width = FreeImage_GetWidth(file);
					height = FreeImage_GetHeight(file);

					// Create Texture
					texture = new Texture(image_data, width, height, GL_RGBA, GL_BGRA);

					FreeImage_Unload(file);

					return *texture;
				}
				else {
					PW_PRINT_ERROR("FreeImage_HasPixels", "No Pixel Data");
					return *texture;
				}
			}
			Texture& File_Loader::Load_BMP(PW_CSTRING file_location) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_BMP };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				PW_BYTE* image_data{ nullptr };
				// Length / Width of image
				PW_UINT width{ 0 };
				PW_UINT height{ 0 };
				// Result
				Texture* texture{ nullptr };

				// Load File
				PW_FI_VOID_CALL(file = FreeImage_Load(image_type, file_location, BMP_DEFAULT));

				if (!file == true) {
					PW_PRINT_ERROR("FreeImage_Load", "Unable to load");
					return *texture;
				}
				if (FreeImage_HasPixels(file) == (BOOL)true) {
					// If successful get data
					image_data = FreeImage_GetBits(file);

					width = FreeImage_GetWidth(file);
					height = FreeImage_GetHeight(file);

					// Create Texture
					texture = new Texture(image_data, width, height, GL_RGB, GL_BGR);

					FreeImage_Unload(file);

					return *texture;
				}
				else {
					PW_PRINT_ERROR("FreeImage_HasPixels", "No Pixel Data");
					return *texture;
				}
			}
			Texture& File_Loader::Load_JPEG(PW_CSTRING file_location) {
				// File Type
				FREE_IMAGE_FORMAT image_type{ FIF_JPEG };
				// File
				FIBITMAP* file{ nullptr };
				// Image Data
				PW_BYTE* image_data{ nullptr };
				// Length / Width of image
				PW_UINT width{ 0 };
				PW_UINT height{ 0 };
				// Result
				Texture* texture{ nullptr };

				// Load File
				PW_FI_VOID_CALL(file = FreeImage_Load(image_type, file_location, JPEG_DEFAULT));

				if (!file == true) {
					PW_PRINT_ERROR("FreeImage_Load", "Unable to load");
					return *texture;
				}
				if (FreeImage_HasPixels(file) == (BOOL)true) {
					// If successful get data
					image_data = FreeImage_GetBits(file);

					width = FreeImage_GetWidth(file);
					height = FreeImage_GetHeight(file);

					// Create Texture
					texture = new Texture(image_data, width, height, GL_RGB, GL_BGR);

					FreeImage_Unload(file);

					return *texture;
				}
				else {
					PW_PRINT_ERROR("FreeImage_HasPixels", "No Pixel Data");
					return *texture;
				}
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////