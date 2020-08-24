
#include <stdlib.h>  
#include <iostream>
#include <time.h> 
#include "RatATat.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
using namespace std;

void test();
int main() {


	test();
	cout << "\nleaks: " << _CrtDumpMemoryLeaks() << endl;;
	return 0;

}
void test() {
	srand(time(NULL));
	RatAtat rat;
	rat.add_player("Human1");
	rat.add_player("Human2");
	rat.add_player("Human3");
	rat.add_player("Human4");
	rat.add_player("Human5");
	
	rat.play();
}