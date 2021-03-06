#pragma once

/*******************************************************************************
**** Includes
*******************************************************************************/

#include "celib/math_types.h"
#include "celib/math/math.inl.h"

namespace cetech {

    /***************************************************************************
    **** Vector4 constatns
    ***************************************************************************/
    namespace vector4 {

        /***********************************************************************
        **** Zero vector
        ***********************************************************************/
        static const Vector4 ZERO = {0.0f, 0.0f, 0.0f, 0.f};


        /***********************************************************************
        **** Unit vector
        ***********************************************************************/
        static const Vector4 UNIT = {1.0f, 1.0f, 1.0f, 1.f};

        /***********************************************************************
        **** Up vector
        ***********************************************************************/
        static const Vector4 UP = {0.0f, 1.0f, 0.0f, 0.f};

        /***********************************************************************
        **** Down vector
        ***********************************************************************/
        static const Vector4 DOWN = {0.0f, -1.0f, 0.0f, 0.f};

        /***********************************************************************
        **** Forward vector
        ***********************************************************************/
        static const Vector4 FORWARDS = {0.0f, 0.0f, 1.0f, 0.f};

        /***********************************************************************
        **** Backward vector
        ***********************************************************************/
        static const Vector4 BACKWARDS = {0.0f, 0.0f, -1.0f, 0.f};

        /***********************************************************************
        **** Right vector
        ***********************************************************************/static const Vector4 RIGHT = {1.0f, 0.0f, 0.0f, 0.f};

        /***********************************************************************
        **** Left vector
        ***********************************************************************/
        static const Vector4 LEFT = {-1.0f, 0.0f, 0.0f, 0.f};
    }

    /***************************************************************************
    **** Vector4 interface
    ***************************************************************************/
    namespace vector4 {

        /***********************************************************************
        **** Make Vector4
        ***********************************************************************/
        CE_INLINE Vector4 make_vector4(const float x,
                                       const float y,
                                       const float z,
                                       const float w);

        /***********************************************************************
        **** Vector len
        ***********************************************************************/
        CE_INLINE float len(const Vector4& v1);

        /***********************************************************************
        **** Vector squared len.
        ***********************************************************************/
        CE_INLINE float len_sq(const Vector4& v1);

        /***********************************************************************
        **** Vector 1/len
        ***********************************************************************/
        CE_INLINE float len_inv(const Vector4& v1);

        /***********************************************************************
        **** Return normalized vector.
        ***********************************************************************/
        CE_INLINE Vector4 normalized(const Vector4& v1);

        /***********************************************************************
        ****  Is vector normalized?
        ***********************************************************************/
        CE_INLINE bool is_normalized(const Vector4& v1);

        /***********************************************************************
        **** Dot product.
        ***********************************************************************/
        CE_INLINE float dot(const Vector4& v1,
                            const Vector4& v2);

        /***********************************************************************
        **** Squared distance between two point.
        ***********************************************************************/
        CE_INLINE float distance_sq(const Vector4& v1,
                                    const Vector4& v2);

        /***********************************************************************
        **** Distance between two point.
        ***********************************************************************/
        CE_INLINE float distance(const Vector4& v1,
                                 const Vector4& v2);

        /***********************************************************************
        **** Get minimal value from vector element.
        ***********************************************************************/
        CE_INLINE float min(const Vector4& v1);

        /***********************************************************************
        **** Get maximum value from vector element.
        ***********************************************************************/
        CE_INLINE float max(const Vector4& v1);

        /***********************************************************************
        **** Get maximum absolute value from vector element.
        ***********************************************************************/
        CE_INLINE float abs_max(const Vector4& v1);

        /***********************************************************************
        **** Get sign vector.
        ***********************************************************************/
        CE_INLINE Vector4 sign_vector(const Vector4& v1);
    }

    /***************************************************************************
    **** Return negativ vector.
    ***************************************************************************/
    CE_INLINE Vector4 operator - (const Vector4 &v1);


    /***************************************************************************
    **** V1 + V2
    ***************************************************************************/
    CE_INLINE Vector4 operator + (const Vector4 &v1, const Vector4 &v2);

    /***************************************************************************
    **** V1 - V2
    ***************************************************************************/
    CE_INLINE Vector4 operator - (const Vector4 &v1, const Vector4 &v2);

    /***************************************************************************
    **** V1 * V2 [x1 * x2, y1 * y2, z1 * z2]
    ***************************************************************************/
    CE_INLINE Vector4 operator* (const Vector4 &v1, const Vector4 &v2);

    /***************************************************************************
    **** V1 / V2 [x1 / x2, y1 / y2, z1 / z2]
    ***************************************************************************/
    CE_INLINE Vector4 operator / (const Vector4 &v1, const Vector4 &v2);

    /***************************************************************************
    **** V1 * scalar
    ***************************************************************************/
    CE_INLINE Vector4 operator* (const Vector4 &v1, const float s);

    /***************************************************************************
    **** V1 / scalar
    ***************************************************************************/
    CE_INLINE Vector4 operator / (const Vector4 &v1, const float s);

    /***************************************************************************
    **** Vector4 implementation
    ***************************************************************************/
    namespace vector4 {
        Vector4 make_vector4(const float x,
                             const float y,
                             const float z,
                             const float w) {
            return {
                       x, y, z, w
            };
        }

        float len(const Vector4& v1) {
            return math::fast_sqrt(len_sq(v1));
        }

        float len_sq(const Vector4& v1) {
            return dot(v1, v1);
        }

        float len_inv(const Vector4& v1) {
            return math::fast_inv_sqrt(len_sq(v1));
        }

        Vector4 normalized(const Vector4& v1) {
            return v1 * len_inv(v1);
        }

        bool is_normalized(const Vector4& v1) {
            return math::abs(1.0f - len_sq(v1)) < 0.001f;
        }

        float dot(const Vector4& v1,
                  const Vector4& v2) {
            return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
        }

        //          Vector4 cross(const Vector4& v1, const Vector4& v2) {
        //        (void)v1;
        //        (void)v2;
        //        // TODO: !!!
        //        //             return make_vector4(
        // //                 (v1.y * v2.z) - (v1.z * v2.y),
        // //                 (v1.z * v2.x) - (v1.x * v2.z),
        // //                 (v1.x * v2.y) - (v1.y * v2.x),
        // //                 );
        //         }

        float distance_sq(const Vector4& v1,
                          const Vector4& v2) {
            return math::square(v2.x - v1.x) + math::square(v2.y - v1.y) + math::square(v2.z - v1.z) + math::square(
                v2.w - v1.w);
        }

        float distance(const Vector4& v1,
                       const Vector4& v2) {
            return math::fast_sqrt(distance_sq(v1, v2));
        }

        float min(const Vector4& v1) {
            return math::min(math::min(math::min(v1.x, v1.y), v1.z), v1.w);
        }

        float max(const Vector4& v1) {
            return math::max(math::max(math::max(v1.x, v1.y), v1.z), v1.w);
        }

        float abs_max(const Vector4& v1) {
            return math::max(math::max(math::max(math::abs(v1.x), math::abs(v1.y)), math::abs(v1.z)), math::abs(v1.w));
        }

        Vector4 sign_vector(const Vector4& v1) {
            return make_vector4(
                math::float_select(v1.x, 1.0f, -1.0f),
                math::float_select(v1.y, 1.0f, -1.0f),
                math::float_select(v1.z, 1.0f, -1.0f),
                math::float_select(v1.w, 1.0f, -1.0f)
                );
        }
    }

    Vector4 operator - (const Vector4 &v1) {
        return vector4::make_vector4(
            -v1.x,
            -v1.y,
            -v1.z,
            -v1.w
            );
    }

    Vector4 operator + (const Vector4 &v1, const Vector4 &v2) {
        return vector4::make_vector4(
            v1.x + v2.x,
            v1.y + v2.y,
            v1.z + v2.z,
            v1.w + v2.w
            );
    }

    Vector4 operator - (const Vector4 &v1, const Vector4 &v2) {
        return vector4::make_vector4(
            v1.x - v2.x,
            v1.y - v2.y,
            v1.z - v2.z,
            v1.w - v2.w
            );
    }

    Vector4 operator* (const Vector4 &v1, const Vector4 &v2) {
        return vector4::make_vector4(
            v1.x * v2.x,
            v1.y * v2.y,
            v1.z * v2.z,
            v1.w * v2.w
            );
    }

    Vector4 operator / (const Vector4 &v1, const Vector4 &v2) {
        return vector4::make_vector4(
            v1.x / v2.x,
            v1.y / v2.y,
            v1.z / v2.z,
            v1.w / v2.w
            );
    }

    Vector4 operator* (const Vector4 &v1, const float s) {
        return vector4::make_vector4(
            v1.x * s,
            v1.y * s,
            v1.z * s,
            v1.w * s
            );
    }

    Vector4 operator / (const Vector4 &v1, const float s) {
        const float inv_s = 1 / s;

        return vector4::make_vector4(
            v1.x * inv_s,
            v1.y * inv_s,
            v1.z * inv_s,
            v1.w * inv_s
            );
    }
}
