// BSD 3 - Clause License
//
// Copyright(c) 2021, Darrian Corkadel
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and /or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef H_ENGINE_MEMORY
#define H_ENGINE_MEMORY
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <map>
#include <tuple>
#include <typeinfo>
#include <string>
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_exception.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Macros
#include "engine_common\engine_macro.h"
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	// //////////////////////////////////////////////////
	// PW_GLOBAL_API Class: pw::Engine_Memory
	// //////////////////////////////////////////////////
	// Purpose:
	//  Records and stores information about the
	//  engine's memory use. 
	// //////////////////////////////////////////////////
	class PW_GLOBAL_API Engine_Memory {
	// Default Class Structures
	public:
		// //////////////////////////////////////////////////
		// PW_STRUCTURES_API struct: pw::Engine_Memory::Memory
		// //////////////////////////////////////////////////
		// Purpose:
		//  Stores memory, memory blocks, memory size and
		//  memory type.
		// //////////////////////////////////////////////////
		struct PW_STRUCTURES_API Memory {
		// Default Class Structures
		public:
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Memory::Memory
			// //////////////////////////////////////////////////
			// Purpose:
			//  Creates a memory object to hold info about the
			//  registered memory.
			// //////////////////////////////////////////////////
			// Parameters: 4
			// (1) void* p_memory;
			// Purpose:
			//  A pointer to a set of memory blocks.   
			// (2) const size_t&& p_blocks;
			// Purpose:
			//  The amount of blocks the given memory has.
			// (3) const size_t&& p_byte_size;
			// Purpose:
			//  The amount of bytes for 1 block of memory.  
			// (4) std::string&& p_type_name;
			// Purpose:
			//  The type of data being stored. 
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Memory(void* p_memory, const size_t&& p_blocks, const size_t&& p_byte_size, std::string&& p_type_name) :
					m_stored_memory{ p_memory }, m_blocks{ p_blocks }, m_bytes{ p_byte_size }, m_type_name{ p_type_name } {
			}
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Memory::Memory
			// //////////////////////////////////////////////////
			// Purpose:
			//  Copys memory data into another structure.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const Memory& rhs;
			// Purpose:
			//  The data to copy into the structure. 
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Memory(const Memory& rhs) :
				m_stored_memory{ rhs.m_stored_memory }, m_blocks{ rhs.m_blocks }, m_bytes{ rhs.m_bytes }, m_type_name{ rhs.m_type_name } {
			}
			// //////////////////////////////////////////////////
			// CLASS_FUNCTION Function: Memory::operator=
			// //////////////////////////////////////////////////
			// Purpose:
			//  Copys memory data into another structure.
			// //////////////////////////////////////////////////
			// Parameters: 1
			// (1) const Memory& rhs;
			// Purpose:
			//  The data to copy into the structure. 
			// //////////////////////////////////////////////////
			CLASS_FUNCTION Memory operator=(const Memory& rhs) {
				m_stored_memory = rhs.m_stored_memory;
				m_blocks = rhs.m_blocks;
				m_bytes = rhs.m_bytes;
				m_type_name = rhs.m_type_name;

				return *this;
			}
		private:
		// Public Functions/Macros
		public:
		// Public Variables
		public:
			// Accessors
			ACCESSOR void*& Stored_Memory() {
				return m_stored_memory;
			}
			const ACCESSOR size_t& Blocks() const {
				return m_blocks;
			}
			const ACCESSOR size_t& Bytes() const {
				return m_bytes;
			}
			const ACCESSOR std::string& Type() const {
				return m_type_name;
			}
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
			// A pointer to the data stored
			void* m_stored_memory;
			// How many blocks of memory are there
			size_t m_blocks;
			// The size of all of the memory together
			size_t m_bytes;
			// The type of memory
			std::string m_type_name;
		};
	private:
	// Public Functions/Macros
	public:
		// //////////////////////////////////////////////////
		// UTILITY Function: Engine_Memory::Allocate
		// //////////////////////////////////////////////////
		// Purpose:
		//  Returns a newly allocated structure of the given
		//  type.
		// //////////////////////////////////////////////////
		// Parameters: 1
		// (1) size_t p_count = 1;
		// Purpose:
		//  The amount of structures to allocate.
		// //////////////////////////////////////////////////
		template<class type>
		static UTILITY type* Allocate(size_t p_count = 1) {
			// If we are only allocating one of a structure then there is different snytax 
			if (p_count == 1) {
				try {
					TRY_LINE type* v_memory = new type;
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + (sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers.insert(std::make_pair(v_memory, Memory(v_memory, std::move(p_count), std::move(sizeof(type) * p_count), typeid(type).name())));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immedetely
					// Since this is used by engine constant we cannot have access to the TO_WSTRING macro so we need to do some string magic
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", std::move(EXCEPTION_LINE), __FILEW__, L"No Function");
				}
			}
			else {
				try {
					TRY_LINE type* v_memory = new type[p_count];
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + (sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers.insert(std::make_pair(v_memory, Memory(v_memory, std::move(p_count), std::move(sizeof(type) * p_count), typeid(type).name())));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immedetely
					// Since this is used by engine constant we cannot have access to the TO_WSTRING macro so we need to do some string magic
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", std::move(EXCEPTION_LINE), __FILEW__, L"No Function");
				}
			}
		}
		// //////////////////////////////////////////////////
		// UTILITY Function: Engine_Memory::Allocate
		// //////////////////////////////////////////////////
		// Purpose:
		//  Returns a newly allocated structure of the given
		//  type. Uses a construtor instead of a default 
		//  constructor.
		// //////////////////////////////////////////////////
		// Parameters: 1
		// (1) no_default&&... constructor_arguments;
		// Purpose:
		//  The arguments for the given structure constructor
		//  type.
		// //////////////////////////////////////////////////
		template<class type, class use_constructor, class ... no_default>
		static UTILITY type* Allocate(no_default&&... constructor_arguments) {
			// If we are only allocating one of a structure then there is different snytax 
			try {
				TRY_LINE type* v_memory = new type(constructor_arguments...);
				// Add memory to the total engine count
				m_heap_memory = m_heap_memory + (sizeof(type));
				// Store the highest about of memory the engine had
				if (m_high_heap_memory < m_heap_memory) {
					m_high_heap_memory = m_heap_memory;
				}
				// Keep a copy of the address in memory so we can check if it was properly destroyed later
				m_memory_pointers.insert(std::make_pair(v_memory, Memory(v_memory, std::move(1), std::move(sizeof(type)), typeid(type).name())));
				// Return the allocated memory
				return v_memory;
			}
			catch (const std::bad_alloc& v_error) {
				// If we can't allocate the memory throw a fatal error and exit the engine immedetely
				// Since this is used by engine constant we cannot have access to the TO_WSTRING macro so we need to do some string magic
				v_error;
				throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", std::move(EXCEPTION_LINE), __FILEW__, L"No Function");
			}
		}
		// //////////////////////////////////////////////////
		// UTILITY Function: Engine_Memory::Allocate
		// //////////////////////////////////////////////////
		// Purpose:
		//  Returns a newly allocated structure of the given
		//  type. Uses a copy constructor instead of the 
		//  default constructor.
		// //////////////////////////////////////////////////
		// Parameters: 2
		// (1) type&& copy;
		// Purpose:
		//  A copy to be used to initilize the structure.
		// (2) size_t p_count = 1;
		// Purpose:
		//  The amount of structures to allocate.
		// //////////////////////////////////////////////////
		template<class type>
		static UTILITY type* Allocate(type&& copy, size_t p_count = 1) {
			// If we are only allocating one of a structure then there is different snytax 
			if (p_count == 1) {
				try {
					TRY_LINE type* v_memory = new type(copy);
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + (sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers.insert(std::make_pair(v_memory, Memory(v_memory, std::move(p_count), std::move(sizeof(type) * p_count), typeid(type).name())));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immedetely
					// Since this is used by engine constant we cannot have access to the TO_WSTRING macro so we need to do some string magic
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", std::move(EXCEPTION_LINE), __FILEW__, L"No Function");
				}
			}
			else {
				try {
					TRY_LINE type* v_memory = new type[p_count](copy);
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + (sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers.insert(std::make_pair(v_memory, Memory(v_memory, std::move(p_count), std::move(sizeof(type) * p_count), typeid(type).name())));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immedetely
					// Since this is used by engine constant we cannot have access to the TO_WSTRING macro so we need to do some string magic
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", std::move(EXCEPTION_LINE), __FILEW__, L"No Function");
				}
			}
		}
		// //////////////////////////////////////////////////
		// UTILITY Function: Engine_Memory::Deallocate
		// //////////////////////////////////////////////////
		// Purpose:
		//  Deletes the allocated memory of the given type.
		//  If it is memory pointed to by a shared pointer
		//  the amount of memory the structure takes up is
		//  deducted from the total engine count since the
		//  shared pointer takes care of this automatically.
		// //////////////////////////////////////////////////
		// Parameters: 2
		// (1) type* p_memory;
		// Purpose:
		//  The memory to be deleted.
		// (2) bool shared_ptr = false;
		// Purpose:
		//  Is this memory pointed to by a shared pointer.
		// //////////////////////////////////////////////////
		template<class type>
		static UTILITY void Deallocate(type* p_memory, bool shared_ptr = false) {
			// If the memory does not exsist then do not delete it
			if (p_memory != nullptr) {
				// For quick time allocations and deletions
				// Find the memory
				auto v_store = m_memory_pointers.find(p_memory);
				// If we find it then delete it
				if (v_store != m_memory_pointers.end()) {
					if (m_memory_pointers.at(p_memory).Blocks() == 1) {
						// Subtract memory from the total engine count
						m_heap_memory = m_heap_memory - m_memory_pointers.at(p_memory).Bytes();
						m_memory_pointers.erase(p_memory);
						if (shared_ptr == false) {
							delete p_memory;
						}
						p_memory = nullptr;
					}
					else {
						// Subtract memory from the total engine count
						m_heap_memory = m_heap_memory - m_memory_pointers.at(p_memory).Bytes();
						m_memory_pointers.erase(p_memory);
						if (shared_ptr == false) {
							delete[] p_memory;
						}
						p_memory = nullptr;
					}
				}
				// If we do not find the address to delete just let the function go out of scope
			}
		}
		// //////////////////////////////////////////////////
		// UTILITY Function: Engine_Memory::Deallocate_All
		// //////////////////////////////////////////////////
		// Purpose:
		//  Deletes all allocated memory recorded by the
		//  engine.
		// //////////////////////////////////////////////////
		// Parameters: NONE
		// //////////////////////////////////////////////////
		static UTILITY void Deallocate_All() {
			// Iterate though all members and delete them all accordingly
			for (auto i = m_memory_pointers.begin(); i != m_memory_pointers.end(); i++) {
				if (i->first != nullptr) {
					if (i->second.Blocks() == 1) {
						delete i->first;
						i->second.Stored_Memory() = nullptr;
						m_heap_memory = m_heap_memory - i->second.Bytes();
					}
					else {
						delete[] i->first;
						i->second.Stored_Memory() = nullptr;
						m_heap_memory = m_heap_memory - i->second.Bytes();
					}
				}
			}
			// Erase all of the members from the program
			m_memory_pointers.erase(m_memory_pointers.begin(), m_memory_pointers.end());
		}
		// //////////////////////////////////////////////////
		// UTILITY Function: Engine_Memory::Deallocate_All
		// //////////////////////////////////////////////////
		// Purpose:
		//  Given an amount of bytes it returns the human
		//  readable value of said bytes.
		// //////////////////////////////////////////////////
		// Parameters: 1
		// (1) const uint64_t& p_bytes;
		// Purpose:
		//  The amount of bytes to be read.
		// //////////////////////////////////////////////////
		static std::wstring Memory_String(const uint64_t& p_bytes) {
			if (p_bytes != 0) {
				// How many factors big it is
				// 1 -> b
				// 2 -> kb
				// 3 -> mb
				// 4 -> gb
				// Conversion units
				// 1024b -> 1kb
				// 1024kb -> 1mb
				// 1024mb -> 1gb
				uint16_t v_level = 1;
				float v_factors = (float)p_bytes;
				while (true) {
					// Test the factor of the units
					v_factors = v_factors / 1024.0f;
					if (v_factors < 1024) {
						v_level = v_level + 1;
						break;
					}
					else {
						v_level = v_level + 1;
					}
				}
				std::wstring v_memory_str{ std::to_wstring(v_factors) };
				switch (v_level) {
					case 1: { // Bytes, B
						uint16_t v_period = v_memory_str.find(L".");
						if (v_period != std::string::npos) {
							uint16_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
							if (v_decimal_count > 2) {
								v_decimal_count = v_decimal_count - 2;
								v_memory_str.erase(OFF64(v_period) + 2, v_decimal_count);

								v_memory_str.append(L"  B");
							}
							else {
								v_memory_str.append(L"  B");
							}
						}
						return v_memory_str;
					}
					case 2: { // Kilobytes, KB
						uint16_t v_period = v_memory_str.find(L".");
						if (v_period != std::string::npos) {
							uint16_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
							if (v_decimal_count > 2) {
								v_decimal_count = v_decimal_count - 2;
								v_memory_str.erase(OFF64(v_period) + 2, v_decimal_count);

								v_memory_str.append(L" KB");
							}
							else {
								v_memory_str.append(L" KB");
							}
						}
						return v_memory_str;
					}
					case 3: { // Megabytes, MB 
						uint16_t v_period = v_memory_str.find(L".");
						if (v_period != std::string::npos) {
							uint16_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
							if (v_decimal_count > 2) {
								v_decimal_count = v_decimal_count - 2;
								v_memory_str.erase(OFF64(v_period) + 2, v_decimal_count);

								v_memory_str.append(L" MB");
							}
							else {
								v_memory_str.append(L" MB");
							}
						}
						return v_memory_str;
					}
					case 4: { // Gigabytes, GB
						uint16_t v_period = v_memory_str.find(L".");
						if (v_period != std::string::npos) {
							uint16_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
							if (v_decimal_count > 2) {
								v_decimal_count = v_decimal_count - 2;
								v_memory_str.erase(OFF64(v_period) + 2, v_decimal_count);

								v_memory_str.append(L" GB");
							}
							else {
								v_memory_str.append(L" GB");
							}
						}
						return v_memory_str;
					}
					default: {
						return std::to_wstring(p_bytes);
					}
				}
			}
			else {
				return std::to_wstring(p_bytes);
			}
		}
		// Accessors
		static const ACCESSOR uint64_t& Heap_Memory() {
			return m_heap_memory;
		}
		static const ACCESSOR uint64_t& High_Heap_Memory() {
			return m_high_heap_memory;
		}
	// Public Variables
	public:
	// Private Functions/Macros 
	private:
	// Private Variables
	private:
		// How much memory is allocated with the new() operator
		static uint64_t m_heap_memory;
		static uint64_t m_high_heap_memory;
		static std::map<void*, Memory> m_memory_pointers;
	};
	// Functions
	// Macros / Definitions
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_MEMORY