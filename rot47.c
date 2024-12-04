#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void rot47(char *caracter)
{
        if(*caracter >= 33 && *caracter <= 126)
                *caracter = 33 + ((*caracter - 33 + 47) %94);
}

int main(int argc, char *argv[])
{
        int descriptor;
        char buffer;
        char *filename = argv[1];
        ssize_t bytes_read;

        if(argc != 2)
        {
                printf("La sintaxis para este comando es: rot47 <archivo>\nInten
talo de nuevo.\n");
                exit(EXIT_FAILURE);
        }

        descriptor = open(filename,O_RDWR);

        if(descriptor == -1)
        {
                printf("El archivo %s no se pudo abrir.\n", filename);
                exit(EXIT_FAILURE);
        }

        while((bytes_read = read(descriptor, &buffer, 1) > 0))
        {
                rot47(&buffer);

                if(lseek(descriptor, -1, SEEK_CUR) == -1)
                {
                        printf("Error al buscar en el archivo.\n");
                        close(descriptor);
                        exit(EXIT_FAILURE);
                }

                if(write(descriptor, &buffer, 1) != 1)
                {
                        printf("Error al escribir en el archivo.\n");
                        close(descriptor);
                        exit(EXIT_FAILURE);
                }
        }

        if(bytes_read == -1)
                printf("Error al leer el archivo.\n");

        close(descriptor);
        return 0;
}
