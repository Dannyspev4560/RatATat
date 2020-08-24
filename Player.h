#ifndef  PLAYER_H_
#define  PLAYER_H_


#include <iostream>
#include "RatATat.h"
class Card;
using namespace std;
class Player
{
protected:
	
	
	string p_name;
	
	RatAtat* g_ratatat;
	Card** p_cards;
	

	
public:
	static const char p_cards_lim = 4;
	Player(string  ,RatAtat* );
	virtual ~Player()=0;//pure virtual destructor - we wont declare player class
	
	void add_card(Card* c,int index);
	void present_card(const int index) const;
	virtual int option_for_player(char) const ;// print the options for
	Card* get_card_p(int index)const;
	void set_card_p(int index, Card*);
	Card* pull_out_c(int index);
	void pull_in_c(Card*,int index);
	
	void print_cards() const;
	char calc_sum_c() const;
	string get_name() const;
	//////////Not member if the Player class///////
	friend ostream& operator<<(ostream& os, const Player& p);

};


class AI_player : public Player 
{
public: 
	AI_player(RatAtat* );
	~AI_player(){}
	int option_for_player(char) const ;
};
class Human_Player : public Player {
public:
	Human_Player(string , RatAtat* );
	~Human_Player(){}
};


#endif // PLAYER_H_
