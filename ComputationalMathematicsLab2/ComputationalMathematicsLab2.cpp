#include "InputData.h"
#include "ApproximateSolutionOfSystemsOfLinearEquations.h"


int main() {
    std::setlocale(LC_ALL, "Russian");
    auto a{ KHAS::InputData{ 2.583, -2.488, -0.869, 0.729 } };
    KHAS::ApproximateSolutionOfSystemsOfLinearEquations ale{ a, std::size_t{99} };
    ale.print();
    return 0;
}