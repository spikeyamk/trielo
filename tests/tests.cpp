#include "trielo/trielo.hpp"
#include "trielo/tests.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

namespace Trielo {
	namespace Tests {
		namespace Functions {
			namespace ReturnsVoid {
				void without_args() {}
				void one_arg(int x = 1) { int junk = x; junk++; }
				void one_function_pointer(void (*ptr)(void)) {
					(void) ptr;
				}
				void two_args(int x = 1, float y = 2.0f) { (void) x; (void) y; };
				void consumes_ostreamable(const Ostreamable& obj) {
					(void) obj;
				}
				void consumes_nonostreamable(const NonOstreamable& obj) {
					(void) obj;
				}
				void consumes_arg_reference(const int& x) {
					(void) x;
				}
			}

			namespace ReturnsInt {
				int without_args() { return 0xFF; }
				int one_arg(int x = 1) { return x * 0xFF; }
				int sum(int x = 1, int y = 0xFF - 1) { return x + y; }
				int product(int x = 1, int y = 0xFF, int z = 1) { return x * y * z; }
			}

			namespace ReturnsBool {
				bool returns_false() { return false; }
				bool returns_true() { return true; }
			}

			namespace ReturnsOstreamable {
				Ostreamable consumes_ostreamable(const Ostreamable& obj) {
					return obj;
				}
				Ostreamable consumes_nonostreamable(const NonOstreamable& obj) {
					(void) obj;
					return Ostreamable {};
				}
			}

			namespace ReturnsNonOstreamable {
				NonOstreamable consumes_ostreamable(const Ostreamable& obj) {
					(void) obj;
					return NonOstreamable {};
				}
				NonOstreamable consumes_nonostreamable(const NonOstreamable& obj) {
					return obj;
				}
			}
		}
	}

	namespace Tests {
		namespace Trielo {
			namespace Vanilla {
				namespace ReturnsVoid {
					int without_args() {
						trielo<&Functions::ReturnsVoid::without_args>();
						return 0;
					}

					int one_arg() {
						trielo<&Functions::ReturnsVoid::one_arg>(1);
						return 0;
					}

					int one_function_pointer() {
						trielo<&Functions::ReturnsVoid::one_function_pointer>(&Functions::ReturnsVoid::without_args);
						return 0;
					}

					int two_args() {
						trielo<&Functions::ReturnsVoid::two_args>(1, 2.0f);
						return 0;
					}	

					int consumes_arg_reference() {
						int x = 696969;
						trielo<&Functions::ReturnsVoid::consumes_arg_reference>(x);
						return 0;
					}	
				}

				namespace ReturnsInt {
					int without_args() {
						if(trielo<&Functions::ReturnsInt::without_args>() == 0xFF) {
							return 0;
						} else {
							return -1;
						}
					}

					int one_arg() {
						if(trielo<&Functions::ReturnsInt::one_arg>(1) == 0xFF) {
							return 0;
						} else {
							return -1;
						}
					}

					int sum() {
						if(trielo<&Functions::ReturnsInt::sum>(1, 0xFF - 1) == 0xFF) {
							return 0;
						} else {
							return -1;
						}
					}

					int product() {
						if(trielo<&Functions::ReturnsInt::product>(1, 0xFF, 1) == 0xFF) {
							return 0;
						} else {
							return -1;
						}
					}
				}

				namespace ReturnsBool {
					int returns_false() {
						if(trielo<&Functions::ReturnsBool::returns_false>() == false) {
							return 0;
						} else {
							return -1;
						}
					}		

					int returns_true() {
						if(trielo<&Functions::ReturnsBool::returns_true>() == true) {
							return 0;
						} else {
							return -1;
						}
					}		
				}
			}

			namespace OK {
				namespace Success {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(::Trielo::Success(0xFF));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(::Trielo::Success(0xFF), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(::Trielo::Success(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(::Trielo::Success(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(::Trielo::Success(false));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(::Trielo::Success(true));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(::Trielo::Success(0x7F));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(::Trielo::Success(0x7F), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(::Trielo::Success(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(::Trielo::Success(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(::Trielo::Success(true));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(::Trielo::Success(false));
							return 0;
						}		
					}
				}
			}

			namespace Fail {
				namespace Success {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(Error(0x7F));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(Error(0x7F), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(Error(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(Error(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(Error(true));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(Error(false));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(Error(0xFF));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(Error(0xFF), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(Error(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(Error(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(Error(false));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(Error(true));
							return 0;
						}		
					}

				}
			}
		}

		namespace Trieloxit {
			namespace OK {
				namespace Success {
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(::Trielo::Success(0xFF));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(::Trielo::Success(0xFF), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(::Trielo::Success(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(::Trielo::Success(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(::Trielo::Success(false));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(::Trielo::Success(true));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(::Trielo::Success(0x7F));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(::Trielo::Success(0x7F), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(::Trielo::Success(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(::Trielo::Success(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(::Trielo::Success(true));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(::Trielo::Success(false));
							return 0;
						}		
					}
				}
			}

			namespace Fail {
				namespace Success{
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(Error(0x7F));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(Error(0x7F), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(Error(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(Error(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(Error(true));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(Error(false));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(Error(0xFF));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(Error(0xFF), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(Error(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(Error(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(Error(false));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(Error(true));
							return 0;
						}		
					}
				}
			}
		}
	}

	namespace Tests {
		using namespace Trielo;
		namespace Trielo {
			void vanilla() {
				trielo<Tests::Trielo::Vanilla::ReturnsVoid::without_args>();
				trielo<Tests::Trielo::Vanilla::ReturnsVoid::one_arg>();
				trielo<Tests::Trielo::Vanilla::ReturnsVoid::one_function_pointer>();
				trielo<Tests::Trielo::Vanilla::ReturnsVoid::two_args>();
				trielo<Tests::Trielo::Vanilla::ReturnsVoid::consumes_arg_reference>();
				trielo<Tests::Trielo::Vanilla::ReturnsInt::without_args>();
				trielo<Tests::Trielo::Vanilla::ReturnsInt::one_arg>();
				trielo<Tests::Trielo::Vanilla::ReturnsInt::sum>();
				trielo<Tests::Trielo::Vanilla::ReturnsInt::product>();
				trielo<Tests::Trielo::Vanilla::ReturnsBool::returns_false>();
				trielo<Tests::Trielo::Vanilla::ReturnsBool::returns_true>();
			}

			void colored() {
				trielo<Tests::Trielo::OK::Success::ReturnsInt::without_args>();
				trielo<Tests::Trielo::OK::Success::ReturnsInt::one_arg>();
				trielo<Tests::Trielo::OK::Success::ReturnsInt::sum>();
				trielo<Tests::Trielo::OK::Success::ReturnsInt::product>();
				trielo<Tests::Trielo::OK::Success::ReturnsBool::returns_false>();
				trielo<Tests::Trielo::OK::Success::ReturnsBool::returns_true>();

				trielo<Tests::Trielo::OK::ERROR::ReturnsInt::without_args>();
				trielo<Tests::Trielo::OK::ERROR::ReturnsInt::one_arg>();
				trielo<Tests::Trielo::OK::ERROR::ReturnsInt::sum>();
				trielo<Tests::Trielo::OK::ERROR::ReturnsInt::product>();
				trielo<Tests::Trielo::OK::ERROR::ReturnsBool::returns_false>();
				trielo<Tests::Trielo::OK::ERROR::ReturnsBool::returns_true>();

			}
		}
	
		namespace Trieloxit {
			void ok_success() {
				trielo<Tests::Trieloxit::OK::Success::ReturnsInt::without_args>();
				trielo<Tests::Trieloxit::OK::Success::ReturnsInt::one_arg>();
				trielo<Tests::Trieloxit::OK::Success::ReturnsInt::sum>();
				trielo<Tests::Trieloxit::OK::Success::ReturnsInt::product>();
				trielo<Tests::Trieloxit::OK::Success::ReturnsBool::returns_false>();
				trielo<Tests::Trieloxit::OK::Success::ReturnsBool::returns_true>();
			}

			void fail_success() {
				trielo<Tests::Trieloxit::Fail::Success::ReturnsInt::without_args>();
				trielo<Tests::Trieloxit::Fail::Success::ReturnsInt::one_arg>();
				trielo<Tests::Trieloxit::Fail::Success::ReturnsInt::sum>();
				trielo<Tests::Trieloxit::Fail::Success::ReturnsInt::product>();
				trielo<Tests::Trieloxit::Fail::Success::ReturnsBool::returns_false>();
				trielo<Tests::Trieloxit::Fail::Success::ReturnsBool::returns_true>();
			}
		}
	}
}

namespace Trielo {
	namespace Tests {
		int run_all() {
			static int trieloxit_fail_num { 0 };
			if(trieloxit_fail_num < 12) {
				std::atexit([]() { 
					trieloxit_fail_num++;
					run_all();
				});
			} else {
				std::exit(EXIT_SUCCESS);
			}

			if(trieloxit_fail_num == 0) {
				using namespace Trielo;
				trielo<Tests::Trielo::vanilla>();
				trielo<Tests::Trielo::colored>();
				trielo<Tests::Trieloxit::ok_success>();
			}

			switch(trieloxit_fail_num) {
				case 0:
					Tests::Trieloxit::OK::ERROR::ReturnsInt::without_args();
					break;
				case 1:
					Tests::Trieloxit::OK::ERROR::ReturnsInt::one_arg();
					break;
				case 2:
					Tests::Trieloxit::OK::ERROR::ReturnsInt::sum();
					break;
				case 3:
					Tests::Trieloxit::OK::ERROR::ReturnsInt::product();
					break;
				case 4:
					Tests::Trieloxit::OK::ERROR::ReturnsBool::returns_false();
					break;
				case 5:
					Tests::Trieloxit::OK::ERROR::ReturnsBool::returns_true();
					break;
			}

			if(trieloxit_fail_num == 6) {
				trielo<Tests::Trieloxit::fail_success>();
			}

			switch(trieloxit_fail_num) {
				case 6:
					Tests::Trieloxit::Fail::ERROR::ReturnsInt::without_args();
					break;
				case 7:
					Tests::Trieloxit::Fail::ERROR::ReturnsInt::one_arg();
					break;
				case 8:
					Tests::Trieloxit::Fail::ERROR::ReturnsInt::sum();
					break;
				case 9:
					Tests::Trieloxit::Fail::ERROR::ReturnsInt::product();
					break;
				case 10:
					Tests::Trieloxit::Fail::ERROR::ReturnsBool::returns_false();
					break;
				case 11:
					Tests::Trieloxit::Fail::ERROR::ReturnsBool::returns_true();
					break;
			}
			return 0;
		}

		int run_get_func_name() {
			if constexpr(
				Detail::func_name<Functions::ReturnsVoid::without_args>() != std::string_view(
					#ifdef _MSC_VER
					"void __cdecl Trielo::Tests::Functions::ReturnsVoid::without_args"
					#else
					"void Trielo::Tests::Functions::ReturnsVoid::without_args"
					#endif
				)
			) {
				return -1;
			}

			return 0;
		}

		int run_get_type_name() {
			int i = 0;
			if(Detail::type_name<decltype(i)>() != std::string_view("int")) {
				return -1;
			}

			return 0;
		}

	}
}

namespace Trielo {
	namespace Tests {
		namespace Print {
			int ostreamable() {
				std::stringstream std_cout_redirect;
				auto default_std_cout = std::cout.rdbuf();
				// Redirect std::cout
				std::cout.rdbuf(std_cout_redirect.rdbuf());

				const int ret = [&std_cout_redirect]() {
					Ostreamable ostreamable;
					Detail::Print::push_func_name_push_args_to_output<Functions::ReturnsVoid::consumes_ostreamable>(std_cout_redirect, ostreamable);
					if(std_cout_redirect.view() != std::string_view(
						#ifdef _MSC_VER
							"void __cdecl Trielo::Tests::Functions::ReturnsVoid::consumes_ostreamable(struct Trielo::Tests::Ostreamable: '4206969')"
						#else
						#endif
					)) {
						return -1;
					}

					// This ugly hack clears the buffer by constructing an std::string from const char* and swapping the contents with it because std::ostringstream::clear() only clears its error state? C++ waduhek?
					std_cout_redirect.str("");
					Detail::Print::push_func_name_push_args_to_output<Functions::ReturnsOstreamable::consumes_ostreamable>(std_cout_redirect, ostreamable);
					if(std_cout_redirect.view() != std::string_view(
						#ifdef _MSC_VER
							"struct Trielo::Tests::Ostreamable __cdecl Trielo::Tests::Functions::ReturnsOstreamable::consumes_ostreamable(struct Trielo::Tests::Ostreamable: '4206969')"
						#else
						#endif
					)) {
						return -2;
					}

					return 0;
				}();

				// Restore std::cout
				std::cout.rdbuf(default_std_cout);

				return ret;
			}

			template<typename... Args>
			concept supports_std_cout = requires (std::ostream& os, const Args&&... args) {
				{ ((os << std::forward<const Args>(args)), ...) } -> std::same_as<std::ostream&>;
			};

			template<typename Arg> requires supports_std_cout<Arg>
			static inline void inner_print(const Arg&& arg) {
				std::cout << std::forward<const Arg>(arg);
			}

			template<typename Arg>
			static inline void inner_print(const Arg&& arg) {
				if constexpr(std::is_pointer_v<Arg>) {
					std::cout << static_cast<const void*>(arg);
				} else {
					std::cout << static_cast<const void*>(&arg);
				}
			}

			template<typename Arg>
			static inline void inner_print_with_trailing_comma(const Arg&& arg) {
				inner_print(std::forward<const Arg>(arg));
				std::cout << ", ";
			}

			template<typename HeadArg, typename... Args> requires supports_std_cout<HeadArg, Args...>
			static inline void my_print(const HeadArg&& head_arg, const Args&&... args) {
				inner_print(std::forward<const HeadArg>(head_arg));
				((inner_print_with_trailing_comma(std::forward<const Args>(args)) << ", "), ...);
			}

			template<typename HeadArg, typename... Args>
			[[deprecated("This type does not support printing")]]
			static inline void my_print(const HeadArg&& head_arg, const Args&&... args) {
				inner_print(std::forward<const HeadArg>(head_arg));
				((inner_print_with_trailing_comma(std::forward<const Args>(args)) << ", "), ...);
			}

			int nonostreamable() {
				std::stringstream std_cout_redirect;
				auto default_std_cout = std::cout.rdbuf();
				// Redirect std::cout
				std::cout.rdbuf(std_cout_redirect.rdbuf());

				const int ret {
					[&std_cout_redirect]() {
						NonOstreamable nonostreamable;
						Detail::Print::push_func_name_push_args_to_output<Functions::ReturnsVoid::consumes_nonostreamable>(std_cout_redirect, nonostreamable);

						const std::string_view before_pointer_value {
							#ifdef _MSC_VER
								"void __cdecl Trielo::Tests::Functions::ReturnsVoid::consumes_nonostreamable(struct Trielo::Tests::NonOstreamable: '"
							#endif
						};
						if(std_cout_redirect.view().substr(0, before_pointer_value.length()) != before_pointer_value) {
							return -1;
						}
						
						const std::string_view after_pointer_value { "')" };
						if(std_cout_redirect.view().find(after_pointer_value, before_pointer_value.length()) == std_cout_redirect.view().size()) {
							return -2;
						}
						
						return 0;
					}()
				};

				// Restore std::cout
				std::cout.rdbuf(default_std_cout);

				return ret;
			}
		}
	}
}


std::ostream& operator<<(std::ostream& os, const Trielo::Tests::Ostreamable& obj) {
	os << obj.x;
	return os;
}
