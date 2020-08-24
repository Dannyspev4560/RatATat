#include <iostream>
#include "Card.h"
#include <stdlib.h> 
#include <bits.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


using namespace std;

char Cat_card::m_cards_type[6] = { 0 };
char Rat_card::m_cards_type[4] = { 0 };
int Rat_card::num_cards(0);
int Cat_card::num_cards(0);
int Swap_card::num_cards(0);
int Peek_card::num_cards(0);
int Draw2_card::num_cards(0);

Card::Card(char val, string text) {
	m_value = val;
	m_text = text;
}

Play_card::Play_card(char val, string text):Card(val,text) 
{
	
}

Rat_card::Rat_card(char val) : Play_card(val, "Rat") {
	num_cards++;
}
Cat_card::Cat_card(char val) : Play_card(val, "Cat") {
	num_cards++;
}



char Cat_card:: toss_val() //Get random num for cat
{
	int val;
	do 
	{
		val = rand() % 5;
	} while (m_cards_type[val] == 4);
	return (char)val;
}




char Rat_card::toss_val() //Get random num for rat
{
	int val;
	do 
	{
		val = rand() % 4 + 6;
	} while ((m_cards_type[val - 6] == 4 && val!=9) || m_cards_type[3] == 9);
	return (char)val;
}
char Card::get_value()const {
	return m_value;
}

Special_card::Special_card(string text) :Card(-1, text) {}

Swap_card::Swap_card():Special_card("Swap"){
	num_cards++;
}

Peek_card::Peek_card() : Special_card("Peek") {
	num_cards++;
}

Draw2_card::Draw2_card() : Special_card("Draw2") {
	num_cards++;
}

void Special_card:: print_card_action_menu() const {
	cout << "choose option:\n1. Dicard without use \n2. Use special card" << endl;
}

void Play_card::print_card_action_menu() const {
	cout << "choose option:\n1. Discard\n2. Replace with one of my cards" << endl;
}


void Play_card::use(Player** players, int curr_player, RatAtat& rat)
{

	cout << "which card do you want to replace? 1...4 from left to right"<<endl;

	int input= players[curr_player]->option_for_player(4);
	
	
	Card* c = rat.pop_and_push_dpile(players[curr_player]->pull_out_c(input));
	players[curr_player]->pull_in_c(c,input);
}


void Draw2_card::use(Player** players, int curr_player, RatAtat& rat) {
	char choice;
	int i = 0;
	while (i < 2)//draw can itirate two times maximum
	{
		
		cout << "Draw another card" << endl;
		
		Card* tmp = rat.pop_c();
		if (curr_player>0) cout << *(tmp) << endl;//check if human
		tmp->print_card_action_menu();
		choice=players[curr_player]->option_for_player(tmp->get_card_action_menu_max_num());
		
		if (choice == 2)//choice 2 means we want to use the card 
		{
			tmp->use(players, curr_player, rat);
			break;
		}
		i++;
	}
	
}
void Peek_card::use(Player** players, int curr_player, RatAtat& rat) {
	char choice;
	if (rat.get_total_players() > 2)
	{
		if (curr_player > 0)
		{
			cout << "which player you want to Peek: "; //check if human
			for (int i = 0; i < rat.get_total_players(); i++)
			{
				if (i != curr_player)
					cout << *(players[i]) << " ";
			}
			cout << endl;
		}

		do
		{
			choice = players[curr_player]->option_for_player(rat.get_total_players());
		} while ((--choice) == curr_player);//--choice beacuse p_arr goes from 0 to cnt_players-1
	}
	//if there are only two players to choose beetween, we will choose to peak the other one
	else curr_player == 0 ? choice = 1 : choice = 0;
	cout << "which card do you want to peek? 1...4 from left to right" << endl;
	int input_opponent = players[curr_player]->option_for_player(4);
	if (curr_player > 0)
	cout << "	" << *(players[choice]->get_card_p(input_opponent)) << endl;

}
void Swap_card::use(Player** players, int curr_player, RatAtat& rat) {
	char choice ;
	if (rat.get_total_players() > 2)
	{
		if (curr_player > 0)
		{
			cout << "which player you want to Swap: ";
			for (int i = 0; i < rat.get_total_players(); i++)
			{
				if (i != curr_player)
					cout << *(players[i]) << " ";
			}
			cout << endl;
		}
		do
		{
			choice = players[curr_player]->option_for_player(rat.get_total_players());
		} while ((--choice) == curr_player);//--choice beacuse p_arr goes from 0 to cnt_players-1
			//choose the opponent
			//cout << "which card do you want to replace from the opponent? 1...4 from left to right" << endl;
			//int input_oppennt = players[curr_player]->option_for_player(4);
		
		
	}
	else curr_player == 0 ? choice = 1 : choice = 0;
		cout << "which card do you want to replace? 1...4 from left to right" << endl;
		int input_mine = players[curr_player]->option_for_player(4);
		//cout << *(players[curr_player]->get_card_p(input_mine));//not needed- for us
		cout << "which card do you want to replace from the opponent? 1...4 from left to right" << endl;
		int input_oppennt= players[curr_player]->option_for_player(4);

		Card* c_opponnent= players[choice]->pull_out_c(input_oppennt);//receive the card i want
		Card* c_mine= players[curr_player]->pull_out_c(input_mine);//dispose the card i chose

		players[curr_player]->pull_in_c(c_opponnent, input_mine);
		players[choice]->pull_in_c(c_mine, input_oppennt);
		
}
ostream& operator<<(ostream& os, const Card& c)
{
	if (c.m_value >= 0)
	{
		os << c.m_text << ", " << (int)c.m_value;
	}
	else
		os << c.m_text;

	return os;

}



	




