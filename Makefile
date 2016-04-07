CXX?=g++

VOLK_FLAGS=$(shell pkg-config --cflags --libs volk)
BOOST_FLAGS?=-lboost_timer -lboost_system

all: table_vs_volk

table_vs_volk: table_vs_volk.cc
	${CXX} $(VOLK_FLAGS) $(BOOST_FLAGS) -o table_vs_volk table_vs_volk.cc

clean:
	rm table_vs_volk

