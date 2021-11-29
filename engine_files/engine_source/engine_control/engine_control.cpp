#include "engine_control\engine_control.h"

//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	int32_t er::Engine_Error::PW_LINE_ = 0;
	std::wstring er::Engine_Error::PW_FILE_{};

	std::string er::Error_Log::m_console_log_name{
		[]() ->std::string {
			std::string v_temp = std::string(__TIME__ + std::string("_console_log.txt"));

			int16_t v_colon = v_temp.find(L':', 0);
			v_temp.erase(v_colon, 1);
			v_temp.insert(v_colon, 1, L'_');
			v_colon = v_temp.find(L':', 0);
			v_temp.erase(v_colon, 1);
			v_temp.insert(v_colon, 1, L'_');

			return v_temp;
		}()
	};
	std::string er::Error_Log::m_error_log_name{
		[]() ->std::string {
			std::string v_temp = std::string(__TIME__ + std::string("_error_log.txt"));

			int16_t v_colon = v_temp.find(L':', 0);
			v_temp.erase(v_colon, 1);
			v_temp.insert(v_colon, 1, L'_');
			v_colon = v_temp.find(L':', 0);
			v_temp.erase(v_colon, 1);
			v_temp.insert(v_colon, 1, L'_');

			return v_temp;
		}()
	};
	uint64_t er::Engine_Exception::m_exception_line{ 0 };

	uint64_t pw::Engine_Memory::m_heap_memory{ 0 };
	uint64_t pw::Engine_Memory::m_high_heap_memory{ 0 };
	std::map<void*, pw::Engine_Memory::Memory> pw::Engine_Memory::m_memory_pointers;

	int32_t cm::Engine_Constant::m_window_width{ 0 };
	int32_t cm::Engine_Constant::m_window_height{ 0 };
	int32_t cm::Engine_Constant::m_hafe_window_width{ 0 };
	int32_t cm::Engine_Constant::m_hafe_window_height{ 0 };

	const wchar_t* cm::Engine_Constant::m_window_name{ L"" };
	PW_DUNI_PTR(GLFWwindow, cm::Engine_Constant::Destroy_GLFW) cm::Engine_Constant::m_current_window{ nullptr };

	int32_t cm::Engine_Constant::m_mouse_x_position{ 0 };
	int32_t cm::Engine_Constant::m_mouse_y_position{ 0 };

	const float cm::Engine_Constant::m_inverse_z_tan{ -(1.0f / tan(glm::radians(45.0f / 2.0f))) };

	int32_t cm::Engine_Constant::m_frames{ 0 };
	int32_t cm::Engine_Constant::m_last_frames{ -1 };
	bool cm::Engine_Constant::m_engine_start{ true };

	std::clock_t cm::Engine_Constant::m_start_time{ 0 };
	std::clock_t cm::Engine_Constant::m_end_time{ 0 };
	float cm::Engine_Constant::m_delta_time{ 0.0f };
	float cm::Engine_Constant::m_elapsed_time{ 0 };

	int32_t cm::Engine_Constant::m_fps_max{0};
	std::vector<int16_t> cm::Engine_Constant::m_fps_averager;
	float cm::Engine_Constant::m_fps_average{0.0f};

	const glm::vec2 cm::Engine_Constant::m_physics_gravity{ glm::vec2(0.0f, -10.0f) };
	PW_FUNCTION cm::Engine_Constant::m_debug_info;

	uint64_t st::Model::model_counter{ 0 };
	uint64_t st::Model::model_id_assigner{ 0 };

	std::wstring co::Engine_Queue::project_name{};

	std::wstring* co::Engine_Queue::current_scene{ nullptr };
	std::map<std::wstring, st::Game_Scene*> co::Engine_Queue::scene_directory{};
	//////////////////////////////////
	CO_NAMESPACE_SRT
	//////////////////////////////////
		// Engine_Control::Destroy_GLFW
		// Static Declarations
		// Class Members
		// End of Class Members
		// Engine_Control
		// Static Declarations
		

		// Class Members
			Engine_Control::Engine_Control():
					main_window{}, m_no_error{ true }, m_has_terminated{ false },
					m_console_complete{ false }, m_glfw_complete{ false },
					m_font_complete{false}, m_queue_complete{ false } {
			}
			Engine_Control::~Engine_Control() {
			}
			void Engine_Control::Init_Engine(const wchar_t* display_name, int32_t display_width, int32_t display_height) {
				try {
					//////////////////////////////////
					// Settings
					//////////////////////////////////
					{
						co::cn::Console_Manip::Set_Up_Console();
						co::cn::Console_Manip::Draw_Screen();

						m_console_complete = true;

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Console", L"Load ( Complete )", ENGINE_MSG);
						#endif // PW_DEBUG_CODE

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
						// MSAA
						PW_GL_VOID_CALL(glfwWindowHint(GLFW_SAMPLES, 4), false);

						// For allowing modern extension features
						glewExperimental = GL_TRUE;

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Settings", L"Load Settings ( Complete )", ENGINE_MSG);
						#endif // PW_DEBUG_CODE
					}
					//////////////////////////////////
					// Window Creation
					//////////////////////////////////
					{
						// For creating a window to use for the application			     1`
						main_window = PW_DUNI_PTR(GLFWwindow, cm::Engine_Constant::Destroy_GLFW)(glfwCreateWindow(
							display_width, display_height,
							TO_STRING(display_name).c_str(),
							NULL, NULL));
						// For checking if any errors occurred
						if (!main_window) {
							er::Engine_Error::PW_Print_Error(er::Severe_Error(L"GLFW", L"Function Error", __LINE__ - 6, __FILEW__, L"glfwCreateWindow"));
						}
						#ifdef PW_DEBUG_MODE
							else {
								PRINT_MSG(L"GLFW", L"Window Creation ( Complete )", SUCCESS_MSG);
							}
						#endif // PW_DEBUG_MODE
						// Set the current window
						cm::Engine_Constant::Set_Window(&*main_window);
						// For setting the current context for GLEW to use 
						PW_GLFW_VOID_CALL(glfwMakeContextCurrent(main_window.get()));
						// MSAA
						PW_GL_VOID_CALL(glEnable(GL_MULTISAMPLE), false);
						// Enable Transparent textures
						PW_GL_VOID_CALL(glEnable(GL_BLEND), false);
						PW_GL_VOID_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), false);

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Settings", L"Display Creation  ( Complete )", ENGINE_MSG);
						#endif // PW_DEBUG_CODE
					}
					//////////////////////////////////
					// Constant Settings
					//////////////////////////////////
					{
						int32_t buffer_width = display_width;
						int32_t buffer_height = display_height;

						// For retrieving the buffer sizes for our given window
						PW_GLFW_VOID_CALL(glfwGetFramebufferSize(main_window.get(), &buffer_width, &buffer_height));

						cm::Engine_Constant::Set_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width)));
						cm::Engine_Constant::Set_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height)));
						buffer_width = buffer_width / 2;
						cm::Engine_Constant::Set_Hafe_Window_Width(std::move<uint32_t>(TO_UINT32(buffer_width)));
						buffer_height = buffer_height / 2;
						cm::Engine_Constant::Set_Hafe_Window_Height(std::move<uint32_t>(TO_UINT32(buffer_height)));
						cm::Engine_Constant::Set_Window_Name(display_name);
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
						PW_GLFW_VOID_CALL(glfwSetInputMode(main_window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL));
						//PW_GLFW_VOID_CALL(glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
					}
					//////////////////////////////////
					// Glew/Program Initialization
					//////////////////////////////////
					{
						// For checking if initializing GLEW failed
						PW_GL_CALL(glewInit() == GLEW_OK);

						#ifdef PW_DEBUG_MODE
							std::wstring v_version_msg{ TO_WSTRING((char*)glGetString(GL_VERSION)) };

							v_version_msg.insert(0, L"GLEW Version: ");

							PRINT_BLOCK(L"GLEW / Program", v_version_msg.c_str(), ENGINE_MSG);
						#endif // !PW_DEBUG_CODE

						#ifdef FREEIMAGE_LIB
							PW_FI_VOID_CALL(FreeImage_Initialise());
						#endif

					}
					//////////////////////////////////
					// Icon Setting
					//////////////////////////////////
					{
						PW_SRD_PTR(GLFWimage) icon = std::make_shared<GLFWimage>(pw::co::File_Loader::Load_Icon(L"Icon.png", true));

						PW_GLFW_VOID_CALL(glfwSetWindowIcon(main_window.get(), 1, icon.get()));

						pw::co::File_Loader::Unload_Icon();
					}
					//////////////////////////////////
					// Finish Up Program Things
					//////////////////////////////////
					{
						// For setting up view port size
						PW_GL_VOID_CALL(glViewport(0, 0, cm::Engine_Constant::Window_Width(), cm::Engine_Constant::Window_Height()), true);
						// For specifying which instance of the window will be used for callback
						PW_GLFW_VOID_CALL(glfwSetWindowUserPointer(main_window.get(), this));

						PW_GL_VOID_CALL(glEnable(GL_DEBUG_OUTPUT), true);

						PW_GLFW_VOID_CALL(glfwShowWindow(main_window.get()));
					}
				}
				catch (const er::Warning_Error& v_error) {
					er::Error_Log::Dump_Log(v_error);

					m_no_error = false;
				}
				catch (const er::Severe_Error& v_error) {
					er::Error_Log::Dump_Log(v_error);

					m_no_error = false;
				}
			}
			void Engine_Control::Run_Engine() {
				//////////////////////////////////
				// Init Key Engine Objects
				//////////////////////////////////
				st::Shader shader{};
				{
					try {
						shader.Create_Shader(L"engine_files/engine_resource/engine_essential/engine_shader/vertex_shader.shader", L"engine_files/engine_resource/engine_essential/engine_shader/fragment_shader.shader");

						st::Text_Renderer::Load_Engine_Font();

						m_font_complete = true;
					}
					catch (const er::Warning_Error& v_error) {
						er::Error_Log::Dump_Log(v_error);

						m_no_error = false; 
						return;
					}
					catch (const er::Severe_Error& v_error) {
						er::Error_Log::Dump_Log(v_error);

						m_no_error = false;
						return;
					}
					try {
						Init_Game();
					}
					catch (const er::Warning_Error& v_error) {
						er::Error_Log::Dump_Log(v_error);

						m_no_error = false;
						return;
					}
					catch (const er::Severe_Error& v_error) {
						er::Error_Log::Dump_Log(v_error);

						m_no_error = false;
						return;
					}
					try {
						Engine_Queue::Load_From_Dir(L"game/",
							shader, main_window, std::make_shared<PW_FUNCTION>(std::bind(&pw::co::Engine_Control::Update_Engine_State, this)));

						m_queue_complete = true;

						#ifdef PW_DEBUG_MODE
							PRINT_BLOCK(L"Engine Queue", L"Project Load ( Completed )", ENGINE_MSG);
						#endif // !PW_DEBUG_CODE
					}
					catch (const er::Warning_Error& v_error) {
						er::Error_Log::Dump_Log(v_error);

						m_no_error = false;
						return;
					}
					catch (const er::Severe_Error& v_error) {
						er::Error_Log::Dump_Log(v_error);

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
							cm::Engine_Constant::Calc_Elapsed_Time(main_window.get());
							cm::Engine_Constant::Calc_Delta_Time();

							// Engine Input
							PW_GLFW_VOID_CALL(glfwPollEvents());
							// Any concurrent events need to be dealt with 
							Engine_Queue::Current_Scene()->Input()->Poll_Active_Events();
							// Engine Frame / Shader
							PW_GL_VOID_CALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f), false);
							PW_GL_VOID_CALL(glClear(GL_COLOR_BUFFER_BIT), false);
							// Update Model Information After An Event
							Engine_Queue::Pre_Queue();
							// Update the projection information for the vertex shader / fragment shader
							shader.Update_Projection();

							Before_Queue();

							// Engine Queue
							Engine_Queue::Run_Queue();

							After_Queue();

							// Swap Open GL Buffers
							Update_Engine_State();

							// Wait until the next frame should run
							cm::Engine_Constant::Wait();
						}
						catch (const er::Warning_Error& v_error) {
							er::Error_Log::Dump_Log(v_error);

							PW_PRINT_ERROR(v_error);
						}
						catch (const er::Severe_Error& v_error) {
							er::Error_Log::Dump_Log(v_error);

							m_no_error = false;
							return;
						}
					}
				}
			}
			void Engine_Control::Terminate_Engine() {
				//////////////////////////////////
				// Engine Clean Up
				//////////////////////////////////
				{
					if (m_has_terminated == false) {
						if (m_glfw_complete == true) {
							PW_GLFW_VOID_CALL(glfwTerminate());
						}
						if (m_font_complete == true) {
							st::Text_Renderer::Delete_Engine_Font();
						}
						if (m_queue_complete == true) {
							Engine_Queue::Clear_Queue();
						}
						m_has_terminated = true;

						#ifdef FREEIMAGE_LIB
							PW_FI_VOID_CALL(FreeImage_DeInitialise());
						#endif // FREEIMAGE_LIB

						if (m_console_complete == true) {
							er::Error_Log::Close_Log();
						}

						pw::Engine_Memory::Deallocate_All();

						if (m_console_complete == true) {
							#ifdef PW_DEBUG_MODE
								cn::Console_Manip::Delete_Console();
							#endif // PW_DEBUG_CODE
						}

					}
				}
			}
			void Engine_Control::Create_Callbacks() const {
				// Set up callback functions for handling key/mouse input
				PW_GLFW_VOID_CALL(glfwSetKeyCallback(main_window.get(), Engine_Input::Handle_Keyboard));
				PW_GLFW_VOID_CALL(glfwSetCursorPosCallback(main_window.get(), Engine_Input::Handle_Mouse_Movement));
				PW_GLFW_VOID_CALL(glfwSetMouseButtonCallback(main_window.get(), Engine_Input::Handle_Mouse_Button))
				// Handle resizing events with ease
				PW_GLFW_VOID_CALL(glfwSetFramebufferSizeCallback(main_window.get(), Engine_Input::Handle_Resize));
				// Handle Scroll Wheel Input
				PW_GLFW_VOID_CALL(glfwSetScrollCallback(main_window.get(), Engine_Input::Handle_Mouse_Scroll));
				// Create callback for image loading using FreeImage
				PW_FI_VOID_CALL(FreeImage_SetOutputMessage(er::Engine_Error::PW_FI_Callback_Handle));
			}
			void Engine_Control::Update_Engine_State() {
				PW_GLFW_VOID_CALL(glfwSwapBuffers(main_window.get()));
			}
			bool Engine_Control::Should_Close() const {
				return !glfwWindowShouldClose(main_window.get());
			}
			bool Engine_Control::No_Error() {
				return m_no_error;
			}
		// End of Class Members
	//////////////////////////////////
	CO_NAMESPACE_END
	//////////////////////////////////
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////

int main(int argc, char* argv[]) {
	pw::co::Engine_Control engine{};
	engine.Init_Engine(L"Pistonworks Window");
	if (engine.No_Error() == false) {
		engine.Terminate_Engine();
	}
	else {
		engine.Run_Engine();
		engine.Terminate_Engine();
		engine.~Engine_Control();
		return 0;
	}
	engine.~Engine_Control();
	return 0;
}