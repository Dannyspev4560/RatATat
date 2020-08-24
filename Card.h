#ifndef  CARD_H_
#define  CARD_H_
#include <iostream>
#include <string>
using namespace std;
#include "Player.h"

class RatAtat;
class Card
{
protected:
	
	char m_value;
	string m_text;
	const static char max_cards = 54;
	
public:
	Card(char value,string text); //Constructor
	virtual ~Card() = 0 {} //Destructor
	Card(const Card& c); //Copy Constructor
	friend ostream& operator<<(ostream& os, const Card& c);
	char get_value()const ;
	
	virtual void use(Player** players, int curr_player, RatAtat& rat) = 0;
	virtual void print_card_action_menu() const = 0;// for every card espically the specail cards different menu will be printed
	virtual int get_card_action_menu_max_num() const = 0;//number of options to choose every round
	
	
};

class Play_card: public Card
{
public:
	
	Play_card(char val, string text);
	virtual ~Play_card()=0{}
	void print_card_action_menu() const;
	void use(Player** players, int curr_player, RatAtat& rat);
};

class Rat_card : public Play_card {

	static int num_cards;
	static char m_cards_type[4];
public:
	Rat_card(char val);
	~Rat_card() { num_cards--; }
	static int get_total_cards() { return num_cards; };
	static char toss_val();
	int get_card_action_menu_max_num() const { return 2; };
};

class Cat_card : public Play_card {

	static int num_cards;
	static char m_cards_type[6];
public:
	Cat_card(char val);
	~Cat_card(){ num_cards--; }
	static int get_total_cards() { return num_cards; };
	static char toss_val() ;
	int get_card_action_menu_max_num() const { return 2; };
};

//---------------------------------------------
class Special_card : public Card
{

public:
	Special_card(string text);
	virtual ~Special_card() = 0 {}
	void print_card_action_menu() const;
};

class Draw2_card : public Special_card {
protected:
	static int num_cards;
public:
	Draw2_card();
	~Draw2_card() { num_cards--; }
	static int get_total_cards() { return num_cards; };
	void use(Player** players, int curr_player, RatAtat& rat);
	int get_card_action_menu_max_num() const { return 2; };
};

class Swap_card : public Special_card {
protected:
	static int num_cards;
public:
	Swap_card();
	~Swap_card() { num_cards--; }
	static int get_total_cards() { return num_cards; };
	void use(Player** players, int curr_player, RatAtat& rat);
	int get_card_action_menu_max_num() const { return 2; };
};

class Peek_card : public Special_card {
protected:
	static int num_cards;
public:
	Peek_card();
	~Peek_card() {  num_cards--;  }
	static int get_total_cards() { return num_cards; };
	void use(Player** players, int curr_player, RatAtat& rat);
	int get_card_action_menu_max_num() const { return 2; };//TODO
};


	

#endif // CARD_H_
