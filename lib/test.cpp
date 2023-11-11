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

void Trielo::test() {
	trielo<&func1>();
	trielo<&func2>();
	trielo<&func3>(3);
	trielo<&func3_5>(3, 5);
	trielo<&func4>(4);
	trielo<&func5>(4, 5);
	trielo<&func6>(6, 5, 4);

	trielo<&func2>(OkErrCode(2));
	trielo<&func5>(OkErrCode(9), 4, 5);
	trielo<&func6>(OkErrCode(15), 6, 5, 4);
	trielo<&func2>(OkErrCode(1));
	trielo<&func5>(OkErrCode(4), 4, 5);
	trielo<&func6>(OkErrCode(1), 6, 5, 4);
	trielo<&func7>(OkErrCode(true), 5);

	trielo<&func7>(FailErrCode(false), 5);

	
	trieloxit<&func2>(OkErrCode(2));
	trieloxit<&func5>(OkErrCode(9), 4, 5);
	trieloxit<&func6>(OkErrCode(15), 6, 5, 4);
	trieloxit<&func2>(OkErrCode(1));
	trieloxit<&func5>(OkErrCode(4), 4, 5);
	trieloxit<&func6>(OkErrCode(1), 6, 5, 4);
	trieloxit<&func7>(OkErrCode(true), 5);
}
