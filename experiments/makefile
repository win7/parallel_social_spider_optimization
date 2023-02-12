CC = mpicc					# mpicc or gcc
CFLAGS = -g -Wall -O2 		# flags when *compiling*
LFLAGS = -g -Wall 			# flags when *linking*
LIBS = -lm 					# math library

SOURCES = main_sso.c clusterCenter.c spider.c population.c utils.c
# SOURCES = main_psso.c clusterCenter.c spider.c population.c topology.c utils.c
# SOURCES = main_population.c clusterCenter.c spider.c population.c topology.c utils.c
# SOURCES = main_fitness.c clusterCenter.c spider.c population.c topology.c utils.c
# SOURCES = main_sso_exp.c clusterCenter.c spider.c population.c topology.c utils.c
# SOURCES = main_psso_exp.c clusterCenter.c spider.c population.c topology.c utils.c

OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = main_sso
# EXECUTABLE = main_psso
# EXECUTABLE = main_population
# EXECUTABLE = main_fitness
# EXECUTABLE = main_sso_exp
# EXECUTABLE = main_psso_exp

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@ $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
