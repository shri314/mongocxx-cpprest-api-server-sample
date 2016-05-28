#define BOOST_TEST_MODULE test_vehicle-rest-server
#include <boost/test/included/unit_test.hpp>

#include "server.h"

#include <cpprest/http_client.h>

#include <future>

template<class Cmd1, class Cmd2>
void ForkAndRun(const Cmd1& parent, const Cmd2& child)
{
   int fdp1[2] = {};
   int x = pipe(fdp1);

   BOOST_REQUIRE(x != -1);

   int fdp2[2] = {};
   int y = pipe(fdp2);

   BOOST_REQUIRE(y != -1);

   int pid = fork();

   BOOST_REQUIRE(pid != -1);

   if(pid == -1)
   {
      close(fdp1[0]);
      close(fdp2[0]);

      close(fdp1[1]);
      close(fdp2[1]);
   }
   if(pid == 0)
   {
      close(0);
      close(1);

      close(fdp1[1]);
      close(fdp2[0]);

      dup2(fdp1[0], 0);
      dup2(fdp2[1], 1);

      try
      {
         int r = child();

         _exit(r);
      }
      catch(...)
      {
         _exit(1);
      }
   }
   else
   {
      try
      {
         close(fdp1[0]);
         close(fdp2[1]);

         fcntl(fdp1[1], F_SETFL, O_NONBLOCK);
         fcntl(fdp2[0], F_SETFL, O_NONBLOCK);

         int r = parent(fdp2[0], fdp1[1]);

         int status;
         wait(&status);

         BOOST_CHECK_EQUAL(r, 0);
         BOOST_CHECK_EQUAL(status, 0);

         close(fdp1[1]);
         close(fdp2[0]);
      }
      catch(...)
      {
         int status;
         wait(&status);
         BOOST_CHECK_EQUAL(status, 0);

         close(fdp1[1]);
         close(fdp2[0]);
      }
   }
}

BOOST_AUTO_TEST_CASE(End2EndTest)
{
   {
      auto&& inst = mongocxx::instance{};
      auto&& conn = mongocxx::client{mongocxx::uri{}};

      auto&& db = conn["MyTestDB"];

      if(db.has_collection("Vehicle"))
         db["Vehicle"].drop();
      if(db.has_collection("VehicleQueries"))
         db["VehicleQueries"].drop();

      auto&& collection = db["Vehicle"];

      for(int i = 0; i < 16; ++i)
      {
         collection.insert_one(
            bsoncxx::builder::stream::document{}
            << "_id" << i
            << "Vehicle_Registration" << ("REG_" + boost::lexical_cast<std::string>(i / 1))
            << "Vehicle_Model"        << ("MOD_" + boost::lexical_cast<std::string>(i / 2))
            << "Vehicle_Make"         << ("MAK_" + boost::lexical_cast<std::string>(i / 4))
            << "Vehicle_Owner"        << ("OWN_" + boost::lexical_cast<std::string>(i / 8))
            << bsoncxx::builder::stream::finalize
         );
      }
   }

   ForkAndRun([&](int from_child, int to_child)
   {
      // parent will do the control - and test the server responses
      sleep(2);

      auto&& f = std::async([from_child, to_child]()
      {
         while(1)
         {
            sleep(1);
            char buff[4096];
            int r = read(from_child, buff, sizeof buff / sizeof * buff);

            if(r == 0)
               break;

            // std::cout << buff << std::flush;
         }
      });

      {
         http_client client(U("http://127.0.0.1:9090"));
         uri_builder builder(U("/vehicle"));

         auto&& task = client
                       .request(methods::GET, builder.to_string())
                       .then([ = ](http_response response)
         {
            BOOST_CHECK_EQUAL(response.status_code(), 200);

            return response.extract_json()
                   .then([](web::json::value v)
            {
               BOOST_CHECK(v.is_array());
               BOOST_CHECK_EQUAL(v.size(), 16);

               int TestCount = 0;
               if(v.is_array() && v.size() >= 16)
               {
                  for(int i = 0; i < 16; ++i)
                  {
                     ++TestCount;
                     BOOST_CHECK_EQUAL(v[i]["Registration"].as_string(), "REG_" + boost::lexical_cast<std::string>(i / 1));
                     BOOST_CHECK_EQUAL(v[i]["Model"].as_string(),        "MOD_" + boost::lexical_cast<std::string>(i / 2));
                     BOOST_CHECK_EQUAL(v[i]["Make"].as_string(),         "MAK_" + boost::lexical_cast<std::string>(i / 4));
                     BOOST_CHECK_EQUAL(v[i]["Owner"].as_string(),        "OWN_" + boost::lexical_cast<std::string>(i / 8));
                  }
               }

               return TestCount;
            });
         });

         BOOST_CHECK_EQUAL(task.get(), 16);
      }

      {
         http_client client(U("http://127.0.0.1:9090"));
         uri_builder builder(U("/vehicle"));
         builder.append_query(U("filterByOwner"), U("OWN_1"));

         auto&& task = client
                       .request(methods::GET, builder.to_string())
                       .then([ = ](http_response response)
         {
            BOOST_CHECK_EQUAL(response.status_code(), 200);

            return response.extract_json()
                   .then([](web::json::value v)
            {
               BOOST_CHECK(v.is_array());
               BOOST_CHECK_EQUAL(v.size(), 8);

               int TestCount = 0;
               if(v.is_array() && v.size() >= 8)
               {
                  for(int i = 8; i < 16; ++i)
                  {
                     ++TestCount;
                     BOOST_CHECK_EQUAL(v[i - 8]["Registration"].as_string(), "REG_" + boost::lexical_cast<std::string>(i / 1));
                     BOOST_CHECK_EQUAL(v[i - 8]["Model"].as_string(),        "MOD_" + boost::lexical_cast<std::string>(i / 2));
                     BOOST_CHECK_EQUAL(v[i - 8]["Make"].as_string(),         "MAK_" + boost::lexical_cast<std::string>(i / 4));
                     BOOST_CHECK_EQUAL(v[i - 8]["Owner"].as_string(),        "OWN_" + boost::lexical_cast<std::string>(i / 8));
                  }
               }

               return TestCount;
            });
         });

         BOOST_CHECK_EQUAL(task.get(), 8);
      }

      {
         http_client client(U("http://127.0.0.1:9090"));
         uri_builder builder(U("/vehicle"));
         builder.append_query(U("filterByOwner"), U("OWN_1"));
         builder.append_query(U("filterByMake"), U("MAK_3"));

         auto&& task = client
                       .request(methods::GET, builder.to_string())
                       .then([ = ](http_response response)
         {
            BOOST_CHECK_EQUAL(response.status_code(), 200);

            return response.extract_json()
                   .then([](web::json::value v)
            {
               BOOST_CHECK(v.is_array());
               BOOST_CHECK_EQUAL(v.size(), 4);

               int TestCount = 0;
               if(v.is_array() && v.size() >= 4)
               {
                  for(int i = 12; i < 16; ++i)
                  {
                     ++TestCount;
                     BOOST_CHECK_EQUAL(v[i - 12]["Registration"].as_string(), "REG_" + boost::lexical_cast<std::string>(i / 1));
                     BOOST_CHECK_EQUAL(v[i - 12]["Model"].as_string(),        "MOD_" + boost::lexical_cast<std::string>(i / 2));
                     BOOST_CHECK_EQUAL(v[i - 12]["Make"].as_string(),         "MAK_" + boost::lexical_cast<std::string>(i / 4));
                     BOOST_CHECK_EQUAL(v[i - 12]["Owner"].as_string(),        "OWN_" + boost::lexical_cast<std::string>(i / 8));
                  }
               }

               return TestCount;
            });
         });

         BOOST_CHECK_EQUAL(task.get(), 4);
      }

      {
         http_client client(U("http://127.0.0.1:9090"));
         uri_builder builder(U("/vehicle"));
         builder.append_query(U("filterByOwner"), U("OWN_1"));
         builder.append_query(U("filterByMake"), U("MAK_3"));
         builder.append_query(U("filterByModel"), U("MOD_7"));

         auto&& task = client
                       .request(methods::GET, builder.to_string())
                       .then([ = ](http_response response)
         {
            BOOST_CHECK_EQUAL(response.status_code(), 200);

            return response.extract_json()
                   .then([](web::json::value v)
            {
               BOOST_CHECK(v.is_array());
               BOOST_CHECK_EQUAL(v.size(), 2);

               int TestCount = 0;
               if(v.is_array() && v.size() >= 2)
               {
                  for(int i = 14; i < 16; ++i)
                  {
                     ++TestCount;
                     BOOST_CHECK_EQUAL(v[i - 14]["Registration"].as_string(), "REG_" + boost::lexical_cast<std::string>(i / 1));
                     BOOST_CHECK_EQUAL(v[i - 14]["Model"].as_string(),        "MOD_" + boost::lexical_cast<std::string>(i / 2));
                     BOOST_CHECK_EQUAL(v[i - 14]["Make"].as_string(),         "MAK_" + boost::lexical_cast<std::string>(i / 4));
                     BOOST_CHECK_EQUAL(v[i - 14]["Owner"].as_string(),        "OWN_" + boost::lexical_cast<std::string>(i / 8));
                  }
               }

               return TestCount;
            });
         });

         BOOST_CHECK_EQUAL(task.get(), 2);
      }

      {
         http_client client(U("http://127.0.0.1:9090"));
         uri_builder builder(U("/vehicle"));
         builder.append_query(U("filterByOwner"), U("OWN_1"));
         builder.append_query(U("filterByMake"), U("MAK_3"));
         builder.append_query(U("filterByModel"), U("MOD_7"));
         builder.append_query(U("filterByRegistration"), U("REG_15"));

         auto&& task = client
                       .request(methods::GET, builder.to_string())
                       .then([ = ](http_response response)
         {
            BOOST_CHECK_EQUAL(response.status_code(), 200);

            return response.extract_json()
                   .then([](web::json::value v)
            {
               BOOST_CHECK(v.is_array());
               BOOST_CHECK_EQUAL(v.size(), 1);

               int TestCount = 0;
               if(v.is_array() && v.size() >= 1)
               {
                  for(int i = 15; i < 16; ++i)
                  {
                     ++TestCount;
                     BOOST_CHECK_EQUAL(v[i - 15]["Registration"].as_string(), "REG_" + boost::lexical_cast<std::string>(i / 1));
                     BOOST_CHECK_EQUAL(v[i - 15]["Model"].as_string(),        "MOD_" + boost::lexical_cast<std::string>(i / 2));
                     BOOST_CHECK_EQUAL(v[i - 15]["Make"].as_string(),         "MAK_" + boost::lexical_cast<std::string>(i / 4));
                     BOOST_CHECK_EQUAL(v[i - 15]["Owner"].as_string(),        "OWN_" + boost::lexical_cast<std::string>(i / 8));
                  }
               }

               return TestCount;
            });
         });

         BOOST_CHECK_EQUAL(task.get(), 1);
      }

      // tell the server to exit
      write(to_child, "q\n", 2);

      f.wait();

      return 0;
   },
   []()
   {
      // child will run the api-server - aftet the database is setup

      server s(9090, "0.0.0.0", "MyTestDB");

      s.run();

      return 0;
   });
}
