LIBNAME = libepolling.a
BIN_SERVER_FILE = epoll_server
BIN_CLIENT_FILE = epoll_client

RANLIB = ranlib
noinst_LIBRARIES = $(LIBNAME)
AM_CPPFLAGS = -I$(top_srcdir)/inc -DDEBUG_MODE -DDebugMsg -DErrMsg
libepolling_a_SOURCES = epolling.c GwTimer_utils.c IpcCtrl.c


bin_PROGRAMS = $(BIN_SERVER_FILE) $(BIN_CLIENT_FILE)
epoll_server_LDADD = -L./ -L$(top_srcdir)/lib/ -lepolling -lpthread
epoll_server_SOURCES = main.c
epoll_server_CFLAGS = -I$(top_srcdir)/inc -DDEBUG_MODE -DDebugMsg -DErrMsg

epoll_client_LDADD = -L./ -L$(top_srcdir)/lib/ -lepolling -lpthread
epoll_client_SOURCES = client_main.c
epoll_client_CFLAGS = -I$(top_srcdir)/inc -DDEBUG_MODE -DDebugMsg -DErrMsg

all:
	rm *.o -rf
	mkdir $(top_srcdir)/lib -p
	mv $(LIBNAME) $(top_srcdir)/lib/
#	$(CC) main.c -I$(top_srcdir)/inc -L$(top_srcdir)/lib/ -lepolling -lpthread -o
	mv $(BIN_SERVER_FILE) $(top_srcdir)/
	mv $(BIN_CLIENT_FILE) $(top_srcdir)/

clean:
	rm $(top_srcdir)/lib/$(LIBNAME)
	rm $(top_srcdir)/$(BIN_SERVER_FILE) $(top_srcdir)/$(BIN_CLIENT_FILE)