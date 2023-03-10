/*! TODO: 
 *
 * @todo Validate buffer size
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define FLAGS 2
#define BUFF_SIZE 100

// Processes es un arreglo de enteros que va a tener unos o ceros depende de que procesos hay que hacer (para evitar multiples strcmp)

int createProyect(char * proyect, char * package){

    return 1;


}

void showUsage(){

    printf("Usage: javapro [proyect-name] [options]\n    -p [package-name] : create an empty package inside the src directory\n    -c [class-name] : create an empty java class file in the src or package directories\n");
}


int validateFlag(char * flag, int processes[], char * flagVals[], char * flagValue){
    char * flags[] = {"-p", "-c"};
    int found = 0;
    int flagNum = -1;

    if (!isalpha(flagValue[0])){
        printf("Something went wrong parsing the flags. Check that they are written correctly\n");
        return 0;
    }


    for (int i = 0; i < FLAGS && !found; i++){
        if (strcmp(flag, flags[i]) == 0){
            flagNum = i;
        }
    }
    
    if (flagNum == -1){
        printf("Error: Unknown flag: %c\n", flag[1]);
    }
    

    if (processes[flagNum]){
        printf("Error: Duplicated flag: %c\n", flag[1]);
        return 0;
    }
    
    found++;
    processes[flagNum]++;
    flagVals[flagNum] = flagValue; 

    return 1;
}



int validateArgs(int dim, char * argList[], int processes[], char * flagVals[]){

   if (dim == 1){
        printf("Error: Missing arguments\n");
        showUsage();
        return 0;
    } 

    if (!isalpha(argList[1][0])){
        printf("Error: The proyect name should come before the arguments and not start with '-'\n");
        showUsage();
        return 0;
    }

    if (dim > 2){

        if (dim % 2 != 0){
            printf("Error: There seems to be missing arguments\n");
            showUsage();
            return 0;
        }

        for (int i = 2; i < dim - 1; i++){
            if (i % 2 == 0 && !validateFlag(argList[i], processes, flagVals, argList[i + 1])){
                showUsage();
                return 0;
            }
            
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{

    int processes[FLAGS] = {0};
    char * flagVals[FLAGS];
    char buffer[BUFF_SIZE];

    if (!validateArgs(argc, argv, processes, flagVals)){
        return 0;
    }

    sprintf(buffer, "mkdir -p %s/src", argv[1]);
    system(buffer);

    for (int i = 0; i < FLAGS; i++){
        if (processes[i]){
            switch (i) {
                case 0:
                    sprintf(buffer, "mkdir %s/src/%s", argv[1], flagVals[0]);
                    system(buffer);
                    break;
                case 1:
                    if (processes[0]){
                        sprintf(buffer, "touch %s/src/%s/%s.java", argv[1], flagVals[0], flagVals[1]);
                        system(buffer);
                    }
                    else {
                        sprintf(buffer, "touch %s/src/%s.java", argv[1], flagVals[1]);
                        system(buffer);
                    } 
                    break; 
            
            }
        }

    }
}
