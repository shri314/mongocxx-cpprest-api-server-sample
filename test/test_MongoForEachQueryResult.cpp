#define BOOST_TEST_MODULE test_MongoForEachQueryResult
#include <boost/test/included/unit_test.hpp>

#include "MongoBuildQueryFilter.h"
#include "MongoForEachQueryResult.h"

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>

#include <boost/lexical_cast.hpp>

BOOST_AUTO_TEST_CASE(BasicTest)
{
   auto&& inst = mongocxx::instance{};
   auto&& conn = mongocxx::client{mongocxx::uri{}};

   auto&& db = conn["MyTestDB"];

   if(db.has_collection("MyTable"))
      db["MyTable"].drop();

   auto&& collection = db["MyTable"];

   {
      {
         const auto&& vars = std::map<std::string, std::string> { };
         const auto&& TableFields = std::vector<std::string> { };

         auto&& query_filter = MongoBuildQueryFilter("MyTable", vars, "abcd", TableFields);

         int Count = MongoForEachQueryResult(collection, query_filter.view(), [](int c, auto && item)
         {
            BOOST_CHECK(false);
         });

         BOOST_CHECK_EQUAL(Count, 0);
      }
   }

   {
      for(int i = 0; i < 6; ++i)
      {
         collection.insert_one(
            bsoncxx::builder::stream::document{}
            << "MyTable_XXX" << ("xxxsomeval" + boost::lexical_cast<std::string>(i))
            << "MyTable_YyY" << ("yyysomeval" + boost::lexical_cast<std::string>(i / 2))
            << bsoncxx::builder::stream::finalize
         );
      }

      {
         const auto&& vars = std::map<std::string, std::string> { { "abcdXXX", "abcdxxxVal" }, { "abcdZZZ", "abcdzzzVal" }, { "def", "defVal" }, { "abcdYYY", "abcdyyyVal" } };
         const auto&& TableFields = { "XXX", "YyY" };

         auto&& query_filter = MongoBuildQueryFilter("MyTable", vars, "junk", TableFields);

         int Count = MongoForEachQueryResult(collection, query_filter.view(), [](int c, auto && item)
         {
            BOOST_CHECK_EQUAL(std::string(bsoncxx::stdx::string_view(item["MyTable_XXX"].get_utf8())), "xxxsomeval" + boost::lexical_cast<std::string>(c));
            BOOST_CHECK_EQUAL(std::string(bsoncxx::stdx::string_view(item["MyTable_YyY"].get_utf8())), "yyysomeval" + boost::lexical_cast<std::string>(c / 2));
         });

         BOOST_CHECK_EQUAL(Count, 6);
      }

      {
         const auto&& vars = std::map<std::string, std::string> { { "abcdYYy", "yyysomeval1" } };
         const auto&& TableFields = { "XXX", "YyY" };

         auto&& query_filter = MongoBuildQueryFilter("MyTable", vars, "abcd", TableFields);

         int Count = MongoForEachQueryResult(collection, query_filter.view(), [](int c, auto && item)
         {
            BOOST_CHECK( 0 <= c && c < 2 );
            BOOST_CHECK_EQUAL(std::string(bsoncxx::stdx::string_view(item["MyTable_XXX"].get_utf8())), "xxxsomeval" + boost::lexical_cast<std::string>(2 + c));
            BOOST_CHECK_EQUAL(std::string(bsoncxx::stdx::string_view(item["MyTable_YyY"].get_utf8())), "yyysomeval1");
         });

         BOOST_CHECK_EQUAL(Count, 2);
      }
   }
}
