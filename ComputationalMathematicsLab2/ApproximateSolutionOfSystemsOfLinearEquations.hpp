#include <iomanip>
#include <cassert>

namespace KHAS {

    template <typename IData>
        requires std::is_convertible_v<std::decay_t<IData>, InputData>
    ApproximateSolutionOfSystemsOfLinearEquations::ApproximateSolutionOfSystemsOfLinearEquations(IData&& data, size_t width_screen)
        : data_input_(std::forward<IData>(data))
        , width_screen_{ width_screen }
        , steps_counts_{} {}

    template <typename T>
    std::string ApproximateSolutionOfSystemsOfLinearEquations::typeToString(T&& value, size_t precision) const noexcept {
        std::stringstream ss{ "" };
        ss << std::fixed << std::setprecision(precision) << std::forward<T>(value);
        return ss.str();
    }

    template <typename Str>
        requires std::is_convertible_v<Str, std::string>
    std::string ApproximateSolutionOfSystemsOfLinearEquations::generateString(Str&& str, size_t width_screen) const noexcept {

        std::string s{ std::forward<Str>(str) };

        size_t size{ s.size() };

        assert(size + 2 <= width_screen);
        size_t part_size{ (width_screen - size - 2) >> 1 };
        return "|" + std::string(part_size, ' ') + s + std::string(part_size + ((size & 1) == 0), ' ') + "|";
    }
}