#pragma once

/*******************************************************************************
**** Includes
*******************************************************************************/

#include "celib/asserts.h"
#include "celib/math_types.h"
#include "celib/math/math.inl.h"
#include "celib/math/vector3.inl.h"
#include "celib/math/simd/simd.h"

namespace cetech {

    /***************************************************************************
    **** Quaternion constatns
    ***************************************************************************/
    namespace quat {

        /***********************************************************************
        **** Zero quaternion
        ***********************************************************************/
        static const Quat ZERO = {0.0f, 0.0f, 0.0f, 0.0f};

        /***********************************************************************
        **** Identity quaternion
        ***********************************************************************/
        static const Quat IDENTITY = {0.0f, 0.0f, 0.0f, 1.0f};

        /***********************************************************************
        **** quaternion (1.0, 0.0, 0.0, 0.0)
        ***********************************************************************/
        static const Quat I = {1.0f, 0.0f, 0.0f, 0.0f};

        /***********************************************************************
        **** quaternion (0.0, 1.0, 0.0, 0.0)
        ***********************************************************************/
        static const Quat J = {0.0f, 1.0f, 0.0f, 0.0f};

        /***********************************************************************
        **** quaternion (0.0, 0.0, 1.0, 0.0)
        ***********************************************************************/
        static const Quat K = {0.0f, 0.0f, 1.0f, 0.0f};
    }

    /***************************************************************************
    **** Quaternion interface
    ***************************************************************************/
    namespace quat {

        /***********************************************************************
        **** Create quaternion
        ***********************************************************************/
        CE_INLINE Quat make_quat(const float x,
                                 const float y,
                                 const float z,
                                 const float w);

        /***********************************************************************
        **** Create quaternion from axis angle
        ***********************************************************************/
        CE_INLINE Quat from_axis_angle(const Vector3& axis,
                                       const float angle_deg);

        /***********************************************************************
        **** Return quaternion len
        ***********************************************************************/
        CE_INLINE float len(const Quat& q1);

        /***********************************************************************
        **** Return squared quaternion len
        ***********************************************************************/
        CE_INLINE float len_sq(const Quat& q1);

        /***********************************************************************
        **** Return quaternion 1/len
        ***********************************************************************/
        CE_INLINE float len_inv(const Quat& q1);

        /***********************************************************************
        **** Return normalized vector.
        ***********************************************************************/
        CE_INLINE Quat normalized(const Quat& q1);

        /***********************************************************************
        **** Is quaternion normalized?
        ***********************************************************************/
        CE_INLINE bool is_normalized(const Quat& q1);
    }

    /***************************************************************************
    **** Return negativ vector.
    ***************************************************************************/
    CE_INLINE Quat operator - (const Quat &q1);

    /***************************************************************************
    **** V1 + V2
    ***************************************************************************/
    CE_INLINE Quat operator + (const Quat &q1, const Quat &q2);

    /***************************************************************************
    **** V1 - V2
    ***************************************************************************/
    CE_INLINE Quat operator - (const Quat &q1, const Quat &q2);

    /***************************************************************************
    **** Q1 * Q2
    ***************************************************************************/
    CE_INLINE Quat operator* (const Quat &q1, const Quat &q2);

    /***************************************************************************
    **** Q1 * V1
    ***************************************************************************/
    CE_INLINE Vector3 operator* (const Quat &q1, const Vector3 &v1);

    /***************************************************************************
    **** V1 * scalar
    ***************************************************************************/
    CE_INLINE Quat operator* (const Quat &q1, const float s);

    /***************************************************************************
    **** V1 / scalar
    ***************************************************************************/
    CE_INLINE Quat operator / (const Quat &q1, const float s);

    /***************************************************************************
    **** Quaternion implementation
    ***************************************************************************/
    namespace quat {
        CE_INLINE Quat make_quat(const float x,
                                 const float y,
                                 const float z,
                                 const float w) {
            return {
                       x, y, z, w
            };
        }

        CE_INLINE Quat from_axis_angle(const Vector3& axis,
                                       const float angle_deg) {
            const float angle_deg_half = angle_deg * 0.5;
            float sin, cos;

            math::fast_sincos(angle_deg_half, sin, cos);

            Quat res = make_quat(
                sin * axis.x,
                sin * axis.y,
                sin * axis.z,
                cos
                );

            return res;
        }

        CE_INLINE float len(const Quat& q1) {
            return math::fast_sqrt(len_sq(q1));
        }

        CE_INLINE float len_sq(const Quat& q1) {
            return (q1.x * q1.x) + (q1.y * q1.y) + (q1.z * q1.z) + (q1.w * q1.w);
        }

        CE_INLINE float len_inv(const Quat& q1) {
            return math::fast_inv_sqrt(len_sq(q1));
        }

        CE_INLINE Quat normalized(const Quat& q1) {
            return q1 * len_inv(q1);
        }

        CE_INLINE bool is_normalized(const Quat& v1) {
            return math::abs(1.0f - len_sq(v1)) < 0.001f;
        }

    }

    CE_INLINE Quat operator - (const Quat &q1) {
        CE_ASSERT(quat::is_normalized(q1));

        return quat::make_quat(
            -q1.x,
            -q1.y,
            -q1.z,
            q1.w
            );
    }

    CE_INLINE Quat operator + (const Quat &q1, const Quat &q2) {
        return quat::make_quat(
            q1.x + q2.x,
            q1.y + q2.y,
            q1.z + q2.z,
            q1.w + q2.w
            );
    }

    CE_INLINE Quat operator - (const Quat &q1, const Quat &q2) {
        return quat::make_quat(
            q1.x - q2.x,
            q1.y - q2.y,
            q1.z - q2.z,
            q1.w - q2.w
            );
    }

    CE_INLINE Quat operator* (const Quat &q1, const Quat &q2) {
        Quat res;
        simd::quat_mult(&q1, &q2, &res);
        return res;
    }

    CE_INLINE Quat operator* (const Quat &q1, const float s) {
        return quat::make_quat(
            q1.x * s,
            q1.y * s,
            q1.z * s,
            q1.w * s
            );
    }

    CE_INLINE Vector3 operator* (const Quat &q1, const Vector3 &v1) {
        const Vector3 qv = vector3::make_vector3(q1.x, q1.y, q1.z);

        Vector3 res = vector3::cross(qv, v1) * (2.0f * q1.w);
        res = res + (v1 * (math::square(q1.w) - vector3::dot(qv, qv)));
        res = res + qv * (2.0f * vector3::dot(qv, v1));

        return res;
    }

    CE_INLINE Quat operator / (const Quat &q1, const float s) {
        const float inv_s = 1 / s;

        return quat::make_quat(
            q1.x * inv_s,
            q1.y * inv_s,
            q1.z * inv_s,
            q1.w * inv_s
            );
    }
}
