#include "trielo/trielo.hpp"
#include "trielo/tests.hpp"
#include <iostream>
#include <cstdlib>

namespace Trielo {
	namespace Functions {
		namespace ReturnsVoid {
			void without_args() {}
			void one_arg(int x = 1) { int junk = x; junk++; }
			void two_args(int x = 1, int y = 2) { int junk = x + y; junk++; }
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
	}

	namespace Tests {
		using namespace Trielo;
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

					int two_args() {
						trielo<&Functions::ReturnsVoid::two_args>(1, 2);
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
							trielo<&Functions::ReturnsInt::without_args>(OkErrCode(0xFF));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(OkErrCode(0xFF), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(OkErrCode(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(OkErrCode(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(OkErrCode(false));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(OkErrCode(true));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(OkErrCode(0x7F));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(OkErrCode(0x7F), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(OkErrCode(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(OkErrCode(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(OkErrCode(true));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(OkErrCode(false));
							return 0;
						}		
					}
				}
			}

			namespace Fail {
				namespace Success {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(FailErrCode(0x7F));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(FailErrCode(0x7F), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(FailErrCode(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(FailErrCode(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(FailErrCode(true));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(FailErrCode(false));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trielo<&Functions::ReturnsInt::without_args>(FailErrCode(0xFF));
							return 0;
						}

						int one_arg() {
							trielo<&Functions::ReturnsInt::one_arg>(FailErrCode(0xFF), 1);
							return 0;
						}

						int sum() {
							trielo<&Functions::ReturnsInt::sum>(FailErrCode(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trielo<&Functions::ReturnsInt::product>(FailErrCode(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trielo<&Functions::ReturnsBool::returns_false>(FailErrCode(false));
							return 0;
						}		

						int returns_true() {
							trielo<&Functions::ReturnsBool::returns_true>(FailErrCode(true));
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
							trieloxit<&Functions::ReturnsInt::without_args>(OkErrCode(0xFF));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(OkErrCode(0xFF), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(OkErrCode(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(OkErrCode(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(OkErrCode(false));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(OkErrCode(true));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(OkErrCode(0x7F));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(OkErrCode(0x7F), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(OkErrCode(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(OkErrCode(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(OkErrCode(true));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(OkErrCode(false));
							return 0;
						}		
					}
				}
			}

			namespace Fail {
				namespace Success{
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(FailErrCode(0x7F));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(FailErrCode(0x7F), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(FailErrCode(0x7F), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(FailErrCode(0x7F), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(FailErrCode(true));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(FailErrCode(false));
							return 0;
						}		
					}
				}

				namespace ERROR {
					namespace ReturnsInt {
						int without_args() {
							trieloxit<&Functions::ReturnsInt::without_args>(FailErrCode(0xFF));
							return 0;
						}

						int one_arg() {
							trieloxit<&Functions::ReturnsInt::one_arg>(FailErrCode(0xFF), 1);
							return 0;
						}

						int sum() {
							trieloxit<&Functions::ReturnsInt::sum>(FailErrCode(0xFF), 1, 0xFF - 1);
							return 0;
						}

						int product() {
							trieloxit<&Functions::ReturnsInt::product>(FailErrCode(0xFF), 1, 0xFF, 1);
							return 0;
						}
					}

					namespace ReturnsBool {
						int returns_false() {
							trieloxit<&Functions::ReturnsBool::returns_false>(FailErrCode(false));
							return 0;
						}		

						int returns_true() {
							trieloxit<&Functions::ReturnsBool::returns_true>(FailErrCode(true));
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
				trielo<Tests::Trielo::Vanilla::ReturnsVoid::two_args>();
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

void my_test_func_name() {

}

namespace Trielo {
	namespace Tests {
		int run_all();

		int run_all() {
			static int trieloxit_fail_num = 0;
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
			if(get_func_name<my_test_func_name>() != std::string("my_test_func_name")) {
				return -1;
			} else {
				return 0;
			}
		}

		int run_get_type_name() {
			int i = 0;
			if(get_type_name<decltype(i)>() != std::string("int")) {
				return -1;
			} else {
				return 0;
			}
		}
	}
}
