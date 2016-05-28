#FIXME - convert this to cmake (cross platform make)

CXX := c++
LINK := c++
CXXFLAGS := -Wall -Werror -std=c++1z -g3

################################################################

INCLUDES := \
   -I./include \
   -I/usr/local/include/mongocxx/v_noabi \
   -I/usr/local/include/libbson-1.0 \
   -I/usr/local/include/libmongoc-1.0 \
   -I/usr/local/include/bsoncxx/v_noabi

LINKFLAGS=-L/usr/local/lib

LIBS := \
   -lmongocxx \
   -lbsoncxx \
   -lcpprest \
   -lboost_system \
   -lssl \
   -lcrypto \
   -lpthread

SOURCES := \
   ./src/vehicle-rest-server.cpp

TEST_SOURCES := \
   ./test/test_ToLower.cpp \
   ./test/test_Bson2Json.cpp \
   ./test/test_ForEachPropertyMatchDo.cpp \
   ./test/test_MongoBuildQueryFilter.cpp \
   ./test/test_MongoBuildQueryLogDocument.cpp \
   ./test/test_MongoForEachQueryResult.cpp \
   ./test/test_vehicle-rest-server.cpp

BINS := vehicle-rest-server

################################################################

OBJS := $(SOURCES:%.cpp=%.o)
DEPS := $(SOURCES:%.cpp=%.deps)

TEST_OBJS := $(TEST_SOURCES:%.cpp=%.o)
TEST_DEPS := $(TEST_SOURCES:%.cpp=%.deps)
TEST_BINS := $(TEST_SOURCES:%.cpp=%.bin)
TEST_CHKS := $(TEST_SOURCES:%.cpp=%.chk)

.PRECIOUS: %.cpp %.c %.h %.o %.deps %.bin

################################################################

all:: compile-all

check:: check-all

################################################################

%.deps: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MG -MP $< > $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(INCLUDES) $<

%.bin: %.o
	$(LINK) $(LINKFLAGS) $(LIBS) -lboost_unit_test_framework $< -o $@

%.chk: %.bin
	MALLOC_CHECK_=0 LD_LIBRARY_PATH=/usr/local/lib $<

################################################################

vehicle-rest-server: $(OBJS)
	$(LINK) $(LINKFLAGS) $(LIBS) $(OBJS) -o $@

run:: vehicle-rest-server
	LD_LIBRARY_PATH=/usr/local/lib vehicle-rest-server

################################################################

deps-all:: $(DEPS) $(TEST_DEPS)

compile-all:: deps-all
	$(MAKE) $(BINS)

compile-test-all:: deps-all
	$(MAKE) $(TEST_BINS)

check-all:: compile-test-all
	$(MAKE) $(TEST_CHKS)

clean::
	rm -f $(BINS) $(OBJS) $(TEST_BINS) $(TEST_OBJS) $(DEPS) $(TEST_DEPS)

init::
	mongo gullu_db res/myjsfile.js

################################################################

#sinclude $(DEPS) $(TEST_DEPS)

################################################################
