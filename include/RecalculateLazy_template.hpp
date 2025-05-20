// Function templates for RecalculateLazy, 
// because I can't define them in a .cpp file, 
// or it won't generate templates properly.

/*!
 * \brief Gets the value stored within the `RecalculateLazy`.
 *
 * If the inner value is poisoned with `poison()` or was never initialised, 
 * it is recalculated using the function passed through the constructor. 
 * 
 * \since 0.1
 * \author Siri
 */
template <typename T>
T RecalculateLazy<T>::get() {
    if (!inner.has_value()) {
#ifdef _SIRI_DEBUG
		try {
#endif
			inner.emplace(recalculate());
#ifdef _SIRI_DEBUG
		} catch (::std::bad_function_call& ex) {
			::std::cerr << ::std::endl <<
				"bad_function_call in RecalculateLazy<" <<
				typeid(T).name() << // NOTE: I'm not sure I can demangle this without using boost or a GNU extension 
									// I don't even think it is mangled on MSVC for example.
									// I should consider if I need this and/or if I want to include boost as a dependency.
				">, is your function pointer non-null and of type <T(void)>?" <<
			::std::endl;
			throw (ex);
		}
#endif
    }
    return inner.value();
}

/*!
 *	\brief 'Poisons' the inner value of the `RecalculateLazy`, so that it must be recalculated.
 *
 *	This function should be a zero-cost operation if already poisoned, 
 *	and should properly destruct the internal value if it exists.
 *
 * \since 0.1
 * \author Siri
 *	\internal
 *	Internally, this function just calls `std::optional::reset()` on the inner value.
 *	This is fine as clearing an already empty optional is seemingly a noop on g++.
 *	This function mainly exists because I used to store a seperate 'poisoned' private member.
 *	If I had done it like this in the first place 
 *	I might have just let `get` share the optional via a `std::shared_ptr` or something.
 */
template <typename T>
void RecalculateLazy<T>::poison() {
	inner.reset();
}
