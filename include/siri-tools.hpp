// This is a mega-header for the whole siri::tools library.

/*
This file is part of siri::tools.

siri::tools is free software: 
you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
as published by the Free Software Foundation, either version 3 of the License, 
or (at your option) any later version.

siri::tools is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with siri::tools. 
If not, see <https://www.gnu.org/licenses/>. 
*/

#pragma once
#include <cstdlib>
#include <iostream>
#include <functional>
#include <optional>
#include <stacktrace>


/*!
 * \brief The root namespace.
 *
 * Defines all classes and functions available by default.
 * Others are available through sub-namespaces that aren't included by default.
 * \since 0.1
 * \author Siri
 */
namespace siri::tools {
	/*!
	 * \brief A function that returns 0.
	 *
	 * Designed to double check that the library is linking and such properly.
	 *
	 * **Example:**
	 * \include{lineno} sanity_check.cpp
	 * \since 0.1
	 * \author Siri
	 */
	int sanity_check();

// <cstdlib> assert macro has issues here.
#undef assert

	// NOTE: These were once constexpr but I'd need to define these inline and thats un-idiomatic.
	/*!
	 * \brief Print an error message and exit from the program if a statement is not true.
	 *
	 * Uses `std::exit()`, rather than `std::abort()`/`std::terminate()`. 
	 * If this behaviour is not desired, try `abort_assert()`.
	 *
	 * This function will exit regardless of debug status.
	 * If this behaviour is not desired, try `debug_assert()`.
	 * 
	 * \since 0.1
	 * \author Siri
	 */
	void assert(bool const &cond, const char *const msg = "<...>") noexcept;

	/*!
	 * \brief Print an error message and exit from the program if a statement is not true.
	 *
	 * Uses `std::exit()`, rather than `std::abort()`/`std::terminate()`. 
	 * If this behaviour is not desired, try `debug_abort_assert()`.
	 *
	 * This function will exit only if `_SIRI_DEBUG` is defined.
	 * If this behaviour is not desired, try `assert()`.
	 * 
	 * \since 0.1
	 * \author Siri
	 */
	void debug_assert([[maybe_unused]] bool const &cond, [[maybe_unused]] const char *const msg = "<...>") noexcept;

	/*!
	 * \brief Print an error message and exit from the program if a statement is not true.
	 *
	 * Uses `std::abort()`, rather than `std::exit()`/`std::terminate()`. 
	 * If this behaviour is not desired, try `assert()`.
	 *
	 * This function will exit regardless of debug status.
	 * If this behaviour is not desired, try `debug_abort_assert()`.
	 * 
	 * \since 0.1
	 * \author Siri
	 */
	void abort_assert(bool const &cond, const char *const msg = "<...>") noexcept;

	/*!
	 * \brief Print an error message and exit from the program if a statement is not true.
	 *
	 * Uses `std::abort()`, rather than `std::exit()`/`std::terminate()`. 
	 * If this behaviour is not desired, try `debug_assert()`.
	 *
	 * This function will exit only if `_SIRI_DEBUG` is defined.
	 * If this behaviour is not desired, try `abort_assert()`.
	 * 
	 * \since 0.1
	 * \author Siri
	 */
	void debug_abort_assert([[maybe_unused]] bool const &cond, [[maybe_unused]] const char *const msg = "<...>") noexcept;
	
	/*!
	 * \brief A OnceCell style object that lazily evaluates it's contents, only when required.
	 *
	 * RecalculateLazy is a generic class, that holds a value of type `T`, that
	 * can only be retrieved via `get()`.
	 * The value stored is constant, and is only ever reevaluated when `get()` is called, 
	 * and the structure has been poisoned with `poison()`.
	 *
	 * **Example:**
	 * \include{lineno} recalculate_lazy.cpp
	 * \since 0.1
	 * \author Siri
	 */
	template <typename T>
	class RecalculateLazy {
	public:
		/*!
		 * \brief Creates a new `RecalculateLazy`, that recalculates values using `recalculate`.
		 * \param recalculate A `std::function` that returns a `T`. 
		 * Used to determine an initial value as well as to recaculate the internal value, if
		 * the structure is ever poisoned.
		 *
		 * Also allocates space for an empty `std::optional<T>`.
	     * \since 0.1
		 * \author Siri
		 */
		explicit RecalculateLazy(std::function<T(void)> recalculate): recalculate(recalculate) {}
		T get();
		void poison();
		/*!
		 * \brief The Destructor. Destroys the optional, and the inner value if it 
		 * `std::is_trivially_destructible`, as well as 
		 * the target of the `std::function` passed into the constructor.
		 *
		 * Destroying the `std::function`'s target is usually expected and correct behavior, 
		 * but if you find a use-case where this behaviour is non-ideal, file an issue,
		 * I'm considering a seperate function that destroys but keeps the `std::function`'s 
		 * target intact if that becomes a problem for any use case.
		 * \since 0.1
		 * \author Siri
		 */
		~RecalculateLazy() = default;
	private:
		std::optional<T> inner = std::nullopt;
		std::function<T()> recalculate;
	};
#include "RecalculateLazy_template.hpp"
}

// Replace <cstdlib> assert with ours.
using siri::tools::assert;
