#pragma once

#include <iostream>

namespace Trielo {
	namespace Tests {
		struct Ostreamable {
			int x { 4206969 };
		};

		struct NonOstreamable {
			int x { 666 };
		};

		int run_all();
		int run_get_func_name();
		int run_get_type_name();

		namespace Print {
			int ostreamable();
			int nonostreamable();
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Trielo::Tests::Ostreamable& obj);


