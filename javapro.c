#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define FLAGS 2

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
    printf("Arguments ok!\n");
    return 1;
}

int main(int argc, char *argv[])
{

    int processes[FLAGS] = {0};
    char * flagVals[FLAGS];

    if (!validateArgs(argc, argv, processes, flagVals)){
        return 0;
    }

    // OK SO, HAY QUE HACER STRINGS MAS GRANDES PARA LOS MKDIR Y DEMASES ASI LOS STRCAT ENTRAN, SINO ES UN CAOS Y SEG FAULT PURGATORY
    // UPDATE: PODEMOS USAR SPRINTF LRPM 

/*

    system(strcat("mkdir ", argv[1]));
    system(strcat("cd ", argv[1]));
    system("mkdir src");

    for (int i = 0; i < FLAGS; i++){
        if (processes[i]){
            switch (i) {
                case 0:
                    system(strcat("mkdir src/", flagVals[0]));
                    break;
                case 1:
                    if (processes[0]){
                        system(strcat(flagVals[1], strcat(flagVals[0], "touch src/")));
                    }
                    else {
                        system(strcat(flagVals[1], "touch src/"));
                    } 
                    break; 
            
            }
        }

    }
*/
}
