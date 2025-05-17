// This is a mega-header for the whole siri::tools library.
// Particularly large components are gated behind `ifdef`s, 
//	but you are still likely to be including a lot of stuff you're not using.
// Consider using the subheaders in `include/siri-tools/`.
#pragma once
#include <iostream>
#include <functional>
#include <optional>


namespace siri::tools {
	int sanity_check();

	template <typename T>
	class RecalculateLazy {
	public:
		explicit RecalculateLazy(std::function<T(void)> recalculate): recalculate(recalculate) {}
		T get();
		void poison();
	private:
		std::optional<T> inner = std::nullopt;
		std::function<T()> recalculate;
		bool poisoned = false;
	};
#include "RecalculateLazy_template.hpp"
}
