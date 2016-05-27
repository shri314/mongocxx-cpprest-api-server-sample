#pragma once

#include <bsoncxx/view_or_value.hpp>
#include <mongocxx/collection.hpp>
#include <mongocxx/cursor.hpp>
#include <mongocxx/options/find.hpp>

template<class CallBack>
inline int MongoForEachQueryResult(mongocxx::collection collection, bsoncxx::document::view_or_value query_filter, const CallBack& callback)
{
   if(collection)
   {
      auto cursor = collection.find(query_filter);

      int count = 0;
      for(auto doc : cursor)
         callback(count++, doc);

      return count;
   }

   return -1;
}
