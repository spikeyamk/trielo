#pragma once

#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <cstdlib>

template<typename Result_Type>
struct OkErrCode {
	Result_Type value;
	explicit OkErrCode(const Result_Type& v) : value{ v } {

	}
};

template <class T>
constexpr std::string_view get_type_name() {
	using namespace std;
#ifdef __clang__
	string_view p = __PRETTY_FUNCTION__;
	return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
	string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
	return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
	return string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
	string_view p = __FUNCSIG__;
	return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

template <auto ptr>
constexpr std::string_view get_function_name() {
	constexpr std::string_view full_name = __PRETTY_FUNCTION__;
	constexpr auto begin = full_name.find("=") + 2;
	constexpr auto end = full_name.find(";", begin);
	return full_name.substr(begin, end - begin);
}

void trielo_print_func_args(void) {}

template <typename HeadArg, typename... TailArg>
void trielo_print_func_args(HeadArg head_arg, const TailArg&... tail_arg) {
	std::cout << get_type_name<decltype(head_arg)>() << ": '" << head_arg << '\'';
	((std::cout << ", " << get_type_name<decltype(head_arg)>() << ": '" << tail_arg << '\''), ...);
}

template <auto funcPtr, typename... Args>
void trielo_print_func_name_and_args(const Args&... args) {
	std::cout << get_function_name<funcPtr>();
	std::cout << "(";
	trielo_print_func_args(args...);
	std::cout << ")";
}

template <auto funcPtr, typename... Args>
auto trielo(Args&&... args) {
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

template <auto funcPtr, typename Result_Type, typename... Args>
auto trielo(OkErrCode<Result_Type> ok_err_code, Args&&... args) {
	static_assert(
		std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>,
			       Result_Type>,
		"Provided function pointer must return the OkErrCode<T> type"
	);

	auto result = funcPtr(std::forward<Args>(args)...);

	if (result == ok_err_code.value) {
		std::cout << "Success: ";
	} else {
		std::cout << "ERROR: ";
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

template <auto funcPtr, typename... Args>
auto trieloxit(Args&&... args) {
	return trielo<funcPtr>(std::forward<Args>(args)...);
}

template <auto funcPtr, typename Result_Type, typename... Args>
auto trieloxit(OkErrCode<Result_Type> ok_err_code, Args&&... args) {
	static_assert(
		std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>,
		Result_Type>, "Provided function pointer must return the OkErrCode<T>"
		"type"
	);

	auto result = funcPtr(std::forward<Args>(args)...);

	if(result == ok_err_code.value) {
		std::cout << "Success: ";
	} else {
		std::cout << "ERROR: ";
	}
	trielo_print_func_name_and_args<funcPtr>(args...);
	std::cout << ": '";
	if constexpr (std::is_same_v<decltype(result), bool>) {
		std::cout << (result ? "true" : "false");
	} else {
		std::cout << result;
	}
	std::cout << '\'' << std::endl;

	if(result != ok_err_code.value) {
		std::exit(EXIT_FAILURE);
	}

	return result;
}
