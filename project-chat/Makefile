all:receiveFile sendFile serverFile 
gcchead=gcc -g -Wall -o
receiveFile:receiveFile.c
	@echo "begin compile"
	@${gcchead} receiveFile receiveFile.c
sendFile:sendFile.c
	@${gcchead} sendFile sendFile.c
serverFile:serverFile.c
	@${gcchead} serverFile serverFile.c
	@echo "compile success"
clean:
	-rm -rf receiveFile sendFile serverFile
.PHONY:clean
