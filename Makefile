CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -L. -lclaves
LDLIBS = -lpthread -lrt

# los ejecutables
all: servidor libclaves.so cliente
.PHONY: all

# $(CFLAGS)
libclaves.so: 
# $(CC) -fPIC -c -g clavesDebug.c
# ld -shared -o $@ clavesDebug.o
	$(CC) -fPIC -c -g claves.c
	ld -shared -o $@ claves.o

servidor:
	$(CC) $(CFLAGS) -g servidor.c proxy.c lines.c common.c $(LDLIBS) -o $@

cliente:
	$(CC) $(CFLAGS) -g cliente.c lines.c common.c $(LDFLAGS) -lrt -o $@ 

 
runcliente: cliente
	env IP_TUPLAS=localhost PORT_TUPLAS=4500 LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./cliente

#para limpiar los ficheros generados
clean:
	rm -f servidor cliente libclaves.so
	rm -f *.o

.PHONY: clean


# -g para que genere informacion para depuracion
# -p para que no de error si ya existe
# -f para que no pregunte si se quiere sobreescribir
# -r para que borre directorios no vacios
# -c para que genere archivos de objeto .o 
# -o para indicar el nombre del fichero que se va a generar
# $^ es una variable que contiene todos los ficheros que dependen de la receta
# $< es una variable que contiene el primer fichero que depende de la receta
# $@ es una variable que contiene el nombre del fichero que se esta generando