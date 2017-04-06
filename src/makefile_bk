include ../../mk/IotMakeRule
DEBUG_FLAG = -DErrMsg -DDebugMsg
all:
	$(CC) -c $(DEBUG_FLAG) -I../inc -I$(BOOST_INC_DIR) -I$(JSON_INC_DIR) -fPIC *.c *.cpp -Os 
	ar rcs lib$(IOT_LIB_LINK_FILE).a *.o
	mv lib$(IOT_LIB_LINK_FILE).a ../lib

clean :
	rm *.o
	rm ../lib/*.a
