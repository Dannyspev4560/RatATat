#include <iostream>
#include "Player.h"
#include <string>
#include "Card.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

using namespace std;

Player::Player(string name="",RatAtat* game=nullptr):g_ratatat(game)
{
	p_name = name;
	p_cards = new Card * [p_cards_lim];
}


AI_player::AI_player(RatAtat* game) : Player("Computer",game) {

}
Human_Player::Human_Player(string name="", RatAtat* game=nullptr) : Player(name,game) {

}
void Player::add_card(Card* c, int index) {
	p_cards[index] = c;
}

void Player::present_card(const int index) const {
	cout <<  *p_cards[index];
}
ostream& operator<<(ostream& os, const Player& p) {
	os << p.p_name;
	return os;
}

int Player::option_for_player(char cnt_c) const // cnt_c==> number of choices that the player can choose from
{
	char num;
	do
	{
		cin >> num;
	} while (((num-'0')>cnt_c) || ((num-'0')<1));

	return (num-'0');
}

int AI_player:: option_for_player(char cnt_c) const
{
	int val= rand() % cnt_c + 1;
	cout << val<<endl;
	return  val;
}


Card* Player::get_card_p(int index) const
{
	return p_cards[--index];
}
Card* Player:: pull_out_c(int index)
{
	Card* c = (p_cards[--index]);
	p_cards[index] = nullptr;
	return c;
}

void Player::pull_in_c(Card* c, int index)
{
	if (c==nullptr) exit(1);
	p_cards[--index] = c;
	
}

void Player::set_card_p(int index, Card* c)
{
	p_cards[index] = c;
}



char Player::calc_sum_c() const
{
	char sum_c = 0;	// sum of cards
	for (int i = 0; i < p_cards_lim; i < i++)
	{
		sum_c += p_cards[i]->get_value();
	}
	return sum_c;
}





string Player:: get_name() const {
	return p_name;
}

Player:: ~Player() {
	for (int i = 0; i < p_cards_lim; i++)
	{
		delete p_cards[i];
	}
	delete[] p_cards;
	
}


void Player::print_cards() const  {

	cout<<p_name << " Cards before discarding special cards :";
	for (int i = 0; i < p_cards_lim; i++) {
		cout << "    " << *(p_cards[i]);
		while (p_cards[i]->get_value() == -1)//
		{
			
			g_ratatat->pop_c(); 
			Card* c= g_ratatat ->pop_and_push_dpile(p_cards[i]);
			p_cards[i] = nullptr;
			p_cards[i] = c;
		}
	}
	cout << endl;
	
	cout << p_name << " Cards after discarding special cards :";
	for (int i = 0; i < p_cards_lim; i++) 
	{
		cout << "    " << *(p_cards[i]);
	}
	cout << endl;
	
}


