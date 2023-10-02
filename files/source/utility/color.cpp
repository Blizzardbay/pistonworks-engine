#include "utility\color.h"

PW_NAMESPACE_SRT
	UTIL_NAMESPACE_SRT
		// Color
		// Static Declarations
			glm::vec4 Color::m_engine_colors[(uint32_t)Default_Colors::Color_Count]{
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
			glm::vec4 Color::Default_Color(const Default_Colors& color) {
				return m_engine_colors[(int32_t)color];
			}
	UTIL_NAMESPACE_END
PW_NAMESPACE_END