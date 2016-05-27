#define BOOST_TEST_MODULE test_MongoBuildQueryLogDocument
#include <boost/test/included/unit_test.hpp>

#include "MongoBuildQueryLogDocument.h"

BOOST_AUTO_TEST_CASE(BasicTest)
{
   const auto&& vars = std::map<std::string, std::string> { { "abcdXXX", "abcdxxxVal" }, { "abcdZZZ", "abcdzzzVal" }, { "def", "defVal" }, { "abcdYYY", "abcdyyyVal" } };
   const auto&& TableFields = { "XXX", "YyY", "AAA" };

   auto&& got_document = MongoBuildQueryLogDocument("MyTable", vars, "abcd", TableFields, "myfilt", "cri", "val");

   auto&& exp_document =
      bsoncxx::builder::stream::document{} << "myfilt" << bsoncxx::builder::stream::open_array
      << bsoncxx::builder::stream::open_document << "cri" << "XXX" << "val" << "abcdxxxVal" << bsoncxx::builder::stream::close_document
      << bsoncxx::builder::stream::open_document << "cri" << "YyY" << "val" << "abcdyyyVal" << bsoncxx::builder::stream::close_document
      << bsoncxx::builder::stream::close_array
      << bsoncxx::builder::stream::finalize;

   BOOST_CHECK(got_document.view() == exp_document.view());
}
