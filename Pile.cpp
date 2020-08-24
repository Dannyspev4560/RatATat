#include <iostream>
#include "Pile.h"
#include "Card.h"
using namespace std;
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//current

Dequeue::Dequeue(char size) //Constructor
{
	m_size = size;
	if (size == 0) {
		m_queue = new Card * [54];//need to delete in the end
		memset(m_queue,0, sizeof(Card*)*54);
	}
	else 
	m_queue = new Card * [size];
	m_capacity = 54;
	m_left = 0;
	m_right = size - 1;

	
	if (size != 0) {
		for (int i = 0; i < size; i++) {

			if (i < 24)
			{
				char card_val = Cat_card::toss_val();
				m_queue[i] = (new Cat_card(card_val));
			}
			else if (i < 45)
			{
				char card_val = Rat_card::toss_val();
				m_queue[i] = (new Rat_card(card_val));
			}
			else if (i < 48) {
				m_queue[i] = new Swap_card;
			}
			else if (i < 51) {
				m_queue[i] = new Draw2_card;
			}
			else {
				m_queue[i] = new Peek_card;
			}

		}
		reshuffle();
	}
}

Dequeue::~Dequeue() //Destructor
{
	for (int i = 0; i < 54; i++)
	{
		if (m_queue[i]!=nullptr)delete m_queue[i];
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
	
	if ((--m_left) < 0)
		m_left = 53;
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
Dequeue::Dequeue(const Dequeue& deq) {
	cout << "CC";//for debugging
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
		//tmp= rand() % 54; //random cell between 0 to 53 to swap
		tmp = rand() % m_size;
		swap(m_queue[tmp], m_queue[m_right]);
		m_right--;

	}
	//m_right = 53;
	m_right = m_size - 1;
}

