#pragma once

#include <iostream>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <functional>
#include <iostream>

#include "fmt/core.h"
#include "fmt/color.h"

#define TRIELO_EQ(call, expected) do {\
    const auto result { call };\
	if(result == expected) {\
    	fmt::print(fmt::fg(fmt::color::green), "Success: ");\
	} else {\
		fmt::print(fmt::fg(fmt::color::red), "ERROR: ");\
	}\
    std::cout << #call << ": '" << result << "'\n";\
} while (false)

#define TRIELO(call) std::cout << #call << ": '" << call << "'\n";

#define TRIELO_VOID(call) std::cout << #call << ": '\n"; call;

namespace Trielo {
	namespace Code {
		template <typename T_Result>
		struct Success {
			T_Result value;
			explicit Success(const T_Result& v) : value{ v } 
			{}
		};

		template <typename T_Result>
		struct Error {
			T_Result value;
			explicit Error(const T_Result& v) : value{ v } 
			{}
		};
	}

	namespace Inner {
		namespace Get {
			template <typename T>
			static inline constexpr std::string_view type_name() {
				#ifdef _MSC_VER
					constexpr std::string_view input { __FUNCSIG__ + 104 };
					constexpr auto end = input.find(">");
					return input.substr(0, end);
				#elif __GNUG__
					constexpr std::string_view p { __PRETTY_FUNCTION__ };
					return std::string_view(p.data() + 61, p.find(';', 61) - 61);
				#endif
			}

			template <auto func_ptr>
			static inline constexpr std::string_view func_name() {
				#ifdef _MSC_VER
					constexpr std::string_view input { __FUNCSIG__ + 104 };
					return std::string_view { input.data(), input.find("(") };
				#elif __GNUG__
					constexpr std::string_view full_name = __PRETTY_FUNCTION__;
					constexpr auto begin = full_name.find("=") + 2;
					constexpr auto end = full_name.find(";", begin);
					return full_name.substr(begin, end - begin);
				#endif
			}
		}
	}

	template<typename... Args>
	concept supports_std_cout = requires (std::ostream& os, const Args&&... args) {
		{ ((os << std::forward<const Args>(args)), ...) } -> std::same_as<std::ostream&>;
	};

	namespace Inner {
		namespace Print {
			template<typename Arg> requires supports_std_cout<Arg>
			static inline void push_one_arg_to_output(std::stringstream& output, Arg&& arg) {
				output << Trielo::Inner::Get::type_name<Arg>() << ": '";
				output << std::forward<Arg>(arg);
				output << '\'';
			}

			template <typename Arg>
			static inline void push_one_arg_to_output(std::stringstream& output, Arg&& arg) {
				output << Trielo::Inner::Get::type_name<Arg>() << ": '";

				if constexpr(std::is_pointer_v<Arg>) {
					output << static_cast<const void*>(arg);
				} else {
					output << static_cast<const void*>(&arg);
				}

				output << '\'';
			}

			static inline void push_func_args_to_output(std::stringstream& output) {}

			template <typename LastArg>
			static inline void push_func_args_to_output(std::stringstream& output, LastArg&& last_arg) {
				push_one_arg_to_output(output, std::forward<LastArg>(last_arg));
			}

			template <typename HeadArg, typename... TailArgs>
			static inline void push_func_args_to_output(std::stringstream& output, HeadArg&& head_arg, TailArgs&&... tail_args) {
				push_one_arg_to_output(output, std::forward<HeadArg>(head_arg));
				output << ", ";
				push_func_args_to_output(output, std::forward<TailArgs>(tail_args)...);
			}

			template <auto func_ptr, typename... Args>
			static inline void push_func_name_push_args_to_output(std::stringstream& output, Args&&... args) {
				output << Trielo::Inner::Get::func_name<func_ptr>();
				output << "(";
				push_func_args_to_output(output, std::forward<Args>(args)...);
				output << ")";
			}
		}

		template<auto func_ptr, typename... Args>
		static inline auto load_output_exec_get_result(std::stringstream& output, Args&&... args) {
			Print::push_func_name_push_args_to_output<func_ptr>(output, std::forward<Args>(args)...);
			const auto result { func_ptr(std::forward<Args>(args)...) };
			output << ": ";
			Trielo::Inner::Print::push_one_arg_to_output(output, std::forward<decltype(result)>(result));
			return std::move(result);
		}
	}

	template<typename T_FuncPtr, typename... Args>
	concept returns_void = std::is_same_v<std::invoke_result_t<T_FuncPtr, Args...>, void>;

	template <auto func_ptr, typename... Args>
	requires returns_void<decltype(func_ptr), Args...>
	inline void trielo(Args&&... args) {
		std::stringstream output;
		Inner::Print::push_func_name_push_args_to_output<func_ptr>(output, std::forward<Args>(args)...);
		func_ptr(std::forward<Args>(args)...);
		std::cout << output.view() << std::endl;
	}

	template <auto func_ptr, typename... Args>
	inline auto trielo(Args&&... args) {
		std::stringstream output;
		const auto result { Inner::load_output_exec_get_result<func_ptr>(output, std::forward<Args>(args)...) };
		std::cout << output.view() << std::endl;
		return std::move(result);
	}

	/*
	template<typename HeadArg, typename... TailArgs> requires supports_std_cout<HeadArg, TailArgs...>
	static inline void my_print(const HeadArg&& head_arg, const TailArgs&&... args) {
		inner_print(std::forward<const HeadArg>(head_arg));
		((inner_print_with_trailing_comma(std::forward<const TailArgs>(args)) << ", "), ...);
	}

	template<typename HeadArg, typename... TailArgs>
	[[deprecated("This type does not support printing")]]
	static inline void my_print(const HeadArg&& head_arg, const TailArgs&&... args) {
		inner_print(std::forward<const HeadArg>(head_arg));
		((inner_print_with_trailing_comma(std::forward<const TailArgs>(args)) << ", "), ...);
	}
	*/
}

namespace Trielo {
	template <auto funcPtr, typename T_Result, typename... Args>
	static auto trielo(Code::Success<T_Result> success_code, Args&&... args) {
		static_assert(
			std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>,
				       T_Result>,
			"Provided function pointer must return the OkErrCode<T> type"
		);

		auto result = funcPtr(std::forward<Args>(args)...);

		if (result == success_code.value) {
    		fmt::print(fmt::fg(fmt::color::green), "Success: ");
		} else {
    		fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
		}
		//Inner::Print::push_func_name_push_args_to_output<funcPtr>(std::forward<Args>(args)...);
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
	static auto trielo(Code::Error<T_Result> error_code, Args&&... args) {
		static_assert(
			std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>,
				       T_Result>,
			"Provided function pointer must return the FailErrCode<T> type"
		);

		auto result = funcPtr(std::forward<Args>(args)...);

		if (result == error_code.value) {
    		fmt::print(fmt::fg(fmt::color::red), "ERROR: ");
		} else {
    		fmt::print(fmt::fg(fmt::color::green), "Success: ");
		}
		//Inner::Print::push_func_name_push_args_to_output<funcPtr>(std::forward<Args>(args)...);
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
	auto trielo_lambda(Code::Success<T_Result> success_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(success_code, std::forward<Args>(args)...);
		if(result != success_code.value) {
			lambda();
		}
		return result;
	}

	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trielo_lambda(Code::Error<T_Result> error_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(error_code, std::forward<Args>(args)...);
		if(result != error_code.value) {
			lambda();
		}
		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Result, typename... Args>
	auto trieloxit(Code::Success<T_Result> success_code, Args&&... args) {
		const auto result = trielo<funcPtr>(success_code, std::forward<Args>(args)...);
		if(result != success_code.value) {
			std::exit(EXIT_FAILURE);
		}
		return result;
	}

	template <auto funcPtr, typename T_Result, typename... Args>
	auto trieloxit(Code::Error<T_Result> error_code, Args&&... args) {
		const auto result = trielo<funcPtr>(error_code, std::forward<Args>(args)...);
		if(result == error_code.value) {
			std::exit(EXIT_FAILURE);
		}
		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trieloxit_lambda(Code::Success<T_Result> success_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(success_code, std::forward<Args>(args)...);
		if(result != success_code.value) {
			lambda();
			std::exit(EXIT_FAILURE);
		}
		return result;
	}

	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trieloxit_lambda(Code::Error<T_Result> error_code, T_Lambda lambda, Args&&... args) {
		const auto result = trielo<funcPtr>(error_code, std::forward<Args>(args)...);
		if(result == error_code.value) {
			lambda();
			std::exit(EXIT_FAILURE);
		}
		return result;
	}
}
