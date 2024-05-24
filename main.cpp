#include <stdio.h>

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
  printf("Todo");
}
void start_new_line() {
  printf("Todo");
}
void save() {
  printf("Todo");
}
void load() {
  printf("Todo");
}
void print_text() {
  printf("Todo");
}
void Insert_at_certain_position() {
  printf("Todo");
}
void search() {
  printf("Todo");
}
void clear() {
  printf("Todo");
}

int main( ) {

  int command = 0;

  while (1) {
    print_help( );
    printf("Chose the comand");
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
    }
  }
}

