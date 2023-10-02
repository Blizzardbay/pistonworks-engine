#include "control\control.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Control
		// Static Declarations
		#ifdef PW_DEBUG_MODE
			std::chrono::steady_clock::time_point Control::m_debug_load_time{};
		#endif // PW_DEBUG_MODE
		// Class Members
			Control::Control() :
					m_require_game_path{ false },
					m_no_error{ true }, m_has_terminated{ false },
					m_console_complete{ false }, m_glfw_complete{ false },
					m_font_complete{ false }, m_queue_complete{ false }, 
					m_alut_complete{ false }, m_main_window{} {
			}
			void Control::Initialize_Engine(int argc, char* argv[], const std::wstring& p_window_name, const int32_t& p_window_width, const int32_t& p_window_height, const bool& p_require_game_path) {
				//////////////////////////////////
				// Engine Initialization
				//////////////////////////////////
				// Static variables that contain trees need to be 
				// allocated manually so we can get rid of their 
				// memory early. This is so we can track when all 
				// memory ( except _Fac_Node ) is deleted.
				if (pw::co::Memory::Initialize() != true) {
					pw::er::Error_Log::Dump_Log(
						pw::cm::Constant::Pistonworks_Path(),
						pw::er::Error_State::Severe_Error()
					);
					m_no_error = false;
					return;
				}
				pw::er::Error_State::Initialize(
					static_cast<void(*)(const pw::er::Warning_Error&)>(pw::er::Error::Print_Error),
					static_cast<void(*)(const pw::er::Severe_Error&)>(pw::er::Error::Print_Error)
				);
				PW_CALL(pw::st::Time_Constant::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(pw::co::Multi_Scope_Timer::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(pw::co::cn::Console_Manip::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(pw::co::Async_Timer::Initialize(), false);
				PW_SET_RET(m_no_error, true);

				#ifdef PW_DEBUG_MODE
					pw::co::Multi_Scope_Timer v_load_timer_s{ L"DLT_S" };
					pw::co::Multi_Scope_Timer v_load_timer_ms{ L"DLT_MS" };
				#endif // PW_DEBUG_MODE

				if (pw::cm::Constant::Pistonworks_Path() == std::filesystem::path()) {
					m_no_error = false;
					co::cn::Console_Manip::Release();
					return;
				}

				m_require_game_path = p_require_game_path;

				if (m_require_game_path == true) {
					if (pw::cm::Constant::Game_Path() == std::filesystem::path()) {
						m_no_error = false;
						co::cn::Console_Manip::Release();
						return;
					}
				}

				PW_CALL(pw::co::Text_Renderer::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(pw::co::Engine_Queue::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(pw::co::Input::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(pw::co::File_Loader::Initialize(), false);
				PW_SET_RET(m_no_error, true);
				//////////////////////////////////
				// Settings
				//////////////////////////////////
				#ifdef PW_DEBUG_MODE
					PW_CALL(co::cn::Console_Manip::Set_Up_Console(), false);
					PW_SET_RET(m_no_error, true);
					PW_CALL(co::cn::Console_Manip::Draw_Screen(), false);
					PW_SET_RET(m_no_error, true);

					m_console_complete = true;
				#else
					FreeConsole();
					m_console_complete = false;
				#endif // PW_DEBUG_MODE

				#ifdef PW_DEBUG_MODE
					PW_CALL(PRINT_BLOCK(L"Console", L"Load ( Completed )", ENGINE_MSG), false);
					PW_SET_RET(m_no_error, true);
				#endif // PW_DEBUG_MODE

				// For Handling GLFW Errors
				PW_GLFW_VOID_CALL(glfwSetErrorCallback(er::Error::GLFW_Callback_Handle), false);
				PW_SET_RET(m_no_error, true);

				// For the initializing GLFW
				PW_GLFW_CALL(glfwInit(), false);
				PW_SET_RET(m_no_error, true);

				m_glfw_complete = true;
						
				// For setting the major  \/ and minor \/ version of GLFW
				// Version---------------->3     .      3
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4), false);
				PW_SET_RET(m_no_error, true);
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5), false);
				PW_SET_RET(m_no_error, true);
				// For only using newer code and excluding other older code
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE), false);
				PW_SET_RET(m_no_error, true);
				// For allowing newer than are defined version code for able use
				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE), false);
				PW_SET_RET(m_no_error, true);

				PW_GLFW_VOID_CALL(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE), false);
				PW_SET_RET(m_no_error, true);

				// For allowing modern extension features
				glewExperimental = GL_TRUE;

				#ifdef PW_DEBUG_MODE
					PW_CALL(PRINT_BLOCK(L"Settings", L"Load Settings ( Completed )", ENGINE_MSG), false);
					PW_SET_RET(m_no_error, true);
				#endif // PW_DEBUG_MODE
				//////////////////////////////////
				// Window Creation
				//////////////////////////////////
				// For creating a window to use for the application
				TRY_LINE m_main_window = std::unique_ptr<GLFWwindow, cm::Destroy_GLFW>(glfwCreateWindow(
					p_window_width, p_window_height,
					TO_STRING(p_window_name).c_str(),
					NULL, NULL));
				// For checking if any errors occurred
				if (!m_main_window) {
					SET_ERROR_STATE(PW_GLFW_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::Control", L"Unable to create window.", ERROR_LINE, __FILEW__, L"Initialize_Engine"));
					PW_SET_RET(m_no_error, true);
				}
				#ifdef PW_DEBUG_MODE
					else {
						PW_CALL(PRINT_MSG(L"GLFW", L"Window Creation ( Completed )", SUCCESS_MSG), false);
						PW_SET_RET(m_no_error, true);
					}
				#endif // PW_DEBUG_MODE
				// Set the current window
				PW_CALL(cm::Constant::Set_Window(&m_main_window), false);
				PW_SET_RET(m_no_error, true);
				// For setting the current context for GLEW to use 
				PW_GLFW_VOID_CALL(glfwMakeContextCurrent(&*m_main_window), false);
				PW_SET_RET(m_no_error, true);
				// MSAA
				PW_GL_VOID_CALL(glfwWindowHint(GLFW_SAMPLES, TO_INT32(2 * GetDpiForWindow(glfwGetWin32Window(&*m_main_window)))), false, false);
				PW_SET_RET(m_no_error, true);
				// MSAA
				PW_GL_VOID_CALL(glEnable(GL_MULTISAMPLE), false, false);
				PW_SET_RET(m_no_error, true);
				// Enable Transparent textures
				PW_GL_VOID_CALL(glEnable(GL_BLEND), false, false);
				PW_SET_RET(m_no_error, true);
				PW_GL_VOID_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false, false);
				PW_SET_RET(m_no_error, true);

				#ifdef PW_DEBUG_MODE
					PW_CALL(PRINT_BLOCK(L"Settings", L"Display Creation  ( Completed )", ENGINE_MSG), false);
					PW_SET_RET(m_no_error, true);
				#endif // PW_DEBUG_MODE
				//////////////////////////////////
				// Constant Settings
				//////////////////////////////////
				int32_t buffer_width = p_window_width;
				int32_t buffer_height = p_window_height;

				// For retrieving the buffer sizes for our given window
				PW_GLFW_VOID_CALL(glfwGetFramebufferSize(&*m_main_window, &buffer_width, &buffer_height), false);
				PW_SET_RET(m_no_error, true);

				PW_CALL(cm::Constant::Set_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width))), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(cm::Constant::Set_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height))), false);
				PW_SET_RET(m_no_error, true);

				buffer_width = buffer_width / 2;
				PW_CALL(cm::Constant::Set_Hafe_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width))), false);
				PW_SET_RET(m_no_error, true);
				buffer_height = buffer_height / 2;
				PW_CALL(cm::Constant::Set_Hafe_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height))), false);
				PW_SET_RET(m_no_error, true);
				PW_CALL(cm::Constant::Set_Window_Name(p_window_name), false);
				PW_SET_RET(m_no_error, true);

				GLFWmonitor* v_monitor = glfwGetPrimaryMonitor();

				cm::Constant::Set_Refresh_Rate(glfwGetVideoMode(v_monitor)->refreshRate);

				(void)pw::st::Camera::Update_Camera();
				//////////////////////////////////
				// Input Callback Init
				//////////////////////////////////
				// For enabling various callbacks to input functions
				PW_CALL(Create_Callbacks(), false);
				PW_SET_RET(m_no_error, true);
				// For enabling or disabling certain settings for window properties
				// GLFW_CURSOR : For enabling or disabling the mouse in the window
				// GLFW_CURSOR_DISABLED : For off , GLFW_CURSOR_NORMAL : For on
				PW_GLFW_VOID_CALL(glfwSetInputMode(&*m_main_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL), false);
				PW_SET_RET(m_no_error, true);
				//////////////////////////////////
				// Glew/Program Initialization
				//////////////////////////////////
				// For checking if initializing GLEW failed
				PW_GL_CALL(glewInit() == GLEW_OK, false);
				PW_SET_RET(m_no_error, true);

				#ifdef PW_DEBUG_MODE
					PW_CALL(std::wstring v_version_msg{ TO_WSTRING(glfwGetVersionString()) }, false);
					PW_SET_RET(m_no_error, true);

					PW_CALL(PRINT_BLOCK(L"GLEW Version", v_version_msg.c_str(), ENGINE_MSG), false);
					PW_SET_RET(m_no_error, true);
				#endif // PW_DEBUG_MODE

				#ifdef FREEIMAGE_LIB
					PW_FI_VOID_CALL(FreeImage_Initialise());
				#endif
				//////////////////////////////////
				// Icon Setting
				//////////////////////////////////
				PW_CALL(GLFWimage* v_icon = pw::co::File_Loader::Load_Icon(L"Icon.png", true), false);
				PW_SET_RET(m_no_error, true);

				PW_GLFW_VOID_CALL(glfwSetWindowIcon(&*m_main_window, 1, v_icon), false);
				PW_SET_RET(m_no_error, true);

				pw::co::File_Loader::Unload_Icon();

				if (pw::co::Memory::Deallocate<GLFWimage>(v_icon) == false) {
					if (v_icon != nullptr) {
						delete v_icon;
						v_icon = nullptr;
					}
				}
				//////////////////////////////////
				// Finish Up Program Things
				//////////////////////////////////
				// For setting up view port size
				PW_GL_VOID_CALL(glViewport(0, 0, TO_INT32(cm::Constant::Window_Width()), TO_INT32(cm::Constant::Window_Height())), false, true);
				PW_SET_RET(m_no_error, true);

				PW_GL_VOID_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), false, false);
				PW_SET_RET(m_no_error, true);

				// For specifying which instance of the window will be used for callback
				PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(&*m_main_window, this), false);
				PW_SET_RET(m_no_error, true);

				PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT), false, true);
				PW_SET_RET(m_no_error, true);

				PW_GLFW_VOID_CALL(glfwShowWindow(&*m_main_window), false);
				PW_SET_RET(m_no_error, true);

				if (TRY_LINE alutInit(&argc, argv) != AL_TRUE) {
					SET_ERROR_STATE(PW_AL_ERROR);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::Control", L"Unable to initialize ALUT.", ERROR_LINE, __FILEW__, L"Initialize_Engine"));
					PW_SET_RET(m_no_error, true);
				}
				else {
					m_alut_complete = true;
				}

				pw::co::Engine_Queue::Set_Scene_Functions(
					std::bind(&Control::Pre_Scene_Load, this, std::placeholders::_1),
					std::bind(&Control::Post_Scene_Load, this, std::placeholders::_1),
					std::bind(&Control::Pre_Scene_Change, this, std::placeholders::_1),
					std::bind(&Control::Post_Scene_Change, this, std::placeholders::_1),
					std::bind(&Control::Pre_Scene_Removal, this, std::placeholders::_1),
					std::bind(&Control::Post_Scene_Removal, this, std::placeholders::_1));

				// Set debug function if in debug mode
				#ifdef PW_DEBUG_MODE
					cm::Constant::Set_Debug_Function(pw::co::Engine_Queue::Print_Debug_Stats);
				#endif // PW_DEBUG_MODE
			}
			void Control::Run_Engine() {
				//////////////////////////////////
				// Init Key Engine Objects
				//////////////////////////////////
				PW_CALL(pw::co::Shader::Create_Shader(L"/files/resource/essential/shader/vertex.shader",
					L"/files/resource/essential/shader/fragment.shader"), true);

				PW_CALL(pw::st::Model::Initialize(), true);

				PW_CALL(Pre_Load(), true);

				if (m_require_game_path == true) {
					PW_CALL(Engine_Queue::Load_From_Dir(m_main_window, std::make_shared<PW_FUNCTION>(std::bind(&pw::co::Control::Update_Engine_State, this))), true);
				}
				else {
					// Load default font for non-project loading users
					PW_CALL(Text_Renderer::Load_Engine_Fonts_Default(), true);
				}

				m_font_complete = true;

				m_queue_complete = true;

				PW_GLFW_VOID_CALL(glfwSwapInterval(TO_INT16(cm::Constant::Vsync())), true);

				#ifdef PW_DEBUG_MODE
					PW_CALL(PRINT_BLOCK(L"Engine Queue", L"Project Load ( Completed )", ENGINE_MSG), true);
				#endif // PW_DEBUG_MODE

				PW_CALL(Initialize_Game(), true);

				pw::co::Multi_Scope_Timer::Print_End<std::chrono::milliseconds, double>(L"DLT_MS", { L"", L"Load Time: ", ENGINE_MSG }, false);
				PW_AFTER_CALL(L"Print_End<std::chrono::milliseconds, double>", true);
				pw::co::Multi_Scope_Timer::Print_End<std::chrono::seconds, double>(L"DLT_S", { L"", L"Load Time: ", ENGINE_MSG }, false);
				PW_AFTER_CALL(L"Print_End<std::chrono::seconds, double>", true);
				//////////////////////////////////
				// Run Engine
				//////////////////////////////////
				while (Control::Should_Close()) {
					// Calculate needed time constants
					PW_CALL(cm::Constant::Calc_Elapsed_Time(&*m_main_window), true);

					// Engine Input
					PW_GLFW_VOID_CALL(glfwPollEvents(), true);
					// Any concurrent events need to be dealt with 
					pw::co::Input* v_current_input = pw::co::Input::Current_Input();
					if (v_current_input != nullptr) {
						PW_CALL(v_current_input->Poll_Active_Events(), true);
					}
					// Engine Frame / Shader
					PW_GL_VOID_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f), true, false);
					PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), true, false);
					// Update Model Information After An Event
					PW_CALL(Engine_Queue::Pre_Queue(), true);
					// Update the projection information for the vertex shader / fragment shader
					PW_CALL(pw::co::Shader::Use(), true);
					PW_CALL(pw::co::Shader::Update_Projection(), true);

					PW_CALL(Before_Queue(), true);

					// Engine Queue
					PW_CALL(Engine_Queue::Run_Queue(), true);

					PW_CALL(After_Queue(), true);

					// Render
					PW_CALL(pw::st::Model::Draw(), true);

					// Swap Open GL Buffers
					PW_CALL(Update_Engine_State(), true);

					// Do final calculations before the next frame
					cm::Constant::Wait();
				}
			}
			void Control::Release_Engine() {
				//////////////////////////////////
				// Engine Clean Up
				//////////////////////////////////
				// Errors at this point cannot be safely tracked.
				// Something really bad must of happened.
				if (m_has_terminated == false) {
					if (m_glfw_complete == true) {
						glfwTerminate();
					}
					if (m_font_complete == true) {
						pw::co::Text_Renderer::Release();
					}
					if (m_queue_complete == true) {
						Engine_Queue::Release();
					}
					m_has_terminated = true;

					#ifdef FREEIMAGE_LIB
						PW_FI_VOID_CALL(FreeImage_DeInitialise());
					#endif // FREEIMAGE_LIB

					if (m_console_complete == true) {
						er::Error_Log::Close_Log(pw::cm::Constant::Pistonworks_Path());
					}

					pw::co::Shader::Release();

					Release_Game();

					if (m_alut_complete == true) {
						pw::co::Listener::Release();
						alutExit();
					}
					pw::cm::Constant::Release();
					pw::er::Error::Release();
					pw::co::File_Loader::Release();
					pw::co::Input::Release();
					pw::st::Time_Constant::Release();
					pw::co::Multi_Scope_Timer::Release();
					pw::st::Model::Release();
					pw::co::Async_Timer::Release();

					#ifdef PW_DEBUG_MODE
						if (m_console_complete == true) {
							cn::Console_Manip::Release();
						}
					#endif // PW_DEBUG_MODE

					pw::co::Memory::Release_All();
				}
			}
			void Control::Create_Callbacks() const {
				// Set up callback functions for handling key/mouse input
				PW_GLFW_VOID_CALL(glfwSetKeyCallback(&*m_main_window, Input::Handle_Keyboard), true);
				PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(&*m_main_window, Input::Handle_Mouse_Movement), true);
				PW_GLFW_VOID_CALL(glfwSetMouseButtonCallback(&*m_main_window, Input::Handle_Mouse_Button), true)
				// Handle resizing events with ease
				PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(&*m_main_window, Input::Handle_Resize), true);
				// Handle Scroll Wheel Input
				PW_GLFW_VOID_CALL(glfwSetScrollCallback(&*m_main_window, Input::Handle_Mouse_Scroll), true);
				// Create callback for image loading using FreeImage
				PW_FI_VOID_CALL(FreeImage_SetOutputMessage(er::Error::FI_Callback_Handle), true);
			}
			void Control::Update_Engine_State() {
				PW_GLFW_VOID_CALL(glfwSwapBuffers(&*m_main_window), true);
			}
			bool Control::Should_Close() const {
				return !glfwWindowShouldClose(&*m_main_window);
			}
			const bool& Control::No_Error() const {
				return m_no_error;
			}
	CO_NAMESPACE_END
PW_NAMESPACE_END