#   Project FreeAX25
#   Copyright (C) 2015  tania@df9ry.de
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as
#   published by the Free Software Foundation, either version 3 of the
#   License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
ifeq (,$(filter _%,$(notdir $(CURDIR))))
include target.mk
else
#----- End Boilerplate

VPATH = $(SRCDIR)

CXXFLAGS =	-std=c++11 -pedantic -Wall -g -rdynamic -fmessage-length=0 \
			-I../../libStringUtil \
			-I../../libJsonX

LDXFLAGS =	-std=c++11 -pedantic -Wall -g -rdynamic -fmessage-length=0 \
			-L../../libJsonX/_$(_ARCH)-$(_CONF) \
			-L../../libB64/_$(_ARCH)-$(_CONF) \
			-L../../libStringUtil/_$(_ARCH)-$(_CONF) \
			-L../../libSocketIO/_$(_ARCH)-$(_CONF)

OBJS     =	FreeAX25.o \
			Channel.o \
			Configuration.o \
			DOMTreeErrorReporter.o \
			Environment.o \
			Instance.o \
			Logger.o \
			Null.o \
			Plugin.o \
			ServerBase.o \
			ServerProxy.o \
			Timer.o \
			TimerManager.o \
			XMLRuntime.o

LIBS     =  -lJsonX -lB64 -lStringUtil -lSocketIO \
			-lpthread -lxerces-c -ldl

TARGET   =	FreeAX25

$(TARGET):	$(OBJS)
	$(CXX) $(LDXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<	
	
all: $(TARGET)
	cp ../*.xml ../*.xsd .
	cp ../../libStringUtil/_$(_ARCH)-$(_CONF)/libStringUtil.so .
	cp ../../libJsonX/_$(_ARCH)-$(_CONF)/libJsonX.so .
	cp ../../libB64/_$(_ARCH)-$(_CONF)/libB64.so .
	cp ../../libSocketIO/_$(_ARCH)-$(_CONF)/libSocketIO.so .
	echo "Build OK"
	
run: all
	LD_LIBRARY_PATH=./ ./$(TARGET)
	echo "Run OK"

#----- Begin Boilerplate
endif
