#include "ApproximateSolutionOfSystemsOfLinearEquations.h"
#include <iomanip>
#include <cassert>


namespace KHAS {

    void ApproximateSolutionOfSystemsOfLinearEquations::print() const noexcept {
        showHeader();
        auto [error_value, is_read] { inputRead() };
        if (!is_read) {
            auto delim{ delimiter('-', width_screen_) };
            std::cerr << delim << "\n" << generateString("Ошибка ввода данных!", width_screen_) << "\n" << delim << "\n";
            return;
        }

        showResult(error_value);
    }

    constexpr std::string ApproximateSolutionOfSystemsOfLinearEquations::delimiter(char c, size_t width_screen) const noexcept
    {
        return std::string(width_screen, c);
    }

    void ApproximateSolutionOfSystemsOfLinearEquations::showHeader(std::ostream& out) const noexcept
    {
        auto delim{ delimiter('-', width_screen_) };
        std::string subject_header{ "Дисциплина:" };
        std::string subject_name{ "Вычислительная математика" };
        std::string student_header{ "Студент:" };
        std::string student_name{ "Хакимов А.С." };
        std::string group_header{ "Группа:" };
        std::string group_name{ "ПБ-11" };
        std::string variant_header{ "Вариант:" };
        std::string variant_name{ "№1" };
        std::string theme_header{ "Тема:" };
        std::string theme_name{ "Приближенное решение систем линейных уравнений" };

        size_t width_left{ (width_screen_ - 3) / 2 - 2 };
        size_t width_right{ width_left + ((width_screen_ & 1) == 0) };

        assert(width_left >= 0 && "you need to increase the width_left of the output on the screen");
        assert(width_right >= 0 && "you need to increase the width_right of the output on the screen");
        assert(subject_header.size() <= width_left && subject_name.size() <= width_right);
        assert(student_header.size() <= width_left && student_name.size() <= width_right);
        assert(group_header.size() <= width_left && group_name.size() <= width_right);
        assert(variant_header.size() <= width_left && variant_name.size() <= width_right);
        assert(theme_header.size() <= width_left && theme_name.size() <= width_right);

        out << delim << "\n";
        out << "| " << std::setw(width_left) << std::left << subject_header << " | " << std::setw(width_right) << std::right << subject_name << " |\n";
        out << "| " << std::setw(width_left) << std::left << student_header << " | " << std::setw(width_right) << std::right << student_name << " |\n";
        out << "| " << std::setw(width_left) << std::left << group_header << " | " << std::setw(width_right) << std::right << group_name << " |\n";
        out << "| " << std::setw(width_left) << std::left << variant_header << " | " << std::setw(width_right) << std::right << variant_name << " |\n";
        out << "| " << std::setw(width_left) << std::left << theme_header << " | " << std::setw(width_right) << std::right << theme_name << " |\n";
        out << delim << "\n";
    }

    void ApproximateSolutionOfSystemsOfLinearEquations::showResult(double error_value) const noexcept {

        auto delim{ delimiter('-', width_screen_) };

        size_t part_width{ width_screen_ / 9 };
        size_t precision_size{ 5 };

        std::cout << delim << "\n"
            << generateString("Результаты поиска приближенного решения системы из 4-х линейных уравнений методом Зейделя", width_screen_) << "\n"
            << generateString("допустимая ошибка при вычислении каждой неизвестой переменной = " + std::to_string(precision(error_value, 4)), width_screen_) << "\n"
            << delim << "\n"
            << generateString("№ шага", part_width) << generateString("x", part_width)
            << generateString("x2", part_width) << generateString("x3", part_width)
            << generateString("x4", part_width) << generateString("x err", part_width)
            << generateString("x2 err", part_width) << generateString("x3 err", part_width)
            << generateString("x4 err", part_width) << "\n"
            << delim << "\n";

        InputData data{ data_input_ };
        InputData tmp{ data_input_ };
        InputData error{ data_input_ };
        size_t step{};

        showInputData(step, data, InputData{ 0, 0, 0 ,0 });
        while (!(error < error_value)) {

            auto vx{ data.calculate_x(data_input_.getX()) };
            auto vx2{ data.calculate_x2(vx, data_input_.getX2()) };
            auto vx3{ data.calculate_x3(vx, vx2, data_input_.getX3()) };
            auto vx4{ data.calculate_x4(vx, vx2, vx3, data_input_.getX4()) };

            tmp = InputData{
                precision(vx, precision_size)
                , precision(vx2, precision_size)
                , precision(vx3, precision_size)
                , precision(vx4, precision_size) };
            error = (tmp - data).to_abs();
            ++step;
            data = tmp;
            showInputData(step, data, error);
        };

        std::cout << delim << "\n";
    }

    [[nodiscard]] std::pair<double, bool> ApproximateSolutionOfSystemsOfLinearEquations::inputRead(std::istream& in) const noexcept {
        double data_result{};
        bool flag_result{};
        std::string cmd_name{ "Введите значение допустимой ошибки:" };
        std::cout << "| " << cmd_name
            << delimiter(' ', 2)
            << delimiter('_', width_screen_ - cmd_name.size() - 5) << "|"
            << delimiter('\b', width_screen_ - cmd_name.size() - 4);

        in >> data_result;

        flag_result = in.good();
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return { data_result, flag_result };
    }

    inline double ApproximateSolutionOfSystemsOfLinearEquations::precision(double num, size_t degree) const noexcept
    {
        auto tmp{ std::pow(10., degree) };
        return std::round(num * tmp) / tmp;
    }

    void ApproximateSolutionOfSystemsOfLinearEquations::showInputData(size_t step, const InputData& data, const InputData& error, std::ostream& out) const noexcept {
        size_t part_width{ width_screen_ / 9 };
        constexpr const size_t precision_size{ 5 };
        out << generateString(std::to_string(step), part_width)
            << generateString(typeToString(data.getX(), precision_size), part_width)
            << generateString(typeToString(data.getX2(), precision_size), part_width)
            << generateString(typeToString(data.getX3(), precision_size), part_width)
            << generateString(typeToString(data.getX4(), precision_size), part_width)

            << generateString(typeToString(error.getX(), precision_size), part_width)
            << generateString(typeToString(error.getX2(), precision_size), part_width)
            << generateString(typeToString(error.getX3(), precision_size), part_width)
            << generateString(typeToString(error.getX4(), precision_size), part_width)
            << "\n";
    }

}
