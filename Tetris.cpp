#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

char option, input;
struct player{
	char name[20];
	char pass[20];
	int score;
}data[200];
char map[20][20], menuAccess[20];
char username[20];
char password[20];
char confirmation[20];

void viewControl(char menuAccess[]){
	printf("Controls:\n");
	printf("-----------------------------------------\n");
	printf("A: left move      W: rotate block\n");
	printf("D: right move     E: swap with next block\n");
	printf("S: down move      Space: drop block\n\n");
	printf("P: pause game\n\n");
	
	printf("Press any key to go back to ");
	if(strcmp(menuAccess, "isInMainMenu") == 0) printf("main menu...");
	else printf("menu...");
	option = getch();
}

int maxIter;
int readScore(){
	FILE *fp = fopen("playerscore.txt", "r");
	int iter = 0; 
	while(fscanf(fp, "%[^#]#%[^#]#%d\n", data[iter].name, data[iter].pass, &data[iter].score) == 3) iter++;	
	fclose(fp);
	return iter;
}

void addUser(char username[], char password[], int userscore){
	FILE *fp = fopen("playerscore.txt", "a");
	fprintf(fp, "%s#%s#%d\n", username, password, userscore);
	fclose(fp);
	return;
}

void swapData(int j){
	struct player temp = data[j];
	data[j] = data[j - 1];
	data[j - 1] = temp;
}

void arrangingScore(int maxIter){
	int i, j;
	for(i = 0; i < maxIter; i++){
		for(j = maxIter; j > i; j--){
			if(data[j].score > data[j - 1].score){
				swapData(j);
			}
			else if(data[j].score == data[j - 1].score){
				if(strcmp(data[j].name, data[j - 1].name) < 0){
					swapData(j);
				}
			}	
		}
	}
	return;
}

// currentBlock position and their coordinates(y, x) reference
// 1) ## 12     2) ####    3)  ##  12    4) ##  12     5) #  1    6)  #  1    7) ### 123
//    ## 34		   1234	      ##  34	     ##  34       #  2        #  2        #   4
// 														  ## 34      ## 34
// Check the Block's Below to Stop Movement
bool belowChecker(int position, int currentBlock, char map[][20], int y1, int y2, int y3, int y4, int x1, int x2, int x3, int x4){
	if(currentBlock == 1) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
	if(position == 1){	
		if(currentBlock == 2) if(map[y1+1][x1] == '#' || map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 3) if(map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 4) if(map[y1+1][x1] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 5) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 6) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 7) if(map[y1+1][x1] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
	}
	else if(position == 2){
		if(currentBlock == 2) if(map[y4+1][x4] == '#') return false;
		if(currentBlock == 3) if(map[y2+1][x2] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 4) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 5) if(map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 6) if(map[y1+1][x1] == '#' || map[y2+1][x2] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 7) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
	}
	else if(position == 3){
		if(currentBlock == 2) if(map[y1+1][x1] == '#' || map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 3) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 4) if(map[y1+1][x1] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 5) if(map[y1+1][x1] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 6) if(map[y2+1][x2] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 7) if(map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
	}
	else if(position == 4){
		if(currentBlock == 2) if(map[y4+1][x4] == '#') return false;
		if(currentBlock == 3) if(map[y2+1][x2] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 4) if(map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 5) if(map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 6) if(map[y2+1][x2] == '#' || map[y3+1][x3] == '#' || map[y4+1][x4] == '#') return false;
		if(currentBlock == 7) if(map[y2+1][x2] == '#' || map[y4+1][x4] == '#') return false;
	}	
	return true;	
}

// Initialize map 
int maxSize = 19, maxColumn = 15;
void initializeMap(char map[][20]){
	for(int row = 0; row < maxSize; row++){
		for(int column = 0; column < maxColumn; column++){
			map[row][column] = '.';
		}
	}
}

// Blocks Coordinates
int y1, y2, y3, y4, x1, x2, x3, x4; 
void blockPlacement(int currentBlock, int *y1, int *y2, int *y3, int *y4, int *x1, int *x2, int *x3, int *x4){
	switch(currentBlock){
		case 1:{
			*y2 = *y1, *y3 = *y1 + 1, *y4 = *y3;
			*x2 = *x1 + 1, *x3 = *x1, *x4 = *x2;
			break;
		}
		case 2:{
			*y2 = *y3 = *y4 = *y1;
			*x2 = *x1 + 1, *x3 = *x2 + 1, *x4 = *x3 + 1;
			break;
		}
		case 3:{
			*y2 = *y1, *y3 = *y1 + 1, *y4 = *y3;
			*x2 = *x1 + 1, *x3 = *x1 - 1, *x4 = *x1;
			break;
		}
		case 4:{
			*y2 = *y1, *y3 = *y1 + 1, *y4 = *y3;
			*x2 = *x1 + 1, *x3 = *x2, *x4 = *x3 + 1;
			break;
		}
		case 5:{
			*y2 = *y1 + 1, *y3 = *y2 + 1, *y4 = *y3;
			*x2 = *x3 = *x1, *x4 = *x3 + 1;
			break;
		}
		case 6:{
			*y2 = *y1 + 1, *y3 = *y2 + 1, *y4 = *y3;
			*x2 = *x4 = *x1, *x3 = *x4 - 1;
			break;
		}
		case 7:{
			*y2 = *y3 = *y1, *y4 = *y1 + 1;
			*x2 = *x1 + 1, *x3 = *x2 + 1, *x4 = *x2;
			break;
		}
	}
		
}

void blockRotation(int position, int currentBlock, int *y1, int *y2, int *y3, int *y4, int *x1, int *x2, int *x3, int *x4){
	if(position == 1){
		if(currentBlock == 2) *y1 += 1, *x1 -= 1, *x3 += 1, *y3 -= 1, *x4 += 2, *y4 -= 2;
		else if(currentBlock == 3) *y1 += 1, *x1 += 1, *x2 += 2, *y3 += 1, *x3 -= 1;
		else if(currentBlock == 4) *y1 += 1, *x1 -= 1, *x2 += 1, *y3 += 1, *x4 += 2;
		else if(currentBlock == 5) *y1 -= 1, *x1 += 1, *y3 += 1, *x3 -= 1, *x4 += 2;
		else if(currentBlock == 6) *x1 += 1, *x2 += 1, *y3 += 1, *x3 -= 1, *y4 += 1, *x4 -= 1;
		else if(currentBlock == 7) *y1 += 1, *x1 -= 1, *x2 += 1, *x3 += 1;
	}
	else if(position == 2){
		if(currentBlock == 2) *y1 -= 2, *y2 -= 1, *y4 += 1, *x1 += 1, *x3 -= 1, *x4 -= 2;
		else if(currentBlock == 3) *y1 -= 1, *x1 -= 1, *x2 -= 2, *y3 -= 1, *x3 += 1;
		else if(currentBlock == 4) *y1 -= 1, *x1 += 1, *x2 -= 1, *y3 -= 1, *x4 -= 2;
		else if(currentBlock == 5) *x1 += 1, *x2 -= 1, *y3 -= 1, *y4 -= 1;
		else if(currentBlock == 6) *y1 += 1, *x1 -= 1, *y3 -= 1, *x3 += 2, *x4 += 1;
		else if(currentBlock == 7) *y1 -= 1, *x1 += 1;	
	}
	else if(position == 3){
		if(currentBlock == 2) *y1 += 2, *x1 -= 2, *y2 += 1, *x2 -= 1, *y4 -= 1, *x4 += 1;
		else if(currentBlock == 3) *y1 += 1, *x1 += 1, *x2 += 2, *y3 += 1, *x3 -= 1;
		else if(currentBlock == 4) *y1 += 1, *x1 -= 1, *x2 += 1, *y3 += 1, *x4 += 2;
		else if(currentBlock == 5) *x1 -= 2, *y2 -= 1, *x2 += 1, *x4 -= 1, *y4 += 1;
		else if(currentBlock == 6) *y1 -= 1, *x1 += 1, *y2 -= 1, *x2 += 1, *x3 -= 1, *x4 -= 1;
		else if(currentBlock == 7) *x2 -= 1, *x3 -= 1, *x4 += 1, *y4 -= 1;
	}
	else if(position == 4){
		if(currentBlock == 2) *y1 -= 1, *x1 += 2, *x2 += 1, *y3 += 1, *y4 += 2, *x4 -= 1;
		else if(currentBlock == 3) *y1 -= 1, *x1 -= 1, *x2 -= 2, *y3 -= 1, *x3 += 1;
		else if(currentBlock == 4) *y1 -= 1, *x1 += 1, *x2 -= 1, *y3 -= 1, *x4 -= 2;
		else if(currentBlock == 5) *y1 += 1, *y2 += 1, *x3 += 1, *x4 -= 1;
		else if(currentBlock == 6) *x1 -= 1, *x2 -= 2, *y2 += 1, *y4 -= 1, *x4 += 1;
		else if(currentBlock == 7) *y4 += 1, *x4 -= 1;
	}
	return;
}

int sy1 = -1, sy2 = -1, sy3 = -1, sy4 = -1, sx1 = -1, sx2 =-1, sx3 = -1, sx4 = -1;
void blockShadow(int position, int currentBlock, char map[][20], int y1, int y2, int y3, int y4, int x1, int x2, int x3, int x4) {
    int breaking;
    if (y1 == maxSize - 1 || y2 == maxSize - 1 || y3 == maxSize - 1 || y4 == maxSize - 1) return;  
    if (map[sy1][sx1] == '*') map[sy1][sx1] = '.';
    if (map[sy2][sx2] == '*') map[sy2][sx2] = '.';
    if (map[sy3][sx3] == '*') map[sy3][sx3] = '.';
    if (map[sy4][sx4] == '*') map[sy4][sx4] = '.';
	
    while(true) {
        y1++; y2++; y3++; y4++;
        breaking = belowChecker(position, currentBlock, map, y1, y2, y3, y4, x1, x2, x3, x4);
        if(breaking == -1 || y1 == maxSize - 1 || y2 == maxSize - 1 || y3 == maxSize - 1 || y4 == maxSize - 1) {
        	sy1 = y1; sy2 = y2; sy3 = y3; sy4 = y4;
            sx1 = x1; sx2 = x2; sx3 = x3; sx4 = x4;
   
            if(map[y1][x1] != '#' && map[y2][x2] != '#' && map[y3][x3] != '#' && map[y4][x4] != '#') {
                map[y1][x1] = map[y2][x2] = map[y3][x3] = map[y4][x4] = '*';
            }
            break;
        }
    }  
	return;
}

int level = 1, totalClear = 0;
double currentScore = 0;
void clearLine(){
	int numOfClear = 0;
	for(int row = 0; row < maxSize; row++){
		int clearRow = 0;
		for(int column = 0; column < maxColumn; column++) if(map[row][column] == '#') clearRow++;
		
		if(clearRow == maxColumn){
			for(int rowAbove = row - 1; rowAbove >= 0; rowAbove--){
				for(int columnAbove = 0; columnAbove < maxColumn; columnAbove++){
					if((rowAbove == y1 && columnAbove == x1) || (rowAbove == y2 && columnAbove == x2) || (rowAbove == y3 && columnAbove == x3) || (rowAbove == y4 && columnAbove == x4)) continue;
						map[rowAbove + 1][columnAbove] = map[rowAbove][columnAbove];
				}
			}
			for(int firstRow = 0; firstRow < maxColumn; firstRow++){
				if(firstRow == x1 || firstRow == x2 || firstRow == x3 || firstRow == x4) continue;
				map[0][firstRow] = '.';
			}
			numOfClear++;
			totalClear++; 
		}
	}
	                // Base Score          Combo Multiplier
	currentScore += (double)(100 * numOfClear) + (100 * (0.5 * numOfClear));
	return;
}

void blockScoring(int drop){
	if(drop == 1) currentScore += 1;
	else if(drop == 2) currentScore += 1.5;
}

void playGame(){
	maxIter = readScore();
	arrangingScore(maxIter);
	initializeMap(map);
	srand(time(NULL));
	bool exitToMain = false, first = true;
	int firstBlock, nextBlock, currentBlock, colorBlock;

	do{
		system("cls");
		colorBlock = rand() % 6 + 1;
		
		// Choosing random block
		if(first == true){
			firstBlock = rand() % 7 + 1;
			nextBlock = rand() % 7 + 1;
			currentBlock = firstBlock;
			first = false;
		}
		else{
			currentBlock = nextBlock;
			nextBlock = rand() % 7 + 1;
		}
		
		// Initializing a Spawned Block
		if(currentBlock == 5 || currentBlock == 6) x1 = 8;
		else x1 = 6;
		y1 = 0;
		blockPlacement(currentBlock, &y1, &y2, &y3, &y4, &x1, &x2, &x3, &x4);
		
		// Checking lose condition
		int position = 1; 
		int breaking = belowChecker(position, currentBlock, map, y1, y2, y3, y4, x1, x2, x3, x4);
		if(breaking == false) break;
		
		do{	
			clearLine();
			// Printing the Map
			blockShadow(position, currentBlock, map, y1, y2, y3, y4, x1, x2, x3, x4);
			map[y1][x1] = map[y2][x2] = map[y3][x3] = map[y4][x4] = '#';
			if(y1 == 18 || y2 == 18 || y3 == 18 || y4 == 18) break;
			
			// Printing Game Board
			for(int row = 0; row < maxSize; row++){
				for(int column = 0; column < maxColumn; column++){
					if((row == y1 && column == x1) || (row == y2 && column == x2) || (row == y3 && column == x3) || (row == y4 && column == x4)){
						if(colorBlock == 1) printf("\033[0;31m"); // Red
						else if(colorBlock == 2) printf("\033[0;32m"); // Green
						else if(colorBlock == 3) printf("\033[0;33m"); // Yellow
						else if(colorBlock == 4) printf("\033[0;34m"); // Blue
						else if(colorBlock == 5) printf("\033[0;35m"); // Purple
						else if(colorBlock == 6) printf("\033[0;36m"); // Cyan
						printf("%c", map[row][column]);
						printf("\033[0m");
					}
					else printf("%c", map[row][column]);	
				}
				// Live Game Stats
				if(row == 1) printf("  Top Score");
				else if(row == 2) printf("  %d", data[0].score);
				else if(row == 4) printf("  Score");
				else if(row == 5) printf("  %.0lf", currentScore);
				else if(row == 7) printf("  Next");
				else if(row == 8){
					if(nextBlock == 1) printf("  ##");
					else if(nextBlock == 2) printf("  ####");
					else if(nextBlock == 3) printf("   ##");
					else if(nextBlock == 4) printf("  ##");
					else if(nextBlock == 5) printf("   #");
					else if(nextBlock == 6) printf("    #");
					else if(nextBlock == 7) printf("  ###");
				}
				else if(row == 9){
					if(nextBlock == 1) printf("  ##");
					else if(nextBlock == 3) printf("  ##");
					else if(nextBlock == 4) printf("   ##");
					else if(nextBlock == 5) printf("   #");
					else if(nextBlock == 6) printf("    #");
					else if(nextBlock == 7) printf("   #");
				}
				else if(row == 10){
					if(nextBlock == 5) printf("   ##");
					else if(nextBlock == 6) printf("   ##");
				}
				else if(row == 12) printf("  Level");
				else if(row == 13) printf("  %d", level);
				printf("\n");
			}
			
			// Check if Block's Bellow Is Occupied
			int breaking = belowChecker(position, currentBlock, map, y1, y2, y3, y4, x1, x2, x3, x4);
			if(breaking == false) break;
			map[y1][x1] = map[y2][x2] = map[y3][x3] = map[y4][x4] = '.';
			
			input = getch();
			system("cls");
			if(input == 'a' || input == 'A'){ // Move block leftward
				if(x1 > 0 && x2 > 0 && x3 > 0 && x4 > 0){
					if(map[y1][x1-1] != '#' && map[y2][x2-1] != '#' && map[y3][x3-1] != '#' && map[y4][x4-1] != '#') x1--, x2--, x3--, x4--;
				}		
			}
			else if(input == 'd' || input == 'D'){ // Move block rightward
				if(x1 < maxColumn - 1 && x2 < maxColumn - 1 && x3 < maxColumn - 1 && x4 < maxColumn - 1){
					if(map[y1][x1+1] != '#' && map[y2][x2+1] != '#' && map[y3][x3+1] != '#' && map[y4][x4+1] != '#') x1++, x2++, x3++, x4++;
				}	
			}
			else if(input == 's' || input == 'S'){ // Move block downward
				y1++, y2++, y3++, y4++;
				blockScoring(1);
			}
			else if(input == 'w' || input == 'W'){ 	// Rotate block
				position++;
				if(position > 4) position = 1;
				blockRotation(position, currentBlock, &y1, &y2, &y3, &y4, &x1, &x2, &x3, &x4);
				if(x1 > 18 || x2 > 18 || x3 > 18 || x4 > 18) x1--, x2--, x3--, x4--;
				else if(x1 < 0 || x2 < 0 || x3 < 0 || x4 < 0) x1++, x2++, x3++, x4++;
				else while(y1 < 0 || y2 < 0 || y3 < 0 || y4 < 0) y1++, y2++, y3++, y4++;
			}
			else if(input == 'e' || input == 'E'){ // Swap current block with the next one
				int temp = currentBlock;
				currentBlock = nextBlock;
				nextBlock = temp;
				position = 1;
				blockPlacement(currentBlock, &y1, &y2, &y3, &y4, &x1, &x2, &x3, &x4);
			}
			else if(input == ' ' || input == ' '){ // Hard drop Block
				while(true){
				 	breaking = belowChecker(position, currentBlock, map, y1, y2, y3, y4, x1, x2, x3, x4);
					if(breaking == -1 || y1 == maxSize - 1 || y2 == maxSize - 1 || y3 == maxSize - 1 || y4 == maxSize - 1) break;
					y1 += 1, y2 += 1, y3 += 1, y4 += 1;
					blockScoring(2);
				}
			}
			else if(input == 'p' || input == 'P'){ // Pause Game
				do{
					system("cls");
					printf("Game Paused\n");
					printf("------------\n");
					printf("1. Resume Game\n");
					printf("2. View Controls\n");
					printf("3. Back to Main Menu\n");
					printf(">> ");
					option = getch();
					
					if(option == '2'){
						system("cls");
						viewControl("isNotInMainMenu");	
					}
					else if(option == '3'){
						exitToMain = true;
						break;
					}	
				}while(option != '1');
				system("cls");	
			}
			if(exitToMain) break;
			
		}while(true);
		printf("\033[0m");
		if(exitToMain) break;	
		
	}while(true);
	
	printf("GAME OVER\n\n");
	printf("Press any key to continue...");
	option = getch();

	maxIter = readScore();
	for(int i = 0; i < maxIter; i++){
		if(strcmp(data[i].name, username) == 0){
			if(currentScore > data[i].score) data[i].score = (int)currentScore;	
		}
	}
	
	FILE *fp = fopen("playerscore.txt", "w");
	for(int i = 0; i < maxIter; i++){
		fprintf(fp, "%s#%s#%d\n", data[i].name, data[i].pass, data[i].score);
	}
	fclose(fp);
	option = getch();
	return;
}

void viewScore(int maxIter){
	int i, start = 0, end = 10;
	maxIter = readScore();
	arrangingScore(maxIter);
	do{
		printf("#-----#----------------------#----------#\n");
		printf("| No. | %-20s | %-8s |\n", "Name", "Score");
		printf("#-----#----------------------#----------#\n");
		for(i = start; i < end; i++){
			printf("|     | %-20s | %-8s |\n", "", "");
			if(i >= maxIter) printf("| %03d | %-20s | %-8d |\n", i + 1, "N/A", 0);
			else printf("| %03d | %-20s | %-8d |\n", i + 1, data[i].name, data[i].score);
		}
		printf("|     | %-20s | %-8s |\n", "", "");
		printf("#-----#----------------------#----------#\n");
		printf("Press A or D to move between pages\n");
		printf("Press X to go back to main menu\n");
		printf(">> ");
		do{
			option = getch();
			if(option == 'a' || option == 'A' || option == 'd' || option == 'D' || option == 'x' || option == 'X') break;
		}while(true);
		
		if(option == 'a' || option == 'A'){
			if(start != 0){
				start -= 10;
				end -= 10;
			}
		}
		else if(option == 'd' || option == 'D'){
			if(end < maxIter){
				start += 10;
				end += 10;
			}	
		}
		else if(option == 'x' || option == 'X') break;
		system("cls");
	}while(true);
	return;
}

bool Register(){
	system("cls");
	do{
		printf("Insert your username\n");
		printf("NB: It's must be more than 2 and less than 15 characters\n");
		printf(">> ");
		scanf("%[^\n]", &username); getchar();
		if(strlen(username) > 2 && strlen(username) < 16) break;
	}while(true);
	system("cls");
	do{
		printf("Insert your password\n");
		printf("NB: It's must be more than 2 and less than 15 characters\n");
		printf(">> ");
		scanf("%[^\n]", &password); getchar();
		if(strlen(username) > 4 && strlen(username) < 16) break;
	}while(true);
	
	do{
		printf("Confirm your password\n");
		printf(">> ");
		scanf("%[^\n]", &confirmation); getchar();
		if(strcmp(password, confirmation) == 0) break;
	}while(true);
	
	addUser(username, password, 0);
	printf("\nSuccesfully added a player\n");
	printf("Press any key to continue...");
	option = getch();
	return true;
}

bool Login(){
	system("cls");
	bool valid;
	
	printf("Insert your username\n");
	printf(">> ");
	scanf("%[^\n]", &username); getchar();

	printf("Insert your password\n");
	printf(">> ");
	scanf("%[^\n]", &password); getchar();
	
	maxIter = readScore();
	for(int iter = 0; iter < maxIter; iter++){
		if((strcmp(data[iter].name, username) == 0) && strcmp(data[iter].pass, password) == 0){
			valid = true;
			break;
		} 
	}
	if(valid){
		printf("\nSuccesfully logged in\n");
		printf("Press any key to continue...");
		option = getch();
	}
	else{
		printf("\nLogin Failed\n");
		printf("Press any key to continue...");
		option = getch();
		return false;	
	}
	return true;
}

void mainMenu(){
	do{	
		system("cls");
		printf("Block Build\n");
		printf("1. Play\n");
		printf("2. View Controls\n");
		printf("3. View Score\n");
		printf("4. Exit\n");
		printf(">> ");
		option = getch();
		system("cls");
	
		switch(option){
			case '1':{
				playGame();
				break;
			}
			case '2':{
				viewControl("isInMainMenu");
				break;
			}
			case '3':{
				viewScore(maxIter);
				break;
			}
		}
	}while(option != '4');
	return;
}

void account(){
	bool valid;
	do{
		system("cls");
		printf("Select Your Progress\n");
		printf("1. Login\n");
		printf("2. Register\n");
		printf(">> ");
		option = getch();
		if(option == '1') valid = Login();
		else if(option == '2') valid = Register();
	}while(!valid);	
	return;
}

int main(){
	account();
	mainMenu();	
	printf("Thanks for Playing!");
	return 0;
}
