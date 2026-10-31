module;
#include <gtest/gtest.h>
export module geotest:math_predicates;
import gengine.types;
import gengine.math;
import gengine.compare;

TEST(Predicates, IsDegeneratedSeg)
{
    geng::Segment deg_seg({6.8, 6.8}, {6.8, 6.8});
    EXPECT_TRUE(geng::math::is_degenerated(deg_seg));
}
