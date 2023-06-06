// Programação de Computadores I
// Paulo Oliveira Gomes de Sousa - 2222031 - 2222031@my.ipleiria.pt
// João José Ribeiro Domingos - 2222034 - 2222034@my.ipleiria.pt

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "src/main.h"
#include "src/functions.c"
#include "src/data.c"

uint8_t main(void)
{
    SetConsoleTitle("Programa de requisicao de livros v1.0.2"); /* Atribuir titulo à consola */
    book = malloc(sizeof(book_t) * MAX_BOOKS);                  /* Alocar dinâmicamente na memória o número de estruturas. */

    reader = malloc(sizeof(reader_t) * MAX_READERS);
    null_all_data();

    do
    {
        system("cls");
        printf("Opcoes de arranque:");
        printf("\n"
               "\n[1] Importar dados dos ficheiros"
               "\n[2] Gerar dados a partir da funcao"
               "\n[3] Dados nulos"
               "\n[0] Sair"
               "\n");

        switch (read_keyboard_dec())
        {
        default:
            printf(BRED "\n\nA opcao escolhida nao existe no menu.\n" COLOR_RESET);
            break;
        case '0':
            return 0;
            break;
        case '1':
            read_files = true;
            start_program = true;
            break;
        case '2':
            generate_data();
            start_program = true;
            break;
        case '3':
            start_program = true;
            break;
        }
    } while (!start_program);

    if (read_files)
    {
        uint8_t book_total = 0;
        uint8_t reader_total = 0;
        book_t *book_file_data; /* Criar temporariamente uma variável de estrutura */
        reader_t *reader_file_data;

        book_file_data = book_read_data(BOOK_FILE, &book_total);
        if (book_file_data == NULL)
            printf(BRED "\nErro ao ler o ficheiro 'books.bin'." COLOR_RESET);
        else
            printf(BGRN "\nFicheiro 'books.bin' lido com sucesso." COLOR_RESET);

        for (uint8_t i = 0; i < book_total; i++)
        {
            strcpy(book[i].title,          book_file_data[i].title);
            strcpy(book[i].author,         book_file_data[i].author);
            strcpy(book[i].editor,         book_file_data[i].editor);
                   book[i].isbn =          book_file_data[i].isbn;
                   book[i].avail =         book_file_data[i].avail;
                   book[i].was_requested = book_file_data[i].was_requested;
                   book[i].who_requested = book_file_data[i].who_requested;
                   book[i].rd.day =        book_file_data[i].rd.day;
                   book[i].rd.month =      book_file_data[i].rd.month;
                   book[i].rd.year =       book_file_data[i].rd.year;
        }
        free(book_file_data);

        reader_file_data = reader_read_data(READER_FILE, &reader_total);
        if (reader_file_data == NULL)
            printf(BRED "\nErro ao ler o ficheiro 'readers.bin'.\n" COLOR_RESET);
        else
            printf(BGRN "\nFicheiro 'readers.bin' lido com sucesso.\n" COLOR_RESET);

        for (uint8_t i = 0; i < reader_total; i++)
        {
            strcpy(reader[i].name,          reader_file_data[i].name);
            strcpy(reader[i].address,       reader_file_data[i].address);
            strcpy(reader[i].email,         reader_file_data[i].email);
            memcpy(reader[i].num_requests,  reader_file_data[i].num_requests, sizeof(reader_file_data[i].num_requests));
            memcpy(reader[i].history,       reader_file_data[i].history, sizeof(reader_file_data[i].history));
                   reader[i].reader_code =  reader_file_data[i].reader_code;
                   reader[i].phone_number = reader_file_data[i].phone_number;
                   reader[i].bd.day =       reader_file_data[i].bd.day;
                   reader[i].bd.month =     reader_file_data[i].bd.month;
                   reader[i].bd.year =      reader_file_data[i].bd.year;
        }
        free(reader_file_data);
        pause_exec();
    }

    /* Calcular quantidade de livros, leitores e requisições ativas */
    for (uint8_t i = 0; i < MAX_BOOKS; i++)
        if (book[i].isbn != 0)
            num_books++;
    for (uint8_t i = 0; i < MAX_READERS; i++)
        if (reader[i].reader_code != 0)
            num_readers++;
    for (uint8_t i = 0; i < MAX_READERS; i++)
        for (uint8_t k = 0; k < MAX_BOOKS; k++)
            num_active_requests += reader[i].num_requests[k];

    do
    {
        system("cls"); /* Limpar consola */
        printf("---| Gestao de Requisi\x87oes de uma Biblioteca |---\n");
        printf("\nTotal de livros:             %d/%d", num_books, MAX_BOOKS);
        printf("\nTotal de leitores:           %d", num_readers);
        printf("\nTotal de requisicoes ativas: %d", num_active_requests);
        printf("\n"
               "\n[1] Registar Livro"
               "\n[2] Registar Leitor"
               "\n[3] Requisitar Livro"
               "\n[4] Devolver Livro"
               "\n[5] Listagens"
               "\n[0] Sair"
               "\n");

        switch (read_keyboard_dec())
        {
        case '0': /* Sair*/
            system("cls");
            printf("---| Sair |---"
                   "\n"
                   "\n[1] Guardar e sair"
                   "\n[2] Sair sem guardar"
                   "\n[0] Voltar"
                   "\n");
            submenu_exit(read_keyboard_dec());
            break;
        case '1': /* Registar livro */
            register_book();
            break;
        case '2': /* Registar leitor */
            register_reader();
            break;
        case '3': /* Requisitar livro */
            request_book();
            break;
        case '4': /* Devolver livro */
            return_book();
            break;
        case '5': /* Lista (sub-menu) */
            system("cls");
            printf("---| Listagens |---"
                   "\n"
                   "\n[1] Lista de livros"
                   "\n[2] Lista de leitores"
                   "\n[3] Total de livros requisitados"
                   "\n[4] Historico de livros requisitados de um leitor"
                   "\n[0] Voltar"
                   "\n");
            submenu_listing(read_keyboard_dec());
            break;
        default:
            printf(BRED "\n\nA opcao escolhida nao existe no menu.\n" COLOR_RESET);
        }
    } while (!end_program);

    if (save_files)
    {
        if (book_write_data(BOOK_FILE, book, MAX_BOOKS))
            printf(BGRN "\nFicheiro 'books.bin' guardado com sucesso!" COLOR_RESET);
        else
            printf(BRED "\nErro ao guardar o ficheiro 'books.bin'." COLOR_RESET);
        free(book);

        if (reader_write_data(READER_FILE, reader, MAX_READERS))
            printf(BGRN "\nFicheiro 'readers.bin' guardado com sucesso!" COLOR_RESET);
        else
            printf(BRED "\nErro ao guardar o ficheiro 'readers.bin'.\n" COLOR_RESET);
        free(reader);

        pause_exec();
    }

    return 0;
}

/*
to do list:
no readers at return_book();
checker for isbn and reader code at setup. If found equal instance, remove struct[i].sub[k] with null_index_data(int i, int k);
checker for birth date at setup. if overflow (day: 32 or month: 13), override to 01/01

check digit at date scanf


# improve at code:
save to only one file
*/