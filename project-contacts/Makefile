OBJS:=contactDao.o main.o util.o contactMenu.o contactType.o contactView.o configuration.o contactDatabaseDao.o
gcchead=gcc -g -Wall -c
mysqlI= -I/usr/include/mysql
mysqlL= -L/usr/lib/mysql -lmysqlclient -lz
contact:${OBJS}
	@echo "begin compile"
	@gcc ${OBJS} ${mysqlL} -o contact
	@echo "compile success"
contactMenu.o:contactMenu.c
	@${gcchead} contactMenu.c -o contactMenu.o
main.o:main.c
	-@${gcchead} main.c -o main.o
util.o:util.c
	@${gcchead} util.c -o util.o
contactDao.o:contactDao.c
	@${gcchead} contactDao.c -o contactDao.o
contactType.o:contactType.c
	@${gcchead} contactType.c -o contactType.o
contactView.o:contactView.c
	@${gcchead} contactView.c -o contactView.o
configuration.o:configuration.c
	@${gcchead} configuration.c -o configuration.o
contactDatabaseDao.o:contactDatabaseDao.c
	@${gcchead} contactDatabaseDao.c ${mysqlI} -o contactDatabaseDao.o
clean:
	-rm -rf *.o contact
.PHONY:clean
