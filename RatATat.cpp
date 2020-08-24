#include <iostream>
#include "Card.h"
#include "RatATat.h"
#include "Player.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
using namespace std;

bool RatAtat:: check_special()const {
	return  (discard_pile->front()->get_value() !=-1) ;
}

RatAtat::RatAtat() :cnt_players(0), ratatat_player(-1), ratatat_round(false)
{
	p_arr = new Player*[6];
	p_arr[cnt_players++] = new AI_player(this);
	pack = new Dequeue(54);
	discard_pile = new Dequeue(0);
}

bool RatAtat::add_player(const string& name) {
	if (cnt_players == 6 || name.empty())
		return false;
	p_arr[cnt_players++] = new Human_Player(name,this);
	return true;
}
char RatAtat:: get_total_players() const {
	return cnt_players;
}
RatAtat:: ~RatAtat() {
	
	delete pack;
	delete discard_pile;//cant delete this
	for (int i = 0; i < cnt_players; i++) {
		delete p_arr[i];
	}
	delete[] p_arr;
}

void RatAtat::refill_pack() {
	while(discard_pile->size()!= 0)
	{
		pack->push_front(discard_pile->pop_front());
	}
	pack->reshuffle();
}
void RatAtat::play() {

	first_draw();

	pop_from_p_to_dpile();//only in the oppenning 
	int cnt = 0;//cnt indicates which player is playing right now

	while (!ratatat_round)//-1 indicates that none of the players call ratatat
	{
		if (cnt != ratatat_player)
		{
			cout << "==========================" << endl;
			cout << "discard pile: " << *(discard_pile->front()) << endl;
			cout << "==========================" << endl;
			cout << "It's " << p_arr[cnt]->get_name() << " turn: " << endl;

			cout << "1. Take a card from draw pile\n";
			char cnt_options = 1;
			if (discard_pile->front()->get_value() != -1)//check if its special card
			{
				cout << "2. Take a card from discard pile\n";
				cnt_options++;
			}

			char p_choice = p_arr[cnt]->option_for_player(cnt_options);
			//cout << (int)p_choice << endl;

			if (p_choice == 1)
			{
				pop_from_p_to_dpile();//put a card form draw pile in discard pile
				if (cnt != 0) {
					cout << "card drawn:	" << *(discard_pile->front()) << endl;
				}
				discard_pile->front()->print_card_action_menu();
				p_choice = p_arr[cnt]->option_for_player(discard_pile->front()->get_card_action_menu_max_num());
				
				if (p_choice == 2) //replace card from draw pile with one of my cards
					discard_pile->front()->use(p_arr, cnt, *this);
			}
			else if (p_choice == 2) {
				discard_pile->front()->use(p_arr, cnt, *this);//discard_pile
			}

			if (ratatat_player == -1)
			{
				cout << "Call RatATat?\n1. No\n2. Yes" << endl;
				p_choice = p_arr[cnt]->option_for_player(2);//if its AI_Player it will do rnd
				//cout << (int)p_choice << endl;
				if ((int)p_choice == 2) {
					ratatat_player = cnt;
					cnt = -1;
				}
				//ratatat_called = (int)p_choice == 1 ? false : true;

			}
		}
		cnt++;
		if (cnt >= cnt_players)
		{
			if (ratatat_player != -1) ratatat_round = true;
				cnt = 0;
		}
	}
	end_gamePrints();
	
}
Card* RatAtat::pop_and_push_dpile(Card* playerCard) {
	Card* temp;
	temp = discard_pile->pop_front();
	discard_pile->push_front(playerCard);
	return temp;
}
//every pop from main pile we immediatly push to the discard pile- same logic all over the proj
void RatAtat::pop_from_p_to_dpile()
{
	Card* c = pack->pop_front();
	if (c != nullptr)
		discard_pile->push_front(c);
	else {
		refill_pack();
		discard_pile->push_front(pack->pop_front());
	}
}

void RatAtat::first_draw() {
	for (int i = 0; i < cnt_players; i++) {
		for (int z = 0 ; z < Player::p_cards_lim;z++) {
			p_arr[i]->add_card(pack->pop_front(),z);
		}
	}
	int cnt = 1;//beacause the AI_Player is the first one there is no need to show his cards
	do
	{
		cout << *(p_arr[cnt]) << endl;
		p_arr[cnt]->present_card(0);
		cout << "  2  hidden card  hidden card  ";
		p_arr[cnt]->present_card(3);
		cout << endl;
		system("pause");// waiting for input from user
		system("CLS");// clear screen
		cnt++;
	} while (cnt < cnt_players);
}

Card* RatAtat::get_drawn_card() const
{
	 discard_pile->push_front(pack->pop_front());
	 return discard_pile->front();
}

Card* RatAtat:: pop_c() {
	pop_from_p_to_dpile();
	return discard_pile->front();
}
void RatAtat::push_c(Card* c) {
	discard_pile->push_front(c);
}
void RatAtat::end_gamePrints() const {
	int cnt = 0;//counter that indicates current player

	while (cnt < cnt_players) {
		p_arr[cnt]->print_cards();
		cnt++;
	}

	char minSum = p_arr[0]->calc_sum_c();
	string winner_name= p_arr[0]->get_name();
	for (int i = 1; i < cnt_players; i++) {
		if (p_arr[i]->calc_sum_c() < minSum) {
			minSum = p_arr[i]->calc_sum_c();
			winner_name = p_arr[i]->get_name();
		}
	}
	cout << "And the winner is: " << winner_name;
}
