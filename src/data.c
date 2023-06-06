/* THIS FILE CONTAINS ONLY TEST DATA */

void generate_data()
{
       uint8_t i = 0;
       uint8_t k = 0;

       /*######### BOOK DATA GENERATOR ############*/

       strcpy(book[i].title,  "Pense Como um Filosofo");
       strcpy(book[i].author, "John Marshall");
       strcpy(book[i].editor, "Alma dos Livros");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9789899054745;
              book[i].avail         = 2;

       i++;

       strcpy(book[i].title,  "Livro do Desassossego");
       strcpy(book[i].author, "Fernando Pessoa");
       strcpy(book[i].editor, "Assirio & Alvim");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9789723717747;
              book[i].avail         = 2;

       i++;

       strcpy(book[i].title,  "Pai Rico, Pai Pobre");
       strcpy(book[i].author, "Robert T. Kiyosaki");
       strcpy(book[i].editor, "Alta books");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9788550801483;
              book[i].avail         = 2;

       i++;

       strcpy(book[i].title,  "O Jardim dos Animais com Alma");
       strcpy(book[i].author, "Jose Rodrigues dos Santos");
       strcpy(book[i].editor, "Gradiva");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9789897850929;
              book[i].avail         = 2;

       i++;

       strcpy(book[i].title,  "Almoco de Domingo");
       strcpy(book[i].author, "Jose Luis Peixoto");
       strcpy(book[i].editor, "Quetzal Editores");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9789897224607;
              book[i].avail         = 2;

       i++;

       strcpy(book[i].title,  "O Sonho");
       strcpy(book[i].author, "Nicholas Sparks");
       strcpy(book[i].editor, "Edicoes Asa");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9789892352008;
              book[i].avail         = 2;

       i++;

       strcpy(book[i].title,  "Durante a Queda Aprendi a Voar");
       strcpy(book[i].author, "Raul Minh'alma");
       strcpy(book[i].editor, "Manuscrito");
              book[i].was_requested = 0;
              book[i].who_requested = 0;
              book[i].isbn          = 9789898975683;
              book[i].avail         = 2;

       /*##########################################*/

       /*######### READER DATA GENERATOR ##########*/

       strcpy(reader[k].name,    "Paulo Sousa");
       strcpy(reader[k].address, "Torres Novas");
       strcpy(reader[k].email,   "2222031@my.ipleiria.pt");
       memset(reader[k].num_requests, 0, sizeof(reader->num_requests));
              reader[k].reader_code  = 2222031;
              reader[k].phone_number = 969096163;
              reader[k].bd.day       = 31;
              reader[k].bd.month     = 1;
              reader[k].bd.year      = 2000;

       k++;

       strcpy(reader[k].name,    "Joao Domingos");
       strcpy(reader[k].address, "Leiria");
       strcpy(reader[k].email,   "2222034@my.ipleiria.pt");
       memset(reader[k].num_requests, 0, sizeof(reader->num_requests));
              reader[k].reader_code  = 2222034;
              reader[k].phone_number = 967655031;
              reader[k].bd.day       = 6;
              reader[k].bd.month     = 8;
              reader[k].bd.year      = 2002;

       k++;

       strcpy(reader[k].name,    "Bernardo Santos");
       strcpy(reader[k].address, "Alcobaca");
       strcpy(reader[k].email,   "2222033@my.ipleiria.pt");
       memset(reader[k].num_requests, 0, sizeof(reader->num_requests));
              reader[k].reader_code  = 2222033;
              reader[k].phone_number = 911139898;
              reader[k].bd.day       = 29;
              reader[k].bd.month     = 6;
              reader[k].bd.year      = 2002;

       k++;

       strcpy(reader[k].name,    "Pedro Ferreira");
       strcpy(reader[k].address, "Torres Novas");
       strcpy(reader[k].email,   "2222035@my.ipleiria.pt");
       memset(reader[k].num_requests, 0, sizeof(reader->num_requests));
              reader[k].reader_code  = 2222035;
              reader[k].phone_number = 916849913;
              reader[k].bd.day       = 13;
              reader[k].bd.month     = 5;
              reader[k].bd.year      = 2001;

       /*##########################################*/
}
