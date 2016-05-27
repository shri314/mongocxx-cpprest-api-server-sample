#define BOOST_TEST_MODULE test_Bson2Json
#include <boost/test/included/unit_test.hpp>

#include "Bson2Json.h"
#include <bsoncxx/builder/stream/document.hpp>

BOOST_AUTO_TEST_CASE(BasicTest)
{
   {
      bsoncxx::builder::stream::document doc{};
      doc << "abcd" << "def";

      auto&& r = Bson2Json( doc.view()["abcd"] );

      BOOST_CHECK_EQUAL( r.is_string(), true );
      BOOST_CHECK_EQUAL( r.as_string(), "def" );
   }

   {
      bsoncxx::builder::stream::document doc{};
      doc << "abcd" << 100;

      auto&& r = Bson2Json( doc.view()["abcd"] );

      BOOST_CHECK_EQUAL( r.is_integer(), true );
      BOOST_CHECK_EQUAL( r.as_integer(), 100 );
   }
}
