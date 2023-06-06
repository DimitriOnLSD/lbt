/// @brief Registar livro
void register_book()
{
    system("cls");
    printf("---| Registar Livro |---\n");
    if (num_books == MAX_BOOKS)
        printf("\nO limite de livros foi atingido.\n");
    else
    {
        bool isbn_exists = false;
        uint8_t i = num_books;
        uint64_t comparator;
        printf("\nISBN: ");
        comparator = type_int();
        if (!comparator) // Caso o utilizador escreva 0, volta ao menu
            return;
        for (uint8_t k = 0; k < MAX_BOOKS; k++)
            if (book[k].isbn == comparator)
                isbn_exists = true;
        if (isbn_exists)
            printf("\nEste ISBN ja existe.");
        else
        {
            printf("Titulo: ");
            type_string(book[i].title);
            printf("Autor: ");
            type_string(book[i].author);
            printf("Editora: ");
            type_string(book[i].editor);
            printf("\nO livro foi registado com sucesso!");
            book[i].isbn = comparator;
            book[i].avail = 2;
            num_books++;
        }
    }
    pause_exec();
}

/// @brief Registar leitor
void register_reader()
{
    system("cls");
    printf("---| Registar Leitor |---\n");
    if (num_readers == MAX_READERS)
        printf("O limite de leitores foi atingido.\n");
    else
    {
        bool reader_code_exists = false;
        uint8_t i = num_readers;
        uint32_t comparator;
        printf("\nCodigo de leitor: ");
        comparator = type_int();
        if (!comparator)
            return;
        for (uint8_t k = 0; k < MAX_READERS; k++)
            if (reader[k].reader_code == comparator)
                reader_code_exists = true;
        if (reader_code_exists)
            printf("\nEste leitor ja se encontra registado.");
        else
        {
            printf("Nome: ");
            type_string(reader[i].name);
            printf("Data de nascimento [dd mm aaaa]: ");
            fflush(stdin);
            scanf(" %u", &reader[i].bd.day);
            scanf(" %u", &reader[i].bd.month);
            scanf(" %u", &reader[i].bd.year);
            constrain_date(&reader[i].bd.day, &reader[i].bd.month, reader[i].bd.year);
            printf("Localidade: ");
            type_string(reader[i].address);
            printf("Contacto telefonico: ");
            reader[i].phone_number = type_int();
            printf("E-mail: ");
            type_string(reader[i].email);
            printf("\nO leitor foi registado com sucesso!");
            memset(reader[i].num_requests, 0, sizeof(reader->num_requests));
            reader[i].reader_code = comparator;
            num_readers++;
        }
    }
    pause_exec();
}

/// @brief Requisitar livro
void request_book()
{
    uint32_t comparator;
    bool cant_request = true;
    bool reader_found = false;
    system("cls");
    printf("---| Requisitar Livro |---\n");
    for (uint8_t i = 0; i < MAX_BOOKS; i++)
        if (book[i].avail == 2)
            cant_request = false;
    if (cant_request)
        printf("\nJa nao existem livros para serem requisitados.\n");
    else
    {
        uint8_t x[MAX_BOOKS] = {0};
        uint8_t n = 0, max = 0;
        printf("\nCodigo de leitor: ");
        comparator = type_int();
        if (!comparator)
            return;
        for (uint8_t i = 0; i < MAX_READERS; i++)
            if (reader[i].reader_code == comparator)
            {
                reader_found = true;
                printf("\n[0] Voltar");
                for (uint8_t k = 0; k < MAX_BOOKS; k++)
                    if (book[k].avail == 2) // verificar se livro está disponível
                    {
                        x[n] = k; // guardar no vetor "x" de index "n" o respetivo livro
                        n++;      // incrementar a unidade de livros
                        printf("\n[%d] %s (ISBN: %lld)", n, book[k].title, book[k].isbn);
                    }
                printf("\n\nQual e o livro que pretende requisitar: ");
                max = n; // guardar o máximo valor de n
                n = type_int();
                if (!n)
                    return;
                n = constrain(n, 1, max);
                n--; // decrementar o n por 1, pois este foi incrementado por 1 no for loop acima
                printf("Data de requisicao [dd mm aaaa]: ");
                fflush(stdin);
                scanf(" %u", &book[x[n]].rd.day);
                scanf(" %u", &book[x[n]].rd.month);
                scanf(" %u", &book[x[n]].rd.year);
                constrain_date(&book[x[n]].rd.day, &book[x[n]].rd.month, book[x[n]].rd.year);
                printf("\n%s de %s foi requisitado!\n",
                       book[x[n]].title, book[x[n]].author);
                reader[i].num_requests[x[n]] = 1; // guarda em "num_requests" o livro como index, e atribui o valor de 1
                for (uint8_t index = 9; index > 0; index--)
                    reader[i].history[index] = reader[i].history[index - 1]; // deslocar elementos do vetor para a direita de modo a preencher o novo valor em index 0
                reader[i].history[0] = x[n];                                 // atribui no index 0 o livro que foi requisitado
                book[x[n]].avail = 1;                                        // valor de 1 significado que está requisitado
                book[x[n]].who_requested = i;                                // guarda quem requisitou o livro (neste caso, o index do leitor)
                book[x[n]].was_requested = 1;                                // atribui valor de 1 devido a ser requisitado uma única vez
                num_active_requests++;
            }
        if (!reader_found)
            printf("Este leitor nao existe.\n");
    }
    pause_exec();
}

/// @brief Devolver livro
void return_book()
{
    uint32_t comparator;
    bool cant_return = true;
    bool reader_found = false;
    system("cls");
    printf("---| Devolver Livro |---\n");
    for (uint8_t i = 0; i < MAX_READERS; i++)
        if (reader[i].reader_code)
            cant_return = false;
    if (cant_return)
        printf("\nNao existem leitores.\n");
    else
        do
        {
            printf("\nCodigo de leitor: ");
            comparator = type_int();
            if (!comparator)
                return;
            for (uint8_t i = 0; i < MAX_READERS; i++)
                if (reader[i].reader_code == comparator)
                {
                    uint8_t x[MAX_BOOKS] = {0};
                    uint8_t n = 0, max = 0;
                    reader_found = true;
                    printf("\nEstes sao os livros que se encontram requisitados:\n");
                    for (uint8_t k = 0; k < MAX_BOOKS; k++)
                        if (reader[i].num_requests[k])
                        {
                            n++;
                            x[n - 1] = k;
                            printf("\n[%d] %s (ISBN: %lld)", n, book[k].title, book[k].isbn);
                        }
                    printf("\n\n%d livros encontrados.", n);
                    if (n)
                    {
                        printf("\n\nQual e o livro que pretende devolver: ");
                        max = n;
                        n = type_int();
                        n = constrain(n, 1, max);
                        n--;
                        printf("O livro encontra-se danificado? [S/N] ");
                        int8_t op = read_keyboard_char();
                        if (toupper(op) == 'S')
                            book[x[n]].avail = 3;
                        else
                            book[x[n]].avail = 2;
                        reader[i].num_requests[x[n]] = 0;
                        book[x[n]].who_requested = 0;
                        num_active_requests--;
                        printf("\n%s de %s foi devolvido apos %d dias.\n",
                               book[x[n]].title, book[x[n]].author, count_days(x[n]));
                    }
                    else
                        printf("\nO leitor %ld nao tem nenhuma requisicao.\n", reader[i].reader_code);
                }
            if (!reader_found)
                printf("Este leitor nao existe.\n");
        } while (!reader_found);
    pause_exec();
}

/// @brief Display do submenu da opção "listagem"
/// @param op
void submenu_listing(char op)
{
    switch (op)
    {
    case '0':
        break;
    case '1':
        book_list();
        break;
    case '2':
        reader_list();
        break;
    case '3':
        all_requests();
        break;
    case '4':
        user_history();
        break;
    default:
        printf(BRED "\n\nA opcao escolhida nao existe no menu.\n" COLOR_RESET);
    }
}

/// @brief Display do submenu da opção "Sair"
/// @param op
void submenu_exit(char op)
{
    switch (op)
    {
    case '0':
        break;
    case '1':
        end_program = true;
        save_files = true;
        break;
    case '2':
        end_program = true;
        save_files = false;
        break;
    default:
        printf(BRED "\n\nA opcao escolhida nao existe no menu.\n" COLOR_RESET);
    }
}

/// @brief Display de todos os livros e os seus respetivos dados
void book_list()
{
    bool book_exist = false;
    system("cls");
    printf("---| Lista de Livros |---\n");
    for (uint8_t i = 0; i < MAX_BOOKS; i++)
        if (book[i].isbn)
        {
            uint8_t k = book[i].who_requested;
            printf("\nISBN:    %lld", book[i].isbn);
            printf("\nTitulo:  %s", book[i].title);
            printf("\nAutor:   %s", book[i].author);
            printf("\nEditora: %s", book[i].editor);
            printf("\nEstado:  ");
            switch (book[i].avail)
            {
            case 1:
                printf(BBLU "Requisitado" COLOR_RESET
                            " por %s (%ld) a %02d/%02d/%04d",
                       reader[k].name, reader[k].reader_code,
                       book[i].rd.day, book[i].rd.month, book[i].rd.year);
                break;
            case 2:
                printf(BGRN "Disponivel" COLOR_RESET);
                break;
            default:
                printf(BRED "Danificado" COLOR_RESET);
            }
            printf("\n_______________________\n");
            book_exist = true;
        }
    if (!book_exist)
        printf("\nNao existem livros.\n");
    pause_exec();
}

/// @brief Display de todos os leitores e os seus respetivos dados
void reader_list()
{
    uint8_t total_requests_by_user = 0;
    uint16_t s1, s2, s3;
    bool reader_exist = false;
    system("cls");
    printf("---| Lista de Leitores |---\n");
    for (uint8_t i = 0; i < MAX_READERS; i++)
    {
        if (reader[i].reader_code)
        {
            printf("\nCodigo de leitor:             %ld ", reader[i].reader_code);
            for (uint8_t k = 0; k < MAX_BOOKS; k++)
                total_requests_by_user += reader[i].num_requests[k];
            printf("\nNumero de requisicoes ativas: %d ", total_requests_by_user);
            total_requests_by_user = 0; /* Colocar a 0 para o próximo user */
            printf("\nNome:                         %s ", reader[i].name);
            printf("\nData de nascimento:           %02d/%02d/%04d",
                   reader[i].bd.day, reader[i].bd.month, reader[i].bd.year);
            printf("\nLocalidade:                   %s", reader[i].address);
            split_phone_number(i, &s1, &s2, &s3);
            printf("\nNumero de telefone:           %03d %03d %03d", s1, s2, s3);
            printf("\nE-mail:                       %s", reader[i].email);
            printf("\n_______________________________________\n");
            reader_exist = true;
        }
    }
    if (!reader_exist)
        printf("\nNao existem leitores.\n");
    pause_exec();
}

/// @brief Display de todas as requisições efetuadas
void all_requests()
{
    uint8_t counter = 0;
    bool found_book = false;
    system("cls");
    printf("---| Total de livros requisitados |---\n");
    for (uint8_t i = 0; i < MAX_BOOKS; i++)
        if (book[i].was_requested)
        {
            found_book = true;
            counter++;
            printf("\nISBN:    %lld", book[i].isbn);
            printf("\nTitulo:  %s", book[i].title);
            printf("\nAutor:   %s", book[i].author);
            printf("\nEditora: %s", book[i].editor);
            printf("\n_______________________\n");
        }
    printf("\n%d livros encontrados.", counter);
    if (!found_book)
        printf("\nNenhum livro foi requisitado.\n");
    pause_exec();
}

/// @brief Display das últimas 10 requisições efetuadas por um leitor
void user_history()
{
    uint32_t comparator;
    bool never_requested = true;
    bool reader_found = false;
    system("cls");
    printf("---| Historico de utilizador |---\n");
    do
    {
        printf("\nCodigo de leitor: ");
        comparator = type_int();
        if (!comparator)
            return;
        for (uint8_t i = 0; i < MAX_READERS; i++)
            if (reader[i].reader_code == comparator)
            {
                reader_found = true;
                printf("\nEstes sao os ultimos 10 livros requisitados por este utilizador:\n");
                for (uint8_t k = 0; k < HISTORY_SIZE; k++)
                {
                    printf("Livro %d:\n", k + 1);
                    if (reader[i].history[k] == -1)
                    {
                        printf("\nISBN:    -");
                        printf("\nTitulo:  -");
                        printf("\nAutor:   -");
                        printf("\nEditora: -");
                        printf("\n_______________________\n");
                    }
                    else
                    {
                        uint8_t n = reader[i].history[k];
                        printf("\nISBN:    %lld", book[n].isbn);
                        printf("\nTitulo:  %s", book[n].title);
                        printf("\nAutor:   %s", book[n].author);
                        printf("\nEditora: %s", book[n].editor);
                        printf("\n_______________________\n");
                    }
                }
            }
        if (!reader_found)
            printf("Este leitor nao existe.\n");
    } while (!reader_found);
    pause_exec();
}

/// @brief Pausa o programa ao esperar dados no buffer para que o utilizador possa ler o display
void pause_exec()
{
    printf("\nPressione qualquer tecla para continuar...");
    _getch();
}

/// @brief Atribui valor 0 a todas as variáveis do tipo inteiro e "N/A" a todas as variáveis do tipo string
void null_all_data()
{
    for (uint8_t i = 0; i < MAX_BOOKS; i++)
    {
        strcpy(book[i].title, "");
        strcpy(book[i].author, "");
        strcpy(book[i].editor, "");
        book[i].was_requested = 0;
        book[i].who_requested = 0;
        book[i].avail = 0;
        book[i].isbn = 0;
        book[i].rd.day = 1;
        book[i].rd.month = 1;
        book[i].rd.year = 1850;
    }
    for (uint8_t i = 0; i < MAX_READERS; i++)
    {
        strcpy(reader[i].name, "");
        strcpy(reader[i].address, "");
        strcpy(reader[i].email, "");
        memset(reader[i].num_requests, 0, sizeof(reader->num_requests));
        memset(reader[i].history, -1, sizeof(reader->history));
        reader[i].reader_code = 0;
        reader[i].phone_number = 0;
        reader[i].bd.day = 1;
        reader[i].bd.month = 1;
        reader[i].bd.year = 1850;
    }
}

/// @brief Usa a data atual do computador e recebe o index da estrutura livros, para calcular o numero de dias entre duas datas
/// @param i
/// @return Devolve o número de dias após devolver um livro
uint16_t count_days(uint8_t i)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    uint16_t current_year = tm.tm_year + 1900;
    uint8_t current_month = tm.tm_mon + 1;
    uint8_t current_day = tm.tm_mday;

    uint16_t num_leap_years = current_year / 4;
    uint16_t num_common_years = current_year - num_leap_years;
    uint32_t total_days = (num_leap_years * 366) + (num_common_years * 365);

    if (current_year % 4 == 0)
        for (uint8_t k = 1; k < current_month; k++)
            total_days += months_leap_year[k - 1];
    else
        for (uint8_t k = 1; k < current_month; k++)
            total_days += months_common_year[k - 1];
    total_days += current_day;
    uint32_t hold_days = total_days;

    num_leap_years = book[i].rd.year / 4;
    num_common_years = book[i].rd.year - num_leap_years;
    total_days = (num_leap_years * 366) + (num_common_years * 365);

    if (book[i].rd.year % 4 == 0)
        for (uint8_t k = 1; k < book[i].rd.month; k++)
            total_days += months_leap_year[k - 1];
    else
        for (uint8_t k = 1; k < book[i].rd.month; k++)
            total_days += months_common_year[k - 1];
    total_days += book[i].rd.day;

    return hold_days - total_days;
}

/// @brief Divide o número de telemóvel em 3 grupos para facilitar a visualização
/// @param i
/// @param split_1
/// @param split_2
/// @param split_3
void split_phone_number(uint8_t i, uint16_t *split_1, uint16_t *split_2, uint16_t *split_3)
{
    *split_1 = reader[i].phone_number / 1000000;                                            // Exemplo: 123456789 => 123
    *split_2 = (uint32_t)(reader[i].phone_number - (*split_1 * 1000000)) / 1000;            // Exemplo: 123456789 => 456
    *split_3 = (uint32_t)reader[i].phone_number - ((reader[i].phone_number / 1000) * 1000); // Exemplo: 123456789 => 789
}

/// @brief Impede a inserção de dados incorretos na data
/// @param day
/// @param month
/// @param year
void constrain_date(uint8_t *day, uint8_t *month, uint16_t year)
{
    *month = constrain(*month, 1, 12);

    if (year % 4 == 0 && *day > months_leap_year[*month - 1])
        *day = months_leap_year[*month - 1];
    else if (*day > months_common_year[*month - 1])
        *day = months_common_year[*month - 1];
}

/// @brief Recebe variável e limita entre min e max
/// @param var
/// @param min
/// @param max
/// @return Devolve um valor parametrizado entre min e max
uint8_t constrain(uint8_t var, uint8_t min, uint8_t max)
{
    if (var > max)
        var = max;
    if (var < min)
        var = min;
    return var;
}

/// @brief Lê o buffer do teclado e guarda em modo string
/// @param str
void type_string(char str[MAX_CHAR])
{
    fflush(stdin);
    gets(str);
}

/// @brief Lê o buffer do teclado e guarda como inteiro
/// @return Devolve inteiro de 64 bits
uint64_t type_int()
{
    uint64_t num;
    fflush(stdin);
    scanf(" %lld", &num);
    return num;
}

/// @brief Ler o buffer do teclado
/// @return Devolve um inteiro em formato caracter
uint8_t read_keyboard_dec()
{
    uint8_t data;
    do
    {
        fflush(stdin);
        data = _getch();
    } while (!(isdigit(data)));
    return data;
}

/// @brief Ler o buffer do teclado
/// @return Devolve um caracter
int8_t read_keyboard_char()
{
    int8_t data;
    do
    {
        fflush(stdin);
        data = _getch();
    } while (!(isalpha(data)));
    return data;
}

/// @brief Escreve dados das estruturas para o ficheiro dos livros
/// @param filename É o ficheiro a guardar
/// @param data É o tamanho total da estrutura como vetor
/// @param total É a quantidade de estruturas [índice]
/// @return Devolve o sucesso ou insucesso das funções realizadas
bool book_write_data(int8_t *filename, book_t *data, uint8_t total)
{
    FILE *fptr;
    fptr = fopen(filename, "wb"); // Guardar em binário

    if (fptr == NULL) // A função fopen devolve um ponteiro que é guardado em fptr. Caso fptr == NULL, existe um problema, logo devolve insucesso
        return false;

    if (fwrite(&total, sizeof(int), 1, fptr) != 1) // Escrever a quantidade de estruturas primeiro
        return false;

    if (fwrite(data, sizeof(book_t), total, fptr) != total) // Escrever no ficheiro dados completos. Caso o número de escritas não corresponder á quantidade de estruturas, devolve um erro
        return false;

    if (fclose(fptr) == EOF) // Fechar o ficheiro. Caso não consiga fechar, este devolve EOF (End of File). Devolve insucesso nesse caso
        return false;

    return true;
}

/// @brief Lê dados das estruturas do ficheiro dos livros
/// @param filename É o ficheiro a ler
/// @param total Devolve como ponteiro o número de estruturas lidas
/// @return Devolve NULL em erros ou devolve os dados lidos do ficheiro
book_t *book_read_data(int8_t *filename, uint8_t *total)
{
    FILE *fptr;
    fptr = fopen(filename, "rb"); // Ler em binário

    if (fptr == NULL)
        return NULL;

    if (fread(total, sizeof(int), 1, fptr) != 1) // Ler a quantidade de estruturas primeiro para usar a função malloc
        return NULL;

    book_t *data = malloc(sizeof(book_t) * *total); // Alocar dinâmicamente na memória o número de estruturas

    if (fread(data, sizeof(book_t), *total, fptr) != *total) // Guardar em data a quantidade de estruturas e os seus dados.
    {
        free(data); // Prevenir memory leak
        return NULL;
    }

    if (fclose(fptr) == EOF)
    {
        free(data);
        return NULL;
    }

    return data;
}

/// @brief Escreve dados das estruturas para o ficheiro dos leitores
/// @param filename É o ficheiro a guardar
/// @param data É o tamanho total da estrutura como vetor
/// @param total É a quantidade de estruturas [índice]
/// @return Devolve o sucesso ou insucesso das funções realizadas
bool reader_write_data(int8_t *filename, reader_t *data, uint8_t total)
{
    FILE *fptr;
    fptr = fopen(filename, "wb");

    if (fptr == NULL)
        return false;

    if (fwrite(&total, sizeof(int), 1, fptr) != 1)
        return false;

    if (fwrite(data, sizeof(reader_t), total, fptr) != total)
        return false;

    if (fclose(fptr) == EOF)
        return false;

    return true;
}

/// @brief Lê dados das estruturas do ficheiro dos leitores
/// @param filename É o ficheiro a ler
/// @param total Devolve como ponteiro o número de estruturas lidas
/// @return Devolve NULL em erros ou devolve os dados lidos do ficheiro
reader_t *reader_read_data(int8_t *filename, uint8_t *total)
{
    FILE *fptr;
    fptr = fopen(filename, "rb");

    if (fptr == NULL)
        return NULL;

    if (fread(total, sizeof(int), 1, fptr) != 1)
        return NULL;

    reader_t *data = malloc(sizeof(reader_t) * *total);

    if (fread(data, sizeof(reader_t), *total, fptr) != *total)
    {
        free(data);
        return NULL;
    }

    if (fclose(fptr) == EOF)
    {
        free(data);
        return NULL;
    }

    return data;
}