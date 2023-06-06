#ifndef MAIN_H
#define MAIN_H

#define MAX_BOOKS 100
#define MAX_READERS 100
#define MAX_CHAR 40
#define HISTORY_SIZE 10
#define DATA_FILE "bin/data.bin"
#define BOOK_FILE "bin/books.bin"
#define READER_FILE "bin/readers.bin"

#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BBLU "\e[1;34m"
#define COLOR_RESET "\e[0m"

struct date
{
    uint8_t day, month;
    uint16_t year;
};

typedef struct
{
    int8_t title[MAX_CHAR];
    int8_t author[MAX_CHAR];
    int8_t editor[MAX_CHAR];
    uint8_t who_requested; // Assim que requisitado, guarda o index do leitor.
    uint8_t was_requested; // Assim que requisitado uma única vez, permanecerá com valor positivo permanentemente
    uint8_t avail;         // 1-Requisitado 2-Disponível 3-Danificado
    uint64_t isbn;         // Numero 13 dígitos
    struct date rd;
} book_t;
book_t *book;

typedef struct
{
    int8_t name[MAX_CHAR];
    int8_t address[MAX_CHAR];
    int8_t email[MAX_CHAR];
    uint8_t num_requests[MAX_BOOKS]; // Vetor que guarda os livros que o utilizador X requista no momento. Ex: num_requests[4] = {1,0,1,0} significa que o utilizador requisitou o livro 0 e 2
    int16_t history[HISTORY_SIZE];   // Vetor que guarda o histórico de livros requisitados pelo utilizador X
    uint32_t reader_code;
    uint32_t phone_number;
    struct date bd;
} reader_t;
reader_t *reader;

bool read_files = false;
bool save_files = false;
bool start_program = false;
bool end_program = false;
uint8_t num_books = 0;
uint8_t num_readers = 0;
uint8_t num_active_requests = 0;
const uint8_t months_common_year[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const uint8_t months_leap_year[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void book_list();
void pause_exec();
void return_book();
void reader_list();
void all_requests();
void request_book();
void user_history();
uint64_t type_int();
void generate_data();
void null_all_data();
void register_book();
void register_reader();
void submenu_exit(char);
void submenu_listing(char);
int8_t read_keyboard_char();
uint8_t read_keyboard_dec();
uint16_t count_days(uint8_t i);
void type_string(char str[MAX_CHAR]);
uint8_t constrain(uint8_t var, uint8_t min, uint8_t max);
book_t *book_read_data(int8_t *filename, uint8_t *total);
reader_t *reader_read_data(int8_t *filename, uint8_t *total);
void constrain_date(uint8_t *day, uint8_t *month, uint16_t year);
bool book_write_data(int8_t *filename, book_t *data, uint8_t total);
bool reader_write_data(int8_t *filename, reader_t *data, uint8_t total);
void split_phone_number(uint8_t i, uint16_t *split_1, uint16_t *split_2, uint16_t *split_3);

#endif