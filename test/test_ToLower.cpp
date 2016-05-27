#define BOOST_TEST_MODULE test_ToLower
#include <boost/test/included/unit_test.hpp>

#include "ToLower.h"
#include <string>

BOOST_AUTO_TEST_CASE(BasicTest)
{
   {
      std::string s = "aBcd";
      BOOST_CHECK_EQUAL(ToLower(s), "abcd");
   }

   {
      auto&& vars = std::map<std::string, std::string> { { "aBcd", "aBcdVal" }, { "deF", "deFVal" } };

      auto&& lower_vars = ToLower(vars);

      BOOST_CHECK_EQUAL(vars.size(), lower_vars.size());
      BOOST_CHECK_EQUAL(vars.find("deF")->second, lower_vars.find("def")->second);
      BOOST_CHECK_EQUAL(vars.find("aBcd")->second, lower_vars.find("abcd")->second);
   }
}

