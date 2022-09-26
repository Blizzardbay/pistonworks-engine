#include "engine_control\engine_control.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// Engine_Control
		// Static Declarations
		#ifdef PW_DEBUG_MODE
			std::chrono::system_clock::time_point Engine_Control::m_debug_load_time{};
		#endif // PW_DEBUG_MODE
		// Class Members
			Engine_Control::Engine_Control():
					m_require_game_path{ false },
					m_no_error{ true }, m_has_terminated{ false },
					m_console_complete{ false }, m_glfw_complete{ false },
					m_font_complete{ false }, m_queue_complete{ false }, 
					m_alut_complete{ false }, m_main_window{} {
			}
			void Engine_Control::Initialize_Engine(int argc, char* argv[], const std::wstring& p_window_name, const int32_t& p_window_width, const int32_t& p_window_height, const bool& p_require_game_path) {
				try {
					//////////////////////////////////
					// Engine Initialization
					//////////////////////////////////
					{
						// Static variables that contain trees need to be 
						// allocated manually so we can get rid of their 
						// memory early. This is so we can track when all 
						// memory ( except _Fac_Node ) is deleted.
						pw::Engine_Memory::Initialize_Memory();
						pw::co::cn::Console_Manip::Initialize_Console();

						#ifdef PW_DEBUG_MODE
							m_debug_load_time = std::chrono::system_clock::now();
						#endif // PW_DEBUG_MODE

						if (pw::cm::Engine_Constant::Pistonworks_Path() == std::filesystem::path()) {
							m_no_error = false;
							co::cn::Console_Manip::Release_Console();
							return;
						}

						m_require_game_path = p_require_game_path;

						if (m_require_game_path == true) {
							if (pw::cm::Engine_Constant::Game_Path() == std::filesystem::path()) {
								m_no_error = false;
								co::cn::Console_Manip::Release_Console();
								return;
							}
						}

						pw::st::Text_Renderer::Initialize_Text_Renderer();
						pw::co::Engine_Queue::Initialize_Queue();
						pw::co::Engine_Input::Initialize_Input();
						pw::co::File_Loader::Initialize_Loader();
					}
					//////////////////////////////////
					// Settings
					//////////////////////////////////
					{
						#ifdef PW_DEBUG_MODE
							co::cn::Console_Manip::Set_Up_Console();
							co::cn::Console_Manip::Draw_Screen();

							m_console_complete = true;
						#else
							FreeConsole();
							m_console_complete = false;
						#endif // PW_DEBUG_MODE

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Console", L"Load ( Completed )", ENGINE_MSG);
						#endif // PW_DEBUG_MODE

						// For Handling GLFW Errors
						PW_GLFW_VOID_CALL(glfwSetErrorCallback(er::Engine_Error::PW_GLFW_Callback_Handle));

						// For the initializing GLFW
						PW_GLFW_CALL(glfwInit());

						m_glfw_complete = true;
						
						// For setting the major  \/ and minor \/ version of GLFW
						// Version---------------->3     .      3
						PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
						PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
						// For only using newer code and excluding other older code
						PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
						// For allowing newer than are defined version code for able use
						PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));

						PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));

						// For allowing modern extension features
						glewExperimental = GL_TRUE;

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Settings", L"Load Settings ( Completed )", ENGINE_MSG);
						#endif // PW_DEBUG_MODE
					}
					//////////////////////////////////
					// Window Creation
					//////////////////////////////////
					{
						// For creating a window to use for the application			     1`
						TRY_LINE m_main_window = std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>(glfwCreateWindow(
							p_window_width, p_window_height,
							TO_STRING(p_window_name).c_str(),
							NULL, NULL));
						// For checking if any errors occurred
						if (!m_main_window) {
							throw er::Severe_Error(L"GLFW", L"Function Error", pw::er::Engine_Exception::Exception_Line(), __FILEW__, L"glfwCreateWindow");
						}
						#ifdef PW_DEBUG_MODE
							else {
								PRINT_MSG(L"GLFW", L"Window Creation ( Completed )", SUCCESS_MSG);
							}
						#endif // PW_DEBUG_MODE
						// Set the current window
						cm::Engine_Constant::Set_Window(&m_main_window);
						// For setting the current context for GLEW to use 
						PW_GLFW_VOID_CALL(glfwMakeContextCurrent(&*m_main_window));
						// MSAA
						PW_GL_VOID_CALL(glfwWindowHint(GLFW_SAMPLES, 2 * GetDpiForWindow(glfwGetWin32Window(&*m_main_window))), false);
						// MSAA
						PW_GL_VOID_CALL(glEnable(GL_MULTISAMPLE), false);
						// Enable Transparent textures
						PW_GL_VOID_CALL(glEnable(GL_BLEND), false);
						PW_GL_VOID_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Settings", L"Display Creation  ( Completed )", ENGINE_MSG);
						#endif // PW_DEBUG_MODE
					}
					//////////////////////////////////
					// Constant Settings
					//////////////////////////////////
					{
						int32_t buffer_width = p_window_width;
						int32_t buffer_height = p_window_height;

						// For retrieving the buffer sizes for our given window
						PW_GLFW_VOID_CALL(glfwGetFramebufferSize(&*m_main_window, &buffer_width, &buffer_height));

						cm::Engine_Constant::Set_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width)));
						cm::Engine_Constant::Set_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height)));
						buffer_width = buffer_width / 2;
						cm::Engine_Constant::Set_Hafe_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width)));
						buffer_height = buffer_height / 2;
						cm::Engine_Constant::Set_Hafe_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height)));
						cm::Engine_Constant::Set_Window_Name(p_window_name);

						GLFWmonitor* v_monitor = glfwGetPrimaryMonitor();

						cm::Engine_Constant::Set_Refresh_Rate(glfwGetVideoMode(v_monitor)->refreshRate);
					}
					//////////////////////////////////
					// Input Callback Init
					//////////////////////////////////
					{
						// For enabling various callbacks to input functions
						Create_Callbacks();
						/* For enabling or disabling certain settings for window properties*/
						/* GLFW_CURSOR : For enabling or disabling the mouse in the window */
						/* GLFW_CURSOR_DISABLED : For off , GLFW_CURSOR_NORMAL : For on    */
						PW_GLFW_VOID_CALL(glfwSetInputMode(&*m_main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
						//PW_GLFW_VOID_CALL(glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
					}
					//////////////////////////////////
					// Glew/Program Initialization
					//////////////////////////////////
					{
						// For checking if initializing GLEW failed
						PW_GL_CALL(glewInit() == GLEW_OK);

						#ifdef PW_DEBUG_MODE
							std::wstring v_version_msg{ TO_WSTRING(glfwGetVersionString()) };

							PRINT_BLOCK(L"GLEW Version", v_version_msg.c_str(), ENGINE_MSG);
						#endif // PW_DEBUG_MODE

						#ifdef FREEIMAGE_LIB
							PW_FI_VOID_CALL(FreeImage_Initialise());
						#endif
					}
					//////////////////////////////////
					// Icon Setting
					//////////////////////////////////
					{
						GLFWimage* v_icon = pw::co::File_Loader::Load_Icon(L"Icon.png", true);

						PW_GLFW_VOID_CALL(glfwSetWindowIcon(&*m_main_window, 1, v_icon));

						pw::co::File_Loader::Unload_Icon();

						if (pw::Engine_Memory::Deallocate<GLFWimage>(v_icon) == false) {
							if (v_icon != nullptr) {
								delete v_icon;
								v_icon = nullptr;
							}
						}
					}
					//////////////////////////////////
					// Finish Up Program Things
					//////////////////////////////////
					{
						// For setting up view port size
						PW_GL_VOID_CALL(glViewport(0, 0, cm::Engine_Constant::Window_Width(), cm::Engine_Constant::Window_Height()), true);

						PW_GL_VOID_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), false);

						// For specifying which instance of the window will be used for callback
						PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(&*m_main_window, this));

						PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT), true);

						PW_GLFW_VOID_CALL(glfwShowWindow(&*m_main_window));

						if (TRY_LINE alutInit(&argc, argv) != AL_TRUE) {
							throw er::Severe_Error(L"Alut", L"Function Error", pw::er::Engine_Exception::Exception_Line(), __FILEW__, L"alutInit");
						}
						else {
							m_alut_complete = true;
						}

						pw::co::Engine_Queue::Set_Scene_Functions(
							std::bind(&Engine_Control::Pre_Scene_Load, this, std::placeholders::_1),
							std::bind(&Engine_Control::Post_Scene_Load, this, std::placeholders::_1),
							std::bind(&Engine_Control::Pre_Scene_Change, this, std::placeholders::_1),
							std::bind(&Engine_Control::Post_Scene_Change, this, std::placeholders::_1),
							std::bind(&Engine_Control::Pre_Scene_Removal, this, std::placeholders::_1),
							std::bind(&Engine_Control::Post_Scene_Removal, this, std::placeholders::_1));

						// Set debug function if in debug mode
						#ifdef PW_DEBUG_MODE
							cm::Engine_Constant::Set_Debug_Function(pw::co::Engine_Queue::Print_Debug_Stats);
						#endif // PW_DEBUG_MODE
					}
				}
				catch (const er::Warning_Error& v_error) {
					er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);

					m_no_error = false;
				}
				catch (const er::Severe_Error& v_error) {
					er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);

					m_no_error = false;
				}
			}
			void Engine_Control::Run_Engine() {
				//////////////////////////////////
				// Init Key Engine Objects
				//////////////////////////////////
				{
					try {
						st::Dynamic_Shader::Create_Shader(L"/engine_files/engine_resource/engine_essential/engine_shader/dynamic_vertex.shader",
							L"/engine_files/engine_resource/engine_essential/engine_shader/dynamic_fragment.shader");

						Pre_Load();

						if (m_require_game_path == true) {
							Engine_Queue::Load_From_Dir(m_main_window, std::make_shared<PW_FUNCTION>(std::bind(&pw::co::Engine_Control::Update_Engine_State, this)));
						}

						m_font_complete = true;

						m_queue_complete = true;

						PW_GLFW_VOID_CALL(glfwSwapInterval(TO_INT16(cm::Engine_Constant::Vsync())));

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Engine Queue", L"Project Load ( Completed )", ENGINE_MSG);
						#endif // PW_DEBUG_MODE

						Initialize_Game();

						#ifdef PW_DEBUG_MODE
							std::chrono::system_clock::time_point v_end_load = std::chrono::system_clock::now();

							std::wstring v_load_seconds{ std::to_wstring(std::chrono::duration<double, std::milli>(v_end_load - m_debug_load_time).count() / 1000.0f) };
							std::wstring v_load_milli{ std::to_wstring(std::chrono::duration<double, std::milli>(v_end_load - m_debug_load_time).count()) };

							size_t v_period = v_load_seconds.find(L".");
							if (v_period != std::string::npos) {
								size_t v_decimal_count = v_load_seconds.size() - OFF64(v_period);
								if (v_decimal_count > 2) {
									v_decimal_count = v_decimal_count - 2;
									v_load_seconds.erase(OFF64(v_period) + 2, v_decimal_count);
								}
							}
							v_period = v_load_milli.find(L".");
							if (v_period != std::string::npos) {
								size_t v_decimal_count = v_load_milli.size() - OFF64(v_period);
								if (v_decimal_count > 2) {
									v_decimal_count = v_decimal_count - 2;
									v_load_milli.erase(OFF64(v_period) + 2, v_decimal_count);
								}
							}

							PRINT_MSG(L"Engine", L"Load Time: " + v_load_seconds + L" s.", ENGINE_MSG);
							PRINT_MSG(L"Engine", L"Load Time: " + v_load_milli + L" ms.", ENGINE_MSG);
						#endif // PW_DEBUG_MODE
					}
					catch (const er::Warning_Error& v_error) {
						er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);

						m_no_error = false; 
						return;
					}
					catch (const er::Severe_Error& v_error) {
						er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);

						m_no_error = false;
						return;
					}
				}
				//////////////////////////////////
				// Run Engine
				//////////////////////////////////
				{
					while (Engine_Control::Should_Close()) {
						try {
							// Calculate needed time constants
							cm::Engine_Constant::Calc_Elapsed_Time(&*m_main_window);

							// Engine Input
							PW_GLFW_VOID_CALL(glfwPollEvents());
							// Any concurrent events need to be dealt with 
							if (Engine_Queue::Current_Scene() != nullptr) {
								Engine_Queue::Current_Scene()->Input()->Poll_Active_Events();
							}
							// Engine Frame / Shader
							PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
							PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
							// Update Model Information After An Event
							Engine_Queue::Pre_Queue();
							// Update the projection information for the vertex shader / fragment shader
							st::Dynamic_Shader::Use();
							st::Dynamic_Shader::Update_Projection();

							Before_Queue();

							// Engine Queue
							Engine_Queue::Run_Queue();

							After_Queue();

							// Swap Open GL Buffers
							Update_Engine_State();

							// Do final calculations before the next frame
							cm::Engine_Constant::Wait();
						}
						catch (const er::Warning_Error& v_error) {
							er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);

							PW_PRINT_ERROR(v_error);
						}
						catch (const er::Severe_Error& v_error) {
							er::Error_Log::Dump_Log(pw::cm::Engine_Constant::Pistonworks_Path(), v_error);

							m_no_error = false;
							return;
						}
					}
				}
			}
			void Engine_Control::Release_Engine() {
				//////////////////////////////////
				// Engine Clean Up
				//////////////////////////////////
				{
					if (m_has_terminated == false) {
						if (m_glfw_complete == true) {
							PW_GLFW_VOID_CALL(glfwTerminate());
						}
						if (m_font_complete == true) {
							st::Text_Renderer::Release_Engine_Fonts();
						}
						if (m_queue_complete == true) {
							Engine_Queue::Release_Queue();
						}
						m_has_terminated = true;

						#ifdef FREEIMAGE_LIB
							PW_FI_VOID_CALL(FreeImage_DeInitialise());
						#endif // FREEIMAGE_LIB

						if (m_console_complete == true) {
							er::Error_Log::Close_Log(pw::cm::Engine_Constant::Pistonworks_Path());
						}

						st::Dynamic_Shader::Release_Shader();

						Release_Game();

						if (m_alut_complete == true) {
							st::Listener::Release_Listener();
							alutExit();
						}
						pw::cm::Engine_Constant::Release_Constants();
						pw::er::Engine_Error::Release_Error();
						pw::co::File_Loader::Release_Loader();
						pw::co::Engine_Input::Release_Input();

						#ifdef PW_DEBUG_MODE
							if (m_console_complete == true) {
								cn::Console_Manip::Release_Console();
							}
						#endif // PW_DEBUG_MODE

						pw::Engine_Memory::Deallocate_All();
					}
				}
			}
			void Engine_Control::Create_Callbacks() const {
				// Set up callback functions for handling key/mouse input
				PW_GLFW_VOID_CALL(glfwSetKeyCallback(&*m_main_window, Engine_Input::Handle_Keyboard));
				PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(&*m_main_window, Engine_Input::Handle_Mouse_Movement));
				PW_GLFW_VOID_CALL(glfwSetMouseButtonCallback(&*m_main_window, Engine_Input::Handle_Mouse_Button))
				// Handle resizing events with ease
				PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(&*m_main_window, Engine_Input::Handle_Resize));
				// Handle Scroll Wheel Input
				PW_GLFW_VOID_CALL(glfwSetScrollCallback(&*m_main_window, Engine_Input::Handle_Mouse_Scroll));
				// Create callback for image loading using FreeImage
				PW_FI_VOID_CALL(FreeImage_SetOutputMessage(er::Engine_Error::PW_FI_Callback_Handle));
			}
			void Engine_Control::Update_Engine_State() {
				PW_GLFW_VOID_CALL(glfwSwapBuffers(&*m_main_window));
			}
			bool Engine_Control::Should_Close() const {
				return !glfwWindowShouldClose(&*m_main_window);
			}
			const bool& Engine_Control::No_Error() const {
				return m_no_error;
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////