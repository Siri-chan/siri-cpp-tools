#include <siri-tools.hpp>

namespace siri::tools {
	// These are labelled maybe_unused since they're unused if _SIRI_DEBUG is undefined.
	// This way, we suppress compiler warnings, since this behaviour is intended.
	void debug_assert([[maybe_unused]] bool const &cond, [[maybe_unused]] const char *const msg /* = "<...>" */) noexcept {
#ifdef _SIRI_DEBUG
		return assert(cond, msg);			
#endif
		return;
	}
	void assert(bool const &cond, const char *const msg /* = "<...>" */) noexcept {
		if (cond) return;
		std::cerr << "Assertion Failed: " << msg << std::endl 
		// <stacktrace> is a C++23 feature but still requires linking with 
		// `-lstdc++exp` with g++. 
		// TODO: Re-add this once it gets stabilised, or just use boost::stacktrace::stacktrace()
		//			because ofc that exists.
			/*
			<<
			"Stacktrace:" << std::endl << std::stacktrace::current() << std::endl; 
			*/
			;
		exit(101);
	}

	// These are labelled maybe_unused since they're unused if _SIRI_DEBUG is undefined.
	// This way, we suppress compiler warnings, since this behaviour is intended.
	void debug_abort_assert([[maybe_unused]] bool const &cond, [[maybe_unused]] const char *const msg /* = "<...>" */) noexcept {
#ifdef _SIRI_DEBUG
		return abort_assert(cond, msg);			
#endif
		return;
	}
	void abort_assert(bool const &cond, const char *const msg /* = <...> */) noexcept {
		if (cond) return;
		std::cerr << "Assertion Failed: " << msg << std::endl 
		// <stacktrace> is a C++23 feature but still requires linking with 
		// `-lstdc++exp` with g++. 
		// TODO: Re-add this once it gets stabilised, or just use boost::stacktrace::stacktrace()
		//			because ofc that exists.
			/*
			<<
			"Stacktrace:" << std::endl << std::stacktrace::current() << std::endl; 
			*/
			;
		abort();
	}
}
