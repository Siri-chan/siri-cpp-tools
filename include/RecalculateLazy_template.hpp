// Function templates for RecalculateLazy, 
// because I can't define them in a .cpp file, 
// or it won't generate templates properly.
template <typename T>
T RecalculateLazy<T>::get() {
    if (!inner.has_value() || poisoned) {
#ifdef _DEBUG
		try {
#endif
			inner.emplace(recalculate());
			poisoned = false;
#ifdef _DEBUG
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

template <typename T>
void RecalculateLazy<T>::poison() {
	poisoned = true;
}
