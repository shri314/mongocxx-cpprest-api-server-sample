#pragma once

#include "ForEachPropertyMatchDo.h"

#include <bsoncxx/builder/stream/document.hpp>

template<class MapT, class DataTableFieldList>
inline auto MongoBuildQueryFilter(const std::string& TableName, const MapT& http_get_vars, const std::string& filterPrefix, const DataTableFieldList& DataTableFields)
{
   bsoncxx::builder::stream::document query_filter{};

   ForEachPropertyMatchDo(http_get_vars, filterPrefix, DataTableFields, [&query_filter, TableName](auto && fn, auto && fv)
   {
      auto&& table_field = TableName + "_" + fn;

      query_filter << table_field << fv;
   });

   return query_filter;
}
