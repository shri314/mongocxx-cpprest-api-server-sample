#define BOOST_TEST_MODULE test_MongoBuildQueryFilter
#include <boost/test/included/unit_test.hpp>

#include "MongoBuildQueryFilter.h"

BOOST_AUTO_TEST_CASE(BasicTest)
{
   const auto&& vars = std::map<std::string, std::string> { { "abcdXXX", "abcdxxxVal" }, { "abcdZZZ", "abcdzzzVal" }, { "def", "defVal" }, { "abcdYYY", "abcdyyyVal" } };
   const auto&& TableFields = { "XXX", "YyY", "AAA" };

   auto&& got_filter = MongoBuildQueryFilter("MyTable", vars, "abcd", TableFields);

   auto&& exp_filter = bsoncxx::builder::stream::document{} << "MyTable_XXX" << "abcdxxxVal" << "MyTable_YyY" << "abcdyyyVal" << bsoncxx::builder::stream::finalize;

   BOOST_CHECK(got_filter.view() == exp_filter.view());
}
