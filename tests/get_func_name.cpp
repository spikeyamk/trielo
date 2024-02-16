#include "trielo/trielo.hpp"
#include "trielo/tests.hpp"

int main() {
    return Trielo::trielo<Trielo::Tests::run_get_func_name>(Trielo::Code::Success(0));
}