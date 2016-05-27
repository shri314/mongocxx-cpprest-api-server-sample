#pragma once

#include <cpprest/json.h>
#include <bsoncxx/types.hpp>
#include <bsoncxx/document/element.hpp>

inline web::json::value Bson2Json(const bsoncxx::document::element& b)
{
   switch(b.type())
   {
      case bsoncxx::type::k_utf8:
      {
         auto&& b_val = bsoncxx::stdx::string_view(b.get_utf8()).to_string();

         return web::json::value::string(U(b_val));
      }

      case bsoncxx::type::k_int64:
      {
         auto&& b_val = b.get_int64();

         return web::json::value::number(b_val);
      }

      case bsoncxx::type::k_int32:
      {
         auto&& b_val = b.get_int32();

         return web::json::value::number(b_val);
      }

      case bsoncxx::type::k_double:
      {
         auto&& b_val = b.get_double();

         return web::json::value::number(b_val);
      }

      case bsoncxx::type::k_bool:
      {
         auto&& b_val = b.get_bool();

         return web::json::value::boolean(b_val);
      }

      case bsoncxx::type::k_array:
      case bsoncxx::type::k_binary:
      case bsoncxx::type::k_code:
      case bsoncxx::type::k_codewscope:
      case bsoncxx::type::k_date:
      case bsoncxx::type::k_dbpointer:
      case bsoncxx::type::k_document:
      case bsoncxx::type::k_maxkey:
      case bsoncxx::type::k_minkey:
      case bsoncxx::type::k_null:
      case bsoncxx::type::k_oid:
      case bsoncxx::type::k_regex:
      case bsoncxx::type::k_symbol:
      case bsoncxx::type::k_timestamp:
      case bsoncxx::type::k_undefined:
         return web::json::value::null();
   }

   return web::json::value::null();
}
