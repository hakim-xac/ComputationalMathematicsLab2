#pragma once

namespace KHAS {


    struct InputData {
    public:
        using value_type = double;
    public:
        explicit InputData(value_type x, value_type x2, value_type x3, value_type x4) noexcept;
        InputData(const InputData& data)            noexcept;
        InputData(InputData&& data)                 noexcept;
        InputData operator =(const InputData& data) noexcept;
        InputData& operator =(InputData&& data)     noexcept;

    public:
        value_type const getX()     const noexcept;
        value_type const getX2()    const noexcept;
        value_type const getX3()    const noexcept;
        value_type const getX4()    const noexcept;

        InputData to_abs()          const noexcept;

        double calculate_x(double x)                                     const noexcept;
        double calculate_x2(double x, double x2)                         const noexcept;
        double calculate_x3(double x, double x2, double x3)              const noexcept;
        double calculate_x4(double x, double x2, double x3, double x4)   const noexcept;

    public:
        InputData operator -(const InputData& rhs)  const;
        bool operator <(const InputData& rhs)       const;
        bool operator <(value_type value)           const;

    private:
        value_type x_{};
        value_type x2_{};
        value_type x3_{};
        value_type x4_{};
    };
}