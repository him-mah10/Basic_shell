main: main.o startNexec.o non_builtins.o print_promt.o remindme.o clockt.o builtins.o pinfo.o getNbreak.o redirect.o piping.o setnunset.o jobs.o
	gcc main.o startNexec.o non_builtins.o print_promt.o remindme.o clockt.o builtins.o pinfo.o getNbreak.o redirect.o piping.o setnunset.o jobs.o

main.o: main.c
	gcc -c main.c

setenv.o: setnunset.c
	gcc -c setnunset.c
	
startNexec.o: startNexec.c
	gcc -c startNexec.c

getNbreak.o: getNbreak.c
	gcc -c getNbreak.c

non_builtins.o:non_builtins.c
	gcc -c non_builtins.c

print_promt.o:print_promt.c
	gcc -c print_promt.c

remindme.o:remindme.c
	gcc -c remindme.c

clockt.o:clockt.c
	gcc -c clockt.c

builtins.o:builtins.c
	gcc -c builtins.c

pinfo.o:pinfo.c
	gcc -c pinfo.c

redirect.o:redirect.c
	gcc -c redirect.c

piping.o:piping.c
	gcc -c piping.c

jobs.o:jobs.c
	gcc -c jobs.c
	
clean: main.o startNexec.o non_builtins.o print_promt.o remindme.o clockt.o builtins.o pinfo.o getNbreak.o redirect.o piping.o setnunset.o jobs.o
	rm *.o