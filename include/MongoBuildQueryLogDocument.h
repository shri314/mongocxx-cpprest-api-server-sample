#pragma once

#include "ForEachPropertyMatchDo.h"

#include <bsoncxx/builder/stream/document.hpp>

template<class MapT, class DataTableFieldList>
inline auto MongoBuildQueryLogDocument(const std::string& TableName, const MapT& http_get_vars, const std::string& filterPrefix, const DataTableFieldList& DataTableFields,
                                       const std::string& jsonNameFilterField = "filter", const std::string& jsonNameFilterCriterion = "by", const std::string& jsonNameFilterValue = "with")
{
   bsoncxx::builder::stream::document doc{};

   auto&& entry_doc = doc << jsonNameFilterField << bsoncxx::builder::stream::open_array;

   ForEachPropertyMatchDo(http_get_vars, filterPrefix, DataTableFields, [ =, &entry_doc](auto && fn, auto && fv)
   {
      entry_doc << bsoncxx::builder::stream::open_document
                << jsonNameFilterCriterion << fn << jsonNameFilterValue << fv
                << bsoncxx::builder::stream::close_document;
   });

   entry_doc << bsoncxx::builder::stream::close_array;

   return doc;
}
