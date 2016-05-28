#pragma once

#include "MongoBuildQueryFilter.h"
#include "MongoBuildQueryLogDocument.h"
#include "MongoForEachQueryResult.h"
#include "Bson2Json.h"

#include <cpprest/http_listener.h>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <exception>
#include <iostream>
#include <chrono>

using namespace utility;                            // Common utilities like string conversions
using namespace web::http;                          // Common HTTP functionality
using namespace web::http::client;                  // HTTP client features
using namespace web::http::experimental::listener;  // HTTP server features

struct server
{
   public:
      explicit server(int port = 8080, const std::string& localip = "0.0.0.0", const std::string& DBName = "gullu_db")
      {
         static std::string DataTableName = "Vehicle";
         static std::string LogTable      = "VehicleQueries";
         static std::string QueryPrefix   = "filterBy";
         static auto&& DataTableFields    = { "Registration", "Make", "Model", "Owner" };

         http_listener L(uri(U("http://" + localip + ":" + boost::lexical_cast<std::string>(port) + "/vehicle")));

         L.support(methods::GET, [DBName](http_request req)
         {
            auto&& http_get_vars = uri::split_query(req.request_uri().query());

            auto&& query_filter = MongoBuildQueryFilter(DataTableName, http_get_vars, QueryPrefix, DataTableFields);

            auto&& query_log_data = MongoBuildQueryLogDocument(DataTableName, http_get_vars, QueryPrefix, DataTableFields);

            web::json::value response_json;
            {
               // FIXME - Check if connection pooling is implemented by mongocxx

               auto&& inst = mongocxx::instance{};
               auto&& conn = mongocxx::client{mongocxx::uri{}};
               auto&& db   = conn[DBName];

               int Count = MongoForEachQueryResult(db[DataTableName], query_filter.view(), [&response_json, table_fields = DataTableFields, table_name = DataTableName](int c, auto && item)
               {
                  web::json::value rec_entry;
                  for(auto && fn : table_fields)
                     rec_entry[U(fn)] = Bson2Json(item[table_name + "_" + fn]);

                  response_json[c] = rec_entry;
               });

               query_log_data << "Results" << Count
                              << "Created" << bsoncxx::types::b_date(
                                 std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                              );

               db[LogTable].insert_one(query_log_data.view());
            }

            req.reply(status_codes::OK, response_json);
         });

         m_Listner = std::move(L);
      }

      void run()
      {
         auto&& t = m_Listner.open().then([]()
         {
            std::cout << "press 'q\\n' to quit\n";

            char x;
            while(std::cin >> x)
               if(x == 'q')
                  break;
         });

         t.wait();
      }

   private:
      http_listener m_Listner;
};
