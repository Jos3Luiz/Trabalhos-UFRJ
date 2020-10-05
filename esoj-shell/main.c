#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> // for fork

#include <sys/types.h>
#include <sys/wait.h> //waitpid

#define MAX_PARAMETER 200
#define MAX_STRING 1024
#define OK        3
#define MEM_ERROR               1
#define BIG_STRING_ERROR        2
#define FILE_UNAVIABLE        3


int restart=0;

void *getMem(unsigned size){
    void *ret;
    if (!(ret = malloc(size))){
        printf("%s","No more memory available!\n");
        exit(MEM_ERROR);
    }
    return ret;

}
//pPath = getenv ("PATH");
int fileExists(char *fname){
    //printf("Buscando por %s\n",fname);
    if( access( fname, F_OK ) != -1 ){
        return 1;
    }
    else{
        return 0;
    }

}

char *getPathNext(char *start){
    for(;*start!=':';start++){
        if (*start==0){
            return NULL;
        }
    }
    return ++start;
}

void _dumpArgs(char **args){
    int c=0;
    for (;*args!=NULL;args++,c++){
        printf("%i: %s\n",c,*args);
        
    }
}

int runProgram(char **argv,char **envp){

    int status;
    pid_t pid_fork;
    char *fname=argv[0];
    char *pPath;
    char fpath[MAX_STRING+1];
    //pPath = getenv ("PATH");
    memset(fpath,0,sizeof(fpath));

    //printf("Running program %s\n",fname);

    //look locally
    if (!fileExists(fname)){
        strcat(fpath,"/bin/");
        strcat(fpath,fname);
        if(!fileExists(fpath)){
            printf("Arquivo inexistente\n");
            return FILE_UNAVIABLE;
        }
        else{
            //printf("Program found at /bin\n");
            strncpy(argv[0],fpath,MAX_STRING);

        }
        
    }

    
    pid_fork=fork();
    //if child
    if(pid_fork==0){
        //printf("Running.. %s\n",argv[0]);
        //fclose(stdin);
        //fclose(stdout);
        //_dumpArgs(argv);
        execve(argv[0],argv,envp);
    }
    //else fork
    else{
        //printf("waiting for pid=%i\n",pid_fork);
        waitpid(pid_fork,&status,0 );
        //https://linux.die.net/man/2/waitpid
        if (WIFEXITED(status)){
            //printf("Exited Normally\n");
        }
    }
    return OK;

}

void sighandler(int number) {
    static int count=0;
    printf("Signal catpured!\n");
    restart = 1;
    if (count > 5){
        exit (MEM_ERROR);
    }
}



int main(int argc,char **argv,char **envp){
    char argument[MAX_STRING+1];
    unsigned argnumber;
    char **argvector;

    if (signal(SIGINT, &sighandler) == SIG_ERR) {
        fprintf(stderr, "Unable to install signal handler\n");
        return EXIT_FAILURE;
    }


    while (1){
        restart=0;
        printf("esojs shell> ");
        scanf("%200s",argument);
        printf("%s\n","Quantos argumentos você quer digitar?");
        scanf("%d",&argnumber);
        //because of argv[0]
        argnumber++;


        //initializas the argv **
        argvector = (char **)getMem(sizeof(char *) * (argnumber+1));
        //finishes w NULL PTR
        argvector[argnumber]=NULL;

        //fill the first string w program name
        argvector[0]=(char *)getMem(MAX_STRING+1);
        strcpy(argvector[0],argument);

        
        for (unsigned i=1;i<argnumber;i++){
            argvector[i]=(char *)getMem(MAX_STRING+1);
            printf("Digite o argumento %i: ",i);
            scanf("%200s",argvector[i]);
            if(restart){
                break;
            }
            //printf("fim do argumento\n");
        }
            
        if(!restart){
            //inherited envp from shells envp
            //_dumpArgs(argvector);
            runProgram(argvector,envp);
            //free the heap
            for(;*argvector!=NULL;argvector++){
                free(*argvector);
            }
            //free(argvector);
        }
        
    






        



    }
}