#include "control\memory.h"

PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		// Memory 
		// Static Declarations
			uint64_t pw::co::Memory::m_heap_memory{ 0 };
			uint64_t pw::co::Memory::m_high_heap_memory{ 0 };
			uint64_t pw::co::Memory::m_allocations{ 0 };
			std::set<pw::co::Memory::Data>* pw::co::Memory::m_memory_pointers{ nullptr };
		// Class Members  
	CO_NAMESPACE_END
PW_NAMESPACE_END