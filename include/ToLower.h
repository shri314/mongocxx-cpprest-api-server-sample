#pragma once

#include <string>
#include <algorithm>

inline std::string ToLower(std::string input)
{
   std::transform(std::begin(input), std::end(input), std::begin(input), ::tolower);

   return std::move(input);
}

template<class MapT>
inline MapT ToLower(MapT input)
{
   MapT result;
   for_each(std::begin(input), std::end(input), [&result](auto && entry)
   {
      result.emplace( ToLower(std::move(entry.first)), std::move(entry.second) );
   });

   return result;
}
