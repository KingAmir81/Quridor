#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::string;
using std:: cin;
using std::endl;
using std::ifstream;
constexpr auto vertical_wall = '|';//this the symbol of vertical wall
constexpr auto horizental_wall = '=';//this the symbol of horizental wall
constexpr auto WIDTH = 55;//this the width of over board game
constexpr auto HEIGHT = 19;//this the height of over board game
static int wall1 = 10;// this is the number of walls for player1
static int wall2 = 10;// this is the number of walls for player2
static string name;//this the name of player that turn 
static int xa = 17, ya = 27;//this the starter situation for player 1 (A)
static int xb = 1, yb = 27;//this the starter situation for player 2 (B)
static bool input_wrong = false;// if users input wrong value this var turn to true and show a warning 
static int counta = 0;//this counter use for indicate the victory of player A
static int countb = 0;//this counter use for indicate the victory of player B
static int countforexit = 0;// this counter use exit from game during the game
static int c = 0;// this counter use for not showing win when the user exit from game
static int visiteda[19][55]{ 0 };//this array use for check the surrounding for player1
static int visitedb[19][55]{ 0 };//this array use for check the surrounding for player1
// this boolean variable use for check if a move illegal and player inpute that show him an error (for player1)
static bool ua = true, da = true, ra = true, la = true, Ua = true, Da = true, Ra = true, La = true, Qa = true, Pa = true, Ta = true, Ya = true;
// this boolean variable use for check if a move illegal and player inpute that show him an error (for player2)
static bool ub = true, db = true, rb = true, lb = true, Ub = true, Db = true, Rb = true, Lb = true, Qb = true, Pb = true, Tb = true, Yb = true;
//this tow boolean variable use for show or not show illegal move
static bool chb = false, cha = false;
// this function show a main menu and ,it's the first functin that we declar i program
bool Menu();
//this function anounce the current information of game
void anounce(string name, int wall1, int wall2);
// this function set over voard for play
void board(char arr[][WIDTH]);
//this function do the command of player1
void player1(char arr[][WIDTH]);
//this function do the command of player2
void player2(char arr[][WIDTH]);
//this function set the walls for A
void wall_A(char [][WIDTH]);
//this function set the walls for B
void wall_B(char[][WIDTH]);
//this function move bead for A
void  bead_A(char arr[][WIDTH]);
//this function move bead for B
void bead_B(char arr[][WIDTH]);
// this function check the bead of board for player A
void moves_are_legal_for_A(int ,int ,char [][WIDTH]);
// this function check the bead of board for player B
void moves_are_legal_for_B(int, int, char[][WIDTH]);
//win function
char win() {

	return '$';
}
// This function check if player 1 surrounded by wall
bool check_surrounding_for_palyer1(int xaf, int yaf, char arr[][WIDTH], int visitedb[][55]);
// This function check if player 1 surrounded by wall
bool check_surrounding_for_palyer2(int xbf, int ybf, char arr[][WIDTH], int visiteda[][55]);
//this the main function that is the core of start abd terminate of our program
int main()
{
		// we define a tow dimensioal array for show the board of game and handl the move ind wall insert  
		char arr[HEIGHT][WIDTH]{};
		// this two for loop draw the board
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if ((i == 0 || i == HEIGHT - 1) && !(j % 6 == 0))arr[i][j] = '-';
				else if (i % 2 == 0 && j % 6 == 0)arr[i][j] = '+';
				else if (i % 2 == 1 && (j == 0 || j == WIDTH - 1))arr[i][j] = '|';
				else arr[i][j] = ' ';
			}
		}
		// this if statment show the menu and start game
		if (Menu())
		{
				// declare player1 if we choose start and play the game
				player1(arr);
			
		}
		// this if statment show the winner of the game
		if(c==0 && countforexit==0)
		cout <<endl<< name << " win"<<endl;
	return 0;
}
//this the first function that the program declare and we can start or exit game
bool Menu(){
	// this integer variable use for choosing between start or exit game
	int choice;
	// this boolean variable use for indicat header of game
	bool w = true;
	//this if statment show a header for menu of game
	if (w)
	{
		cout << "\n\t\t\t\t\t\t\t\t\t\t\t* Wellcom to my Quridor game *\n";
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < 211; j++)cout << '#';
			cout << "\n";
		}
		w = false;
	}
	// this the menu bar
	cout << "\n\n1- start play-game" << endl;
	cout << "2- tutorial" << endl;
	cout << "3- exit from game\n\n\n";
	cout << "enter the number of your choice : " << endl;
	// inpute the decision for start or exit
	cin >> choice;
	// start = 1
	if (choice == 1)
	{
		system("cls");
		return true;
	}
	// tutorial = 2
	else if (choice == 2) {
		string str;
		ifstream myfile("a.txt");
		while (getline(myfile, str))
		{
			cout << str << endl;

		}
		cout << "\n\n\n";
	}
	// exit = 3
	else if (choice == 3) {
		c++;
		return false;
	}
	// if inpute other number program give you and warning statment and show menu again 
	else
	{
		cout << "This nubmer is invalid!\nplease enter a valid number\n";
		Menu();
	}
	Menu();

}
// this function declar in each cycle of game and show results of game
void anounce(string name,int wall1,int wall2)
{
	cout << "\n\n";
	// show the num of wall for player 1
	cout << "walls of player1 : "<< wall1<<endl;
	// show the num of wall for player 2
	cout << "walls of player2 : "<< wall2<<endl;
	// show turn for play
	cout <<"\n\n\t\t\t    " << "turn for :" << name << "\n\n\t ";
	// insert an empty space 
	for (int k = 0; k < 55; k++) {
		if (k % 6 == 0 && k != 0 && k != 54)cout << k / 6;
		else cout <<' ';
	}
	cout << "\n";
}
// this function print the boar dfor each turn for palyer
void board(char arr[HEIGHT][WIDTH]) {
		//this the starter situation for player 1 (A)
		arr[xa][ya] = 'A';
		//this the starter situation for player 2 (B)
		arr[xb][yb] = 'B';
		// print the board 
		for (int i = 0; i < HEIGHT; i++)
		{
			cout << "\t";
			if (i % 2 == 0 && i != 0 && i != 18)cout << i / 2;
			else cout << ' ';
			for (int j = 0; j < WIDTH; j++)
			{
				cout <<arr[i][j];
			}
			cout << endl;
		}
	}
// this function implemantion the command of player1
void player1(char arr[][WIDTH])
	{
		// this if statment check if a move illegal and print and warning for player1
		if (cha && (ua == false || da == false || ra == false || la == false || Ua == false || Da == false || Ra == false || La == false || Pa == false
			|| Qa == false || Ta == false || Ya == false)) {
		cout << "this move is illegal !! try again" << endl;
		}
		if (input_wrong)// this statment remind you to dont'n input invalid character
		cout << "\nthis choice is invalide!!\ntry again\n";
		input_wrong = false;
		name = "player1";// this assignment use for the turn for player1
		anounce(name, wall1, wall2);//declar the anounce functin
		board(arr);//declar the board functin
		char move;
		// show that you can move or set wall
		cout << "\nIf you want to move your bead press 'b'" << endl;
		if (wall1 != 0)
			cout << "If you want to use wall presss 'w'" << endl;
		else cout << "you can't use wall\n";
		cout<<"if you want to back to menu (m) " << endl;
		cin >> move;
		if (move == 'b')
			 bead_A(arr);
		// this statment lead player to set wall
		else if (move == 'w')
		{
			wall1--;
			wall_A(arr);
		}
		//this statment lead player to exit from game
		else if (move == 'm') {
			system("cls");
			countforexit++;
		}
		// show you input an invalid character
		else {
			input_wrong = true;
			system("cls");
			player1(arr);
		}
		// this statment check tow counter and then decied to turn to another player or finish the game and the winner
		if(counta==0 && countforexit==0){
		system("cls");
		player2(arr);}
	}
// this function implemantion the command of player1
void player2(char arr[HEIGHT][WIDTH])
	{
	// this if statment check if a move illegal and print and warning for player2
	if (chb && (ub == false || db == false || rb == false || lb == false || Ub == false || Db == false || Rb == false || Lb == false || Pb == false
		|| Qb == false || Tb == false || Yb == false)) {
		cout << "this move is illegal !! try again" << endl;
	}
	if (input_wrong)// this statment remind you to dont'n input invalid character
		cout << "\nthis choice is invalide!!\ntry again\n";
	input_wrong = false;
		name = "player2";// this assignment use for the turn for player2
		anounce(name, wall1, wall2);//declar the anounce functin
		board(arr);//declar the board functin
		char move;
		// show that you can move or set wall
		cout << "\nIf you want to move your bead press 'b'" << endl;
		if (wall1 != 0)
			cout << "If you want to use wall presss 'w'" << endl;
		else cout << "you can't use wall\n";
		cout << "if you want to back to menu (m) " << endl;
		cin >> move;
		if (move == 'b')
			bead_B(arr);
		// this statment lead player to set wall
		else if (move == 'w')
		{
			wall2--;
			wall_B(arr);
		}
		//this statment lead player to exit from game
		else if (move == 'm') {
			system("cls");
			countforexit++;
		}
		// show you input an invalid character
		else {
			input_wrong = true;
			system("cls");
			player2(arr);
		}
		// this statment check tow counter and then decied to turn to another player or finish the game and the winner
		if (countb == 0 && countforexit==0) {
			system("cls");
			player1(arr);
		}
	}
//this function move bead for A
void bead_A(char arr[HEIGHT][WIDTH])
{
	// declare this function for show the legal move to player
	moves_are_legal_for_A(xa,ya,arr);
	char ch;
	cin >> ch;
	// this statment use for anounce the win of player1 
	if (xa == 1)
	{
		ch=win();
	}
	switch (ch)
	{
		// case for move to up cell
		case 'u':
			if (ua == false) {
				cha = true;
				system("cls");
				player1(arr);			
			}
			arr[xa][ya] = ' ';
			xa -= 2;
			break;
		// case for move to down cell
		case 'd':
			if (da == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa += 2;
			break;
			// case for move to double up cell
		case 'U':
			if (Ua == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa -= 4;
			break;
			// case for move to right cell
		case 'r':
			if (ra == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			ya += 6;
			break;
			// case for move to left cell
		case 'l':
			if (la == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			ya -= 6;
			break;
			// case for move to doule right cell
		case 'R':
			if (Ra == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			ya += 12;
			break;
			// case for move to doule left cell
		case 'L':
			if (La == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			ya -= 12;
			break;
			// case for move to doule down cell
		case 'D':
			if (Da == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa += 4;
			break;
			// case for move to down-right cell
		case 'Q':
			if (Qa == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa += 2;
			ya += 6;
			break;
			// case for move to down-left cell
		case 'P':
			if (Pa == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa += 2;
			ya -= 6;
			break;
			// case for move to up-right cell
		case 'T':
			if (Ta == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa -= 2;
			ya += 6;
			break;
			// case for move to up-left cell
		case 'Y':
			if (Ya == false) {
				cha = true;
				system("cls");
				player1(arr);
			}
			arr[xa][ya] = ' ';
			xa -= 2;
			ya -= 6;
			break;
			// break for win
		case'$':
			counta++;
			break;
		default:
			cout << "\n\nthis inpute is invalid \n\n" << endl;
			bead_A(arr);
			break;
	}
}
//this function move bead for B
void bead_B(char arr[HEIGHT][WIDTH])
{
	// declare this function for show the legal move to player
	moves_are_legal_for_B(xb, yb, arr);
	char ch;
	cin >> ch;
	// this statment use for anounce the win of player2
	if (xb == 17)
	{
		ch = win();

	}
	switch (ch)
	{
		// case for move to up cell
	case 'u':
		if (ub == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb -= 2;
		break;
		// case for move to down cell
	case 'd':
		if (db == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb += 2;
		break;
		// case for move to double down cell
	case 'D':
		if (Db == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb+= 4;
		break;
		// case for move to right cell
	case 'r':
		if (rb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		yb += 6;
		break;
		// case for move to left cell
	case 'l':
		if (lb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		yb -= 6;
		break;
		// case for move to double up cell
	case 'U':
		if (Ub == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb -= 4;
		// case for move to double right cell
	case 'R':
		if (Rb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		yb+= 12;
		break;
		// case for move to double left cell
	case 'L':
		if (Lb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		yb -= 12;
		break;
		// case for move to down-right cell
	case 'Q':
		if (Qb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb += 2;
		yb += 6;
		break;
		// case for move to down-left cell
	case 'P':
		if (Pb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb += 2;
		yb -= 6;
		break;
		// case for move to up-right cell
	case 'T':
		if (Tb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb -= 2;
		yb += 6;
		break;
		// case for move to up-left cell
	case 'Y':
		if (Yb == false) {
			chb = true;
			system("cls");
			player2(arr);
		}
		arr[xb][yb] = ' ';
		xb -= 2;
		yb -= 6;
		break;
		// break for win
	case '$':
		countb++;
		break;
	default:
		cout << "\n\nthis inpute is invalid \n\n" << endl;
		bead_B(arr);
		break;
	}
}
//this two function check he legal move for both two player
void moves_are_legal_for_A(int x,int y,char arr[HEIGHT][WIDTH])
{

	char ch;
	cout << "if you want to come back and insert wall press (( W )) or for continu press (( B )):\n" << endl;
	cin >> ch;
	if (ch == 'W') { wall_A(arr); }
	else {
		// this statment ckeck that the player can move bead up or not
		if ((arr[x - 2][y] == ' ' && arr[x - 1][y] != horizental_wall ) || arr[x - 1][y]=='-') {
			cout << "you can input << u >> for up " << endl;
			ua = true;
		}
		else {
			ua = false;
		}
		// this statment ckeck that the player can move bead down or not
		if (arr[x - 2][y] == ' ' && arr[x + 1][y] != horizental_wall && arr[x + 1][y] != '-') {
			cout << "you can input << d >> for down " << endl;
			da = true;
		}
		else {
			da = false;
		}
		// this statment ckeck that the player can move bead right or not
		if (arr[x][y + 6] == ' ' && arr[x][y + 3] != vertical_wall) {
			cout << "you can input << r >> for right " << endl;
			ra = true;
		}
		else {
			ra = false;
		}
		// this statment ckeck that the player can move bead left or not
		if (arr[x][y - 6] == ' ' && arr[x][y - 3] != vertical_wall) {
			cout << "you can input << l >> for left " << endl;
			la = true;
		}
		else {
			la = false;
		}
		// this statment ckeck that the player can move bead double up or not
		if (arr[x - 2][y] == 'B' && arr[x - 3][y] != horizental_wall) {
			cout << "you can input << U >> for double up " << endl;
			Ua = true;
		}
		else {
			Ua = false;
		}
		// this statment ckeck that the player can move bead double up or not
		if (arr[x + 2][y] == 'B') {
			cout << "you can input << D >> for double down " << endl;
			Da = true;
		}
		else {
			Da = false;
		}
		// this statment ckeck that the player can move bead double right or not
		if (arr[x][y + 6] == 'B' && arr[x][y + 9] != vertical_wall) {
			cout << "you can input << R >> for double right " << endl;
			Ra = true;
		}
		else {
			Ra = false;
		}
		// this statment ckeck that the player can move bead double left or not
		if (arr[x][y - 6] == 'B' && arr[x][y - 9] != vertical_wall) {
			cout << "you can input << L >> for double left " << endl;
			La = true;
		}
		else {
			La = false;
		}
		// this statment ckeck that the player can move bead down-right or not
		if (arr[x + 2][y] == 'B' && arr[x + 3][y] == horizental_wall && arr[x + 2][y + 3] != '|') {
			cout << "you can input << Q >> for  down-right " << endl;
			Qa = true;
		}
		else {
			Qa = false;
		}
		// this statment ckeck that the player can move bead down-left or not
		if (arr[x + 2][y] == 'B' && arr[x + 3][y] == horizental_wall && arr[x + 2][y - 3] != '|') {
			cout << "you can input << P >> for  down-left" << endl;
			Pa = true;
		}
		else {
			Pa = false;
		}
		// this statment ckeck that the player can move bead down-right or not
		if (arr[x - 2][y] == 'B' && arr[x - 3][y] == horizental_wall && arr[x - 2][y + 3] != '|') {
			cout << "you can input << T >> for  up-right " << endl;
			Ta = true;
		}
		else {
			Ta = false;
		}
		// this statment ckeck that the player can move bead down-left or not
		if (arr[x - 2][y] == 'B' && arr[x - 3][y] == horizental_wall && arr[x - 2][y - 3] != '|') {
			cout << "you can input << Y >> for  up-left" << endl;
			Ya = true;
		}
		else {
			Ya = false;
		}
		cha = false;
	}
	return;
}
void moves_are_legal_for_B(int x, int y, char arr[HEIGHT][WIDTH]){
	char ch;
	cout << "if you want to come back and insert wall press (( W )) or for continu press (( B )):\n" << endl;
	cin >> ch;
	if (ch == 'W') { wall_B(arr); }
	else {
		// this statment ckeck that the player can move bead up or not
		if (arr[x - 2][y] == ' ' && arr[x - 1][y] != horizental_wall && arr[x - 1][y] != '-') {
			cout << "you can input << u >> for up " << endl;
			ub = true;
		}
		else {
			ub = false;
		}
		// this statment ckeck that the player can move bead down or not
		if ((arr[x + 2][y] == ' ' && arr[x + 1][y] != horizental_wall) || arr[x + 1][y] == '-') {
			cout << "you can input << d >> for down " << endl;
			db = true;
		}
		else {
			db = false;
		}
		// this statment ckeck that the player can move bead right or not
		if (arr[x][y + 6] == ' ' && arr[x][y + 3] != vertical_wall) {
			cout << "you can input << r >> for right " << endl;
			rb = true;
		}
		else {
			rb = false;
		}
		// this statment ckeck that the player can move bead left or not
		if (arr[x][y - 6] == ' ' && arr[x][y - 3] != vertical_wall) {
			cout << "you can input << l >> for left " << endl;
			lb = true;
		}
		else {
			lb = false;
		}
		// this statment ckeck that the player can move bead double up or not
		if (arr[x - 2][y] == 'A' && arr[x - 3][y] != horizental_wall) {
			cout << "you can input << U >> for double up " << endl;
			Ub = true;
		}
		else {
			Ub = false;
		}
		// this statment ckeck that the player can move bead double down or not
		if (arr[x + 2][y] == 'A' && arr[x + 3][y] != horizental_wall) {
			cout << "you can input << D >> for double down " << endl;
			Db = true;
		}
		else {
			Db = false;
		}
		// this statment ckeck that the player can move bead double right or not
		if (arr[x][y + 6] == 'A' && arr[x][y + 9] != vertical_wall) {
			cout << "you can input << R >> for double right " << endl;
			Rb = true;
		}
		else {
			Rb = false;
		}
		// this statment ckeck that the player can move bead double left or not
		if (arr[x][y - 6] == 'A' && arr[x][y - 9] != vertical_wall) {
			cout << "you can input << L >> for double left " << endl;
			Lb = true;
		}
		else {
			Lb = false;
		}
		// this statment ckeck that the player can move bead up-right or not
		if (arr[x + 2][y] == 'A' && arr[x + 3][y] == horizental_wall && arr[x + 2][y + 3] != '|') {
			cout << "you can input << T >> for  up-right " << endl;
			Qb = true;
		}
		else {
			Qb = false;
		}
		// this statment ckeck that the player can move bead down-left or not
		if (arr[x + 2][y] == 'A' && arr[x + 3][y] == horizental_wall && arr[x + 2][y - 3] != '|') {
			cout << "you can input << P >> for  down-left" << endl;
			Pb = true;
		}
		else {
			Pb = false;
		}
		// this statment ckeck that the player can move bead up-left or not
		if (arr[x - 2][y] == 'A' && arr[x - 3][y] == horizental_wall && arr[x - 2][y - 3] != '|') {
			cout << "you can input << Y >> for  up-left" << endl;
			Yb = true;
		}
		else {
			Yb = false;
		}
		// this statment ckeck that the player can move bead down-right or not
		if (arr[x - 2][y] == 'A' && arr[x - 3][y] == horizental_wall && arr[x - 2][y + 3] != '|') {
			cout << "you can input << Q >> for  down-right " << endl;
			Tb = true;
		}
		else {
			Tb = false;
		}
		chb = false;
	}
	return;
}
// this function set the wall for player1
void wall_A(char arr[HEIGHT][WIDTH])
{
	// define a character for desicion between statment
	char wall;
	//print statment 
	cout << "choose between  vertical_wall (press v) or horizental_wall (press h) :" << endl;
	cin >> wall;
	// vertical_wall
	if (wall == 'v') {
		int xwv, ywv;
		// enter the y and x of your vertical wall
		cout << "enter the y of wall : \n";
		cin >> xwv;
		cout << "enter the x of wall : \n";
		cin >> ywv;
		//check if another wall inserted hear before and show warning then come cack to hte player1
		if ((arr[(xwv * 2) - 1][ywv * 6] == '|' || arr[(xwv * 2) + 1][ywv * 6] == '|') || (arr[(xwv * 2)][(ywv * 6)-3] =='=' && arr[(xwv * 2)][(ywv * 6) + 3]=='=')){
			system("cls");
			cout << "this situation is ful! try again\n\n";
			wall1++;
			player1(arr);
		}
		// set the vertical wall
			arr[(xwv * 2) - 1][ywv * 6] = '|';
			arr[(xwv * 2) + 1][ywv * 6] = '|';
			// praper visiteda for check surrrounding
			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 55; j++)
					visitedb[i][j] = 0;
			// praper visiteda for check surrrounding
			for (int i = 0; i < 19; i++)
				for (int j = 0; j < 55; j++)
					visiteda[i][j] = 0;
			// check surrrounding
		if (check_surrounding_for_palyer1(xa, ya, arr, visitedb) || check_surrounding_for_palyer2(xb, yb, arr, visiteda))
			{
				// turn the ful wall to empty for desicion again
				arr[(xwv * 2) - 1][ywv * 6] = ' ';
				arr[(xwv * 2) + 1][ywv * 6] = ' ';
				system("cls");
				cout << "you can't surround a player  with wall" << endl;
				wall1++ ;
				player1(arr);
			}
	}
	//horizental_wall
	else if (wall == 'h') {
		int xwh, ywh;
		// enter the y and x of your horizental wall
		cout << "enter the y of wall : \n";
		cin >> xwh;
		cout << "enter the x of wall : \n";
		cin >> ywh;
		//check if another wall inserted hear before and show warning then come cack to hte player2
		if ((arr[(xwh * 2)][(ywh * 6) - 3] == '=' || arr[(xwh * 2)][(ywh * 6) + 3] == '=') || (arr[(xwh * 2) - 1][ywh * 6] == '|' && arr[(xwh * 2) + 1][ywh * 6] == '|')){
			system("cls");
			cout << "this situation is full! try again\n\n";
			wall1++;
			player1(arr);
		}
		arr[(xwh * 2)][(ywh * 6) - 3] = '=';
		arr[(xwh * 2)][(ywh * 6) + 3] = '=';
		// praper visiteda for check surrrounding
		for (int i = 0; i < 19; i++)
			for (int j = 0; j < 55; j++)
				visitedb[i][j] = 0;
		// praper visiteda for check surrrounding
		for (int i = 0; i < 19; i++)
			for (int j = 0; j < 55; j++)
				visiteda[i][j] = 0;
		if ( check_surrounding_for_palyer1(xa, ya, arr, visitedb) ||  check_surrounding_for_palyer2(xb, yb, arr, visiteda) )
		{
			// turn the ful wall to empty for desicion again
			arr[(xwh * 2)][(ywh * 6) - 3] = ' ';
			arr[(xwh * 2)][(ywh * 6) + 3] = ' ';
			system("cls");
			cout << "you can't surround a player  with wall" << endl;
			wall1++;
			player1(arr);
		}
	}
	else { 
		cout << "this choice is invalide!!\ntry again";
		wall_A(arr); 
	}

}
// this function set the wall for player2
void wall_B(char arr[HEIGHT][WIDTH])
{
	// define a character for desicion between statment
	char wall;
	//print statment 
	cout << "choose between  vertical_wall (press v) or horizental_wall (press h) :" << endl;
	cin >> wall;
	// vertical_wall
	if (wall == 'v') {
		int xwv, ywv;
		// enter the y and x of your vertical wall
		cout << "enter the y of wall : \n";
		cin >> xwv;
		cout << "enter the x of wall : \n";
		cin >> ywv;
		if ((arr[(xwv * 2) - 1][ywv * 6] == '|' || arr[(xwv * 2) + 1][ywv * 6] == '|') || (arr[(xwv * 2)][(ywv * 6) - 3] == '=' && arr[(xwv * 2)][(ywv * 6) + 3] == '='))
		{
			system("cls");
			cout << "this situation is ful! try again\n\n";
			wall2++;
			player2(arr);
		}
		arr[(xwv * 2) - 1][ywv * 6] = '|';
		arr[(xwv * 2) + 1][ywv * 6] = '|';
		// praper visiteda for check surrrounding
		for (int i = 0; i < 19; i++)
			for (int j = 0; j < 55; j++)
				visitedb[i][j] = 0;
		// praper visiteda for check surrrounding
		for (int i = 0; i < 19; i++)
			for (int j = 0; j < 55; j++)
				visiteda[i][j] = 0;
		// check surrrounding
		if ( check_surrounding_for_palyer1(xa, ya, arr, visitedb) ||  check_surrounding_for_palyer2(xb, yb, arr, visiteda) )
		{
			// turn the ful wall to empty for desicion again
			arr[(xwv * 2) - 1][ywv * 6] = ' ';
			arr[(xwv * 2) + 1][ywv * 6] = ' ';
			system("cls");
			cout << "you can't surround a player  with wall" << endl;
			wall2++;
			player2(arr);
		}
	}
	//horizental_wall
	else if (wall == 'h') {
		int xwh, ywh;
		// enter the y and x of your horizental wall
		cout << "enter the y of wall : \n";
		cin >> xwh ;
		cout << "enter the x of wall : \n";
		cin >> ywh;
		if ( arr[(xwh * 2)][(ywh * 6) - 3] == '=' || arr[(xwh * 2)][(ywh * 6) + 3] == '=' || (arr[(xwh * 2) - 1][ywh * 6] == '|' && arr[(xwh * 2) + 1][ywh * 6] == '|')) {
			system("cls");
			cout << "this situation is full! try again\n\n";
			wall2++;
			player2(arr);
		}
		arr[(xwh * 2)][(ywh * 6) - 3] = '=';
		arr[(xwh * 2)][(ywh * 6) + 3] = '=';
		// praper visiteda for check surrrounding
		for (int i = 0; i < 19; i++)
			for (int j = 0; j < 55; j++)
				visitedb[i][j] = 0;
		// praper visiteda for check surrrounding
		for (int i = 0; i < 19; i++)
			for (int j = 0; j < 55; j++)
				visiteda[i][j] = 0;
		if ( check_surrounding_for_palyer1(xa, ya, arr, visitedb) ||  check_surrounding_for_palyer2(xb, yb, arr, visiteda) )
		{			
			// turn the ful wall to empty for desicion again
			arr[(xwh * 2) ][(ywh * 6)+3] = ' ';
			arr[(xwh * 2) ][(ywh * 6)-3] = ' ';
			system("cls");
			cout << "you can't surround a player  with wall" << endl;
			wall2++;
			player2(arr);
		}
	}
	else {
		cout << "this choice is invalide!!\ntry again";
		wall_B(arr);
	}
} 
//this two function use for check surrounding of players
bool check_surrounding_for_palyer1(int xaf, int yaf, char arr[][WIDTH], int visitedb[][55])
{
	// we set the visitedb[xaf][yaf] = 1 in each cycle that this function call itself
	visitedb[xaf][yaf] = 1;
	// if this statment occur it means that the player 1 can reach the top wall row
	if (arr[xaf - 1][yaf] == '-')
	{
		return false;
	}
	// for check surrounding at up
	else if (arr[xaf - 1][yaf] != '='   &&  visitedb[xaf -2][yaf] != 1)//up
	{
		xaf -= 2;
		check_surrounding_for_palyer1(xaf, yaf, arr, visitedb);
	}
	// for check surrounding at right
	else if (arr[xaf][yaf + 3] != '|' && visitedb[xaf][yaf + 6] != 1)//right
	{
		yaf += 6;
		check_surrounding_for_palyer1(xaf, yaf, arr, visitedb);
	}
	// for check surrounding at down
	else if (arr[xaf + 1][yaf] != '='&& arr[xaf + 1][yaf] != '-' && visitedb[xaf + 2][yaf] != 1)//down
	{
		xaf += 2;
		check_surrounding_for_palyer1(xaf, yaf, arr, visitedb);
	}
	// for check surrounding at left
	else if (arr[xaf][yaf - 3] != '|' && visitedb[xaf][yaf - 6] != 1)//left
	{
		yaf -= 6;
		check_surrounding_for_palyer1(xaf, yaf, arr, visitedb);
	}
	// if this statment occur it means that the player 1 can't reach the top wall row
	else{
		return true;
	}
	
}
bool check_surrounding_for_palyer2(int xbf, int ybf, char arr[][WIDTH], int visiteda[][55])
{
	// we set the visitedb[xaf][yaf] = 1 in each cycle that this function call itself
	 visiteda[xbf][ybf] = 1;
	// if this statment occur it means that the player 2 can reach the down wall row
	if (arr[xbf + 1][ybf] == '-')
	{
		return false;
	}
	// for check surrounding at up
	else if (arr[xbf - 1][ybf] != '=' && arr[xbf - 1][ybf] != '-' && visiteda[xbf - 2][ybf] != 1)//up
	{
		xbf -= 2;
		check_surrounding_for_palyer2(xbf, ybf, arr, visiteda);
	}
	// for check surrounding at right
	else if (arr[xbf][ybf + 3] != '|' && visiteda[xbf][ybf + 6] != 1)//right
	{
		ybf += 6;
		check_surrounding_for_palyer2(xbf, ybf, arr, visiteda);
	}
	// for check surrounding at down
	else if (arr[xbf + 1][ybf] != '=' && visiteda[xbf + 2][ybf] != 1)//down
	{
		xbf += 2;
		check_surrounding_for_palyer2(xbf, ybf, arr, visiteda);
	}
	// for check surrounding at left
	else if (arr[xbf][ybf - 3] != '|' && visiteda[xbf][ybf - 6] != 1)//left
	{
		ybf -= 6;
		check_surrounding_for_palyer2(xbf, ybf, arr, visiteda);
	}
	// if this statment occur it means that the player 2 can't reach the down wall row
	else {
		return true;
	}
}
