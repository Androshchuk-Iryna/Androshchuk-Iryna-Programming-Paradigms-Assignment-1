// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
//
// typedef struct erow { // структура для зберігання рядків
//   int size; // довжина рядка
//   char* chars; // вказівник на символи рядка
// } erow;
//
// erow* text =NULL; // вказівник на рядки
// int numrows =0; // кількість рядків
//
// void print_help() {
//   printf("1 - Append text to the end \n");
//   printf("2 - Start a new line \n");
//   printf("3 - Save the information\n");
//   printf("4 - Loading from file \n");
//   printf("5 - Print the current text  \n");
//   printf("6 - Insert text at the certain position \n");
//   printf("7 - Text search \n");
//   printf("8 - Clear console \n");
// }
//
// void append_text() {
//   printf("Enter text to append: ");
//   char buffer[1024];
//   fgets(buffer, 1024, stdin);
//   char *newline_position = strchr(buffer, '\n');
//   if (newline_position != NULL) {
//     *newline_position = '\0'; // заміна '\n' на '\0'
//   }
// // перевірка на наявність рядків
//   if (text != NULL) {
//     text =(erow*)realloc(text, sizeof(erow));
//     text[0].size =0;
//     text[0].chars = NULL;
//     numrows++;
//   }
//
//   erow* current_row =&text[numrows -1]; // вказівник на поточний рядок
//   current_row->size +=strlen(buffer); // збільшення розміру рядка
//   current_row->chars = (char*)realloc(current_row->chars, current_row->size +1);
//   strcat(current_row -> chars,buffer);
// }
//
// void start_new_line() {
//   text = (erow*)realloc(text, sizeof(erow)* (numrows +1)); // виділення памʼяті для нового рядка
//   text[numrows].size = 0; // Iніціалізація нового рядка з нульовою довжиною
//   text[numrows].chars = (char*)malloc(1); // виділення 1 біта памʼяті для '\n'
//   text[numrows].chars[0] = '\0'; // встановлення '\0' в початок рядка
//   numrows++;
//   printf("New line is started.\n");
// }
//
// void save() {
//   printf("Enter file name to save:");
//   char filename[256];
//   fgets(filename, 256, stdin);
//   filename[strcspn(filename,"\n")] = '\0'; // заміна '\n' на '\0'
//
//   FILE* file;
//   file =fopen (filename, "w");
//   if (file == NULL) {
//     printf("Can not write to this file \n");
//     return;
//   }
//   for (int i = 0; i < numrows; i++) {
//     fprintf(file, "%.*s\n", text[i].size, text[i].chars);
//   }
//   fclose(file);
//   printf("Text saved to %s \n", filename);
//
// }
//
// void load() {
//   printf("Enter filename to load: ");
//   char filename[256];
//   fgets(filename, 256, stdin);
//   filename[strcspn(filename, "\n")] = '\0';
//
//   FILE* file = fopen(filename, "r");
//   if (file == NULL) {
//     printf("Could not open file for reading.\n");
//     return;
//   }
//
//   char buffer[1024];
//   while (fgets(buffer, 1024, file) != NULL) {
//     buffer[strcspn(buffer, "\n")] = '\0'; //заміна '\n' на '\0'
//     text = (erow*)realloc(text, sizeof(erow) * (numrows + 1)); // виділення памʼяті для нового рядка
//     text[numrows].size = strlen(buffer);
//     text[numrows].chars = (char*)malloc(text[numrows].size + 1); // виділення памʼяті для символів рядка
//     strcpy(text[numrows].chars, buffer); // копіювання з буфера до e
//     numrows++;
//   }
//
//   fclose(file);
//   printf("Text loaded from %s.\n", filename);
// }
//
// void print_text() {
//   for (int i =0; i < numrows; i++) {
//     printf("%s\n", text[i].chars);
//   }
// }
//
// void insert_at_certain_position() {
//   int line, pos;
//   printf("Enter line number: ");
//   scanf("%d", &line);
//   getchar();
//   if (line <= 0 || line > numrows) {
//     printf("Invalid line number.\n");
//     return;
//   }
//
//   printf("Enter position in line: ");
//   scanf("%d", &pos);
//   getchar();
//   if (pos < 0 || pos > text[line - 1].size) {
//     printf("Invalid position.\n");
//     return;
//   }
//
//   printf("Enter text to insert: ");
//   char buffer[1024];
//   fgets(buffer, 1024, stdin);
//   buffer[strcspn(buffer, "\n")] = '\0'; // заміна '\n' на '\0'
//
//   erow* curent_row = &text[line - 1]; // вказівник на поточний рядок
//   int n_size =curent_row ->size + strlen(buffer);   // обчислення нового розміру рядка
//   curent_row ->chars = (char*)realloc(curent_row->chars, n_size + 1); // виділення памʼяті для нового рядка
//   char *destination = curent_row->chars + pos-1;  // вказівник на позицію вставки
//   size_t remaining_chars = curent_row->size - pos+1;  // кількість символів, які залишились після позиції вставки
//   memmove(destination + strlen(buffer), destination, remaining_chars + 1);  // зсув символів вправо
//   memcpy(destination, buffer, strlen(buffer));  // копіювання текту у певне місце
//   curent_row->size = n_size; // оновлення розміру рядка
// }
//
// void search() {
//   printf("Enter text to search: ");
//   char buffer[1024];
//   fgets(buffer, 1024, stdin);
//   buffer[strcspn(buffer, "\n")] = '\0'; // заміна '\n' на '\0'
//
//   for (int i = 0; i < numrows; i++) {
//     char *pos = strstr(text[i].chars, buffer); // пошук підрядка
//     if (pos) {
//       int index = pos - text[i].chars; // обчислення позиції підрядка
//       printf("Found at the position %d %d: %s\n", i + 1, index + 1, text[i].chars); // виведення результату
//     }
//   }
// }
//
// void clear() {
//   for (int i =0; i <numrows; i++) {
//     free(text[i].chars);
//   }
//   free(text);
//   text = NULL;
//   numrows = 0;
//   printf("Console cleared \n");
// }
//
// int main() {
//   int command = 0;
//
//   while (true) {
//     printf(" If you need help print 0\n");
//     printf("Chose the command: ");
//     scanf("%d", &command);
//     getchar();
//
//     switch (command) {
//       case 1:
//         append_text();
//         break;
//       case 2:
//         start_new_line();
//         break;
//       case 3:
//         save();
//         break;
//       case 4:
//         load();
//         break;
//       case 5:
//         print_text();
//         break;
//       case 6:
//         insert_at_certain_position();
//         break;
//       case 7:
//         search();
//         break;
//       case 8:
//         clear();
//         break;
//       case 0:
//         print_help();
//         break;
//       default:
//         printf("Please, enter the valid command: \n");
//         break;
//     }
//   }
// }
