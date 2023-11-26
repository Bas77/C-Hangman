#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
void gameHangman(int, int);
void settingsHangman();
void mainMenu();
char* searchWordHangman(int);
int leaderboardDecision();
void leaderboardInput();
void progressbar(int);
void leaderboardOutput();
int Page();
void menuHangman();
void rulesHangman();
int main(){
	mainMenu();
	return 0;
}

void mainMenu(){
	int selection, flag = 0;
	do{
		system("cls");
		printf("1. Play Hangman\n");
		printf("2. Leaderboard\n");
		printf("3. Exit\n");
		if(flag == 1){
		printf("\nInput invalid!\n");
		}
		printf(">>");
		scanf("%d", &selection);
		switch (selection){
			case 1:
				flag = 2;
				menuHangman();
				break;
			case 2:
				flag = 2;
				leaderboardOutput(1);
				break;
			case 3:
				return;
				break;
			default:
				flag = 1;
				system("cls");
		}
	} while(flag == 1||flag == 2);
}

void menuHangman(){
	int flag = 0, selection;
	int diff,health;
	do{
		system("cls");
		printf("1. Play\n");
		printf("2. Rules\n");
		printf("3. Settings\n");
		printf("4. Back\n");
		if(flag == 1){
		printf("\nInput invalid!\n");
		}
		printf(">>");
		scanf("%d", &selection);
		switch (selection){
			case 1:
				flag = 2;
				FILE *file = fopen("hmsettings.in", "r");
				fscanf(file,"%d#%d", &diff, &health);
				fclose(file);
				gameHangman(diff,health);
				break;
			case 2:
				flag = 2;
				rulesHangman();
				break;
			case 3:
				flag = 2;
				settingsHangman();
				break;
			case 4:
				return;
				break;
			default:
				flag = 1;
				system("cls");
		}
	} while(flag == 1||flag == 2);
}

void settingsHangman(){
	system("cls");
	FILE *file = fopen("hmsettings.in", "r");
	int diff, health;
	char diffstr[100];
	fscanf(file, "%d#%d", &diff, &health);
	printf("Current settings: \n");
	if(diff == 1){
            strcpy(diffstr, "Easy");
        } else if(diff == 2){
            strcpy(diffstr, "Medium");
        } else if(diff == 3){
            strcpy(diffstr, "Hard");
        }
	printf("Difficulty = %s\n", diffstr);
	if (health <= 0){
		printf("Health = Infinity\n");
	} else{
		printf("Health = %d\n", health);
	}
	fclose(file);
	printf("Change a setting?\n");
	printf("(d = difficulty) (h = health) (any = back)\n");
	int selection = getch();
	if(selection == 'd'){
		printf("Enter a new difficulty: \n");
		printf("(e = easy) (m = medium) (h = hard)\n");
		int diffSelect = getch();
		
		if (diffSelect == 'e'){
			diff = 1;
		}else if (diffSelect == 'm'){
			diff = 2;
		}else if (diffSelect == 'h'){
			diff = 3;
		} else{
			printf("Invalid, previous difficulty will be used.");
			sleep(1);
			printf(".");
			sleep(1);
		}
		FILE *filew = fopen("hmsettings.in", "w");
		fprintf(filew,"%d#%d", diff,health);
		fclose(filew);
	} else if (selection == 'h'){
		printf("Enter a new health: \n(0 for infinity)\n");
		scanf("%d", &health);
		FILE *filew2 = fopen("hmsettings.in", "w");
		fprintf(filew2,"%d#%d", diff,health);
		fclose(filew2);
	}
	return;
}
void rulesHangman(){
	system("cls");
	printf("Rules:\n\n");
	printf("There are 3 difficulties.\n");
	printf("\ta. Easy: Words consists of 3 letters.\n");
	printf("\tb. Medium: Words consists of 5 letters.\n");
	printf("\tc. Hard: Words consists of 7 or more letters.\n");
	printf("Every time you guess wrong, your health will decrement by one, this does not matter if you have infinity.\n");
	printf("Entering an already guessed letter will also decrement your health, so be careful!\n");
	printf("When you have completely guessed the word, you can save your achievement in the leaderboards.\n");
	printf("\n\nEnter any key to go back.");
	getch();
	return;
}
void gameHangman(int diff,int health){
	char answer[20];
	int currentHealth;
	if(health > 0){
		currentHealth = health;
	} else{
		currentHealth = -1;
	}
	int i;
	char ii;
	strcpy(answer,searchWordHangman(diff));
	char guess[20];
	char nextchar;
	int flagForCorrect, flagForFirst = 0, flagInput;
	int rightLetters = 0, guessCount = 0;
	int answerLen = strlen(answer);
	bool index[100] = {false}, guessedLetter[100] = {false}, correct[100] = {false};
	while(rightLetters < answerLen){
		system("cls");
		if(currentHealth == 0){
			printf("You lost!\n");
			sleep(1);
			printf(".\n");
			sleep(1);
			return;
		}
		printf("HANGMAN\n");
		
		for(i = 0; i < answerLen; i++){
			if(correct[i] == true){
				printf("%c", answer[i]);
			} else{
				printf("_");
			}
		}
		printf("\n");
		printf("Guessed Letters:\n");
		for(ii = 'A'; ii <= 'Z'; ii++){
			if(guessedLetter[ii] == true){
				printf("%c", ii);
			}
		}
		printf("\n");
		printf("Unguessed Letters:\n");
		for(ii = 'A'; ii <= 'Z'; ii++){
			if(guessedLetter[ii] == false){
				printf("%c", ii);
			}
		}
		printf("\n\n");
		if(currentHealth > 0){
			printf("Current Health = %d\n", currentHealth);
		}
		if(flagForFirst == 1){
		printf("You have guessed %c!\n", guess[0]);
		}
		
		if(flagForCorrect == 1){
			printf("Letter is already guessed before!\n");
		} else if(flagForCorrect  == 2){
			printf("Your guess is correct!\n");
		} else if(flagForCorrect  == 3){
			printf("There is no %c in the word!\n", guess[0]);
		}
		
		flagInput = 0;
		do{
			if(flagInput == 1){
			printf("Invalid input!\n");
			}	
			printf("Enter a letter:\n");
			scanf(" %s", &guess); getchar();
			if(guess[0] >= 'a' && guess[0] <= 'z'){
			guess[0]-= 32;
			}
			flagInput = 1;
		}while(strlen(guess)!=1||isalpha(guess[0])==0);
		printf("\n");
		
		bool previousAnswer = false;
		if(guessedLetter[guess[0]] == true){
			flagForCorrect = 1;
			currentHealth--;
		} else{
			
			for(i = 0; i<answerLen;i++){
				if(guess[0] == answer[i]){
					previousAnswer = true;
					flagForCorrect  = 2;
					rightLetters++;
					correct[i] = true;
				}
			}
			
			if(previousAnswer == false){
				flagForCorrect  = 3;
				currentHealth--;
			}
			
		}
		
		guessedLetter[guess[0]] = true;
		guessCount++;
		flagForFirst = 1;
	}
	
	system("cls");
	printf("Congratulations! You won!\n");
	printf("Your word is: %s\n", answer);
	printf("You guessed it in %d tries!\n", guessCount);
	printf("Press any key to continue.");
	getch();
	
	system("cls");
	int decision = leaderboardDecision();
	system("cls");
	if(decision == 1){
		leaderboardInput(answer,guessCount,diff);
	}
	return;
}

char* searchWordHangman(int diff){
	
	char searchDiff[100];
	char searching[100];
	bool found = false; 
	srand(time(0));
	rand();
	int filerandom;
	char *fileword = malloc(1000);
	int random = rand()%100 + 1;
	if(diff == 1){
		strcpy(searchDiff, "easywords.in");
	} else if (diff == 2){
		strcpy(searchDiff, "medwords.in");
	} else if (diff == 3){
		strcpy(searchDiff, "hardwords.in");
	}
	FILE *file = fopen(searchDiff, "r");

	if(!file){
		system("cls");
		perror("Error");
		printf("Unable to open file %s.\n", searchDiff);
		return NULL;
	}
	found = false;
	while (fscanf(file," %d %[^\n]", &filerandom, fileword) == 2 && found == false){
		if(filerandom == random){
			found = true;
		}
	}
	fclose(file);
	return fileword;
}

void progressbar(int speed){
	int i;
	char x = 219;
	printf("Please wait...\n");
	for (i = 1; i <= 30; i++){
		printf("%c", x);
		usleep(speed * 20000);
	}
	printf("\nCompleted!\n");
	
	return;
}

int leaderboardDecision(){
	char decision[10];
	printf("Would you like to enter your previous game to the leaderboard?\n");
	printf("(Y/N)\n");
	printf(">>");
	scanf(" %s", &decision); getchar();
	if(decision[0]=='Y'||decision[0]=='y'){
		
		return 1;
	} else{
		system("cls");
		printf("Deleting previous game.");
		sleep(1);
		printf(".");
		sleep(1);
		printf(".");
		sleep(1);
		
		return 0;
	}
}

void leaderboardInput(char answer[],int guesses, int diff){
	int number;
	char name[100];
	char diffstr[100];
	FILE *filenumber = fopen("number.in", "r");
	
	fscanf(filenumber,"%d", &number);
	
	system("cls");
	printf("Please enter your name: ");
	scanf("%[^\n]", &name);
	FILE *file = fopen("leaderboard.in", "a+");
	if(diff == 1){
            strcpy(diffstr, "Easy");
        } else if(diff == 2){
            strcpy(diffstr, "Medium");
        } else if(diff == 3){
            strcpy(diffstr, "Hard");
        }
        
	fprintf(file,"%d#%s#%s#%s#%d\n",number+1,name,diffstr,answer,guesses);
	progressbar(3);
	printf("Press any key to continue.");
	fclose(file); 
	fclose(filenumber);
	
	FILE *filenumber2 = fopen("number.in", "w");
	fprintf(filenumber2, "%d\n", number+1);
	fclose(filenumber2); 
	getch();
	system("cls");
	return;
}
void leaderboardOutput(int currentPage){
	system("cls");
	printf("Leaderboard:\n");
	
    int count = 0;
    int page = Page();
    int lineScanned, pageSelect;
    int diff, guesses;
    char diffstr[100];
    char name[100];
    char word[100];

    // Open the file
    FILE *file = fopen("leaderboard.in", "r");
    if (file == NULL) {
        printf("Error opening the leaderboard file.\n");
        return;
    }

    // Read data from the file
    while(fscanf(file, "%d#%[^#]#%[^#]#%[^#]#%d\n", &lineScanned, name, diffstr, word, &guesses) == 5){

        // Print the leaderboard entry
        if(lineScanned >= currentPage*5-4 && lineScanned <= currentPage *5){
        printf("%d. %s\n", lineScanned, name);
        printf("Difficulty: %s\n", diffstr);
        printf("Word: %s\n", word);
        printf("Number of tries: %d\n", guesses);
        printf("\n");
    	}
    }
	printf("Page: %d/%d\n", currentPage,Page());

    fclose(file);
    printf("Which page to go to?\n");
    printf("(n = next page) (b = prev page) (s = select page) (any = exit)\n");
    char selection = '\0';
    selection = getch();
//    system("cls");
    if(selection == 's'){
    	printf("Enter page: ");
		scanf("%d", &pageSelect); getchar();
		if(pageSelect > Page()||pageSelect <= 0){
			system("cls");
			printf("Page doesn't exist!\n");
			printf("Going back to main menu.");
			sleep(1);
			printf(".");
			sleep(1);
			printf(".");
			sleep(1);
			printf(".");
		} else{
			leaderboardOutput(pageSelect);
			return;
		}
		return;
	} else if(selection == 'n' && currentPage!= Page()){
		leaderboardOutput(currentPage+1);
		return;
	} else if(selection == 'b' && currentPage!=1){
		leaderboardOutput(currentPage-1);
		return;
	} else if((selection == 'b' && currentPage==1) ||(selection == 'n' && currentPage==Page())){
			system("cls");
			printf("Page doesn't exist!\n");
			printf("Going back to main menu.");
			sleep(1);
			printf(".");
			sleep(1);
			printf(".");
			sleep(1);
			printf(".");
			return;
	} else{
		return;
	}
}


int Page(){
	int count = 0;
	int page;

	FILE *file2 = fopen("number.in", "r");
	
	fscanf(file2, "%d", &count);
	if(count % 5 == 0){
		page = count/5;
	} else{
		page = count/5+1;
	}
	fclose(file2);
	return page;
}