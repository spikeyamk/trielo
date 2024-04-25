#include "trielo/trielo.hpp"
#include "trielo/tests.hpp"

int main() {
    return Trielo::trielo<Trielo::Tests::run_all>(Trielo::Success(0));
}
