// BSD 3 - Clause License
//
// Copyright(c) 2021-2023, Darrian Corkadel
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
#ifndef H_MEMORY
#define H_MEMORY
//////////////////////////////////
#include "common\build.h"
//////////////////////////////////
// C++ Headers
#pragma warning(push)
#pragma warning(disable: PW_ALL_WARNINGS)
#include <set>
#include <tuple>
#include <typeinfo>
#include <string>
#pragma warning(pop)
//////////////////////////////////
// Project Headers
//////////////////////////////////
// Engine Common Headers
#include "common\error_state.h"
#include "common\macro.h"
//////////////////////////////////
// Engine Control Headers
//////////////////////////////////
// Engine Structures Headers
//////////////////////////////////
// Engine Utility Headers
//////////////////////////////////
PW_NAMESPACE_SRT
	CO_NAMESPACE_SRT
		class Memory {
		// Default Class Structures
		public:
			struct Data {
			// Default Class Structures
			public:
				/* Error List: NONE */
				Data(void* p_data) :
					m_stored_memory{ p_data }, m_array_member{ false }, m_blocks{ 0 }, m_bytes{ 0 }, m_type_name{ "" } {
				}
				/* Error List: NONE */
				Data(void* p_data, const size_t& p_blocks, const size_t& p_byte_size, const std::string& p_type_name, const bool& p_array_member = false) :
					m_stored_memory{ p_data }, m_array_member{ p_array_member }, m_blocks{ p_blocks }, m_bytes{ p_byte_size }, m_type_name{ p_type_name } {
				}
				/* Error List: NONE */
				Data(const Data& p_rhs) :
					m_stored_memory{ p_rhs.m_stored_memory }, m_array_member{ p_rhs.m_array_member }, m_blocks{ p_rhs.m_blocks }, m_bytes{ p_rhs.m_bytes }, 
					m_type_name{ p_rhs.m_type_name } {
				}
				/* Error List: NONE */
				Data operator=(const Data& rhs) {
					this->m_stored_memory = rhs.m_stored_memory;
					this->m_blocks = rhs.m_blocks;
					this->m_bytes = rhs.m_bytes;
					this->m_type_name = rhs.m_type_name;

					return *this;
				}
			private:
			// Public Functions/Macros
			public:
				/* Error List: NONE */
				const size_t& Blocks() const {
					return this->m_blocks;
				}
				/* Error List: NONE */
				const size_t& Bytes() const {
					return this->m_bytes;
				}
				/* Error List: NONE */
				const std::string& Type() const {
					return this->m_type_name;
				}
				/* Error List: NONE */
				const bool& Array_Member() const {
					return this->m_array_member;
				}
				// Public Variables
			public:
			// A pointer to the data stored
				void* m_stored_memory;
			// Private Functions/Macros 
			private:
			// Private Variables
			private:
				// If the memory is apart of an array
				bool m_array_member;
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
			/* Error List: PW_MEMORY_FAILURE */
			_NODISCARD static bool Initialize() noexcept {
				// Not tracked by engine, guaranteed memory deallocation
				// Could cause memory leak if terminated prematurely but at that point
				// windows should clean up the program memory
				TRY_LINE m_memory_pointers = new(std::nothrow) std::set<pw::co::Memory::Data>();

				if (m_memory_pointers == nullptr) {
					SET_ERROR_STATE(PW_MEMORY_FAILURE);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Memory", L"Failure To Allocate Memory Tracker.", ERROR_LINE, __FILEW__, L"Initialize"));
					return false;
				}
				return true;
			}
			/* Error List: PW_ZERO_ALLOCATION, PW_FUNCTION_ERROR, PW_ALLOCATION_FAILURE */
			template<class type>
			_NODISCARD static type* Allocate(const size_t p_count = 1, const bool& p_array = false) noexcept {
				if (TRY_LINE p_count == 0) {
					SET_ERROR_STATE(PW_ZERO_ALLOCATION);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::Memory", L"Invalid Parameter: p_count was 0", ERROR_LINE, __FILEW__, L"Allocate"));
					return nullptr;
				}
				// If we are only allocating one of a structure then there is different syntax 
				if (p_count == 1) {
					PW_CALL(type* v_memory = new(std::nothrow) type, false);

					if (v_memory == nullptr) {
						// If we can't allocate the memory throw a fatal error and exit the engine immediately
						SET_ERROR_STATE(PW_ALLOCATION_FAILURE);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Memory", L"Failure To Allocate Memory.", ERROR_LINE, __FILEW__, L"Allocate"));
						return nullptr;
					}

					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Data(v_memory, p_count, (size_t)sizeof(type) * p_count, typeid(type).name()));
					// Return the allocated memory
					return v_memory;
				}
				else {
					PW_CALL(type* v_memory = new(std::nothrow) type[p_count], false);

					if (v_memory == nullptr) {
						// If we can't allocate the memory throw a fatal error and exit the engine immediately
						SET_ERROR_STATE(PW_ALLOCATION_FAILURE);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Memory", L"Failure To Allocate Memory.", ERROR_LINE, __FILEW__, L"Allocate"));
						return nullptr;
					}
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Data(v_memory, p_count, (size_t)sizeof(type) * p_count, typeid(type).name()));

					if (p_array == true) {
						for (size_t i = 1; i < p_count; i++) {
							m_memory_pointers->insert(Data(v_memory + i, 1, (size_t)sizeof(type) * 1, typeid(type).name(), true));
						}
					}
					// Return the allocated memory
					return v_memory;
				}
			}
			/* Error List: PW_FUNCTION_ERROR, PW_ALLOCATION_FAILURE */
			template<class type, class ...no_default>
			_NODISCARD static type* Allocate_Args(no_default&&... constructor_arguments) {
				// If we are only allocating one of a structure then there is different syntax 
				PW_CALL(type* v_memory = new(std::nothrow) type(constructor_arguments...), false);

				if (v_memory == nullptr) {
					// If we can't allocate the memory throw a fatal error and exit the engine immediately
					SET_ERROR_STATE(PW_ALLOCATION_FAILURE);
					SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Memory", L"Failure To Allocate Memory.", ERROR_LINE, __FILEW__, L"Allocate"));
					return nullptr;
				}
				// Add memory to the total engine count
				m_heap_memory = m_heap_memory + ((size_t)sizeof(type));
				// Store the highest about of memory the engine had
				if (m_high_heap_memory < m_heap_memory) {
					m_high_heap_memory = m_heap_memory;
				}
				m_allocations = m_allocations + 1;
				// Keep a copy of the address in memory so we can check if it was properly destroyed later
				m_memory_pointers->insert(Data(v_memory, 1, (size_t)sizeof(type) * 1, typeid(type).name()));
				// Return the allocated memory
				return v_memory;
			}
			/* Error List: PW_ZERO_ALLOCATION, PW_FUNCTION_ERROR, PW_ALLOCATION_FAILURE */
			template<class type>
			_NODISCARD static type* Allocate(type&& copy, const size_t p_count = 1, const bool& p_array = false) {
				if (TRY_LINE p_count == 0) {
					SET_ERROR_STATE(PW_ZERO_ALLOCATION);
					SET_ERROR_TYPE(pw::er::Warning_Error(L"pw::co::Memory", L"Invalid Parameter: p_count was 0", ERROR_LINE, __FILEW__, L"Allocate"));
					return nullptr;
				}
				// If we are only allocating one of a structure then there is different syntax 
				if (p_count == 1) {
					PW_CALL(type* v_memory = new(std::nothrow) type(copy), false);

					if (v_memory == nullptr) {
						// If we can't allocate the memory throw a fatal error and exit the engine immediately
						SET_ERROR_STATE(PW_ALLOCATION_FAILURE);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Memory", L"Failure To Allocate Memory.", ERROR_LINE, __FILEW__, L"Allocate"));
						return nullptr;
					}

					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Data(v_memory, p_count, (size_t)sizeof(type) * p_count, typeid(type).name()));
					// Return the allocated memory
					return v_memory;
				}
				else {
					PW_CALL(type* v_memory = new(std::nothrow) type[p_count], false);

					if (v_memory == nullptr) {
						// If we can't allocate the memory throw a fatal error and exit the engine immediately
						SET_ERROR_STATE(PW_ALLOCATION_FAILURE);
						SET_ERROR_TYPE(pw::er::Severe_Error(L"pw::co::Memory", L"Failure To Allocate Memory.", ERROR_LINE, __FILEW__, L"Allocate"));
						return nullptr;
					}
					for (size_t i = 0; i < p_count; i++) {
						v_memory[i] = type(copy);
					}
					// Add memory to the total engine count
					m_heap_memory = m_heap_memory + ((size_t)sizeof(type) * p_count);
					// Store the highest about of memory the engine had
					if (m_high_heap_memory < m_heap_memory) {
						m_high_heap_memory = m_heap_memory;
					}
					m_allocations = m_allocations + 1;
					// Keep a copy of the address in memory so we can check if it was properly destroyed later
					m_memory_pointers->insert(Data(v_memory, std::move(p_count), std::move((size_t)sizeof(type) * p_count), typeid(type).name()));

					if (p_array == true) {
						for (size_t i = 1; i < p_count; i++) {
							m_memory_pointers->insert(Data(v_memory + i, 1, (size_t)sizeof(type) * 1, typeid(type).name(), true));
						}
					}
					// Return the allocated memory
					return v_memory;
				}
			}
			/* Error List: NONE */
			template<class type>
			_NODISCARD static bool Deallocate(type* p_memory) {
				// If the memory does not exist then do not delete it
				if (p_memory != nullptr) {
					// For quick time allocations and deletions
					// Find the memory
					auto v_store = m_memory_pointers->find(Data(p_memory));
					// If we find it then delete it
					if (v_store != m_memory_pointers->end()) {
						if (v_store->Blocks() == 1) {
							if (v_store->Array_Member() != true) {
								// Subtract memory from the total engine count
								m_heap_memory = m_heap_memory - v_store->Bytes();
								m_allocations = m_allocations - 1;
								// There may be a error set here but it would get to absurdity to error handle at 
								// this point, ~type()
								delete p_memory;
							}
							// Array memory can only be deallocated by the head pointer so act like the
							// memory was deleted.
							m_memory_pointers->erase(v_store);
							p_memory = nullptr;

							return true;
						}
						else {
							// Subtract memory from the total engine count
							m_heap_memory = m_heap_memory - v_store->Bytes();
							m_allocations = m_allocations - 1;
							// There may be a error set here but it would get to absurdity to error handle at 
							// this point, ~type()
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
			/* Error List: NONE */
			static void Release_All() {
				// Iterate though all members and delete them all accordingly
				for (auto i = m_memory_pointers->begin(); i != m_memory_pointers->end(); i++) {
					if (i->m_stored_memory != nullptr) {
						if (i->Blocks() == 1) {
							if (i->Array_Member() != true) {
								// Subtract memory from the total engine count
								m_heap_memory = m_heap_memory - i->Bytes();
								m_allocations = m_allocations - 1;

								delete i->m_stored_memory;
							}
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
			/* Error List: NONE */
			_NODISCARD static std::wstring Memory_String(const uint64_t& p_bytes) {
				// Note when considering memory size,
				// Metric wrongly defines the sizes of KB,MB,GB when it comes to memory
				// So the system will use ISO-80000 / Memory values for defining memory size
				// This means instead of metric 1000 we will use 1024 as the factor size
				// This also means that KB,MB,GB will be interchangeable with KiB,MiB,GiB
				// Whys does memory have to have such odd standards and not a consistent profile
				if (p_bytes != 0) {
					// How many factors big it is
					// 1 -> B
					// 2 -> KiB
					// 3 -> MiB
					// 4 -> GiB
					// Conversion units
					// 1024b -> 1KiB
					// 1024kb -> 1MiB
					// 1024mb -> 1GiB
					size_t v_level{ 1 };
					double v_factors{ static_cast<double>(p_bytes) };
					while (true) {
						// Test the factor of the units
						v_factors = v_factors / 1024.0;
						if (v_factors < 1024.0) {
							v_level = ADD_UINT64(v_level, 1);
							break;
						}
						else {
							v_level = ADD_UINT64(v_level, 1);
						}
					}
					std::wstring v_memory_str{ std::to_wstring(v_factors) };
					switch (v_level) {
						case 1: { // Bytes, B
							size_t v_period = v_memory_str.find(L".");
							if (v_period != std::string::npos) {
								size_t v_decimal_count = v_memory_str.size() - OFF_UINT64(v_period);
								if (v_decimal_count > 2) {
									v_decimal_count = v_decimal_count - 2;
									v_memory_str.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);

									v_memory_str.append(L"  B");
								}
								else {
									v_memory_str.append(L"  B");
								}
							}
							return v_memory_str;
						}
						case 2: { // Kilobytes, KiB
							size_t v_period = v_memory_str.find(L".");
							if (v_period != std::string::npos) {
								size_t v_decimal_count = v_memory_str.size() - OFF_UINT64(v_period);
								if (v_decimal_count > 2) {
									v_decimal_count = v_decimal_count - 2;
									v_memory_str.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);

									v_memory_str.append(L" KB");
								}
								else {
									v_memory_str.append(L" KB");
								}
							}
							return v_memory_str;
						}
						case 3: { // Megabytes, MiB 
							size_t v_period = v_memory_str.find(L".");
							if (v_period != std::string::npos) {
								size_t v_decimal_count = v_memory_str.size() - OFF_UINT64(v_period);
								if (v_decimal_count > 2) {
									v_decimal_count = v_decimal_count - 2;
									v_memory_str.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);

									v_memory_str.append(L" MB");
								}
								else {
									v_memory_str.append(L" MB");
								}
							}
							return v_memory_str;
						}
						case 4: { // Gigabytes, GiB
							size_t v_period = v_memory_str.find(L".");
							if (v_period != std::string::npos) {
								size_t v_decimal_count = v_memory_str.size() - OFF_UINT64(v_period);
								if (v_decimal_count > 2) {
									v_decimal_count = v_decimal_count - 2;
									v_memory_str.erase(ADD_UINT64(OFF_UINT64(v_period), 2), v_decimal_count);

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
			/* Error List: NONE */
			static const uint64_t& Heap_Memory() {
				return m_heap_memory;
			}
			/* Error List: NONE */
			static const uint64_t& High_Heap_Memory() {
				return m_high_heap_memory;
			}
			/* Error List: NONE */
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
			static std::set<pw::co::Memory::Data>* m_memory_pointers;
		};
		/* Error List: NONE */
		inline bool operator==(const pw::co::Memory::Data& lhs, const pw::co::Memory::Data& rhs) {
			if (lhs.m_stored_memory == rhs.m_stored_memory) {
				return true;
			}
			else {
				return false;
			}
		}
		/* Error List: NONE */
		inline bool operator==(const pw::co::Memory::Data& lhs, const void* rhs) {
			if (lhs.m_stored_memory == rhs) {
				return true;
			}
			else {
				return false;
			}
		}
		/* Error List: NONE */
		inline bool operator==(const void* lhs, const pw::co::Memory::Data& rhs) {
			if (lhs == rhs.m_stored_memory) {
				return true;
			}
			else {
				return false;
			}
		}
		/* Error List: NONE */
		inline bool operator<(const pw::co::Memory::Data& lhs, const pw::co::Memory::Data& rhs) {
			if (lhs.m_stored_memory < rhs.m_stored_memory) {
				return true;
			}
			else {
				return false;
			}
		}
		/* Error List: NONE */
		inline bool operator>(const pw::co::Memory::Data& lhs, const pw::co::Memory::Data& rhs) {
			if (lhs.m_stored_memory > rhs.m_stored_memory) {
				return true;
			}
			else {
				return false;
			}
		}
	CO_NAMESPACE_END
PW_NAMESPACE_END
#endif // !H_MEMORY