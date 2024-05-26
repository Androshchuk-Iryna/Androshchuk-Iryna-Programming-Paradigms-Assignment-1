#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct erow {
  int size;
  char* chars;
} erow;

erow* text =NULL;
int numrows =0;

void print_help() {
  printf("1 - Append text to the end \n");
  printf("2 - Start a new line \n");
  printf("3 - Save the information\n");
  printf("4 - Loading from file \n");
  printf("5 - Print the current text  \n");
  printf("6 - Insert text at the certain position \n");
  printf("7 - Text search \n");
  printf("8 - Clear console \n");
}

void append_text() {
  printf("Enter text to append: ");
  char buffer[1024];
  fgets(buffer, 1024, stdin);
  char *newline_position = strchr(buffer, '\n');
  if (newline_position != NULL) {
    *newline_position = '\0';
  }

  if (!text) {
    text =(erow*)realloc(text, sizeof(erow));
    text[0].size =0;
    text[0].chars = NULL;
    numrows++;
  }

  erow* current_row =&text[numrows -1];
  current_row->size +=strlen(buffer);
  current_row->chars = (char*)realloc(current_row->chars, current_row->size +1);
  strcat(current_row -> chars,buffer);
}

void start_new_line() {
  text = (erow*)realloc(text, sizeof(erow)* (numrows +1));
  text[numrows].size = 0;
  text[numrows].chars = (char*)malloc(1); // виділення 1 біта памʼяті для '\n'
  text[numrows].chars[0] = '\0';
  numrows++;
  printf("New line is started.\n");
}

void save() {
  printf("Enter file name to save:");
  char filename[256];
  fgets(filename, 256, stdin);
  filename[strcspn(filename,"\n")] = '\0'; //replace \n with \0

  FILE* file;
  file =fopen (filename, "w");
  if (file == NULL) {
    printf("Can not write to this file \n");
    return;
  }
  for (int i = 0; i < numrows; i++) {
    fprintf(file, "%.*s\n", text[i].size, text[i].chars);
  }
  fclose(file);
  printf("Text saved to %s \n", filename);

}

void load() {
  printf("Todo");
}

void print_text() {
  for (int i =0; i < numrows; i++) {
    printf("%s\n", text[i].chars);
  }
}

void Insert_at_certain_position() {
  printf("Todo");
}

void search() {
  printf("Enter text to search: ");
  char buffer[1024];
  fgets(buffer, 1024, stdin);
  buffer[strcspn(buffer, "\n")] = '\0'; // Replace \n with \0

  for (int i = 0; i < numrows; i++) {
    char *pos = strstr(text[i].chars, buffer);
    if (pos) {
      int index = pos - text[i].chars;
      printf("Found at the position  %d  %d: %s\n", i + 1, index + 1, text[i].chars);
    }
  }
}

void clear() {
  for (int i =0; i <numrows; i++) {
    free(text[i].chars);
  }
  free(text);
  text = NULL;
  numrows = 0;
  printf("Console cleared\n");
}

int main() {
  int command = 0;

  while (true) {
    printf(" If you need help print 0\n");
    printf("Chose the command ");
    scanf("%d", &command);
    getchar();

    switch (command) {
      case 1:
        append_text();
        break;
      case 2:
        start_new_line();
        break;
      case 3:
        save();
        break;
      case 4:
        load();
        break;
      case 5:
        print_text();
        break;
      case 6:
        Insert_at_certain_position();
        break;
      case 7:
        search();
        break;
      case 8:
        clear();
        break;
      case 0:
        print_help();
        break;
      default:
        printf("Please, enter the command\n");
        break;
    }
  }
}

