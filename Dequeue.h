#ifndef  DEQUEUE_H_
#define  DEQUEUE_H_
#include "Card.h" 

class Dequeue
{
	char m_size;
	char m_capacity;
	Card** m_queue;
	char m_left;
	char m_right;
	
public:
	Dequeue(char size=0);
	~Dequeue();
	void push_back( Card* c);
	Card* pop_back();
	void push_front(Card* c);
	Card* pop_front();
	Card* front() const;
	Card* back() const;
	char size() const;
	bool is_empty() const;
	void reshuffle();
};


#endif // DEQUEUE_H_