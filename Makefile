	
ifeq (,$(filter _%,$(notdir $(CURDIR))))
include target.mk
else
#----- End Boilerplate

VPATH = $(SRCDIR)

CXXFLAGS =	-std=c++11 -pedantic -Wall -g -fmessage-length=0

LDXFLAGS =	-std=c++11 -pedantic -Wall -g -fmessage-length=0

OBJS     =	FreeAX25.o \
			XMLRuntime.o \
			DOMTreeErrorReporter.o \
			Utils.o \
			Logger.o \
			Timer.o \
			TimerManager.o \
			Environment.o \
			Configuration.o \
			Plugin.o \
			Instance.o \
			Setting.o

LIBS     =  -lpthread -lxerces-c -ldl

TARGET   =	FreeAX25

$(TARGET):	$(OBJS)
	$(CXX) $(LDXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<	
	
all: $(TARGET)
	cp ../*.xml ../*.xsd .
	echo "Build OK"

#----- Begin Boilerplate
endif
