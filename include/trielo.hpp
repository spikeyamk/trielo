#pragma once

#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <functional>

#include "fmt/core.h"
#include "fmt/color.h"

namespace Trielo {
	template <typename T_Result>
	struct OkErrCode {
		T_Result value;
		explicit OkErrCode(const T_Result& v) : value{ v } 
		{}
	};

	template <typename T_Result>
	struct FailErrCode {
		T_Result value;
		explicit FailErrCode(const T_Result& v) : value{ v } 
		{}
	};

	template <typename T>
	static inline constexpr std::string_view get_type_name() {
		#ifdef _MSC_VER
			constexpr std::string_view input { __FUNCSIG__ + 96 };
    		constexpr auto end = input.find(">");
			return input.substr(0, end);
		#endif
		#ifdef __GNUG__
			constexpr std::string_view p { __PRETTY_FUNCTION__ };
			return std::string_view(p.data() + 49, p.find(';', 49) - 49);
		#endif
	}

	template <auto FuncPtr>
	static inline constexpr std::string_view get_function_name() {
		#ifdef _MSC_VER
			constexpr std::string_view input { __FUNCSIG__ + 100 };
			return std::string_view { input.data(), input.find("(") };
		#endif 
		#ifdef __GNUG__
			constexpr std::string_view full_name = __PRETTY_FUNCTION__;
			constexpr auto begin = full_name.find("=") + 2;
			constexpr auto end = full_name.find(";", begin);
			return full_name.substr(begin, end - begin);
		#endif
	}

	static inline void trielo_print_func_args(void) {}

	template <typename HeadArg, typename... TailArg>
	static inline void trielo_print_func_args(HeadArg head_arg, const TailArg&... tail_arg) {
		std::cout << get_type_name<decltype(head_arg)>() << ": '" << head_arg << '\'';
		((std::cout << ", " << get_type_name<decltype(head_arg)>() << ": '" << tail_arg << '\''), ...);
	}

	template <auto funcPtr, typename... Args>
	static inline void trielo_print_func_name_and_args(const Args&... args) {
		std::cout << get_function_name<funcPtr>();
		std::cout << "(";
		trielo_print_func_args(args...);
		std::cout << ")";
	}
}

namespace Trielo {
	template <auto funcPtr, typename... Args>
	static auto trielo(Args&&... args) {
		constexpr bool returns_void = std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>, void>;
		if constexpr (returns_void) {
			trielo_print_func_name_and_args<funcPtr>(args...);
			std::cout << std::endl;
			funcPtr(std::forward<Args>(args)...);
		} else {
			auto result = funcPtr(std::forward<Args>(args)...);

			trielo_print_func_name_and_args<funcPtr>(args...);
			std::cout << ": '";
			if constexpr (std::is_same_v<decltype(result), bool>) {
				std::cout << (result ? "true" : "false");
			} else {
				std::cout << result;
			}
			std::cout << '\'' << std::endl;

			return result;
		}
	}

	template <auto funcPtr, typename T_Result, typename... Args>
	static auto trielo(OkErrCode<T_Result> ok_err_code, Args&&... args) {
		static_assert(
			std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>,
				       T_Result>,
			"Provided function pointer must return the OkErrCode<T> type"
		);

		auto result = funcPtr(std::forward<Args>(args)...);

		if (result == ok_err_code.value) {
    		fmt::print(fmt::fg(fmt::color::green), "Success: ");
		} else {
    		fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
		}
		trielo_print_func_name_and_args<funcPtr>(args...);
		std::cout << ": '";
		if constexpr (std::is_same_v<decltype(result), bool>) {
			std::cout << (result ? "true" : "false");
		} else {
			std::cout << result;
		}
		std::cout << '\'' << std::endl;

		return result;
	}

	template <auto funcPtr, typename T_Result, typename... Args>
	static auto trielo(FailErrCode<T_Result> fail_err_code, Args&&... args) {
		static_assert(
			std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>,
				       T_Result>,
			"Provided function pointer must return the FailErrCode<T> type"
		);

		auto result = funcPtr(std::forward<Args>(args)...);

		if (result == fail_err_code.value) {
    		fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
		} else {
    		fmt::print(fmt::fg(fmt::color::green), "Success: ");
		}
		trielo_print_func_name_and_args<funcPtr>(args...);
		std::cout << ": '";
		if constexpr (std::is_same_v<decltype(result), bool>) {
			std::cout << (result ? "true" : "false");
		} else {
			std::cout << result;
		}
		std::cout << '\'' << std::endl;

		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trielo_lambda(OkErrCode<T_Result> ok_err_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(ok_err_code, std::forward<Args>(args)...);
		if(result != ok_err_code.value) {
			lambda();
		}
		return result;
	}

	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trielo_lambda(FailErrCode<T_Result> fail_err_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(fail_err_code, std::forward<Args>(args)...);
		if(result != fail_err_code.value) {
			lambda();
		}
		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Result, typename... Args>
	auto trieloxit(OkErrCode<T_Result> ok_err_code, Args&&... args) {
		const auto result = trielo<funcPtr>(ok_err_code, std::forward<Args>(args)...);
		if(result != ok_err_code.value) {
			std::exit(EXIT_FAILURE);
		}
		return result;
	}

	template <auto funcPtr, typename T_Result, typename... Args>
	auto trieloxit(FailErrCode<T_Result> fail_err_code, Args&&... args) {
		const auto result = trielo<funcPtr>(fail_err_code, std::forward<Args>(args)...);
		if(result == fail_err_code.value) {
			std::exit(EXIT_FAILURE);
		}
		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trieloxit_lambda(OkErrCode<T_Result> ok_err_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(ok_err_code, std::forward<Args>(args)...);
		if(result != ok_err_code.value) {
			lambda();
			std::exit(EXIT_FAILURE);
		}
		return result;
	}

	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trieloxit_lambda(FailErrCode<T_Result> fail_err_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(fail_err_code, std::forward<Args>(args)...);
		if(result == fail_err_code.value) {
			lambda();
			std::exit(EXIT_FAILURE);
		}
		return result;
	}
}