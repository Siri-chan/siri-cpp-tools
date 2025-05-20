// This is a mega-header for the whole siri::tools library.
#pragma once
#include <iostream>
#include <functional>
#include <optional>


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
