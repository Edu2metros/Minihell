#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"

char* read_user_input() {
  char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
  if (!buffer) {
    exit(EXIT_FAILURE);
  }

  int i = 0;
  char c;
  while ((c = getchar()) != EOF && c != '\n') {
    buffer[i++] = c;
  }
  buffer[i] = '\0';
  printf("%s\n", buffer);
  return buffer;
}

char** split_input_into_tokens(char* line) {
  int token_count = 0;
  char** tokens = malloc(sizeof(char*) * BUFFER_SIZE);
  if (!tokens) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  char* token = strtok(line, TOKEN_DELIMITERS);
  while (token) {
    tokens[token_count++] = token;
    token = strtok(NULL, TOKEN_DELIMITERS);
  }
  tokens[token_count] = NULL;
  return tokens;
}

void execute_command(char** tokens) {
  char command[BUFFER_SIZE] = "";
  for (int i = 0; tokens[i] != NULL; i++) {
    strcat(command, tokens[i]);
    strcat(command, " ");
  }
  system(command); // começar daqui, fazer os built in
}

int main(void) {
  while (1) {
    printf("Minishell $> ");
    char* line = read_user_input();
    char** tokens = split_input_into_tokens(line);
    execute_command(tokens);
    free(line);
    free(tokens);
  }

  return EXIT_SUCCESS;
}


/* mostrar o prompt
ler o comando de usuário
executar (???)


Parser -> interpretar o comando, por exemplo eu mando: echo 'Hello World' > output.txt 
Built-in -> comandos e funcionalidades já incorporados no sistema, --Váriavel de ambiente PATH--
*/