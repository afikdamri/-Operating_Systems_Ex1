#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<dirent.h>
#include <unistd.h>

void echo(char str[30]){
    for(int i = 4; i < 20; i++){
        printf("%c", str[i]);
    }
}

void pathfile(){
    char path[100] = {'\0'};
    if (getcwd(path, sizeof(path)) != NULL)
    {
        printf("My directory -> %s\n", path);
    }
    else
    {
        perror("Error Path!");
        exit(1);
    }
}

void directory(const char* dirname){
    DIR *dir;
    struct dirent *sd;
    dir = opendir(".");
    if (dir == NULL){
        printf("Error! Unable to open directory.\n");
        exit(1);
    }
    while ((sd = readdir(dir)) != NULL){
        printf(">> %d%s\n",sd->d_type, sd->d_name);
    }
    closedir(dir);   
}

void copyfile(char src[30], char dest[30]){
    char tav = ' ';
    FILE *p_src = fopen(src, "rb");
    if(p_src == NULL){
        printf("Error open source file");
        exit(1);
    }
    FILE *p_dest = fopen(dest, "ab");
    if(p_dest == NULL){
        printf("Error open destination file");
        exit(1);
    }
    while(fread(&tav, 1, 1, p_src) == 1){
        fwrite(&tav, sizeof(char), 1, p_dest);
        
    }
    fclose(p_src);
    fclose(p_dest);
}

void copy(char str[30]){
    char src[30] = {'\0'};
    char dest[30] = {'\0'};
    int i = 5, j = 0;
    while(str[i] != ' '){
        src[i - 5] = str[i];
        i+=1;
    }
    i++;
    while (str[i+1] != '\0' )
    {
        dest[j] = str[i];
        i+=1;
        j+=1;
    }
    copyfile(src, dest);
}

void delete(char str[30]){
    char temp[30] = {'\0'};
    int i = 7;
    while(str[i] != '\0'){
        temp[i - 7] = str[i];
        i+=1;
    }
    unlink(temp);
}

void cd(char str[30]){
    char temp[27] = {'\0'};
    for(int i = 3; i < 27; i++){
        temp[i-3] = str[i];
    }
    chdir(temp);
    pathfile();
}

int main(){
    char str[30] = {'\0'};
    DIR *dir;
    printf("Yes master ?");
    scanf("%[^\n]%*c", str);
  
    pathfile();
    while (strncmp(str, "EXIT", 4))
    {
        if (strncmp(str, "ECHO", 4) == 0){
            echo(str);
        } 
        else if (strncmp(str, "DIR", 3) == 0){
            directory(".");
        }
        else if (strncmp(str, "CD", 2) == 0){
            cd(str); // Is a system call or library function ?
        }
        else if (strncmp(str, "COPY", 4) == 0){
            copy(str); // Is a system call or library function ?
        }
        else if (strncmp(str, "DELETE", 6) == 0){
            delete(str); // Is a system call or library function ?
        }
        else{
            int id = fork();
            if(id == -1){
                printf("Error to create the process");
                exit(1);
            }
            if(id == 0) {
                char p[50] = "/bin/";
                strcat(p, str);
                execlp(p, str, NULL); 
            }
            wait(NULL);
        }
        printf("\nYes master ?");
        scanf("%[^\n]%*c", str);
    }
    return 0;
}

