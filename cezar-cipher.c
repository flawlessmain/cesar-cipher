#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

//check the help function for use behaviour.
void help(char*);

void encrypt(char*, char*);
void decrypt(char*, char*);

void encrypt_file(char*, char*, int);
void decrypt_file(char*, char*, int);

int main(int argc, char *argv[]){

    switch (argc){
        case 4:
            if ((strcmp(argv[3], "-f")) && (strcmp(argv[3], "-fs"))) {
                if (!strcmp(argv[1], "-e")) {
                    encrypt(argv[2], argv[3]);
                    printf("%s\n", argv[3]);
                    break;
                }
                else if (!(strcmp(argv[1], "-d"))){
                    decrypt(argv[2], argv[3]);
                    printf("%s\n", argv[3]);
                    break;
                };
            }
        case 3:
        case 2:
            if (!strcmp(argv[1], "--help")) {
                help(argv[0]); 
                break;
            }
        case 1:
            printf("Not enough arguments! Expected at least 3. Or no flags given. Try using --help.\n");
            break;
        case 5:
            if (!strcmp(argv[3], "-f")){
                if (!strcmp(argv[1], "-e")) {
                    encrypt_file(argv[2], argv[4], false);
                    break;
                }
                else if(!strcmp(argv[1], "-d")){
                    decrypt_file(argv[2], argv[4], false);
                    break;
                } 
                else printf("Not enough arguments. Or wrong flags are given. Try using --help.\n");
            } else if (!strcmp(argv[3], "-fs")) {
                if (!strcmp(argv[1], "-e")) {
                    encrypt_file(argv[2], argv[4], true);
                    break;
                }
                else if (!(strcmp(argv[1], "-d"))){
                    decrypt_file(argv[2], argv[4], true);
                    break;
                }
                else printf("Not enough arguments. Or wrong flags are given. Try using --help.\n");
            }
        default:
            printf("Too many arguments! Program expects maximum 5. Or wrong flags are given. Try using --help for detail explanation!\n");
            break;
    }

    return 0;
}

void help(char *program_name){
    char help[] = "Hello world!";
    printf("Type %s followed by 1 or 2 flags with text or filepath.\n",program_name);
    printf("Pass your text with doublequotes like this: \"Hello, World!\"\n");
    printf("Flags: -e to encrypt, -d to decrypt, type key number(+/-3) and -f to specify the /path/to/the/file\n");
    printf("If -f flag specified you can save result directly in file you working on by changing flag to -fs.\n");
    printf("Also you can use pipe > to store result in file.\n");
    printf("Please NOTE: if you have special symbols in your string - like \" or singlequotes, use \\ to pass them.\n");
    encrypt("3", help);
    printf("Example: %s -e 3 Hello world!\t Result: %s\n", program_name, help);
}

void encrypt(char *_key, char *text){
    int key = atoi(_key);
    char *p = text;
    while((*p) != '\0'){
        *(p++) += key;
    }
}

void decrypt(char *_key, char *text){
    int key = atoi(_key);
    char *p = text;
    while((*p) != '\0'){
        *(p++) -= key;
    }
}

void encrypt_file(char *_key, char *file_path, int override){
    FILE *fptr;
    char buffer[1024];
    if (override){
        fptr = fopen(file_path, "r+");
        if (fptr == NULL) {
            printf("Error while loading file. Check if you specidied path correctly.\n");
            exit(0);
        }
        else {
            if (fgets(buffer, 1024, fptr) != NULL){
                encrypt(_key, buffer);
                rewind(fptr);
                fputs(buffer, fptr);
                printf("File overrided succesfully! Your data is encrypted.\n");
            }
        }
        fclose(fptr);
    } 
    else {
        fptr = fopen(file_path, "r");
        if (fptr == NULL){
            printf("Error while loading file. Check if you specidied path correctly.\n");
            exit(0);
        } 
        else {
            if (fgets(buffer, 1024, fptr) != NULL){
                encrypt(_key, buffer);
                puts(buffer);
            }
        }
        fclose(fptr);
    }
}

void decrypt_file(char *_key, char *file_path, int override){
    FILE *fptr;
    char buffer[1024];
    if (override){
        fptr = fopen(file_path, "r+");
        if (fptr == NULL){
            printf("Error while loading file. Check if you specidied path correctly.\n"); 
            exit(0);
        }
        else {
            if (fgets(buffer, 1024, fptr) != NULL){
                decrypt(_key, buffer);
                rewind(fptr);
                fputs(buffer, fptr);
                printf("File overrided succesfully! Your data is decrypted.\n");
            }
        }
        fclose(fptr);
    } 
    else {
        fptr = fopen(file_path, "r");
        if (fptr == NULL){
            printf("Error while loading file. Check if you specidied path correctly.\n");
            exit(0);
        } 
        else {
            if (fgets(buffer, 1024, fptr) != NULL){
                decrypt(_key, buffer);
                puts(buffer);
            }
        }
        fclose(fptr);
    }
}