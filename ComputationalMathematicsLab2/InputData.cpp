#include "InputData.h"
#include <tuple>
#include <utility>

namespace KHAS {
    InputData::InputData(value_type x, value_type x2, value_type x3, value_type x4) noexcept
        : x_{ x }, x2_{ x2 }, x3_{ x3 }, x4_{ x4 } {}

    InputData::InputData(const InputData& data) noexcept
        : x_{ data.x_ }
        , x2_{ data.x2_ }
        , x3_{ data.x3_ }
        , x4_{ data.x4_ } {}

    InputData::InputData(InputData&& data) noexcept
        : x_{ std::move(data.x_) }
        , x2_{ std::move(data.x2_) }
        , x3_{ std::move(data.x3_) }
        , x4_{ std::move(data.x4_) } {}

    InputData InputData::operator =(const InputData& data) noexcept {

        x_ = data.x_;
        x2_ = data.x2_;
        x3_ = data.x3_;
        x4_ = data.x4_;
        return *this;
    }

    InputData& InputData::operator =(InputData&& data) noexcept {
        x_ = std::move(data.x_);
        x2_ = std::move(data.x2_);
        x3_ = std::move(data.x3_);
        x4_ = std::move(data.x4_);
        return *this;
    }


    InputData::value_type const InputData::getX() const noexcept { return x_; }
    InputData::value_type const InputData::getX2() const noexcept { return x2_; }
    InputData::value_type const InputData::getX3() const noexcept { return x3_; }
    InputData::value_type const InputData::getX4() const noexcept { return x4_; }

    InputData InputData::to_abs() const noexcept {
        return InputData{ fabs(x_), fabs(x2_), fabs(x3_), fabs(x4_) };
    }

    double InputData::calculate_x(double x) const noexcept {
        return x - 0.281 * x2_ + 0.167 * x3_ - 0.292 * x4_;
    };

    double InputData::calculate_x2(double x, double x2) const noexcept {
        return x2 + 0.110 * x - 0.291 * x3_ - 0.339 * x4_;
    };

    double InputData::calculate_x3(double x, double x2, double x3) const noexcept {
        return x3 + 0.154 * x - 0.303 * x2 + 0.183 * x4_;
    };

    double InputData::calculate_x4(double x, double x2, double x3, double x4) const noexcept {
        return x4 - 0.243 * x + 0.169 * x2 - 0.435 * x3;
    };

    InputData InputData::operator -(const InputData & rhs) const {
        return InputData{ x_ - rhs.x_, x2_ - rhs.x2_, x3_ - rhs.x3_, x4_ - rhs.x4_ };
    }

    bool InputData::operator <(const InputData& rhs) const {
        return std::tie(x_, x2_, x3_, x4_) < std::tie(rhs.x_, rhs.x2_, rhs.x3_, rhs.x4_);
    }

    bool InputData::operator <(value_type value) const {
        return std::tie(x_, x2_, x3_, x4_) < std::tie(value, value, value, value);
    }

}