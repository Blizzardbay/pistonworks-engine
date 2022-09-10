// BSD 3 - Clause License
//
// Copyright(c) 2021-2022, Darrian Corkadel
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
#include "engine_common\engine_build.h"
//////////////////////////////////
// #FILE_INFO#
// +(HEADER_ONLY)
//////////////////////////////////
// C++ Headers
#include <codeanalysis\warnings.h>
#pragma warning (push)
#pragma warning (disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <set>
#include <tuple>
#include <typeinfo>
#include <string>
#pragma warning (pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "engine_common\engine_exception.h"
#include "engine_common\engine_macro.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Pistonworks Engine           //
// Created By : Darrian Corkadel//
//////////////////////////////////
PW_NAMESPACE_SRT
//////////////////////////////////
	class Engine_Memory {
	// Default Class Structures
	public:
		struct Memory;

		template<class type>
		static bool Deallocate(type* p_memory) {
			// If the memory does not exist then do not delete it
			if (p_memory != nullptr) {
				// For quick time allocations and deletions
				// Find the memory
				auto v_store = m_memory_pointers->find(Memory(p_memory));
				// If we find it then delete it
				if (v_store != m_memory_pointers->end()) {
					if (v_store->Blocks() == 1) {
						// Subtract memory from the total engine count
						m_heap_memory = m_heap_memory - v_store->Bytes();
						m_allocations = m_allocations - 1;

						delete p_memory;

						m_memory_pointers->erase(v_store);
						p_memory = nullptr;

						return true;
					}
					else {
						// Subtract memory from the total engine count
						m_heap_memory = m_heap_memory - v_store->Bytes();
						m_allocations = m_allocations - 1;

						delete[] p_memory;

						m_memory_pointers->erase(v_store);
						p_memory = nullptr;

						return true;
					}
				}
				// If we do not find the address to delete just let the function go out of scope
				return false;
			}
			// If the memory is nullptr then make sure fall backs don't try to delete it
			// The memory could have been allocated and set to nullptr thus losing the memory
			// But that would not be at the fault of the engine
			// I might add two sets of pointers in the future to prevent this
			// So the memory is handled regardless, but there are other draw backs...
			return true;
		}
		struct Memory {
		// Default Class Structures
		public:
			Memory(void* p_memory) :
				m_stored_memory{ p_memory }, m_blocks{ 0 }, m_bytes{ 0 }, m_type_name{ "" } {
			}
			Memory(void* p_memory, const size_t& p_blocks, const size_t& p_byte_size, const std::string& p_type_name) :
				m_stored_memory{ p_memory }, m_blocks{ p_blocks }, m_bytes{ p_byte_size }, m_type_name{ p_type_name } {
			}
			Memory(const Memory& rhs) :
				m_stored_memory{ rhs.m_stored_memory }, m_blocks{ rhs.m_blocks }, m_bytes{ rhs.m_bytes }, m_type_name{ rhs.m_type_name } {
			}
			Memory operator=(const Memory& rhs) {
				m_stored_memory = rhs.m_stored_memory;
				m_blocks = rhs.m_blocks;
				m_bytes = rhs.m_bytes;
				m_type_name = rhs.m_type_name;

				return *this;
			}
		private:
		// Public Functions/Macros
		public:
			const size_t& Blocks() const {
				return m_blocks;
			}
			const size_t& Bytes() const {
				return m_bytes;
			}
			const std::string& Type() const {
				return m_type_name;
			}
			// Public Variables
		public:
		// A pointer to the data stored
			void* m_stored_memory;
		// Private Functions/Macros 
		private:
		// Private Variables
		private:
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
		static void Initialize_Memory() {
			// Not tracked by engine, guaranteed memory deallocation
			m_memory_pointers = new std::set<pw::Engine_Memory::Memory>();
		}
		template<class type>
		static type* Allocate(size_t p_count = 1) {
			// If we are only allocating one of a structure then there is different syntax 
			if (p_count == 1) {
				try {
					TRY_LINE type* v_memory = new type;
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Memory(v_memory, std::move(p_count), std::move((size_t)sizeof(type) * p_count), typeid(type).name()));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immediately
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", EXCEPTION_LINE, __FILEW__, L"No Function");
				}
			}
			else {
				try {
					TRY_LINE type* v_memory = new type[p_count];
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Memory(v_memory, std::move(p_count), std::move((size_t)sizeof(type) * p_count), typeid(type).name()));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immediately
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", EXCEPTION_LINE, __FILEW__, L"No Function");
				}
			}
		}
		template<class type, class use_constructor, class ... no_default>
		static type* Allocate(no_default&&... constructor_arguments) {
			// If we are only allocating one of a structure then there is different syntax 
			try {
				TRY_LINE type* v_memory = new type(constructor_arguments...);
				// Add memory to the total engine count
				m_heap_memory = m_heap_memory + ((size_t)sizeof(type));
				// Store the highest about of memory the engine had
				if (m_high_heap_memory < m_heap_memory) {
					m_high_heap_memory = m_heap_memory;
				}
				m_allocations = m_allocations + 1;
				// Keep a copy of the address in memory so we can check if it was properly destroyed later
				m_memory_pointers->insert(Memory(v_memory, std::move(1), std::move((size_t)sizeof(type) * 1), typeid(type).name()));;
				// Return the allocated memory
				return v_memory;
			}
			catch (const std::bad_alloc& v_error) {
				// If we can't allocate the memory throw a fatal error and exit the engine immediately
				v_error;
				throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", EXCEPTION_LINE, __FILEW__, L"No Function");
			}
		}
		template<class type>
		static type* Allocate(type&& copy, size_t p_count = 1) {
			// If we are only allocating one of a structure then there is different syntax 
			if (p_count == 1) {
				try {
					TRY_LINE type* v_memory = new type(copy);
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Memory(v_memory, std::move(p_count), std::move((size_t)sizeof(type) * p_count), typeid(type).name()));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immediately
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", EXCEPTION_LINE, __FILEW__, L"No Function");
				}
			}
			else {
				try {
					TRY_LINE type* v_memory = new type[p_count](copy);
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Memory(v_memory, std::move(p_count), std::move((size_t)sizeof(type) * p_count), typeid(type).name()));
					// Return the allocated memory
					return v_memory;
				}
				catch (const std::bad_alloc& v_error) {
					// If we can't allocate the memory throw a fatal error and exit the engine immediately
					v_error;
					throw pw::er::Severe_Error(L"Engine Memory", L"Bad Alloc", EXCEPTION_LINE, __FILEW__, L"No Function");
				}
			}
		}
		static void Deallocate_All() {
			// Iterate though all members and delete them all accordingly
			for (auto i = m_memory_pointers->begin(); i != m_memory_pointers->end(); i++) {
				if (i->m_stored_memory != nullptr) {
					if (i->Blocks() == 1) {
						delete i->m_stored_memory;
						m_allocations = m_allocations - 1;
						m_heap_memory = m_heap_memory - i->Bytes();
					}
					else {
						delete[] i->m_stored_memory;
						m_allocations = m_allocations - 1;
						m_heap_memory = m_heap_memory - i->Bytes();
					}
				}
			}
			// Erase all of the members from the program
			delete m_memory_pointers;
		}
		static std::wstring Memory_String(const uint64_t& p_bytes) {
			if (p_bytes != 0) {
				// How many factors big it is
				// 1 -> b
				// 2 -> kb
				// 3 -> mb
				// 4 -> gb
				// Conversion units
				// 1000b -> 1kb
				// 1000kb -> 1mb
				// 1000mb -> 1gb
				size_t v_level = 1;
				float v_factors = (float)p_bytes;
				while (true) {
					// Test the factor of the units
					v_factors = v_factors / 1000.0f;
					if (v_factors < 1000.0f) {
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
					size_t v_period = v_memory_str.find(L".");
					if (v_period != std::string::npos) {
						size_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
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
					size_t v_period = v_memory_str.find(L".");
					if (v_period != std::string::npos) {
						size_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
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
					size_t v_period = v_memory_str.find(L".");
					if (v_period != std::string::npos) {
						size_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
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
					size_t v_period = v_memory_str.find(L".");
					if (v_period != std::string::npos) {
						size_t v_decimal_count = v_memory_str.size() - OFF64(v_period);
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
		static const uint64_t& Heap_Memory() {
			return m_heap_memory;
		}
		static const uint64_t& High_Heap_Memory() {
			return m_high_heap_memory;
		}
		static const uint64_t& Allocations() {
			return m_allocations;
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
		static uint64_t m_allocations;
		static std::set<pw::Engine_Memory::Memory>* m_memory_pointers;
	};
	inline bool operator==(const pw::Engine_Memory::Memory& lhs, const pw::Engine_Memory::Memory& rhs) {
		if (lhs.m_stored_memory == rhs.m_stored_memory) {
			return true;
		}
		else {
			return false;
		}
	}
	inline bool operator==(const pw::Engine_Memory::Memory& lhs, const void* rhs) {
		if (lhs.m_stored_memory == rhs) {
			return true;
		}
		else {
			return false;
		}
	}
	inline bool operator==(const void* lhs, const pw::Engine_Memory::Memory& rhs) {
		if (lhs == rhs.m_stored_memory) {
			return true;
		}
		else {
			return false;
		}
	}
	inline bool operator<(const pw::Engine_Memory::Memory& lhs, const pw::Engine_Memory::Memory& rhs) {
		if (lhs.m_stored_memory < rhs.m_stored_memory) {
			return true;
		}
		else {
			return false;
		}
	}
	inline bool operator>(const pw::Engine_Memory::Memory& lhs, const pw::Engine_Memory::Memory& rhs) {
		if (lhs.m_stored_memory > rhs.m_stored_memory) {
			return true;
		}
		else {
			return false;
		}
	}
//////////////////////////////////
PW_NAMESPACE_END
//////////////////////////////////
#endif // !H_ENGINE_MEMORY