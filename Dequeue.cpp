#include <iostream>
#include "Dequeue.h"
using namespace std;
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


Dequeue::Dequeue(char size) //Constructor
{
	m_size = size;
	m_queue = new Card*  [m_size];//need to delete in the end
	m_capacity = 54;
	m_left = 0;
	m_right = size - 1;

	for (int i = 0; i < size; i++) {
		//int num = Card::toss_val();
		//Card temp(num);
		//m_queue[i] = (new Card(num));
	}
}

Dequeue::~Dequeue() //Destructor
{
	for (int i = 0; i < 52; i++)
	{
		delete m_queue[i];
	}
	delete[] m_queue;
}

void Dequeue::push_back( Card* c)
{
	m_queue[m_right] = c;
	m_size++;
	m_right++;

}

Card* Dequeue::pop_back()
{
	//TODO: check the size and create condition if the size is 0...

	Card* c = (m_queue[m_right]);

	m_queue[m_right] = nullptr;
	m_size--;
	m_right--;
	/*if (m_right == 0) {
		m_right = 51;
	}*/

	return c;
}

void Dequeue::push_front(Card* c)
{
	//if m_left equals 0 break...
	m_left--;
	m_queue[m_left] = c;
	m_size++;
}



Card* Dequeue::pop_front() {
	//check the size and create condition if the size is 0...
	Card* c = (m_queue[m_left]);

	m_queue[m_left] = nullptr;
	m_size--;
	m_left++;
	/*if ((m_left + 1) == 52)
	{
		m_left = 0;

	}*/
	return c;
}


char Dequeue::size() const
{
	return m_size;
}

bool Dequeue::is_empty() const
{
	if (m_size == 0) return true;// empty Dequeue 
	
	return false;
}


Card* Dequeue::front() const 
{
	return(m_queue[m_left]);
}

Card* Dequeue::back() const 
{
	return(m_queue[m_right]);
}

void Dequeue::reshuffle()
{
	int tmp;
	while (m_left != m_right)
	{
		tmp= rand() % 52; //random cell between 0 to 51 to swap
		swap(m_queue[tmp], m_queue[m_right]);
		m_right--;

	}
	m_right = 51;
}

