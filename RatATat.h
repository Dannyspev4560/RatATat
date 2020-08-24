#ifndef RATATAT_H
#define RATATAT_H
class Player;
#include "Pile.h"
#include <string>
#include <iostream>

using namespace std;

class RatAtat {
	char cnt_players;
	Player** p_arr;
	Dequeue*  pack;
	Dequeue* discard_pile;//private
	int ratatat_player;//which player called ratatat
	bool ratatat_round;//indicates if ratatat round (after the call) is done
public:
	
	RatAtat();
	~RatAtat();
	bool add_player(const string& name);
	void play();
	void first_draw();
	bool check_special() const;
	Card* get_drawn_card() const;
	Card* pop_and_push_dpile(Card*);
	char get_total_players() const;
	Card* pop_c();
	void push_c(Card* c);
	void end_gamePrints() const;
	void refill_pack();//--
	void pop_from_p_to_dpile();
};

#endif // !RATATAT_H

