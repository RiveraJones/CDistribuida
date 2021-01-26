
all:	maxthreads tls barreras mm_prog6-1 sched_attr_fig6.19

maxthreads:	maxthreads.o 
	cc -o maxthreads maxthreads.c -lpthread

barreras:	barreras.o 
	cc -o barreras barreras.c -lpthread

mm_prog6-1:	mm_prog6-1.o 
	cc -o mm_prog6-1 mm_prog6-1.c -lpthread

sched_attr_fig6.19:	sched_attr_fig6.19.o
	cc -o sched_attr_fig6.19 sched_attr_fig6.19.c-lpthread

tls:	 tls.o 
	cc -o tls tls.c -lpthread

