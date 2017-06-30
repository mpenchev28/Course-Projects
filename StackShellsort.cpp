//Stack sorted with Shellsort method (no arrays used).
#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;


int br = 0; //брояч дължина на стек
bool flag2 = false;
int n = 0;
int br1 = 0;
int br2 = 0;

struct elem {
	int key;
	elem *next;
} *stack, *s1, *s2, *s3, *s4, *w8;

int count_n();
elem *push(elem *st, int value);
elem *pop(elem *st, int &value);
void sort();
void stack_apart();
void help_reverserLOW();
void help_reverserHIGH();
void Save_to_file(elem *st);
void Get_from_file();
void printStack();
void find(elem *st);

int main() {
	int choice;
	//MENU
	do {
		do {
			cout << "1. Creating Stack." << endl;
			cout << "2. Sorting the elements with Shell's method." << endl;
			cout << "3. Finding the largest and smallest element devisable by 5.\n   /They will be deleted at the end of this operation/" << endl;
			cout << "4. Add results in the file." << endl;
			cout << "5. Exit" << endl;
			cin >> choice;
		} while (choice<1 || choice>5);
		switch (choice) {
		case 1:
			Get_from_file();
			printStack();
			break;
		case 2:
			count_n();
			sort();
			//printStack();
			break;
		case 3:
			find(stack);
			break;
		case 4:
			Save_to_file(stack);
			break;
		case 5:
			exit(1);
		}
	} while (choice != 6);



	system("pause");
	return 0;
}

elem *push(elem *st, int value) {				// вмъква елемент в стека
	elem *top;				// временен указател към първия елемент (върха)
	top = new elem;				// заделяме памет за новия елемент
	top->key = value;				// присвояваме данните
	top->next = st;				// насочваме 'следващия' към предишния първи
	st = top;
	return top;
}
elem *pop(elem *st, int &value) {
	elem *top; // указател към върха на структурата на подаден стек
	value = st->key;
	top = st;
	st = st->next;
	delete top;
	return st;
}
void Get_from_file() { // Извличане данни от файл и добавяне в стек
	int x;
	ifstream inputFile;
	inputFile.open("Input.txt");
	while (!(inputFile.eof())) {
		inputFile >> x; // записваме данните през променливата х и ги
		stack = push(stack, x); // довавяме в стека с push(stack, x);
		br++;
	}
	inputFile.close();
}
void Save_to_file(elem *st) { // Функция за запис на вече сортирания стек
	ofstream outputFile;
	outputFile.open("Output.txt", ios::trunc); /*създаваме фаил или изчистваме съдържанието на
											   вече създаден файл отворен за запис*/
	while (st) {
		outputFile << st->key << "\n"; // Записва стойността на върха на основния стек
		st->next; // сочи предходния елемент преди върха(следващия надолу елемент)
	}
outputFile.close();
}
void printStack() {
	int num;
	elem *temp; 
	temp = NULL;
	cout << "Stack: ";
	while (stack) {
		stack = pop(stack, num);
		cout << num << " | ";
		temp = push(temp, num);
	}
	cout << endl;
	cout << endl;
	while (temp) {
		temp = pop(temp, num);
		stack = push(stack, num);
	}

}
void stack_apart() {  
	cout << "STACK APART" << endl;
	int num;				// помощна променлива за запис на стойности в стек
	for (int i=0; i < (br/2); i++) {
		stack = pop(stack, num); // извлича най-горния елемент на стек
		s1 = push(s1, num); // поставя този елемент във временния стек temp
		cout << "FOR NUM: " << num << endl;
		num = 0;
		br1++;
	}
	while (stack) {
		stack = pop(stack, num); // пресипва остатъка от основния стек
		s2 = push(s2, num); // във временния стек за преобръщане temp
		cout << "WHILE NUM: " << num << endl;
		num = 0;
		br2++;
	}
}
void help_reverserLOW() {
	int num;
	while (s3) {
		s3 = pop(s3, num);
		s1 = push(s1, num);
		num = 0;
	}
	while (s1) {
		s1 = pop(s1, num);
		s2 = push(s2, num);
		num = 0;
	}
	while (s2) {
		s2 = pop(s2, num);
		stack = push(stack, num);
		num = 0;
	}

}
void help_reverserHIGH(){
	int num;
	while (s4) {
		s4 = pop(s4, num);
		s1 = push(s1, num);
		num = 0;
	}
	while (s1) {
		s1 = pop(s1, num);
		s2 = push(s2, num);
		num = 0;
	}
	while (s2) {
		s2 = pop(s2, num);
		stack = push(stack, num);
		num = 0;
	}

}
void find(elem *st) {
	int num;
	int count = 0;
	elem *temp = new elem;
	elem *theRest = new elem;
	while (stack) {
		stack = pop(stack, num);
		if ((num % 5) == 0) {
			temp = push(temp, num);
			count++;
		}
		else {
			theRest = push(theRest, num);
		}
	}
	//sort();
	for (int i = 0; i <= count; i++) {
		temp = pop(temp, num);
		if (i == 0) {
			cout << "Max number: " << num << endl;
		}
		if (i == count) {
			cout << "Min number: " << num << endl;
		}
		theRest = push(theRest, num);
	}
	while (theRest) {
		stack = push(stack, num);
	}
}
int count_n() {
	if (br % 2 == 0) {
		n = br / 2;
		return n;
	}
	else {
		n = br / 2 + 1;
		return n;
	}

}

void sort() {
	int flag = false;
	int num = 0;
	int x = 0;
	int y = 0;
	int h_num;
	int c1, c2, c3, c4; //count variables
	c1 = c2 = c3 = c4 = 0;
//PART1 (n/2)
	cout << "PART1" << endl;
	stack_apart();
	for (int j = 0; j < n; j++) {
		if (br1 != 0) {
			s1 = pop(s1, x);
			br1--;
		}
		if (br2 != 0) {
			s2 = pop(s2, y);
			br2--;
		}
		if (x<=y) {
			s3 = push(s3, x);
			s4 = push(s4, y);
		}
		if (x > y) {
			s3 = push(s3, y);
			s4 = push(s4, x);
		}
		else{
			cout << "Nope!" << endl;
		}
	}
	help_reverserLOW();
	help_reverserHIGH();
//PART2 (n/4)
	cout << "PART2" << endl;
	for (int i = n / 2; i > 0;i--) {
		stack = pop(stack, h_num);
		s1 = push(s1, h_num);
	}
	for (int i = n / 2; i > 0; i--) {
		stack = pop(stack, h_num);
		s2 = push(s2, h_num);
	}
	for (int i = n / 2; i > 0; i--) {
		stack = pop(stack, h_num);
		s3 = push(s3, h_num);
	}
	for (int i = n / 2; i > 0; i--) {
		stack = pop(stack, h_num);
		s4 = push(s4, h_num);
	}
	//s3 <-> s4
	for (int i = n / 2; i > 0; i--) {
		s3 = pop(s3, x);
		s4 = pop(s4, y);
		if (x <= y) {
			stack = push(stack, x);
			w8 = push(w8, y);
		}
		if (x > y) {
			w8 = push(w8, x);
			stack = push(stack, y);
		}
		else {
			cout << "NOPE s3 <-> s4!!!" << endl;
		}
	}
	while (w8) {
		w8 = pop(w8, h_num);
		s3 = push(s3, h_num);
	}
	//s1 <-> s3
	for (int i = n / 2; i > 0; i--) {
		s1 = pop(s1, x);
		s3 = pop(s3, y);
		if (x <= y) {
			stack = push(stack, x);
			w8 = push(w8, y);
		}
		if (x > y) {
			w8 = push(w8, x);
			stack = push(stack, y);
		}
		else {
			cout << "NOPE s1 <-> s3" << endl;
		}
	}
	while (w8) {
		w8 = pop(w8, h_num);
		s1 = push(s1, h_num);
	}
	//s1 <-> s2
	for (int i = n / 2; i > 0; i--) {
		s1 = pop(s1, x);
		s2 = pop(s2, y);
		if (x <= y) {
			stack = push(stack, x);
			w8 = push(w8, y);
		}
		if (x > y) {
			w8 = push(w8, x);
			stack = push(stack, y);
		}
		else {
			cout << "NOPE s1 <-> s2" << endl;
		}
	}
	while (w8) {
		w8 = pop(w8, h_num);
		s1 = push(s1, h_num);
	}
	while (s1) {
		s1 = pop(s1, h_num);
		stack = push(stack, h_num);
	}
	printStack();
//PART3 (n/n)
	cout << "PART3" << endl;
	for (int i = n * 2; i > 0; i--) {
		//EVEN numbers
		while (stack) {
			stack = pop(stack, x);
			s1 = push(s1, x);
			stack = pop(stack, y);
			s2 = push(s2, y);
		}
		for (int i = n; i > 0; i--) {
			s1 = pop(s1, x);
			cout << "S1: " << x << endl;
			s2 = pop(s2, y);
			cout << "S2: " << y << endl;
			if (x <= y) {
				stack = push(stack, x);
				stack = push(stack, y);
				c1++; //expected c1 = n = 6
			}
			else {
				if (x > y) {
					stack = push(stack, y);
					stack = push(stack, x);
				}
				else {
					cout << "NOPE PART3" << endl;
				}
			}
		}
		printStack();
		system("pause");
		//ODD numbers
		stack = pop(stack, h_num);
		s1 = push(s1, h_num);
		for (int i = n - 1; i > 0; i--) {
			stack = pop(stack, x);
			s2 = push(s2, x);
			stack = pop(stack, y);
			s3 = push(s3, y);
			x = 0;
			y = 0;
		}
		//s2 <-> s3
		cout << "ODD s2 <-> s3" << endl;
		for (int i = n - 1; i > 0; i--) {
			cout << "FOR h_num: " << h_num << endl;
			s2 = pop(s2, x);
			s3 = pop(s3, y);
			if (x <= y) {
				stack = push(stack, x);
				stack = push(stack, y);
				c2++; //expected x2 = n-1 = 5
			}
			else {
				if (x > y) {
					stack = push(stack, y);
					stack = push(stack, x);
				}
				else {
					cout << "NOPE s2 <-> s3 (PART3)" << endl;
				}
			}
		}
		s1 = pop(s1, h_num);
		cout << "h_num: " << h_num << endl;
		stack = push(stack, h_num);
		printStack();
		cout << "c1: " << c1 << endl;
		cout << "c2: " << c2 << endl;
		cout << "c3: " << c3 << endl;
		cout << "c4: " << c4 << endl;
		cout << "\n";
		c1 = c2 = 0;
	}

//SORTED
	cout << "Stack is sorted!" << endl;
	printStack();
}
