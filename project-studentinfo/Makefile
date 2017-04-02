all: client system
gcchead=gcc -g -Wall -o
client:client.c
	@echo "begin compile"
	@${gcchead} client client.c
system:system.c
	@${gcchead} system system.c
	@echo "compile success"
clean:
	-rm -rf client system
.PHONY:clean
