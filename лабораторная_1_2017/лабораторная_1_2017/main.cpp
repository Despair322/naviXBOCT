#include <iostream>
#include "iterator.h"
#include <conio.h>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
    Iterator a("D:\\1542\\GG", "*");
    FileItem *b;

    while (a.hasMore()){
        b = a.next();
        std::cout << b->fname.c_str() << "  ::  " << b->fMask.c_str() << "\n";
		delete b;
    }
	_getch();
    return 0;
}
