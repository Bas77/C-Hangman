#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(){
	char answer[10] = "TEST";
	char guess;
	int flagForCorrect, flagForFirst = 0, flagInput;
	int rightLetters = 0, guessCount = 0;
	int answerLen = strlen(answer);
	bool index[100] = {false}, guessedLetter[100] = {false}, correct[100] = {false};
	while(rightLetters < answerLen){
		system("cls");
		printf("HANGMAN\n");
		
		for(int i = 0; i < answerLen; i++){
			if(correct[i] == true){
				printf("%c", answer[i]);
			} else{
				printf("_");
			}
		}
		printf("\n");
		
		if(flagForFirst == 1){
		printf("You have guessed %c!\n", guess);
		}
		
		if(flagForCorrect == 1){
			printf("Letter is already guessed before!\n");
		} else if(flagForCorrect  == 2){
			printf("Your guess is correct!\n");
		} else if(flagForCorrect  == 3){
			printf("There is no %c in the word!\n", guess);
		}
		
		//TODO
		//Correct this input validation to be one character only.
		flagInput = 0;
		do{
			if(flagInput == 1){
			printf("Invalid input!\n");
			}	
			printf("Enter a letter:\n");
			scanf("%c", &guess); getchar();
			if(guess >= 'a' && guess <= 'z'){
			guess-= 32;
			}
			flagInput = 1;
		}while(guess < 'A' && guess > 'Z');
		printf("\n");
		
		bool previousAnswer = false;
		if(guessedLetter[guess] == true){
			flagForCorrect = 1;
		} else{
			
			for(int i = 0; i<answerLen;i++){
				if(guess == answer[i]){
					previousAnswer = true;
					flagForCorrect  = 2;
					rightLetters++;
					correct[i] = true;
				}
			}
			
			if(previousAnswer == false){
				flagForCorrect  = 3;
			}
			
		}
		
		guessedLetter[guess] = true;
		guessCount++;
		flagForFirst = 1;
	}
	
	system("cls");
	printf("Congratulations! You won!\n");
	printf("Your word is: %s\n", answer);
	printf("You guessed it in %d tries!\n", guessCount);
}