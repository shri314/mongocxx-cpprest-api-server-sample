# mongocxx-cpprest-api-server-sample

PREREQUISITES:
==============
- For details of the prerequisites - see res/prerequisites_log.txt

BUILDING:
=========
- Currently the make file supports Linux only, but the code is cross platform

- Assuming that the prerequisites are installed

   make             # compile the code base
   make check       # run the tests - some of the tests require mongodb to be running
   make init        # run the initialization script to create appropriate mongodb collections
   make run         # run the server

DESIGN:
=======
- class 'server' listens on 8080, and handles all incoming requests
   - the implementation uses cpprest/http_server class
   - a handler is registered to work for /vehicle

- When a request arrives, the handler is invoked
   - a filter for mongodb query is built from the incoming HTTP GET parameters
   - this is submitted to the mongodb
   - the response from mongodb is processed and converted to a json response

WEB.RESOURCES:
==============
cpprest sdk          : https://github.com/Microsoft/cpprestsdk                                                          [GITHUB]
                     : http://microsoft.github.io/cpprestsdk/index.html                                                 [REFERENCE DOC]
                     : https://casablanca.codeplex.com/wikipage?title=Http%20Client%20Tutorial                          [HTTP CLIENT TUTORIAL]
                     : http://mariusbancila.ro/blog/2013/08/19/full-fledged-client-server-example-with-cpprest-sdk-110/ [CLIENT-SERVER TUTORIAL]

mongocxx and bsoncxx : https://github.com/mongodb/mongo-cxx-driver                                                      [GITHUB]
                     : http://mongodb.github.io/mongo-cxx-driver/index.html                                             [REFERENCE DOC]
                     : https://github.com/mongodb/mongo-cxx-driver/wiki/Quickstart-Guide-(New-Driver)                   [QUICK START TUTORIAL]

mongodb              : https://www.mongodb.com/
