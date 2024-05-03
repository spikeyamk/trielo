#pragma once

#include <iostream>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <utility>
#include <functional>
#include <iostream>

namespace Trielo {
	namespace Detail {
		inline void print_success() {
			std::cout << "\033[32mSuccess: \033[m";\
		}

		inline void print_error() {
			std::cout << "\033[31mERROR: \033[m";\
		}

		template <typename T>
		inline std::string_view type_name() {
			return typeid(T).name();
		}

		template <auto func_ptr>
		inline consteval std::string_view func_name() {
			#ifdef _MSC_VER
				constexpr std::string_view input { __FUNCSIG__ + 104 };
				return std::string_view { input.data(), input.find("(") };
			#elif __GNUG__
				constexpr std::string_view full_name { __PRETTY_FUNCTION__ };
				constexpr auto begin { full_name.find("=") + 2 };
				constexpr auto end { full_name.find(";", begin) };
				return full_name.substr(begin, end - begin);
			#endif
		}
	}
}

#define TRIELO_EQ(call, expected) do {\
    const auto result { call };\
	if(result == expected) {\
		Trielo::Detail::print_success();\
	} else {\
		Trielo::Detail::print_error();\
	}\
    std::cout << #call << ": '" << result << "'\n";\
} while (false)

#define TRIELO(call) std::cout << #call << ": '" << call << "'\n";

#define TRIELO_VOID(call) std::cout << #call << ": '\n"; call;

namespace Trielo {
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
		{} };

	namespace Detail {
		namespace Print {
			template<typename... Args>
			concept supports_std_cout = requires (std::ostream& os, const Args&&... args) {
				{ ((os << std::forward<const Args>(args)), ...) } -> std::same_as<std::ostream&>;
			};

			template<typename Arg> requires supports_std_cout<Arg>
			inline void push_one_arg_to_output(std::ostream& output, Arg&& arg) {
				output << Trielo::Detail::type_name<Arg>() << ": '";
				output << std::forward<Arg>(arg);
				output << '\'';
			}

			template <typename Arg>
			inline void push_one_arg_to_output(std::ostream& output, Arg&& arg) {
				output << Trielo::Detail::type_name<Arg>() << ": '";

				if constexpr(std::is_pointer_v<Arg>) {
					output << static_cast<const void*>(arg);
				} else {
					output << static_cast<const void*>(&arg);
				}

				output << '\'';
			}

			inline void push_func_args_to_output(std::ostream& output) {
                (void) output;
            }

			template <typename LastArg>
			inline void push_func_args_to_output(std::ostream& output, LastArg&& last_arg) {
				push_one_arg_to_output(output, std::forward<LastArg>(last_arg));
			}

			template <typename HeadArg, typename... TailArgs>
			inline void push_func_args_to_output(std::ostream& output, HeadArg&& head_arg, TailArgs&&... tail_args) {
				push_one_arg_to_output(output, std::forward<HeadArg>(head_arg));
				output << ", ";
				push_func_args_to_output(output, std::forward<TailArgs>(tail_args)...);
			}

			template <auto func_ptr, typename... Args>
			inline void push_func_name_push_args_to_output(std::ostream& output, Args&&... args) {
				output << Trielo::Detail::func_name<func_ptr>();
				output << "(";
				push_func_args_to_output(output, std::forward<Args>(args)...);
				output << ")";
			}
		}

		template<auto func_ptr, typename... Args>
		inline auto load_output_exec_get_result(std::stringstream& output, Args&&... args) {
			Print::push_func_name_push_args_to_output<func_ptr>(output, std::forward<Args>(args)...);
			const auto result { func_ptr(std::forward<Args>(args)...) };
			output << ": ";
			Trielo::Detail::Print::push_one_arg_to_output(output, std::forward<decltype(result)>(result));
			return std::move(result);
		}
	}

	template<typename T_FuncPtr, typename... Args>
	concept returns_void = std::is_same_v<std::invoke_result_t<T_FuncPtr, Args...>, void>;

	template <auto func_ptr, typename... Args>
	requires returns_void<decltype(func_ptr), Args...>
	inline void trielo(Args&&... args) {
		std::stringstream output;
		Detail::Print::push_func_name_push_args_to_output<func_ptr>(output, std::forward<Args>(args)...);
		func_ptr(std::forward<Args>(args)...);
		std::cout << output.view() << std::endl;
	}

	template <auto func_ptr, typename... Args>
	inline auto trielo(Args&&... args) {
		std::stringstream output;
		const auto result { Detail::load_output_exec_get_result<func_ptr>(output, std::forward<Args>(args)...) };
		std::cout << output.view() << std::endl;
		return std::move(result);
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Result, typename... Args>
	auto trielo(Success<T_Result> success_code, Args&&... args) {
		static_assert(
			std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>, T_Result>,
			"Provided function pointer must return the Success<T> type"
		);

		const auto result { funcPtr(std::forward<Args>(args)...) };

		if (result == success_code.value) {
			std::cout << "\033[32mSuccess: \033[m";
		} else {
			std::cout << "\033[31mERROR: \033[m";
		}
		Detail::Print::push_func_name_push_args_to_output<funcPtr>(std::cout, std::forward<Args>(args)...);
		std::cout << ": ";
		Detail::Print::push_one_arg_to_output(std::cout, result);
		std::cout << std::endl;

		return result;
	}

	template <auto funcPtr, typename T_Result, typename... Args>
	auto trielo(Error<T_Result> error_code, Args&&... args) {
		static_assert(
			std::is_same_v<std::invoke_result_t<decltype(funcPtr), Args...>, T_Result>,
			"Provided function pointer must return the Error<T> type"
		);

		const auto result { funcPtr(std::forward<Args>(args)...) };

		if (result == error_code.value) {
			Detail::print_error();
		} else {
			Detail::print_success();
		}
		Detail::Print::push_func_name_push_args_to_output<funcPtr>(std::cout, std::forward<Args>(args)...);
		std::cout << ": ";
		Detail::Print::push_one_arg_to_output(std::cout, result);
		std::cout << std::endl;

		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trielo_lambda(Success<T_Result> success_code, T_Lambda lambda, Args&&... args) {
		const auto result { trielo<funcPtr>(success_code, std::forward<Args>(args)...) };
		if(result != success_code.value) {
			lambda();
		}
		return result;
	}

	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trielo_lambda(Error<T_Result> error_code, T_Lambda lambda, Args&&... args) {
		const auto result { trielo<funcPtr>(error_code, std::forward<Args>(args)...) };
		if(result != error_code.value) {
			lambda();
		}
		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Result, typename... Args>
	auto trieloxit(Success<T_Result> success_code, Args&&... args) {
		const auto result { trielo<funcPtr>(success_code, std::forward<Args>(args)...) };
		if(result != success_code.value) {
			std::exit(EXIT_FAILURE);
		}
		return result;
	}

	template <auto funcPtr, typename T_Result, typename... Args>
	auto trieloxit(Error<T_Result> error_code, Args&&... args) {
		const auto result { trielo<funcPtr>(error_code, std::forward<Args>(args)...) };
		if(result == error_code.value) {
			std::exit(EXIT_FAILURE);
		}
		return result;
	}
}

namespace Trielo {
	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trieloxit_lambda(Success<T_Result> success_code, T_Lambda lambda, Args&&... args) {
		const auto result { trielo<funcPtr>(success_code, std::forward<Args>(args)...) };
		if(result != success_code.value) {
			lambda();
			std::exit(EXIT_FAILURE);
		}
		return result;
	}

	template <auto funcPtr, typename T_Lambda, typename T_Result, typename... Args>
	auto trieloxit_lambda(Error<T_Result> error_code, T_Lambda lambda, Args&&... args) {
		const auto result { trielo<funcPtr>(error_code, std::forward<Args>(args)...) };
		if(result == error_code.value) {
			lambda();
			std::exit(EXIT_FAILURE);
		}
		return result;
	}
}
