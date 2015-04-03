#include "BasicStringBuilder.h"
#include "QStringBuilder.h"

#include "gtest/gtest.h"

#include <string>

template <typename StringType, typename BuilderType>
struct BasicTest
{
  BasicTest ()
  {
    StringType t = BuilderType{ s("It's test %1 we're testing %2 arg function %3. Does it work? %4")}.arg (2).arg (3.5).arg (c('G')).arg (s("Some kind of string"));
    auto q = QString ("It's test %1 we're testing %2 arg function %3. Does it work? %4").arg (2).arg (3.5).arg ('G').arg ("Some kind of string");
    EXPECT_EQ (qs(q), t);

    t = BuilderType{ s("%1 %2 %3 %4") }.setIntegerBase (2).arg (8).setIntegerBase (3).arg (8).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
    q = QString {"%1 %2 %3 %4"}.arg (8, 0, 2).arg (8, 0, 3).arg (8, 0, 4).arg (8, 0, 5);
    EXPECT_EQ (qs(q), t);

    t = BuilderType{ s("%1 %2 %3\n%4 %5 %6") }.setFieldWidth (10).arg (s("Test"), s("Test"), s("Test")).setFieldWidth (-10).arg (s("Test"), s("Test"), s("Test"));
    q = QString {"%1 %2 %3\n%4 %5 %6"}.arg ("Test", 10).arg ("Test", 10).arg ("Test", 10).arg ("Test", -10).arg ("Test", -10).arg ("Test", -10);
    EXPECT_EQ (qs(q), t);


    t = BuilderType{ s("%1 %2 %3 %4 %5 %6") }.setFieldWidth (10).setFillChar (c('_')).setFloatingPointFormat ('g', 5).arg (12.123, 0.00005).
                    setFloatingPointFormat ('f').setPrecision (5).arg (12.123, 0.00005).setFloatingPointFormat ('e', 6).arg (12.123, 0.00005);
    q = QString {"%1 %2 %3 %4 %5 %6"}.arg (12.123, 10, 'g', 5, '_').arg (0.00005, 10, 'g', 5, '_').arg (12.123, 10, 'f', 5, '_')
                                     .arg (0.00005, 10, 'f', 5, '_').arg (12.123, 10, 'e', 6, '_').arg (0.00005, 10, 'e', 6, '_');
    EXPECT_EQ (qs (q), t);

    t = BuilderType { s("%1\n%2\n%3\n%4") }.setFieldWidth (25).setFillChar (c('_')).setIntegerBase (2).arg (12312312u).
                                            setIntegerBase (3).arg (12312312u).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
    q = QString {"%1\n%2\n%3\n%4"}.arg (12312312u, 25, 2, QChar{'_'}).arg (12312312u, 25, 3, QChar{'_'}).arg (8, 25, 4, QChar{'_'})
                                  .arg (8, 25, 5, QChar{'_'});
    EXPECT_EQ (qs (q), t);

    t = BuilderType{ s("%1 %2 %3 %4") }.setIntegerBase (16).arg (10000000).setIntegerBase (36).arg (10000000).setIntegerBase (13)
                                       .arg (10000000).setIntegerBase (35).arg (10000000);
    q = QString{ "%1 %2 %3 %4" }.arg (10000000, 0, 16).arg (10000000, 0, 36).arg (10000000, 0, 13).arg (10000000, 0, 35);
    EXPECT_EQ (qs (q), t);

    t = BuilderType{s("%9 %28 %7 %13 %1") }.arg (1, 2, 3, 4, 5); // funny how this call to arg will actually compile with QString
    q = QString{ "%9 %28 %7 %13 %1" }.arg (1).arg (2).arg (3).arg (4).arg (5);
    EXPECT_EQ (qs (q), t);

  }

  StringType qs (const QString &str)
  {
    return s (str.toLatin1 ().constData ());
  }

  typename StringType::value_type c (char cArg)
  {
    return static_cast<typename StringType::value_type> (cArg);
  }
  
  StringType s (const char *str)
  {
    return s (str, typename std::is_same<StringType, std::wstring>::type {});
  }
  
  std::wstring s (const char *str, std::true_type)
  {
    std::string t {str};
    return std::wstring {t.begin (), t.end ()};
  }
  
  StringType s (const char *str, std::false_type)
  {
    return StringType {str};
  }
};


TEST (WarmupTest, QString)
{
  BasicTest<QString, QStringBuilder> {};
}

TEST (WarmupTest, string)
{
#ifdef _MSC_VER
  _set_output_format (_TWO_DIGIT_EXPONENT); // Microsoft specific, to unify behavior with Qt
#endif // _MSC_VER
  BasicTest<std::string, StdStringBuilder> ();
}

TEST (WarmupTest, wstring)
{
#ifdef _MSC_VER
  _set_output_format (_TWO_DIGIT_EXPONENT); // Microsoft specific, to unify behavior with Qt
#endif // _MSC_VER
  BasicTest<std::wstring, StdWstringBuilder> ();
}

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
