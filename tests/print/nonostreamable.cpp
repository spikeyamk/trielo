#include "trielo/trielo.hpp"
#include "trielo/tests.hpp"

int main() {
    return Trielo::trielo<Trielo::Tests::Print::nonostreamable>(Trielo::Code::Success(0));
}