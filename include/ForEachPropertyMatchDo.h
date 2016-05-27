#pragma once

#include "ToLower.h"

#include <string>

// E.g.: Say if map contains get params of - http://.../path?filterbyRegistration=...&filterbyMake=...&otherField1=...&anotherField2=...
//     : query_prefix = std::string("filterby");
//     : query_suffixes = std::vector<std::string> { "Registration", "make" };
//
template<class Map, class StrList, class Action>
inline void ForEachPropertyMatchDo(Map properties_cased, const std::string& query_prefix, const StrList& query_suffixes, const Action& callback)
{
   auto&& properties = ToLower( properties_cased );

   for(auto && qs_entry_cased : query_suffixes)
   {
      auto&& q_field = ToLower(query_prefix + std::string(qs_entry_cased));

      auto&& f = properties.find(q_field);

      if(f != properties.end() && !f->second.empty())
      {
         callback( qs_entry_cased, f->second );
      }
   }
}
