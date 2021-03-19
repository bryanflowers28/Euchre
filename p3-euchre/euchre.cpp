#include "Player.h"
#include "Card.h"
#include "Pack.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

class Game {
private:
	int score_one;
	int score_two;
	int limit;
	std::vector<Player*> players;
	int dealer;
    int eldest;
    int eldestNext;
    int eldestNextNext;
	Pack deck;
	int hand;
	Card upcard;
    bool teamOneOrderUp;
    bool deckShuffle;
    int tricks1;
    int tricks2;
    string orderedSuit;
    int leadPerson;
    int second;
    int third;
    int fourth;
    std::vector<Card> played_cards;
    Card ledCard;
    
public:
	Game()
		: score_one(0), score_two(0), limit(0), dealer(0), eldest(1),
    eldestNext(2), eldestNextNext(3), hand(0), teamOneOrderUp(false),
    deckShuffle(false), tricks1(0), tricks2(0), orderedSuit(""), leadPerson(7),
    second(2), third(3), fourth(0) {}
    
    string get_order_suit() {
        return orderedSuit;
    }
    
    void set_order_suit(string set_order_suit) {
        orderedSuit = set_order_suit;
    }
    
    int get_dealer() {
        return dealer;
    }
    
    int get_eldest() {
        return eldest;
    }
    
    int get_eldestNext() {
        return eldestNext;
    }
    
    int get_eldestNextNext() {
        return eldestNextNext;
    }
    
    int get_tricks1() {
        return tricks1;
    }
    
    void increment_tricks1() {
        ++tricks1;
    }
    
    void set_tricks1(int set_trick) {
        tricks1 = set_trick;
    }
    
    int get_tricks2() {
        return tricks2;
    }
    
    void increment_tricks2() {
        ++tricks2;
    }
    
    void set_tricks2(int set_trick) {
        tricks2 = set_trick;
    }
    
    int get_score_1() {
        return score_one;
    }
    
    int get_score_2() {
        return score_two;
    }
    
    bool did_team1_order_up() {
        return teamOneOrderUp;
    }
    int get_lead_person() {
        return leadPerson;
    }
    
    void set_lead_person(int person) {
        leadPerson = person;
    }
    
    void set_second(int second_val) {
        second = second_val;
    }
    
    void set_third(int third_val) {
        third = third_val;
    }
    
    void set_fourth(int fourth_val) {
        fourth = fourth_val;
    }
    
    int get_second() {
        return second;
    }
    
    int get_third() {
        return third;
    }
    
    int get_fourth() {
        return fourth;
    }
    
    string get_player_name(int person_index) {
        return players[person_index]->get_name();
    }
    
    int find_best() {
        int best = 0;
        Card bestCard = played_cards[0];
        for (int i = 1; i < 4; ++i) {
            if (Card_less(bestCard, played_cards[i], played_cards[0],
                          orderedSuit)) {
                best = i;
                bestCard = played_cards[i];
            }
        }
        return best;
    }
    
    Card lead_card_game(int person) {
        return (players[person])->lead_card(orderedSuit);
    }
    
    Card play_card_game(int person) {
        return players[person]->play_card(ledCard, orderedSuit);
    }
    
    void lead_push_back_vector(int person) {
        ledCard = lead_card_game(person);
        played_cards.push_back(ledCard);
    }
    
    void push_back_vector(int person) {
        played_cards.push_back(play_card_game(person));
    }
    
    //counts/resets tricks and changes score. sees who ordered.
	void increase_score(bool team_one_ordered, int team1_tricks,
                        int team2_tricks) {
        if ((team1_tricks > team2_tricks) && team_one_ordered) {
            //Need to add cout output to different endings
            // NOT EUCHRED
            if (get_tricks1() == 3 || get_tricks1() == 4) {
                ++score_one;
                set_tricks1(0);
                set_tricks2(0);
                std::cout << players[0]->get_name() << " and "
                << players[2]->get_name() <<
                " win the hand" << '\n';
                std::cout << players[0]->get_name() << " and "
                << players[2]->get_name() << " have "
                << score_one << " points" << '\n';
                std::cout << players[1]->get_name() << " and "
                << players[3]->get_name() <<
                " have " << score_two << " points" << '\n';
            }
            //MARCH
            else if (get_tricks1() == 5) {
                ++score_one;
                ++score_one;
                set_tricks1(0);
                set_tricks2(0);
                std::cout << players[0]->get_name() << " and "
                << players[2]->get_name() <<
                " win the hand" << '\n' << "march!" << '\n';
                std::cout << players[0]->get_name() << " and "
                << players[2]->get_name() << " have "
                << score_one << " points" << '\n';
                std::cout << players[1]->get_name() << " and "
                << players[3]->get_name() <<
                " have " << score_two << " points" << '\n';
            }
        }
        //EUCHRED
        else if ((team1_tricks > team2_tricks) && !(team_one_ordered)) {
            ++score_one;
            ++score_one;
            set_tricks1(0);
            set_tricks2(0);
            std::cout << players[0]->get_name() << " and "
            << players[2]->get_name() <<
            " win the hand" << '\n' << "euchred!" << '\n';
            std::cout << players[0]->get_name() << " and "
            << players[2]->get_name() << " have "
            << score_one << " points" << '\n';
            std::cout << players[1]->get_name() << " and "
            << players[3]->get_name() <<
            " have " << score_two << " points" << '\n';
        }
        else if ((team2_tricks > team1_tricks) && !(team_one_ordered)) {
            // NOT EUCHRED
            if (get_tricks2() == 3 || get_tricks2() == 4) {
                ++score_two;
                set_tricks1(0);
                set_tricks2(0);
                std::cout << players[1]->get_name() << " and "
                << players[3]->get_name() <<
                " win the hand" << '\n';
                std::cout << players[1]->get_name() << " and "
                << players[3]->get_name() << " have "
                << score_two << " points" << '\n';
                std::cout << players[0]->get_name() << " and "
                << players[2]->get_name() <<
                " have " << score_one << " points" << '\n';
            }
            //MARCH
            else if (get_tricks2() == 5) {
                ++score_two;
                ++score_two;
                set_tricks1(0);
                set_tricks2(0);
                std::cout << players[1]->get_name() << " and "
                << players[3]->get_name() <<
                " win the hand" << '\n' << "march!" << '\n';
                std::cout << players[1]->get_name() << " and "
                << players[3]->get_name() << " have "
                << score_two << " points" << '\n';
                std::cout << players[0]->get_name() << " and "
                << players[2]->get_name() <<
                " have " << score_one << " points" << '\n';
            }
        }
        //EUCHRED
        else {
            ++score_two;
            ++score_two;
            set_tricks1(0);
            set_tricks2(0);
            std::cout << players[1]->get_name() << " and "
            << players[3]->get_name() <<
            " win the hand" << '\n' << "euchred!" << '\n';
            std::cout << players[1]->get_name() << " and "
            << players[3]->get_name() << " have "
            << score_two << " points" << '\n';
            std::cout << players[0]->get_name() << " and "
            << players[2]->get_name() <<
            " have " << score_one << " points" << '\n';
        }
	}
    
    //goes at end of hand to move on dealer and eldest.
    void next_hand_player_calculator() {
        if (dealer == 0) {
            ++dealer;
            ++eldest;
            ++eldestNext;
            eldestNextNext = 0;
        }
        else if (dealer == 1) {
            ++dealer;
            ++eldest;
            ++eldestNextNext;
            eldestNext = 0;
        }
        else if (dealer == 2) {
            ++dealer;
            ++eldestNext;
            ++eldestNextNext;
            eldest = 0;
        }
        else {
            ++eldest;
            ++eldestNext;
            ++eldestNextNext;
            dealer = 0;
        }
    }
    Card get_upcard() {
        return upcard;
    }
    
    void make_trump_game() {
        // eldest round 1
        if (players[eldest]->make_trump(get_upcard(), 0, 1, orderedSuit)) {
            players[dealer]->add_and_discard(get_upcard());
            if (players[eldest] == players[0] || players[eldest] ==
                players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        //nexteldest round 1
        }
        else if (players[eldestNext]->make_trump(get_upcard(), 0, 1,
                                                 orderedSuit)) {
            players[dealer]->add_and_discard(get_upcard());
            if (players[eldestNext] == players[0] || players[eldestNext] ==
                players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
            //nextnexteldest round 1
        } else if (players[eldestNextNext]->make_trump(get_upcard(), 0, 1,
                                                       orderedSuit)) {
            players[dealer]->add_and_discard(get_upcard());
            if (players[eldestNextNext] == players[0] ||
                players[eldestNextNext] == players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        } else if (players[dealer]->make_trump(get_upcard(), 1, 1,
                                               orderedSuit)) {
            players[dealer]->add_and_discard(get_upcard());
            if (players[dealer] == players[0] || players[dealer] ==
                players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        }
        else if (players[eldest]->make_trump(get_upcard(), 0, 2, orderedSuit)) {
            if (players[eldest] == players[0] || players[eldest] ==
                players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        }
        else if (players[eldestNext]->make_trump(get_upcard(), 0, 2,
                                                 orderedSuit)) {
            if (players[eldestNext] == players[0] || players[eldestNext] ==
                players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        }
        else if (players[eldestNextNext]->make_trump(get_upcard(), 0, 2,
                                                     orderedSuit)) {
            if (players[eldestNextNext] == players[0] ||
                players[eldestNextNext] == players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        }
        else if (players[dealer]->make_trump(get_upcard(), 1, 2, orderedSuit)) {
            if (players[dealer] == players[0] || players[dealer] == players[2] ) {
                teamOneOrderUp = 1;
            } else {
                teamOneOrderUp = 0;
            }
        }
        leadPerson = eldest;
                    
    }
    
	void add_player(Player* player) {
		players.push_back(player);
	}

	void delete_players() {
		for (int i = 0; i < 4; ++i) {
			delete players[i];
		}
	}
    
    void reset_played_cards() {
        played_cards.clear();
    }

	void set_limit(int num) {
		limit = num;
	}

	int get_limit() {
		return limit;
	}

	void determine_shuffle(bool shuffle_val) {
        if (shuffle_val) {
            deckShuffle = 1;
        }
	}
    
    bool get_shuffle_val () {
        return deckShuffle;
    }
    
    void shuffle_deck(bool shuffle_val) {
        if (shuffle_val) {
            deck.shuffle();
        }
        else {
            deck.reset();
        }
    }
    
    void give_cards() {
        //3-2-3-2
        //cout << get_dealer() << get_eldest() << get_eldestNext() <<
        //get_eldestNextNext() << endl;
        //cout << "pack index:" << deck.next << endl;
        /*for (int i = 0; i < 24; i++) {
            cout << deck.deal_one() << endl;
        }*/
        players[get_eldest()]->add_card(deck.deal_one());
        players[get_eldest()]->add_card(deck.deal_one());
        players[get_eldest()]->add_card(deck.deal_one());
        
        players[get_eldestNext()]->add_card(deck.deal_one());
        players[get_eldestNext()]->add_card(deck.deal_one());
        
        players[get_eldestNextNext()]->add_card(deck.deal_one());
        players[get_eldestNextNext()]->add_card(deck.deal_one());
        players[get_eldestNextNext()]->add_card(deck.deal_one());
        
        players[get_dealer()]->add_card(deck.deal_one());
        players[get_dealer()]->add_card(deck.deal_one());
        
        //2-3-2-3
        players[get_eldest()]->add_card(deck.deal_one());
        players[get_eldest()]->add_card(deck.deal_one());
        
        players[get_eldestNext()]->add_card(deck.deal_one());
        players[get_eldestNext()]->add_card(deck.deal_one());
        players[get_eldestNext()]->add_card(deck.deal_one());
        
        players[get_eldestNextNext()]->add_card(deck.deal_one());
        players[get_eldestNextNext()]->add_card(deck.deal_one());
        
        players[get_dealer()]->add_card(deck.deal_one());
        players[get_dealer()]->add_card(deck.deal_one());
        players[get_dealer()]->add_card(deck.deal_one());
    }

	void new_pack(std::istream& pack_input){
		Pack deck(pack_input);
	}
	
	void hand_begin() {
		upcard = deck.deal_one();
		cout << "Hand " << hand << endl;
		cout << players[dealer]->get_name() << " deals" << endl;
		cout << upcard << " turned up" << endl;
        hand++;
	}
    void reset_tricks() {
        tricks1 = 0;
        tricks2 = 0;
    }
};



int main(int argc, char* argv[]) {
	if ((argc != 12) || (atoi(argv[3]) <= 0 || atoi(argv[3]) >= 100)
		|| !((strcmp(argv[2], "shuffle") == 0) || (strcmp(argv[2],
                                                          "noshuffle") == 0)) ||
		!((strcmp(argv[5], "Simple") == 0) || (strcmp(argv[5],
                                                      "Human") == 0)) ||
		!((strcmp(argv[7], "Simple") == 0) || (strcmp(argv[7],
                                                      "Human") == 0)) ||
		!((strcmp(argv[9], "Simple") == 0) || (strcmp(argv[9],
                                                      "Human") == 0)) ||
		!((strcmp(argv[11], "Simple") == 0) || (strcmp(argv[11],
                                                       "Human") == 0))) {
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return 1;
	}
	
    //output commands
	for (int i = 0; i < 12; ++i) {
		cout << argv[i] << ' ';
	}
	cout << endl;
    
    //create game
	Game euchre;
    
    //set deck
    ifstream fin;
    fin.open(argv[1]);
    if (!(fin.is_open())) {
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
    euchre.new_pack(fin);
    
    //determine if shuffling will occur
    euchre.determine_shuffle(strcmp(argv[2], "shuffle") == 0);
    
    //add players
    euchre.add_player(Player_factory(argv[4], argv[5]));
    euchre.add_player(Player_factory(argv[6], argv[7]));
	euchre.add_player(Player_factory(argv[8], argv[9]));
	euchre.add_player(Player_factory(argv[10], argv[11]));
    
    //set limit
	euchre.set_limit(atoi(argv[3]));
    
    //while no one has satisfied point requirement
    while ((euchre.get_score_1() < atoi(argv[3])) && (euchre.get_score_2() <
           atoi(argv[3]))) {
        //first determine shuffling, deck control
        //cout << "shuffle" << endl;
        euchre.shuffle_deck(euchre.get_shuffle_val());
        //hand out cards
        //cout << "give it\n";
        euchre.give_cards();
        //cout the beginning of the hand
        //cout << "hand will begin" << endl;
        euchre.hand_begin();
        //cout << "make trump\n";
        //determine trump
        euchre.make_trump_game();
        cout << endl;
        int x = 0;

        while (x < 5) {
            int bestIndex = 0;
            int personIndex = 0;
            euchre.lead_push_back_vector(euchre.get_lead_person());
            euchre.push_back_vector(euchre.get_second());
            euchre.push_back_vector(euchre.get_third());
            euchre.push_back_vector(euchre.get_fourth());
            bestIndex = euchre.find_best();
            personIndex = (euchre.get_lead_person() + bestIndex) % 4;
            if (personIndex == 0 || personIndex == 2) {
                euchre.increment_tricks1();
                cout << euchre.get_player_name(personIndex)
                << " takes the trick" << '\n';
            }
            else {
                euchre.increment_tricks2();
                cout << euchre.get_player_name(personIndex)
                << " takes the trick" << '\n';
            }
            euchre.set_lead_person(personIndex);
            euchre.set_second((personIndex + 1) % 4);
            euchre.set_third((personIndex + 2) % 4);
            euchre.set_fourth((personIndex + 3) % 4);
            euchre.reset_played_cards();
            ++x;
            cout << '\n';
        }
        //cout << endl;
        //determines scores to give
        euchre.increase_score(euchre.did_team1_order_up(), euchre.get_tricks1(), euchre.get_tricks2());
        //sets up index for all players
        //cout << "son to next hand calc" << endl;
        euchre.next_hand_player_calculator();
        //cout << "bpiy" << endl;
        euchre.reset_tricks();
        cout << '\n';
    }
    if (euchre.get_score_1() > euchre.get_score_2()) {
        cout << euchre.get_player_name(0) << " and " <<
        euchre.get_player_name(2) << " win!" << '\n';
    }
    else {
        cout << euchre.get_player_name(1) << " and " <<
        euchre.get_player_name(3) << " win!" << '\n';
    }
	euchre.delete_players();
	return 0;
}
