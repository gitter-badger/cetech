#ifdef CETECH_TEST

#include "catch/catch.hpp"

#include "celib/memory/memory.h"
#include "celib/math/matrix33.inl.h"

#include "celib/test_utils.h"

TEST_CASE( "Matrix33 operation", "[matrix33]" ) {
    cetech::Matrix33 m1 = cetech::matrix33::IDENTITY;

    SECTION( "m1 * v" ) {
        cetech::Vector3 res = m1 * cetech::vector3::UP;

        REQUIRE_ALMOST( res.x, cetech::vector3::UP.x);
        REQUIRE_ALMOST( res.y, cetech::vector3::UP.y);
        REQUIRE_ALMOST( res.z, cetech::vector3::UP.z);
    }

    SECTION( "from_axis_angle()" ) {
        cetech::Matrix33 m = cetech::matrix33::from_axis_angle(cetech::vector3::FORWARDS, 90.0f);
        cetech::Vector3 res = m * cetech::vector3::UP;

        REQUIRE_ALMOST( res.x, cetech::vector3::LEFT.x);
        REQUIRE_ALMOST( res.y, cetech::vector3::LEFT.y);
        REQUIRE_ALMOST( res.z, cetech::vector3::LEFT.z);
    }

}
#endif
