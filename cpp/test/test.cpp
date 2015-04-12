#include <limits.h>
#include <gtest/gtest.h>


#include "types/mathTypes.hpp"
#include "types/plane.hpp"
#include "types/shape.hpp"

TEST(Vector3d, Vector3dTest) {
    Vector3d zero = Vector3d();
    Vector3d one = Vector3d(3.14, 3.14, 3.14);
    ASSERT_DOUBLE_EQ(0, zero.x);
    ASSERT_DOUBLE_EQ(0, zero.y);
    ASSERT_DOUBLE_EQ(0, zero.z);
    ASSERT_DOUBLE_EQ(3.14, one.x);
    ASSERT_DOUBLE_EQ(3.14, one.y);
    ASSERT_DOUBLE_EQ(3.14, one.z);
    Vector3d length = Vector3d(3, 2, -1);
    ASSERT_DOUBLE_EQ(3.7416573867739413, length.length());
    Vector3d normal = Vector3d(6, 6, 6);
    normal = normal.normalize();
    ASSERT_DOUBLE_EQ(normal.length(), 1);
    normal = Vector3d(1, 0, 0);
    normal = normal.normalize();
    ASSERT_DOUBLE_EQ(normal.length(), 1);

}

TEST(Plane, PlaneTest) {

    Vector3d verts[] = {
        Vector3d(1, 1, 0),
        Vector3d(0, 1, 0),
        Vector3d(0, 0, 0),
    };

    Vector3d point(0, 0, 0), point2(10, 10, 10), point3(0.2, 0.2, 0);

    ASSERT_EQ(pointInPolygon(point, verts, 3), true);
    ASSERT_EQ(pointInPolygon(point2, verts, 3), false);

    Plane plane(verts[0], verts[1], verts[2]);
    ASSERT_DOUBLE_EQ(plane.DistanceToPlane(point), 0);
    //ASSERT_DOUBLE_EQ(plane.DistanceToPlane(point2),10);
    e_loc dist = plane.DistanceToPlane(point2);
    cout << dist << endl;
    Vector3d inters = plane.RayIntersection(point2, point3)-point2;
    inters.write();
    ASSERT_EQ(pointInPolygon(inters, verts, 3), true);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
