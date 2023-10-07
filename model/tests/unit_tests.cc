#include <gtest/gtest.h>

#include "../model.cc"
using namespace s21;
using namespace std;

TEST(Calc, Test1) {
  Model m;
  double res = 0;
  double orig = 5 + 4;
  bool success = m.Reckoner("5 + 4", 0, &res);
  EXPECT_EQ(res, orig);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test2) {
  Model m;
  double res = 0;
  double orig = INFINITY;
  bool success = m.Reckoner("4^acos(x/4)/tan(2*x)", 0, &res);
  EXPECT_EQ(res, orig);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test3) {
  Model m;
  double res = 0;
  double orig = 4 + 4;
  bool success = m.Reckoner("x+x", 4, &res);
  EXPECT_EQ(res, orig);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test4) {
  Model m;
  double res = 0;
  double orig = 123 + 0.456;
  bool success = m.Reckoner("123+0.456", 0, &res);
  EXPECT_EQ(res, orig);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test5) {
  Model m;
  double res = 0;
  double orig = -(-1);
  bool success = m.Reckoner("-(-1)", 0, &res);
  EXPECT_EQ(res, orig);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test6) {
  Model m;
  double res = 0;
  double x = 2.0;
  double orig = pow(4, acos(x / 4)) / tan(2 * x);
  bool success = m.Reckoner("4^acos(x/4)/tan(2*x)", x, &res);
  EXPECT_EQ(success, true);
  EXPECT_EQ(res, orig);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test6_2) {
  Model m;
  double res = 0;
  double x = 2.0;
  double orig = (pow(4, acos(x / 4)) / tan(2 * x));
  bool success = m.Reckoner("(4^acos(x/4))/tan(2*x)", x, &res);
  EXPECT_EQ(success, true);
  EXPECT_EQ(res, orig);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test6_3) {
  Model m;
  double res = 0;
  double x = 2.0;
  double orig = -0.58934793341;
  bool success = m.Reckoner(
      "(4 ^acos( 2/4 )/tan( 2*2 )/( 5 ^acos( 2/4 ))/tan(tan(tan( 2*2))))", x,
      &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test7) {
  Model m;
  double res = 0;
  double orig = 4;
  bool success = m.Reckoner("(((((((2+2)))))))", 0, &res);
  EXPECT_EQ(res, orig);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test8) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("(2+2)))))))", 0, &res);
  EXPECT_EQ(success, false);
}
TEST(Calc, Test9) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("(((((((2+2))", 0, &res);
  EXPECT_EQ(success, false);
}
TEST(Calc, Test10) {
  Model m;
  double res = 0;
  double orig = -2;
  bool success = m.Reckoner("1+-3", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_EQ(res, orig);
}
TEST(Calc, Test11) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("1+/3", 0, &res);
  EXPECT_EQ(success, false);
}
TEST(Calc, Test12) {
  Model m;
  double res = 0;
  double orig = 1.15782128235;
  bool success = m.Reckoner("tan(2*2)", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test13) {
  Model m;
  double res = 0;
  double orig = 6.268113;
  bool success = m.Reckoner("1+2*3^sin(0.4)^3*2+1", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test14) {
  Model m;
  double res = 0;
  double orig = 1.041782;
  bool success = m.Reckoner("2^sin(0.4)^3", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test15) {
  Model m;
  double res = 0;
  double orig = 4.5;
  bool success = m.Reckoner("81/3^2/2", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test16) {
  Model m;
  double res = 0;
  double orig = 8.9799773536;
  bool success = m.Reckoner(
      "-(1+3*(5%3+100))/50/1*20+-(50^2*(5+3^2)%(3*2)+31*20/"
      "(10*-5^(2+1)))+39^2*48*10*123-50-10",
      0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test17) {
  Model m;
  double res = 0;
  double orig = 1.59353;
  bool success = m.Reckoner(
      "acos(-0.5)+asin(-0.5)+atan(0.1)*cos(30)*sin(20)*tan(45)", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test18) {
  Model m;
  double res = 0;
  double orig = 7.196192602521;
  bool success =
      m.Reckoner("(ln(50)+100)%(2+2.5)+(log(100)*20)^(2+2)+sqrt(25)", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test19) {
  Model m;
  double res = 0;
  double orig = 1.0603073792140916;
  bool success = m.Reckoner("-(cos(20)+-10)%2", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test20) {
  Model m;
  double res = 0;
  double orig = 0.707106781186547524;
  bool success = m.Reckoner("sin(45)", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test21) {
  Model m;
  double res = 0;
  double orig = 1;
  bool success = m.Reckoner("-4+5", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test22) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("-----2", 0, &res);
  EXPECT_EQ(success, false);
}

TEST(Calc, Test23) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("2*/3", 0, &res);
  EXPECT_EQ(success, false);
}

TEST(Calc, Test24) {
  Model m;
  double res = 0;
  double orig = -5;
  bool success = m.Reckoner("-2+-3", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_TRUE((fabs(orig) - fabs(res)) < 0.0000001);
}
TEST(Calc, Test25) {
  Model m;
  double res = 0;
  double orig = 0.0016;
  bool success = m.Reckoner("(-5)^(-4)", 0, &res);
  EXPECT_EQ(success, true);
  EXPECT_EQ(res, orig);
}
TEST(Calc, Test26) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("*5", 0, &res);
  EXPECT_EQ(success, false);
}
TEST(Calc, Test27) {
  Model m;
  double res = 0;
  bool success = m.Reckoner(
      "+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1",
      0, &res);
  EXPECT_EQ(success, true);
  EXPECT_EQ(res, 130);
}
TEST(Calc, Test28) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("9+sin()+1", 0, &res);
  EXPECT_EQ(success, false);
}
TEST(Calc, Test29) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("2+7.555", 0, &res);
  EXPECT_EQ(success, true);
}
TEST(Calc, Test30) {
  Model m;
  double res = 0;
  bool success = m.Reckoner("2+7.55.5", 0, &res);
  EXPECT_EQ(success, false);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
