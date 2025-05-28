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
#ifdef _SIRI_NOBOOST
				typeid(T).name() << // NOTE: I'm not sure I can demangle this without using boost or a GNU extension 
									// I don't even think it is mangled on MSVC for example.
#else
				boost::typeindex::type_id<T>().pretty_name() <<
#endif
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
