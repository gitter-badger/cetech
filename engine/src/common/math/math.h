#pragma once

#include <cmath>

#include "../types.h"

namespace cetech {

    /*! Math
     */
    namespace math {
        /*! PI
         */
        constexpr float PI = 3.1415926535897932f;

        /*! 1/PI
         */
        constexpr float INV_PI = 0.31830988618f;

        /*! PI/2
         */
        constexpr float HALF_PI = 1.57079632679f;

        /*! e
         */
        constexpr float EULERS_NUMBER = 2.71828182845904523536f;

        constexpr float DOUBLE_SMALL_NUMBER = 1.e-8f;
        constexpr float FLOAT_SMALL_NUMBER = 1.e-4f;
        constexpr float BIG_NUMBER = .4e+38f;
        constexpr float MAX_FLT = 3.402823466e+38f;
    }

    namespace math {
        /*! Return greater of two numbers.
         * \param a First number.
         * \param b Second number.
         * \return greater of two numbers.
         */
        template < class T >
        CE_INLINE T max( const T a, const T b);

        /*! Return smaller of two numbers.
         * \param a First number.
         * \param b Second number.
         * \return smaller of two numbers.
         */
        template < class T >
        CE_INLINE T min( const T a, const T b);

        /*! Clamps a value between a minimum and maximum value.
         * \param a Value.
         * \param min Down range.
         * \param max Upper range.
         * \return Value between a minimum and maximum.
         */
        template < class T >
        CE_INLINE T clamp( const T a, const T min, const T max);

        /*! Return absolute value.
         * \param a Number.
         * \return Absolute value
         */
        template < class T > T
        abs( const T a);

        /*! Compare two floats.
         * \param f1 Float 1.
         * \param f2 Float 2.
         * \param epsilon Epsilon.
         */
        CE_INLINE bool almost_equal(const float f1, const float f2, const float epsilon = FLOAT_SMALL_NUMBER);


        /*! X * X
         * \param x
         * \return x * x
         */
        CE_INLINE float square(const float x);

        /*! Fast version of sqrt.
         * \param number Number.
         * \return sqrt.
         */
        CE_INLINE float fast_sqrt(const float number);

        /*! Fast version of invert sqrt.
         * Bassed on quake3 inv_sqrt bu constant is change to 0x5f375a86.
         * \param number Number.
         * \return invert sqrt.
         */
        CE_INLINE float fast_inv_sqrt(const float number);

        /*! Deg to Rad.
         * \param deg Deg.
         * \return Rad.
         */
        CE_INLINE float deg2rad(const float deg);

        /*! Rad to Deg.
         * \param rad Deg.
         * \return Deg.
         */
        CE_INLINE float rad2deg(const float rad);

        /*! Fast version of sin.
         * \param angle_deg Angle in deg.
         * \return sin
         */
        CE_INLINE float fast_sin(const float angle_deg);

        /*! Fast version of sin, cos.
         * \param angle_deg Angle in deg.
         * \param sin Sin.
         * \param cos Cos.
         */
        CE_INLINE void fast_sincos(const float angle_deg, float& sin, float& cos);

        /*! Return value based on value a. (  )
         * \param a Input value.
         * \param ge_zero Value for a >= 0.0f.
         * \param lt_zero Value for a <= 0.0f.
         * \return a >= 0.0f ? ge_zero : lt_zero
         */
        CE_INLINE float float_select(const float a, const float ge_zero, const float lt_zero);
    }


    namespace math {
        template < class T >
        T max( const T a, const T b) {
            return (a >= b) ? a : b;
        }

        template < class T >
        T min( const T a, const T b) {
            return (a <= b) ? a : b;
        }

        template < class T >
        T abs( const T a) {
            return (a >= 0) ? a : -a;
        }

        template < >
        CE_INLINE float abs( const float a) {
            const int y = (int&)a & 0x7FFFFFFF;
            return (float&)y;
        }

        template < class T >
        T clamp( const T a, const T min, const T max) {
            return (a < min ? min : (a < max ? a : max));
        }

        bool almost_equal(const float f1, const float f2, float epsilon) {
            return abs(f1 - f2) < epsilon;
        }

        float fast_sqrt(const float number) {
            return fast_inv_sqrt(number) * number;
        }

        float fast_inv_sqrt(const float number) {
            const float fuconstant = 0x5f375a86;
            const float three_halfs = 1.5f;
            const float number_half = number * 0.5f;


            union {
                float f;
                long l;
            } fl;

            fl.l = 0;
            fl.f = number;

            fl.l = fuconstant - (fl.l >> 1); // what the fuck?

            fl.f = fl.f * (three_halfs - (number_half * fl.f * fl.f)); // 1st iteration
            fl.f = fl.f * (three_halfs - (number_half * fl.f * fl.f)); // 2nd iteration

            return fl.f;
        }

        float square(const float x) {
            return x * x;
        }

        float deg2rad(const float deg) {
            static const float to_rad = PI / 180.0f;
            return deg * to_rad;
        }

        float rad2deg(const float rad) {
            static const float to_deg = 180.0f / PI;
            return rad * to_deg;
        }

        float fast_sin(const float angle_deg) {
            float angle_rad = deg2rad(angle_deg);

            if (PI < angle_rad) {
                angle_rad = angle_rad - int((angle_rad + PI) * INV_PI) * HALF_PI;
            } else if (angle_rad < -PI) {
                angle_rad = angle_rad - int((angle_rad - PI) * INV_PI) * HALF_PI;
            }

            return angle_rad *
                   (1 - angle_rad * angle_rad *
                    (0.16666667f - angle_rad * angle_rad *
                     (0.00833333f - angle_rad * angle_rad * (0.0001984f - angle_rad * angle_rad * 0.0000027f))));
        }

        void fast_sincos(const float angle_deg, float& sin, float& cos) {
            sin = fast_sin(angle_deg);
            cos = fast_sqrt(1 - sin * sin);
        }

        float float_select(const float a, const float ge_zero, const float lt_zero) {
            return a >= 0.0f ? ge_zero : lt_zero;
        }
    }
}
