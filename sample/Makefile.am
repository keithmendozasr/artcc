AM_CXXFLAGS = -Wall -Werror -pedantic -std=c++11 -I$(top_builddir)/include

bin_PROGRAMS = artcctest
artcctest_SOURCES = artcctest.cpp
artcctest_LDADD = $(top_builddir)/src/libartcc.la -llog4cpp
