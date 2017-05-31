GTEST_ROOT = $(top_builddir)/test/gtf/googletest
AM_CXXFLAGS = -Wall -Werror -pedantic -std=c++11 -I$(top_builddir)/include -I$(GTEST_ROOT) -I$(GTEST_ROOT)/include

TESTS = task scheduler
bin_PROGRAMS = task scheduler
task_SOURCES = task.cpp
task_LDADD = $(top_builddir)/src/libartcc.la -llog4cpp
task_LDFLAGS = -pthread

scheduler_SOURCES = scheduler.cpp
scheduler_LDADD = $(top_builddir)/src/libartcc.la -llog4cpp
scheduler_LDFLAGS = -pthread
