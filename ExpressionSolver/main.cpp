#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <locale.h>
#include <ctime>

struct Node
{
	char value[20];
	Node* left;
	Node* right;
};

int isoperation(char symbol)
{
	switch (symbol)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	default:
		return 0;
		break;
	}
}

bool check_for_correct_brackets(char* str)
{
	int opening_bracket = 0, closing_bracket = 0, p = 0;
	for (int i = 0; i < strlen(str); ++i) {
		if (closing_bracket > opening_bracket)
			return 0;
		else if ((str[i] == '(') && (str[i + 1] == ')'))
			return 0;
		else if ((str[i] == '(') && isoperation(str[i + 1]))
			p = 1;
		else if ((str[i + 1] == ')') && isoperation(str[i]) && (p == 1))
			return 0;
		else if ((isalnum(str[i])) && (str[i + 1] == '('))
			return 0;
		else if ((isalnum(str[i + 1])) && (str[i] == ')'))
			return 0;
		else if (!(isalnum(str[i]) || isoperation(str[i]) || (str[i] == '(') || (str[i] == ')') || (str[i] == ',')))
			return 0;
		else
			p = 0;

		if (str[i] == '(')
			++opening_bracket;
		if (str[i] == ')')
			++closing_bracket;
	}

	if (opening_bracket == closing_bracket)
		return 1;
	else
		return 0;
}

bool isNumber(char c)
{
	if (!strchr("0123456789", c))
		return 0;
	return 1;
}

bool check_for_comma(char* str)
{
	int p = 0;
	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == ',')
			p++;

		if ((str[i] == ',') && (!isNumber(str[i + 1])))
			return 0;
		else if ((str[i + 1] == ',') && (!isNumber(str[i])))
			return 0;
		else if ((str[i] == ',') && (i == 0))
			return 0;
		else if ((str[i] == ',') && (i == strlen(str) - 1))
			return 0;
		else if (!isNumber(str[i]) && (str[i] != ','))
			p = 0;

		if (p > 1)
			return 0;
	}
	return 1;
}

char* insert_null(char* str, int k)
{
	char* newstr = new char[100];
	for (int i = 0; i < k; ++i)
		newstr[i] = str[i];
	newstr[k] = '0';
	for (int i = k + 1; i < strlen(str) + 2; ++i)
		newstr[i] = str[i - 1];
	return newstr;
}

bool validation_of_operation(char* str)
{
	for (int i = 0; i < strlen(str); ++i) {
		if ((isoperation(str[i + 1]) == 2) && (str[i] == '('))
			return 0;

		else if ((isoperation(str[i]) == 2) && (i == 0))
			return 0;

		else if ((isoperation(str[i])) && ((i + 1 == strlen(str)) || (str[i + 1] == ')')))
			return 0;

		else if ((isoperation(str[i]) == 2) && (i == 0))
			return 0;

		else if ((isoperation(str[i])) && (isoperation(str[i + 1])))	//åñëè äâå îïåğàöèè ïîäğÿä - âûõîä
			return 0;
	}

	return 1;
}

char* insert_bracket_for_variable(char** str)
{
	int p = 0, start = 0, end = 0;
	char* perem = new char[10];
	for (int i = 0; i <= strlen(*str); ++i) {
		if (isalpha((*str)[i]) && (p == 0)) {
			start = i;
			end = i;
			p = 1;
		}
		else if (!((isoperation((*str)[i]) != 0) || ((*str)[i] == '(') || ((*str)[i] == ')') || ((*str)[i] == '\0'))
			&& (p == 1)) {
			p = 1;
			end = i;
		}
		else if (p == 1){
			for (int j = strlen(*str); j >= start; --j)
				(*str)[j + 1] = (*str)[j];
			(*str)[start] = '(';
			for (int j = strlen(*str); j >= end + 2; --j)
				(*str)[j + 1] = (*str)[j];
			(*str)[end + 2] = ')';
			p = 0;
		}
	}
	return (*str);
}

char* variable_initialization(char* str, int r)
{
	char* perem = new char[20], *var = new char[20], *povt_perem = new char[10];
	int p = 0, start = 0, end = 0, int_var = 0;
	perem[0] = '\0';
	povt_perem[0] = '\0';
	int c = 0;
	for (int i = 0; i < strlen(str) + 1; ++i) {
		if (isalpha(str[i]) && (p == 0)) {
			perem[strlen(perem) + 1] = '\0';
			perem[strlen(perem)] = str[i];
			start = i;
			end = i;
			p = 1;
		}
		else if (!((isoperation(str[i]) != 0) || (str[i] == '(') || (str[i] == ')') || (str[i] == '\0'))
			&& (p == 1)) {
			perem[strlen(perem) + 1] = '\0';
			perem[strlen(perem)] = str[i];
			p = 1;
			end = i;
		}
		else if (p == 1) {
			printf("Èíèöèàëèçèğóéòå ïåğåìåííóş %s: ", perem);
			if (r == 1)
				std::cin >> var;
			else {
				int_var = rand() % (101)-50;
				std::cout << int_var << std::endl;
				_itoa_s(int_var, var, 10, 10);
			}
			if (end - start + 1 >= strlen(var)) {
				for (int j = start + strlen(var) - 1; j < end; ++j)
					for (int y = start; y < strlen(str); ++y)
						str[y] = str[y + 1];
				for (int j = start; j < start + strlen(var); ++j) {
					str[j] = var[c];
					++c;
				}
			}
			else {
				if (i != strlen(str)) {
						for (int j = end - start + 1; j < strlen(var); ++j)
							for (int y = strlen(str); y >= end + 1; --y)
								str[y + 1] = str[y];
						for (int j = start; j < start + strlen(var); ++j) {
							str[j] = var[c];
							++c;
						}
				}
				else {
					for (int j = 1; j < strlen(var); ++j)
						str[strlen(str) + j] = '\0';
					for (int j = start; j < start + strlen(var); ++j) {
						str[j] = var[c];
						++c;
					}
				}
			}
			p = 0;
			c = 0;
			for (int z = end + 1; z < strlen(str) + 1; ++z) {
				if (isalpha(str[z]) && (p == 0)) {
					povt_perem[strlen(povt_perem) + 1] = '\0';
					povt_perem[strlen(povt_perem)] = str[z];
					p = 1;
					start = z;
					end = z;
				}
				else if (!((isoperation(str[z]) != 0) || (str[z] == '(') || (str[z] == ')') || (str[z] == '\0'))
					&& (p == 1)) {
					povt_perem[strlen(povt_perem) + 1] = '\0';
					povt_perem[strlen(povt_perem)] = str[z];
					end = z;
					p = 1;
				}
				else if (!strcmp(perem, povt_perem)) {
					c = 0;
					if (end - start + 1 >= strlen(var)) {
						for (int j = start + strlen(var) - 1; j < end; ++j)
							for (int y = start; y < strlen(str); ++y)
								str[y] = str[y + 1];
						for (int j = start; j < start + strlen(var); ++j) {
							str[j] = var[c];
							++c;
						}
					}
					else {
						if (z != strlen(str)) {
							for (int j = end - start + 1; j < strlen(var); ++j)
								for (int y = strlen(str); y >= end + 1; --y)
									str[y + 1] = str[y];
							for (int j = start; j < start + strlen(var); ++j) {
								str[j] = var[c];
								++c;
							}
						}
						else {
							for (int j = 1; j < strlen(var); ++j)
								str[strlen(str) + j] = '\0';
							for (int j = start; j < start + strlen(var); ++j) {
								str[j] = var[c];
								++c;
							}
						}
					}
					p = 0;
					c = 0;
					z = z - strlen(perem);
					povt_perem[0] = '\0';
				}
				else {
					p = 0;
					c = 0;
					povt_perem[0] = '\0';
				}
			}
			i = i - strlen(perem);
			p = 0;
			c = 0;
			perem[0] = '\0';
		}
	}
	return str;
}

char* unary_operation(char** str)
{
	for (int i = 0; i < strlen(*str); ++i) {
		if ((isoperation((*str)[i + 1]) == 1) && ((*str)[i] == '('))
			(*str) = insert_null((*str), i + 1);

		else if ((isoperation((*str)[i]) == 1) && (i == 0))
			(*str) = insert_null((*str), i);

		else if ((isoperation((*str)[i]) == 2) && (isoperation((*str)[i + 1]) == 1))
			(*str) = insert_null((*str), i + 1);

		else if ((isoperation((*str)[i]) == 1) && (isoperation((*str)[i + 1]) == 1))
			(*str) = insert_null((*str), i + 1);
	}

	return (*str);
}

bool search_variable(char* str)
{
	for (int i = 0; i < strlen(str); ++i) {
		if (((int)str[i] > 96) && ((int)str[i] < 123))
			return 1;
	}
	return 0;
}

int isNumber(char* str)
{
	for (int i = 0; i < strlen(str); ++i)
		if (!strchr(",0123456789", str[i]))
			return 0;
	return 1;
}

Node* MakeTree(char* str, int first, int last)
{
	Node* Tree = new Node;
	int priority, min_priority, bracket = 0, k;
	char* piece_str = new char[100], c;

	for (int i = first; i <= last; ++i)
		piece_str[i - first] = str[i];
	piece_str[last - first + 1] = '\0';

	if (first == last) {
		strcpy_s(Tree->value, piece_str);
		Tree->left = NULL;
		Tree->right = NULL;
		return Tree;
	}
	else if (isNumber(piece_str)) {
		strcpy_s(Tree->value, piece_str);
		Tree->left = NULL;
		Tree->right = NULL;
		return Tree;
	}

	min_priority = 100;

	for (int i = first; i <= last; ++i) {
		c = str[i];
		if (c == '(')
			++bracket;
		else if (c == ')')
			--bracket;
		else if (bracket == 0) {
			priority = isoperation(c);
			if (priority && (priority <= min_priority)) {
				min_priority = priority;
				k = i;
			}
		}
	}

	if ((min_priority == 100) && (str[first] == '(') && (str[last] == ')'))
		return MakeTree(str, first + 1, last - 1);
	else {
		Tree->value[1] = '\0';
		Tree->value[0] = str[k];
		Tree->left = MakeTree(str, first, k - 1);
		Tree->right = MakeTree(str, k + 1, last);
	}
	return Tree;
}

int isNumber(Node *Tree)
{
	int i = 0;
	if (!Tree)
		return 0;

	if (strcmp(Tree->value, "-") == 0)
		return 1;

	while (Tree->value[i])
		if (!strchr("-,0123456789", Tree->value[i++]))
			return 0;
	return 1;
}

void FullOrder_ShowTree(Node* MyTree);
void SymmetricOrder_ShowTree(Node* MyTree);
void ReverseOrder_ShowTree(Node* MyTree);
void ShowTree(Node* MyTree);

void Calculate(Node **Tree)
{
	float a, b, c = 0;

	if ((*Tree) == NULL)
		return;
	if (!isNumber((*Tree)->left))
		return;
	if (!isNumber((*Tree)->right))
		return;

	a = atof((*Tree)->left->value);
	b = atof((*Tree)->right->value);

	switch ((*Tree)->value[0]) {
	case '+': c = a + b; break;
	case '-': c = a - b; break;
	case '*': c = a * b; break;
	case '/':
		if (b == 0) {
			puts("\nÎøèáêà. Äåëèòü íà íîëü íåëüçÿ");
			exit(1);
		}
		c = a / b;
		break;
	}

	delete (*Tree)->left;
	delete (*Tree)->right;
	sprintf_s((*Tree)->value, 20, "%f", c);
	(*Tree)->left = NULL;
	(*Tree)->right = NULL;
}

void evaluate(Node** Tree)
{
	if ((*Tree) != NULL) {
		evaluate(&(*Tree)->left);
		evaluate(&(*Tree)->right);
		Calculate(Tree);
	}
}

int main()
{
	setlocale(0, "russian");
	srand(time(NULL));

	char* str = new char[100];
	puts("Ââåäèòå âûğàæåíèå:");	//(k*4-2)/(1+8*(h-3))
	gets_s(str, 100);

	//ÏĞÎÂÅĞÊÀ ÍÀ ÏÓÑÒÎÒÓ ÂÂÎÄÀ//
	if (strlen(str) == 0) {
		puts("Âû íè÷åãî íå ââåëè");
		system("pause");
		return 0;
	}
	
	//ÏĞÎÂÅĞÊÀ ÍÀ ÊÎĞĞÅÊÒÍÎÑÒÜ ÑÊÎÁÎÊ//
	if (!check_for_correct_brackets(str)) {
		puts("Âû ââåëè íåêêîğåêòíîå âûğàæåíèå");
		system("pause");
		return 0;
	}

	//ÏĞÎÂÅĞÊÀ ÍÀ ÊÎĞĞÅÊÒÍÎÑÒÜ ÇÀÏßÒÛÕ//
	if (!check_for_comma(str)) {
		puts("Âû ââåëè íåêêîğåêòíîå âûğàæåíèå");
		system("pause");
		return 0;
	}

	//ÏĞÎÂÅĞÊÀ ÍÀ ÊÎĞĞÅÊÒÍÎÑÒÜ ÎÏÅĞÀÖÈÉ//
	if (!validation_of_operation(str)) {
		puts("Âû ââåëè íåêêîğåêòíîå âûğàæåíèå");
		system("pause");
		return 0;
	}

	int r;
	//ÈÍÈÖÈÀËÈÇÀÖÈß ÏÅĞÅÌÅÍÍÛÕ//
	if (search_variable(str)) {
		str = insert_bracket_for_variable(&str);
		do {
			puts("\nÂûáåğèòå ğåæèì èíèöèàëèçâàöèè ïåğåìåííûõ:\n"
				"\t1 - âğó÷íóş\n"
				"\t2 - àâòîìàòè÷åñêè");
			std::cin >> r;
		} while ((r < 1) && (r > 2));

		str = variable_initialization(str, r);
	}

	//ÏĞÎÂÅĞÊÀ ÍÀ ÊÎĞĞÅÊÒÍÎÑÒÜ ÇÀÏßÒÛÕ//
	if (!check_for_comma(str)) {
		puts("Âû ââåëè íåêêîğåêòíîå âûğàæåíèå");
		system("pause");
		return 0;
	}

	//ÓÑÒĞÀÍÅÍÈÅ ÓÍÀĞÍÛÕ ÎÏÅĞÀÖÈÉ//
	str = unary_operation(&str);

	puts("Ââîä êîğğåêòíûé. Ïğåîáğàçîâàííàÿ ñòğîêà:");
	printf("%s\n", str);

	//ÏÎÑÒĞÎÅÍÈÅ ÄÅĞÅÂÀ//
	Node* MyTree = MakeTree(str, 0, strlen(str) - 1);

	//ÂÛÂÎÄ ÄÅĞÅÂÀ//
	ShowTree(MyTree);
	puts("");

	//ÂÛ×ÈÑËÅÍÈÅ ÂÛĞÀÆÅÍÈß//
	evaluate(&MyTree);

	//ÂÛÂÎÄ ĞÅÇÓËÜÒÀÒÀ ÍÀ İÊĞÀÍ//
	printf("\nĞåçóëüòàò âû÷èñëåíèÿ âûğàæåíèÿ: %s\n", MyTree->value);

	// ÎÑÂÎÁÎÆÄÅÍÈÅ ÏÀÌßÒÈ //
	delete MyTree;
	delete[] str;

	system("pause");
	return 0;
}





void ShowTree(Node* MyTree)
{
	printf("\nÏğÿìîé îáõîä äåğåâà: ");
	FullOrder_ShowTree(MyTree);
	printf("\nÑèììåòğè÷íûé îáõîä äåğåâà: ");
	SymmetricOrder_ShowTree(MyTree);
	printf("\nÎáğàòíûé îáõîä äåğåâà: ");
	ReverseOrder_ShowTree(MyTree);
}

void FullOrder_ShowTree(Node* MyTree)
{
	if (MyTree != NULL) {
		printf("%s ", MyTree->value);
		FullOrder_ShowTree(MyTree->left);
		FullOrder_ShowTree(MyTree->right);
	}
}

void SymmetricOrder_ShowTree(Node* MyTree)
{
	if (MyTree != NULL) {
		SymmetricOrder_ShowTree(MyTree->left);
		printf("%s ", MyTree->value);
		SymmetricOrder_ShowTree(MyTree->right);
	}
}

void ReverseOrder_ShowTree(Node* MyTree)
{
	if (MyTree != NULL) {
		ReverseOrder_ShowTree(MyTree->left);
		ReverseOrder_ShowTree(MyTree->right);
		printf("%s ", MyTree->value);
	}
}