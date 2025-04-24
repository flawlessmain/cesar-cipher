#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

//program name followed by flag of encryption or decryption and optionally -f to work with file followed by a filepath 
// cipher -e to encrypt (step) 2 -f /file/to/path
// cipher -d to decrypt (step -3 just some text

void help(char*);

void encrypt(char*, char*);
void decrypt(char*, char*);

void encrypt_file(char*, char*, int);
void decrypt_file(char*, char*, int);

//1st argument - program name
int main(int argc, char *argv[]){

    switch (argc){
        case 1:
            printf("Error! Not enough arguments! Try using --help.\n");
            break;
        case 2:
            if (!strcmp(argv[1], "--help")) help(argv[0]);
            else printf("Error wrong argument! Try using --help.\n");
            break;
        case 3:
            printf("Error! Not enough arguments! Try using --help.\n");
            break;
        case 4:
            if (!strcmp(argv[1], "-d")) decrypt(argv[2], argv[3]);
            else encrypt(argv[2], argv[3]);
            break;
        case 5:
            if (!strcmp(argv[3], "-f")) {
                if (!strcmp(argv[1], "-d")) decrypt_file(argv[3], argv[4], false);
                else encrypt_file(argv[3], argv[4], true);
            } else {
                if (!strcmp(argv[1], "-d")) decrypt_file(argv[3], argv[4], false);
                else encrypt_file(argv[3], argv[4], true);
            }
        break;
    }


    return 0;
}

void help(char *program_name){
    printf("Type %s followed by 1 or 2 flags with text or filepath.\n",program_name);
    printf("Flags: -e to encrypt, -d to decrypt, type key number(+/-3) and -f to specify the /path/to/the/file\n");
    printf("If -f flag specified you can save result directly in file you working on by changing flag to -fs.\n");
    printf("Also you can use pipe > to store result in file.\n");
    printf("Example: %s -e 3 Hello world!\t Result: %s\n", program_name, "TODO");
}

void encrypt(char *_key, char *text){
    int key = atoi(_key);
    char *p = text;
    while((*p) != '\0'){
        *(p++) += key;
    }
    printf("%s\n", text);
}

void decrypt(char *_key, char *text){
    int key = atoi(_key);
    char *p = text;
    while((*p) != '\0'){
        *(p++) -= key;
    }
    printf("%s\n", text);
}

void encrypt_file(char *_key, char *file_path, int override){}
void decrypt_file(char *_key, char *file_path, int override){}