#pragma once
#include <type_traits>
#include <string>
#include <iostream>
#include <sstream>
#include "InputData.h"

namespace KHAS {
    class ApproximateSolutionOfSystemsOfLinearEquations {
    public:
        template <typename IData>
            requires std::is_convertible_v<std::decay_t<IData>, InputData>
        explicit ApproximateSolutionOfSystemsOfLinearEquations(IData&& data, size_t width_screen);

    public:
        void print() const noexcept;

    private:
        constexpr std::string delimiter(char c, size_t width_screen)    const noexcept;
        void showHeader(std::ostream& out = std::cout)                  const noexcept;
        void showResult(double error_value)                             const noexcept;
        double precision(double num, size_t degree)                     const noexcept;
        void showInputData(size_t step, const InputData& data, const InputData& error, std::ostream& out = std::cout) const noexcept;
        [[nodiscard]] std::pair<double, bool> inputRead(std::istream& in = std::cin) const noexcept;

    private:
        template <typename T>
        std::string typeToString(T&& value, size_t precision = 4) const noexcept;

        template <typename Str>
            requires std::is_convertible_v<Str, std::string>
        std::string generateString(Str&& str, size_t width_screen) const noexcept;

    private:
        InputData data_input_;
        size_t width_screen_;
        size_t steps_counts_;
    };

}

#include "ApproximateSolutionOfSystemsOfLinearEquations.hpp"