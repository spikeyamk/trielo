#include "trielo.hpp"

void func1(void) {}

int func2(void) {
	return 2;
}

void func3(int x) {}

void func3_5(int x, int y) {}

int func4(int x) {
	return x;
}

int func5(int x, int y) {
	return x + y;
}

int func6(int x, int y, int z) {
	return x + y + z;
}

bool func7(int x) {
	if(x == 0) {
		return true;
	} else {
		return false;
	}
}

int main() {
	Trielo::trielo<&func1>();
	Trielo::trielo<&func2>();
	Trielo::trielo<&func3>(3);
	Trielo::trielo<&func3_5>(3, 5);
	Trielo::trielo<&func4>(4);
	Trielo::trielo<&func5>(4, 5);
	Trielo::trielo<&func6>(6, 5, 4);

	Trielo::trielo<&func2>(Trielo::OkErrCode(2));
	Trielo::trielo<&func5>(Trielo::OkErrCode(9), 4, 5);
	Trielo::trielo<&func6>(Trielo::OkErrCode(15), 6, 5, 4);
	Trielo::trielo<&func2>(Trielo::OkErrCode(1));
	Trielo::trielo<&func5>(Trielo::OkErrCode(4), 4, 5);
	Trielo::trielo<&func6>(Trielo::OkErrCode(1), 6, 5, 4);
	Trielo::trielo<&func7>(Trielo::OkErrCode(true), 5);

	Trielo::trielo<&func7>(Trielo::FailErrCode(false), 5);

	/*
	Trielo::trieloxit<&func2>(Trielo::OkErrCode(2));
	Trielo::trieloxit<&func5>(Trielo::OkErrCode(9), 4, 5);
	Trielo::trieloxit<&func6>(Trielo::OkErrCode(15), 6, 5, 4);
	Trielo::trieloxit<&func2>(Trielo::OkErrCode(1));
	Trielo::trieloxit<&func5>(Trielo::OkErrCode(4), 4, 5);
	Trielo::trieloxit<&func6>(Trielo::OkErrCode(1), 6, 5, 4);
	Trielo::trieloxit<&func7>(Trielo::OkErrCode(true), 5);
	*/
}
