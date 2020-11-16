#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> // for fork

#include <sys/types.h>
#include <sys/wait.h> //waitpid

#define MAX_STRING              1024
#define OK                      3
#define MEM_ERROR               1
#define FILE_UNAVIABLE          3

//some macros to check global reset variable for interruption
#define CONTINUE_RESET if(reset){continue;}
#define BREAK_RESET if(reset){break;}

//change path depending on system
#ifdef __linux__ 
#define BINPATH "/bin/"
#elif __APPLE__
#define BINPATH "/sbin/"
#endif

//colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int reset=0;

//enable color if in a linux terminal
void colorPrint(char *string,char *color){
    #ifdef __linux__ 
    printf("%s%s%s",color,string,RESET);
    #else
    printf("%s"string);
    #endif
}

//wraper for malloc but with checks.
void *getMem(unsigned size){
    void *ret;
    if (!(ret = malloc(size))){
        printf("%s","No more memory available!\n");
        exit(MEM_ERROR);
    }
    return ret;
}

//boolean check if file exists.
int fileExists(char *fname){
    int isOk=0;
    if( access( fname, F_OK ) != -1 ){
        isOk=1;
    }
    return isOk;
}

//run program after reciving argv
int runProgram(char **argv,char **envp){
    int status;
    pid_t pid_fork;
    //make buffer a little bigger to avoid buffer ovrflw when copying fname with strcat
    char fpath[MAX_STRING+100] = BINPATH;
    char *toRun=argv[0];

    //look locally first
    if (!fileExists(argv[0])){

        //look on /bin or /sbin
        strcat(fpath,argv[0]);
        if(!fileExists(fpath)){
            printf("%s :",argv[0]);
            colorPrint("Arquivo inexistente\n",RED);
            return FILE_UNAVIABLE;
        }
        else{
            //change to new path
            toRun=fpath;
        }
        
    }

    //fork and run command
    pid_fork=fork();
    //if child
    if(pid_fork==0){
        if (execve(toRun,argv,envp)==-1){
            perror("execve error: ");
        }
    }
    //else parent wait until command returned
    //https://linux.die.net/man/2/waitpid
    else{
        waitpid(pid_fork,&status,0 );
        if (!WIFEXITED(status)){
            printf("Error!\n");
        }
    }
    return OK;

}

void sigInt(int number) {
    //when reciving int, changes global reset var to repeate loop.
    reset=1;
}

void getInput(char *dst,unsigned size){
    
    if (fgets(dst,size,stdin)!=NULL){
        //removes end of line and replaces for a null byte
        dst[strlen(dst)-1] = 0;

    }
    //if EOF error aka ctrl-d, leave program
    else{
        printf("\n");
        exit(0);
    }
    
}

unsigned getNumber(){
    char numberStr[16];
    char *check;
    int result;
    getInput(numberStr,16);
    result=strtol(numberStr,&check,10);
    if(*check!=0 || result <0){
        printf("Numero de argumentos inválido %i \n",result);
        reset=1;
    }
    return result;

}

int main(int argc,char **argv,char **envp){
    char command[200];
    unsigned argnumber;
    char **argvector;

    //install signal handler to handle SIGUSR1
    if (signal(SIGUSR1, &sigInt) == SIG_ERR) {
        fprintf(stderr, "Unable to install signal handler\n");
        return EXIT_FAILURE;
    }

    while (1){
        reset=0;

        //color banner
        colorPrint("awesome-shell",GRN);
        if(geteuid() != 0){
            colorPrint("$ ",BLU);
        }
        else{
            colorPrint("# ",MAG);
        }

        //get first comand
        getInput(command,MAX_STRING);
        CONTINUE_RESET

        //get command number
        printf("%s\n","Quantos argumentos você quer digitar?");
        argnumber = getNumber();
        CONTINUE_RESET

        //initializas the argv **
        argvector = (char **)getMem(sizeof(char *) * (argnumber+2));

        //fill the first string w program name
        argvector[0]=command;

        //finishes w NULL PTR
        argvector[argnumber+1]=NULL;
        
        for (unsigned i=1;i<=argnumber;i++){
            argvector[i]=(char *)getMem(MAX_STRING+1);
            printf("Digite o argumento %i: ",i);

            getInput(argvector[i],MAX_STRING);
            BREAK_RESET
        }

        CONTINUE_RESET
        runProgram(argvector,envp);


        //clean, but first item of argvlist is on stack not on heap
        for (unsigned i=1;i <(argnumber+2); i++){
            free(argvector[i]);
        }
        //clean dinamic created array
        free(argvector);
    }

    return OK;
}