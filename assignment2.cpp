#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
using namespace std;

struct Erow { // структура для зберігання рядків
    int size; // довжина рядка
    char* chars; // вказівник на символи рядка
};


class Editor {
    Erow* text = nullptr; // вказівник на рядки
    int numrows = 0; // кількість рядків
    char *copied_text = nullptr;

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
        cout << "10 - cut \n";
        cout << "11 - copy \n";
        cout << "12 - paste \n";
        cout << "13 - Insert with replacment \n";

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
        if (found != NULL) {
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
    void delet() {
        int row, pos, len;
        cout << "Enter row number: ";
        cin >> row;
        if (row < 1 || row > numrows) {
            cout << "Invalid row number\n";
            return;
        }
        cout << "Enter position: ";
        cin >> pos;
        if (pos < 0 || pos > text[row - 1].size) {
            cout << "Invalid position\n";
            return;
        }
        cout << "Enter length: ";
        cin >> len;
        getchar();
        if (pos + len > text[row - 1].size) {
            cout << "Invalid length\n";
            return;
        }
        Erow* curent_row = &text[row - 1];
        size_t remaining_chars = curent_row->size - pos - len + 1;
        memmove(curent_row->chars + pos, curent_row->chars + pos + len, remaining_chars + 1);
        curent_row->size -= len;
        curent_row->chars = (char*)realloc(curent_row->chars, curent_row->size + 1);
        curent_row->chars[curent_row->size] = '\0';
    }
    void cut() {
        int row, pos, len;
        cout << "Enter row number: ";
        cin >> row;
        if (row < 1 || row > numrows) {
            cout << "Invalid row number\n";
            return;
        }
        cout << "Enter position: ";
        cin >> pos;
        if (pos < 0 || pos > text[row - 1].size) {
            cout << "Invalid position\n";
            return;
        }
        cout << "Enter number of symbols you whant to delete: ";
        cin >> len;
        getchar();
        if (pos + len > text[row - 1].size) {
            cout << "Invalid length\n";
            return;
        }

        Erow* curent_row = &text[row - 1];

        delete[] copied_text;
        copied_text = new char[len + 1];
        strncpy(copied_text, curent_row->chars + pos, len);
        copied_text[len] = '\0';

        size_t remaining_chars = curent_row->size - pos - len;// кількість символів, які залишились після видалення
        memmove(curent_row->chars + pos, curent_row->chars + pos + len, remaining_chars + 1);
        curent_row->size -= len; // оновлення розміру рядка
        curent_row->chars = (char*)realloc(curent_row->chars, curent_row->size + 1);
        curent_row->chars[curent_row->size] = '\0';

        cout << "Text cut: " << copied_text << endl;
    }
    void copy() {
        int row, pos, len;
        cout << "Enter row number: ";
        cin >> row;
        if (row < 1 || row > numrows) {
            cout << "Invalid row number\n";
            return;
        }
        cout << "Enter position: ";
        cin >> pos;
        if (pos < 0 || pos > text[row - 1].size) {
            cout << "Invalid position\n";
            return;
        }
        cout << "Enter number of symbols you whant to copy: ";
        cin >> len;
        getchar();
        if (pos + len > text[row - 1].size) {
            cout << "Invalid length\n";
            return;
        }
        Erow* current_row = &text[row - 1];

        delete[] copied_text;
        copied_text = new char[len + 1];
        strncpy(copied_text, current_row->chars + pos - 1, len);
        copied_text[len] = '\0';

        cout << "Text copied: " << copied_text << endl;
    }
    void paste( ) {
        if (copied_text == nullptr){
            cout << "Nothing to paste\n";
            return;
        }
        int row, pos;
        cout << "Enter row number: ";
        cin >> row;
        if (row < 1 || row > numrows) {
            cout << "Invalid row number\n";
            return;
        }
        cout << "Enter position: ";
        cin >> pos;
        if (pos < 0 || pos > text[row - 1].size) {
            cout << "Invalid position\n";
            return;
        }
        Erow* curent_row = &text[row - 1];
        int n_size = curent_row->size + strlen(copied_text);
        curent_row->chars = (char*)realloc(curent_row->chars, n_size + 1);

        memmove(curent_row->chars + pos - 1 + strlen(copied_text), curent_row->chars + pos - 1, curent_row->size - pos + 1);
        memcpy(curent_row->chars + pos - 1, copied_text, strlen(copied_text));
        curent_row->size = n_size;
        curent_row->chars[curent_row->size] = '\0';
    }

    void insert_with_replacment() {
        int row, pos;
        cout << "Enter line number: ";
        cin >> row;
        if (row < 1 || row > numrows) {
            cout << "Invalid row number\n";
            return;
        }
        cout << "Enter index: ";
        cin >> pos;
        getchar();
        if (pos < 0 || pos > text[row - 1].size) {
            cout << "Invalid position\n";
            return;
        }
        cout << "Enter text to insert: ";
        char buffer[1024];
        cin.getline(buffer, 1024);
        buffer[strcspn(buffer, "\n")] = '\0';

        Erow* current_row = &text[row - 1]; // вказівник на поточний рядок
        int buffer_len = strlen(buffer);// довжина тексту для вставки

        int new_size = pos - 1 + buffer_len + (current_row->size - pos);
        char* new_chars = new char[new_size + 1];
        memcpy(new_chars, current_row->chars, pos - 1); // копіювання тексту до позиції вставки
        memcpy(new_chars + pos - 1, buffer, buffer_len); // копіювання тексту для вставки
        // копіювання тексту після позиції вставки
        if (pos - 1 + buffer_len < current_row->size) {
            memcpy(new_chars + pos - 1 + buffer_len, current_row->chars + pos - 1 + buffer_len, current_row->size - pos + 1);
        }

        new_chars[new_size] = '\0';

        delete[] current_row->chars;
        current_row->chars = new_chars;
        current_row->size = new_size;

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
            case 9:
                editor.delet();
            break;
            case 10:
                editor.cut();
            break;
            case 11:
                editor.copy();
            break;
            case 12:
                editor.paste();
            break;
            case 13:
                editor.insert_with_replacment();
            break;
            default:
                cout << "Please, enter the valid command: \n";
            break;
        }
    }
}