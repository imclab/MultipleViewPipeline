#include <gtest/gtest.h>
#include <test/Helpers.h>
#include <mvp/ConvexPolygon.h>

using namespace std;
using namespace mvp;
using namespace vw;
using namespace vw::test;

TEST(ConvexPolygon, contains) {
  vector<Vector2> pt_list(4);

  pt_list[0] = Vector2(30, 40);
  pt_list[1] = Vector2(30, 80);
  pt_list[2] = Vector2(50, 80);
  pt_list[3] = Vector2(50, 40);

  ConvexPolygon poly(pt_list);

  EXPECT_TRUE(poly.contains(Vector2(40, 50)));
  EXPECT_FALSE(poly.contains(Vector2(20, 20)));
}

TEST(PolygonMath, intersect) {
  vector<Vector2> pt_list(4);

  pt_list[0] = Vector2(30, 40);
  pt_list[1] = Vector2(30, 80);
  pt_list[2] = Vector2(50, 80);
  pt_list[3] = Vector2(50, 40);
  ConvexPolygon poly1(pt_list);

  pt_list[0] = Vector2(40, 30);
  pt_list[1] = Vector2(40, 70);
  pt_list[2] = Vector2(60, 70);
  pt_list[3] = Vector2(60, 30);
  ConvexPolygon poly2(pt_list);

  pt_list[0] = Vector2(45, 50);
  pt_list[1] = Vector2(45, 60);
  pt_list[2] = Vector2(47, 60);
  pt_list[3] = Vector2(47, 50);
  ConvexPolygon poly3(pt_list);

  pt_list[0] = Vector2(48, 20);
  pt_list[1] = Vector2(48, 60);
  pt_list[2] = Vector2(70, 60);
  pt_list[3] = Vector2(70, 20);
  ConvexPolygon poly4(pt_list);

  EXPECT_TRUE(poly1.intersects(poly2));
  EXPECT_TRUE(poly1.intersects(poly3));
  EXPECT_TRUE(poly2.intersects(poly3));
  EXPECT_TRUE(poly1.intersects(poly4));
  EXPECT_TRUE(poly2.intersects(poly4));
  EXPECT_FALSE(poly3.intersects(poly4));
}

TEST(PolygonMath, circulation_direction) {
  EXPECT_GT(circulation_direction(Vector2(2, 2), Vector2(3, 3), Vector2(1, 5)), 0);
  EXPECT_LT(circulation_direction(Vector2(1, 5), Vector2(3, 3), Vector2(2, 2)), 0);
  EXPECT_EQ(circulation_direction(Vector2(2, 2), Vector2(3, 3), Vector2(4, 4)), 0);
}