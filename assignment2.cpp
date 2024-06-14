#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct Erow { // структура для зберігання рядків
    int size; // довжина рядка
    char* chars; // вказівник на символи рядка
};


class Editor {
    Erow* text = nullptr; // вказівник на рядки
    int numrows = 0; // кількість рядків

public:
    void print_help() {
        cout << "1 - Append text to the end \n";
        cout << "2 - Start a new line \n";
        cout << "3 - Save the information\n";
        cout << "4 - Loading from file \n";
        cout << "5 - Print the current text  \n";
        cout << "6 - Insert text at the certain position \n";
        cout << "7 - Text search \n";
        cout << "8 - Clear console \n";
        cout << "9 - delet  \n";
        cout << "10 - undo \n";
        cout << "11 - redo \n";
        cout << "12 - cut \n";
        cout << "13 - copy \n";
        cout << "14 - paste \n";
        cout << "15 - Insert with replacment \n";

    }
    void append_text() {
        cout << "Enter text to append: ";
        char buffer[1024];
        cin.getline(buffer, 1024);
        char *newline_position = strchr(buffer, '\n');
        if (newline_position != nullptr) {
            *newline_position = '\0'; // заміна '\n' на '\0'
        }

        // Якщо text ще не існує, створити новий рядок
        if (text == nullptr) {
            text = (Erow*)malloc(sizeof(Erow));
            text[0].size = 0;
            text[0].chars = (char*)malloc(1);  // Алокуємо пам'ять для кінцевого '\0'
            text[0].chars[0] = '\0';  // Ініціалізуємо порожнім рядком
            numrows = 1;
        }

        // Додаємо текст до останнього рядка
        int current_row = numrows - 1;
        int new_size = text[current_row].size + strlen(buffer);

        text[current_row].chars = (char*)realloc(text[current_row].chars, new_size + 1);
        strcpy(text[current_row].chars + text[current_row].size, buffer);

        text[current_row].size = new_size;
    }
    void start_new_line() {
        text = (Erow*)realloc(text, sizeof(Erow)* (numrows +1)); // виділення памʼяті для нового рядка
        text[numrows].size = 0; // Iніціалізація нового рядка з нульовою довжиною
        text[numrows].chars = (char*)malloc(1); // виділення 1 біта памʼяті для '\n'
        text[numrows].chars[0] = '\0'; // встановлення '\0' в початок рядка
        numrows++;
        cout << "New line is started.\n";
    }
    void save(){
        cout << "Enter file name to save:";
        char filename[256];
        cin.getline(filename, 256);
        filename[strcspn(filename,"\n")] = '\0'; // заміна '\n' на '\0'

        FILE* file;
        file =fopen (filename, "w");
        if (file == NULL) {
            cout << "Error opening file\n";
            return;
        }

        for (int i = 0; i < numrows; i++) {
            fprintf(file, "%s\n", text[i].chars);
        }
        fclose(file);
    }
    void load() {
        cout << "Enter filename to load: ";
        char filename[256];
        cin.getline(filename, 256);

        FILE* file;
        file = fopen(filename, "r");
        if (file == NULL) {
            cout << "Error opening file\n";
            return;
        }

        char buffer[1024];
        while (fgets(buffer, 1024, file)) {
            char *newline_position = strchr(buffer, '\n');
            if (newline_position != NULL) {
                *newline_position = '\0'; // заміна '\n' на '\0'
            }

            text = (Erow*)realloc(text, sizeof(Erow)* (numrows +1)); // виділення памʼяті для нового рядка
            text[numrows].size = strlen(buffer); // Iніціалізація нового рядка з нульовою довжиною
            text[numrows].chars = (char*)malloc(text[numrows].size +1); // виділення 1 біта памʼяті для '\n'
            strcpy(text[numrows].chars, buffer);
            numrows++;
        }
        fclose(file);
    }
    void print_text() {
        for (int i = 0; i < numrows; i++) {
            cout << text[i].chars << endl;
        }
    }
    void insert_text() {
        int row, pos;
        cout << "Enter row number: ";
        cin >> row;
        cout << "Enter position: ";
        cin >> pos;
        getchar();
        if (row < 1 || row > numrows) {
            cout << "Invalid row number\n";
            return;
        }
        if (pos < 0 || pos > text[row - 1].size) {
            cout << "Invalid position\n";
            return;
        }
        cout << "Enter text to insert: ";
        char buffer[1024];
        cin.getline(buffer, 1024);
        buffer[strcspn(buffer, "\n")] = '\0';

        Erow* curent_row = &text[row - 1]; // вказівник на поточний рядок
        int n_size =curent_row ->size + strlen(buffer);   // обчислення нового розміру рядка
        curent_row ->chars = (char*)realloc(curent_row->chars, n_size + 1); // виділення памʼяті для нового рядка
        char *destination = curent_row->chars + pos-1;  // вказівник на позицію вставки
        size_t remaining_chars = curent_row->size - pos+1;  // кількість символів, які залишились після позиції вставки
        memmove(destination + strlen(buffer), destination, remaining_chars + 1);  // зсув символів вправо
        memcpy(destination, buffer, strlen(buffer));  // копіювання текту у певне місце
        curent_row->size = n_size;
        }

    void search_text() {
        cout << "Enter text to search: ";
        char buffer[1024];
        cin.getline(buffer, 1024);
        buffer[strcspn(buffer, "\n")] = '\0';

        bool found = false;
        for (int i = 0; i < numrows; i++) {
            char* pos = strstr(text[i].chars, buffer);
            while (pos != NULL) {
                cout << "Text found at line " << i + 1 << " position " << pos - text[i].chars + 1 << endl;
                found = true;
                pos = strstr(pos + 1, buffer);
            }
        }
        if (!found) {
            cout << "Text not found\n";
        }
    }
    void clear_console() {
        for (int i = 0; i <numrows; i++) {
            delete[] text[i].chars;
        }
        delete[] text;
        text = nullptr;
        numrows = 0;
        cout << "Console cleared\n";
    }
};


int main() {
    Editor editor;
    int command = 0;

    while (true) {
        printf(" If you need help print 0\n");
        printf("Chose the command: ");
        scanf("%d", &command);
        getchar();

        switch (command) {
            case 1:
                editor.append_text();
            break;
            case 2:
                editor.start_new_line();
            break;
            case 3:
                editor.save();
            break;
            case 4:
                editor.load();
            break;
            case 5:
                editor.print_text();
            break;
            case 6:
                editor.insert_text();
            break;
            case 7:
                editor.search_text();
            break;
            case 8:
                editor.clear_console();
            break;
            case 0:
                editor.print_help();
            break;
            default:
                cout << "Please, enter the valid command: \n";
            break;
        }
    }
}