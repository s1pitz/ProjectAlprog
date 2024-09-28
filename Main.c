#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define BKCSPC 8
#define ENTER 13
#define TAB 9

//komponen menu 
struct menu{
    int kode;
    char nama[51];
    int harga;
};

//loading
void loading(){
	int i;
	printf("Loading ");
	for(i=0; i<10; i++){
		printf(". ");
		sleep(1);
	}
}

//loading tapi ada system cls + print logo
void loadingClear(){
	system("cls");

	int i, j, c;

	for(i=0; i<3; i++){
		FILE *fptr = fopen("Logo.txt", "r"); //open file
		if(fptr == NULL){
		printf("Cannot open file \n");
        exit(0);
		}
	
		c = fgetc(fptr); //read contents from file
		while(c != EOF){
			printf ("%c", c);
        	c = fgetc(fptr);
		}
		fclose(fptr);
		for(i = 0; i < 92; i++){
			printf("%c", 254);
		}
		
		puts("\n\nPlease wait while we are processing your input");
		printf("Loading ");
		for(j=0; j<3; j++){
			sleep(1);
			printf(". ");
			sleep(1);
		}
		system("cls");
	}
}

//buat masukin data dari file HargaMenuScan
struct menu Menu[101];

//data pembelian
void adminData(int quantity[], int kode[], long long int total, int count){
	
	time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    
	int i;

	FILE *fptr = fopen("dataPembelian.txt", "a");
	
	for(i = 0; i < count; i++){
		if(i == count-1){
			fprintf(fptr, "%d-%d-%d-%d-%d-%lld-9999\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, quantity[i], kode[i], total);
		} else {
			fprintf(fptr, "%d-%d-%d-%d-%d-%lld-%d\n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, quantity[i], kode[i], total, i);
		}
	}
	
	fclose(fptr);

}

//buat print waktu
void waktu(){
	struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    printf("%s", asctime(ptr));
}

//buat masukkin menu baru
int adminInputMenu(int n){

	start:

	system("cls");

	int input, i;
	int temp;
	
	printf("Input number of new menu : ");
	scanf("%d", &input); getchar();

	char menu[input+1][1001];
	int price[input+1];

	printf("\n");
	
	if(input == 0){
		puts("No new menu added\n");
	}

	for(i=1; i<=input; i++){

		printf("Input name of menu : ");
		scanf("%[^\n]", menu[i]); getchar();
		printf("Input price : ");
		scanf("%d", &price[i]); getchar();
		printf("\n");
	}

	FILE *fmenu = fopen("HargaMenuScan.txt", "a");
	for(i=1; i<=input; i++){
		fprintf(fmenu, "\n%d#%s#%d", n++, menu[i], price[i]);
	}
	fclose(fmenu);

	temp = n-input;

	FILE *fnewmenu = fopen("NewMenu.txt", "a");
	for(i=1; i<=input; i++){
		fprintf(fmenu, "\n%d. %-44s %d", temp, menu[i], price[i]);
		temp++;
	}
	fclose(fnewmenu);

	puts("Choice");
	puts("1. Try again");
	puts("2. Exit to reload menu");

	choiceAdminMenu:
			
	printf("Your Choice : ");
			
	int choice;
	scanf("%d", &choice); getchar();

	if(choice == 1){
		goto start;
	}
	else if(choice == 2){
		return choice;
	}
	else{
		puts("\nWrong input, Please try again!\n");
		goto choiceAdminMenu;
	}

}

//password
void adminPassword(){
	
	system("cls");
	int check = 5;
	
	char pass[101];
	char var;
	int i;
	int correct, incorrect;
	
	do{
		correct = 0;
		incorrect = 0;
		i=0;
		printf("Please enter 4 digits password (%d tries remaining) : ", check);
		while(i<4){
			var = getch();
			if(var == ENTER){
				pass[i] = '\0';
				break;
			}
			else if(var == TAB){
				continue;
			}
			else if(var == BKCSPC){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}
			else{
				pass[i] = var;
				i++;
				printf("*");
			}
		}
		
		char password[] = {"2023"};
		
		for(i=0; i<4; i++){
			if(pass[i] != password[i]){
				incorrect++;
			}
			else if(pass[i] == password[i]){
				correct+=1;
			}
		}
		
		if(correct == 4){
			break;
		}
		else{
			check-=1;
			if(check == 0){
				break;
			}
			else{
				printf("\nWrong input, Please try again\n\n");
			}
		}
		
	}while(correct != 4);
	
	if(check == 0){
		puts("\n\n0 tries remaining");
		puts("Please try again later, Thank you");
		exit(0);
	}
	
}

void adminHistory();

int main(){
	
	//variabel
	int i, j, n=1;
	int adminChoice;
	int hasil;
	
	//nge scan data dari HargaMenuScan buat di masukin ke dalem struct
	FILE *fpmenu = fopen("HargaMenuScan.txt", "r");
	while(fscanf(fpmenu, "%d#%[^#]#%d\n", &Menu[n].kode, Menu[n].nama, &Menu[n].harga) != EOF){
		n++;
	}
	fclose(fpmenu);
	
	//buat print logo
	FILE *fptr;
	char c;
	
	start:

	fptr = fopen("Logo.txt", "r"); //open file
	if(fptr == NULL){
		printf("Cannot open file \n");
        exit(0);
	}
	
	c = fgetc(fptr); //read contents from file
	while(c != EOF){
		printf ("%c", c);
        c = fgetc(fptr);
	}
	fclose(fptr);

	for(i = 0; i < 92; i++){
		printf("%c", 254);
	}
	puts("\n");
	
	//buat home page
	int choice;
	
	wrongInput:
	puts("Choice");
	puts("1. Order");
	puts("2. Exit");
	
	printf("Your Choice : ");
	scanf("%d", &choice); getchar();
	
	switch(choice){
		//order
		case 1:
			loadingClear();
			system("cls");
			FILE *fp;
			
			int i;
			int kode[101];
			int quantity[101];
			long long int total = 0;
			char sure[11];
			int x, y;
			int count, valid;
			long int tax;
			long long int totalRound, totalAkhir;

			do{
				//print menu
				fp = fopen("Menu.txt", "r");
				if(fp == NULL){
					printf("Cannot open file \n");
					exit(0);
				}
				c = fgetc(fp);
			
				while (c != EOF){
					printf ("%c", c);
        			c = fgetc(fp);
				}
				fclose(fp);
				
				puts(" ");

				//print menu baru
				FILE *fpnewmenu = fopen("NewMenu.txt", "r");
				if(fpnewmenu == NULL){
					printf("Cannot open file \n");
					exit(0);
				}
				c = fgetc(fpnewmenu);
			
				while (c != EOF){
					printf ("%c", c);
        			c = fgetc(fpnewmenu);
				}
				fclose(fpnewmenu);

				puts(" ");

				count = 0;
				for(x = 0; x < 101; x++){
					valid = 0;
					printf("\nOrder Code : ");
					scanf("%d", &kode[x]); getchar();
					
					if(kode[x] == 0){
						break;
					} else{
						for(y = 0; y < n; y++){
							if(kode[x] == Menu[y].kode){
								valid = 1;
								break;
							}
						}
					}
					if(valid == 1){
						printf("%d. %s Rp.%d\n", Menu[kode[x]].kode, Menu[kode[x]].nama, Menu[kode[x]].harga);
						printf("Quantity: ");
					
						scanf("%d", &quantity[x]); getchar();
						total += (Menu[kode[x]].harga * quantity[x]);
						for(y = 0; y < count; y++){
							if(kode[x] == kode[y]){
								quantity[y] += quantity[x];
								count--;
								x--;
								break;
							}
						}
						count++;
					} else {
						printf("\aInvalid Code!\n");
						x--;
					}
					
				}
				
				printf("\nAre you Sure?\n");
				printf("YES / NO\n");
				scanf("%s", sure); getchar();
				system("cls");
			} 
			while (strcmp(sure,"YES") != 0 && strcmp(sure,"Yes") != 0 && strcmp(sure, "yes") != 0);

			loadingClear();
	
			for(i = 0; i < 55; i++){
				printf("-");
			}
			printf("\n                      \e[1m\e[3mBIRA CAFE\e[m\e[m                  \n");
			
			for(i = 0; i < 55; i++){
				printf("-");
			}
			printf("\n              ");

			waktu();
	
			for(i = 0; i < 55; i++){
				printf("-");
			}
			printf("\nQty                 Nama Pesanan                  Harga\n");
	
			for(i = 0; i < 55; i++){
				printf("-");
			}
			printf("\n");
			
			for(i = 0; i < count; i++){
				printf("x%-3d %-40s %9d\n", quantity[i], Menu[kode[i]].nama, (Menu[kode[i]].harga * quantity[i]));
			}
			
			for(i = 0; i < 55; i++){
				printf("-");
			}
			printf("\nSub Total");
	
			for(i = 0; i < 37; i++){
				printf(" ");
			}
			printf("%9lld\n", total);	
			
			tax = (0.11) * total;
			
			totalRound = total + tax;
			
			//Rounding ke atas biar untung HEHE
			float bagi = (float)totalRound/100;
			totalAkhir = ceil(bagi) * 100;
			
			printf("Tax (11%%)");
	
			for(i = 0; i < 37; i++){
				printf(" ");
			}
			printf("%9ld\n", tax);
		
			printf("Rounding");
			
			for(i = 0; i < 38; i++){
				printf(" ");
			}
			printf("%9lld\n", (totalAkhir - totalRound));
			
			printf("\e[1mTotal\e[m");
			
			for(i = 0; i < 41; i++){
				printf(" ");
			}
			printf("%9lld\n", totalAkhir);
			
			for(i = 0; i < 55; i++){
				printf("-");
			}
			printf("\n\n");	
			
			adminData(quantity, kode, total, count);

			//goto wrongInput;

			puts("Choice");
			puts("1. Back");
			puts("2. Exit");

			choice2:
			
			printf("Your Choice : ");
			
			int choice2;
			scanf("%d", &choice2); getchar();

			if(choice2 == 1){
				system("cls");
			 	goto start;
			}
			else if(choice2 == 2){
			 	printf("\n");
			 	goto exit;
			}
			else{
			 	puts("Wrong input, Please try again!");
			 	goto choice2;
			}
			
		break;
		
		//exit
		case 2:
			loadingClear();
			//system("cls");
			printf("\n");
			exit:
			puts("Thank you, See you next time!");
		break;
		
		//admin
		case 9999:

			adminPassword();

			loadingClear();

			system("cls");
			puts("Choice");
			puts("1. History");
			puts("2. Input menu");

			do{
	
				printf("Your Choice : ");
		
				scanf("%d", &adminChoice); getchar();

				if(adminChoice < 1 || adminChoice > 3){
					printf("\nWrong input, Please try again!\n\n");
				}

			} while(adminChoice < 1 || adminChoice > 3);
				
			switch(adminChoice){
				case 1:
					adminHistory(n); //history and summary
					
					puts("\nChoice");
					puts("1. Back");
					puts("2. Exit");
					
					wrongInputHistory:
					
					printf("Your Choice : ");
		
					scanf("%d", &hasil); getchar();
					
					if(hasil == 1){
						system("cls");
						goto start;
					}
					else if(hasil == 2){
						printf("\n");
						goto exit;
					}
					else{
						puts("\nWrong input, Please try again!\n");
						goto wrongInputHistory;
					}
					
					break;
				case 2:
					//input menu
					hasil = adminInputMenu(n);

					if(hasil == 2){
						printf("\n");
						goto exit;
					}
					break;
				default:
					break;
				}
			break;
		default:
			puts("\nWrong input, Please try again!\n");
			goto wrongInput;
		break;	
	}
	
	return 0;
}

void adminHistory(int n){

    adminAgain: 
	system("cls");

	int i, j;
	int showMonth = 0;
	
	char bulan[12][15] = {"January","February","March", "April",
						  "May", "June", "July", "August",
						  "September", "October", "November", "December"};
						  
	int d1, m1, y1, m = 1;
	
	printf("Input day   : ");
	scanf("%d", &d1); getchar();
	printf("Input month : ");
	scanf("%d", &m1); getchar();
	printf("Input year  : ");
	scanf("%d", &y1); getchar();
	system("cls");
	
	int countOrderNum = 1;
			
	int day[10001], month[10001], year[10001], kuantitas[10001], code[10001], penanda[10001];
	long long int totalAdmin[10001];
			
	FILE *fp2 = fopen("DataPembelian.txt","r");
			
	while(fscanf(fp2, "%d-%d-%d-%d-%d-%lld-%d\n", &day[m], &month[m], &year[m], &kuantitas[m], &code[m], &totalAdmin[m], &penanda[m]) != EOF){
		m++;
	}
	
	//buat summary bulanan
    for(i = 0; i <= m; i++){
		if(d1 == 0 && month[i] == m1 && year[i] == y1 && m1 != 0 && y1 != 0){
			showMonth = 1;
		}
	}

	int onlyOne = 1, historyValid = 0;
	
	int summary[n];
	int totalSummary = 0;
	long long int grandTotal = 0;
	
	int monthlySummary[n];
	int totalMonthly = 0;
	long long int grandMonthly = 0;
	
	//assign value ke semua elemen array
	memset(summary, 0, n*sizeof(summary[0])); //untuk daily summary
	memset(monthlySummary, 0, n*sizeof(monthlySummary[0])); //untuk monthlysummary
	
	//history bon
	for(i = 1; i <= m; i++){
		if(day[i] == d1 && month[i] == m1 && year[i] == y1 && d1 != 0 && m1 != 0 && y1 != 0){
					
			if(penanda[i] == 0){
				onlyOne = 0;
				printf("====================================================\n");
				printf("||              Order Number - %-4d               ||\n", countOrderNum);
				printf("----------------------------------------------------\n");
				printf("|| x%3d %-36s [%2d] ||\n", kuantitas[i], Menu[code[i]].nama, Menu[code[i]].kode);
				printf("||%48s||\n", " ");
			} else if(penanda[i] == 9999 && onlyOne == 1){
				printf("====================================================\n");
				printf("||              Order Number - %-4d               ||\n", countOrderNum);
				printf("----------------------------------------------------\n");
				printf("|| x%3d %-36s [%2d] ||\n", kuantitas[i], Menu[code[i]].nama, Menu[code[i]].kode);
				printf("----------------------------------------------------\n");
				printf("|| Total                                 %8lld ||\n", totalAdmin[i]);
				printf("====================================================\n\n");
				countOrderNum++;
			} else if (penanda[i] == 9999){
				onlyOne = 1;
				printf("|| x%3d %-36s [%2d] ||\n", kuantitas[i], Menu[code[i]].nama, Menu[code[i]].kode);
				printf("----------------------------------------------------\n");
				printf("|| Total                                 %8lld ||\n", totalAdmin[i]);
				printf("====================================================\n\n");
				countOrderNum++;
			} else {
				printf("|| x%3d %-36s [%2d] ||\n", kuantitas[i], Menu[code[i]].nama, Menu[code[i]].kode);
				printf("||%48s||\n", " ");
			}
			historyValid = 1;		
		} else {
			if(i == m-1 && showMonth == 0 && historyValid == 0 && (day[i] != d1 || month[i] != m1 || year[i] != y1)){
				printf("\aWrong Input, Please Try Again!\n");
                sleep(3);
                goto adminAgain;
				break;
			}
		}
	}
	
	if(historyValid == 1){
		
		printf(" Ready to See Summary?\n");
		printf(" Press Any Key to Continue ");
		getch();
		system("cls");
		
		puts("====================================================");
		puts("||                    Summary                     ||");
		puts("====================================================");
		
		//cuman output biar rapih kalau beda bulan
		printf("|| Date : %2d %s %d", d1, bulan[m1-1], y1);
		for(i = 1; i <= 32-(strlen(bulan[m1-1])); i++){
			printf(" ");
		}
		printf("||\n");
		
		puts("====================================================");
		
		//proses ngitung setiap kode ada berapa yang kejual
		for(i = 1; i <= m; i++){
			if(day[i] == d1 && month[i] == m1 && year[i] == y1){
				summary[code[i]] += kuantitas[i];
			}
		}
		
		for(i = 1; i <= n-1; i++){
			if(i == n-1){
				printf("|| [%2d] %-37sx%4d||\n", Menu[i].kode, Menu[i].nama, summary[i]);
			} else {
				printf("|| [%2d] %-37sx%4d||\n", Menu[i].kode, Menu[i].nama, summary[i]);
				printf("||%48s||\n", " ");
			}
		}
		
		for(i = 1; i <= n-1; i++){
			totalSummary += summary[i];
		}
		
		for(i = 1; i <= n-1; i++){
			grandTotal = grandTotal + (summary[i] * Menu[i].harga);
		}
		
		puts("====================================================");
		printf("|| Total Products Sold                        %4d||\n", totalSummary);
		printf("|| Grand Total                        %12lld||\n", grandTotal);
		puts("====================================================");
		
	} else {
		
	}
	
	if(showMonth == 1){
		
		puts("====================================================");
		puts("||                    Summary                     ||");
		puts("====================================================");
		
		//cuman output biar rapih kalau beda bulan
		printf("|| Month : %s %d",  bulan[m1-1], y1);
		for(i = 1; i <= 34-(strlen(bulan[m1-1])); i++){
			printf(" ");
		}
		printf("||\n");
		
		puts("====================================================");
		
		//proses ngitung setiap kode ada berapa yang kejual
		for(i = 1; i <= m; i++){
			if(month[i] == m1 && year[i] == y1){
				monthlySummary[code[i]] += kuantitas[i];
			}
		}
		
		for(i = 1; i <= n-1; i++){
			if(i == n-1){
				printf("|| [%2d] %-37sx%4d||\n", Menu[i].kode, Menu[i].nama, monthlySummary[i]);
			} else {
				printf("|| [%2d] %-37sx%4d||\n", Menu[i].kode, Menu[i].nama, monthlySummary[i]);
				printf("||%48s||\n", " ");
			}
		}
		
		for(i = 1; i <= n-1; i++){
			totalMonthly += monthlySummary[i];
		}
		
		for(i = 1; i <= n-1; i++){
			grandMonthly = grandMonthly + (monthlySummary[i] * Menu[i].harga);
		}
		
		puts("====================================================");
		printf("|| Total Products Sold                        %4d||\n", totalMonthly);
		printf("|| Grand Total                        %12lld||\n", grandMonthly);
		puts("====================================================");

	} else {
		
	}
}
