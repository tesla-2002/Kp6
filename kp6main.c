#include "inout.h"
#include "passenger.h"
#include "search.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Введите:\n%s ./file_txt ./file_bin\n", argv[0]);
        exit(0);
	}

	FILE* filetxt = fopen(argv[1], "a+");
	FILE* filebin = fopen(argv[2], "a+");

	if (!filetxt || !filebin) {
		printf("Не удалось открыть один из файлов\n");
		exit(1);
	}
	
	int index = 0, size = 0;
	Passenger* pass = (Passenger*)malloc(sizeof(**pass));
	pass[index] = (Passenger)malloc(sizeof(**pass));
    while (passenger_read_bin(pass[index], filebin)) {
   		index++;
   		size++;
   		pass[index] = (Passenger)malloc(sizeof(**pass));
   		pass = (Passenger*)realloc(pass, (size+1) * sizeof(**pass));
    } 

    free(pass[index]);
    pass = (Passenger*)realloc(pass, size * sizeof(**pass));

    int flag = 0;
    while (1) {
    	printf("Что Вы хотите сделать?\n [1]-Вывести содержимое бинарного файла\n [2]-Добавить в текстовый файл\n\
 [3]-Добавить в бинарный файл\n [4]-Удалить из текстового файла\n [5]-Удалить из бинарного файла\n\
 [6]-Поиск пассажира по условию варианта\n [0]-Завершить\n");
    	scanf("%d", &flag);
    	switch(flag) {
    		case PRINT:
    			passenger_print(pass, size);
    			break;

    		case ADDTOTXT:
    			passenger_add_to_txt(filetxt);
    			break;

    		case ADDTOBIN:
    			passenger_add_to_bin(filebin);
    			break;

    		case DELETEFROMTXT:
    			char buffer[LEN_STR];
    			printf("Введите фамилию пассажира, которого нужно удалить из списка:\t");
    			scanf("%s", buffer);
    			passenger_delete_from_txt(argv[1], buffer, filetxt);
    			break;

			case DELETEFROMBIN:
				char buffer1[LEN_STR];
    			printf("Введите фамилию пассажира, которого нужно удалить из списка:\t");
    			scanf("%s", buffer1);
				passenger_delete_from_bin(argv[2], buffer1, filebin);
				break;

			case SEARCH:
				int ind = search_max(pass,size);
				if (ind!=-1) {
					printf("\nДа, такой пассажир есть: %s\t%s\n", pass[ind]->surname, pass[ind]->initials);
				} else {
					printf("\nТакого пассажира нет в списке.\n");
				}

				break;

			default:
				pass_free(pass,size);
				fclose(filetxt);
				fclose(filebin);
				return 0;
		}
    }
}