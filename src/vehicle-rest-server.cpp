#include "server.h"

int main(int argc, char* argv[])
{
   try
   {
      server s;

      s.run();
   }
   catch(const std::exception& e)
   {
      std::cerr << "Error occurred - " << e.what() << "\n";
   }

   return 0;
}
