#define BOOST_TEST_MODULE test_ForEachPropertyMatchDo
#include <boost/test/included/unit_test.hpp>

#include "ForEachPropertyMatchDo.h"

BOOST_AUTO_TEST_CASE(BasicTest)
{
   {
      auto&& vars = std::map<std::string, std::string> { { "abcdXXX", "abcdxxxVal" }, { "abcdZZZ", "abcdzzzVal" }, { "def", "defVal" }, { "abcdYYY", "abcdyyyVal" } };

      {
         auto&& filter = { "XXX", "YyY", "AAA" };
         auto&& fill = std::map<std::string, std::string> {};

         ForEachPropertyMatchDo(vars, "aBcd", filter, [&fill](auto && k, auto && v)
         {
            fill.emplace(k, v);
         });

         BOOST_CHECK_EQUAL(fill.size(), 2u);
         BOOST_CHECK_EQUAL(fill.find("XXX")->second, "abcdxxxVal");
         BOOST_CHECK_EQUAL(fill.find("YyY")->second, "abcdyyyVal");
      }
   }
}
