#include "Player.h"
#include "Card.h"
#include <iostream>
#include <string>
#include <array>
#include <cassert>
#include <algorithm>
#include <vector>


class Simple : public Player {
public:
    Simple(std::string const simple_name) 
        : name(simple_name) {}
    
    const std::string& get_name() const override {
        return name;
    }
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        hand.push_back(c);
    }
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, std::string &order_up_suit) const override {
        //make trump has two parts. Round 1 and Round 2.
        if (round == 1) {
            int counter = 0;
            //loops through all cards in hand. At least 2 means order up.
            for (int i = 0; i < 5; ++i) {
                //this is kinda ugly. basically searches for face card and
                //left bower line up with upcard suit
                if ((hand[i].get_suit() == upcard.get_suit() &&
                     hand[i].is_face()) ||
                    hand[i].is_left_bower(upcard.get_suit())) {
                    ++counter;
                }
            }
            if (counter >= 2) {
                order_up_suit = upcard.get_suit();
                std::cout << get_name() << " orders up " << order_up_suit
                << std::endl;
                return true;
            }
            // if you dont have at least two of right card, pass
            else {
                std::cout << get_name() << " passes" << std::endl;
                return false;
            }
        }
        //this is Round 2. Similar structure. Utilizes Suit_next(), add dealer
        // option.
        else {
            //if dealer, must  order up opposite suit of upcard.
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                std::cout << get_name() << " orders up " << order_up_suit
                << std::endl;
                return true;
            }
            else {
                int counter = 0;
                for (int i = 0; i < 5; ++i) {
                    if ((hand[i].get_suit() == Suit_next(upcard.get_suit()) &&
                         hand[i].is_face()) ||
                        hand[i].is_left_bower(Suit_next(upcard.get_suit()))) {
                        ++counter;
                    }
                }
                if (counter >= 1) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    std::cout << get_name() << " orders up " << order_up_suit
                    << std::endl;
                    return true;
                }
                else {
                    std::cout << get_name() << " passes" << std::endl;
                    return false;
                }
            }
        }
    }
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        std::sort(hand.begin(), hand.end());
        //check it out
        if (Card_less(hand[0], upcard, upcard.get_suit())) {
            hand[0] = upcard;
        }
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) override {
        //first part counts if all cards in hand are of trump suit.
        std::sort(hand.begin(), hand.end());
        int trumpNum = 0;
        for (size_t suitNum = 0; suitNum < hand.size(); ++suitNum) {
            if (hand[suitNum].get_suit(trump) == trump) {
                ++trumpNum;
            }
        }
        //if all cards are of trump suit, return greatest card.
        //made a sort function.
        if (trumpNum == hand.size()) {
            Card max = hand[0];
            size_t index = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (Card_less(max, hand[i], trump)) {
                        max = hand[i];
                        index = i;
                }
            }
            Card tempBestCard = max;
            hand.erase(hand.begin() + index);
            std::cout << tempBestCard << " led by " << get_name() << '\n';
            return tempBestCard;
        }
        //enter branch if not all cards are of trump suit
        else {
            //different part: check if card at end is same suit as trump. If it
            //isn't, return card. If it is, go down to next card.
            size_t index = 0;
            std::vector<Card> temp;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (!(hand[i].get_suit(trump) == trump)) {
                    temp.push_back(hand[i]);
                    index = i;
                }
            }
            Card max = temp[0];
            for (size_t j = 0; j < temp.size(); ++j) {
                if (Card_less(max, temp[j], trump)) {
                    max = temp[j];
                }
            }
            Card tempBestCard = max;
            hand.erase(hand.begin() + index);
            std::cout << tempBestCard << " led by " << get_name() << '\n';
            return tempBestCard;
        }
        //need this part just so that this funtion returns someting. should
        //never come here though.
        return hand[0];
    }
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card& led_card, const std::string& trump) override {
        std::sort(hand.begin(), hand.end());
        //first part counts if all cards in hand are of lead suit.
        int leadNum = 0;
        for (size_t suitNum = 0; suitNum < hand.size(); ++suitNum) {
            if (hand[suitNum].get_suit() == led_card.get_suit()) {
                ++leadNum;
            }
        }
        //if no cards are of lead suit, return lowest card.
        //made a sort function.
        if (leadNum == 0) {
            Card min = hand[0];
            size_t index = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (Card_less(hand[i], min, trump)) {
                        min = hand[i];
                        index = i;
                }
            }
            Card tempBestCard = min;
            hand.erase(hand.begin() + index);
            std::cout << tempBestCard << " played by " << get_name() << '\n';
            return tempBestCard;
        }
        else {
            //different part: check if card at end is same suit as lead. If it
            //is, return card. If it isn't, go down to next card.
            size_t index = 0;
            std::vector<Card> temp;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (hand[i].get_suit(trump) == led_card.get_suit(trump)) {
                    temp.push_back(hand[i]);
                    index = i;
                }
            }
            Card max = temp[0];
            for (size_t j = 0; j < temp.size(); ++j) {
                if (Card_less(max, temp[j], trump)) {
                    max = temp[j];
                }
            }
            Card tempBestCard = max;
            hand.erase(hand.begin() + index);
            std::cout << tempBestCard << " played by " << get_name() << '\n';
            return tempBestCard;
        }
        return hand[0];
    }
    
private:
    static const int HAND_SIZE = 5;
    std::vector<Card> hand;
    std::string const name;
    size_t handSize = hand.size();
};

class Human: public Player {
public:
    Human(std::string const human_name)
        : name(human_name) {}

    const std::string& get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
 //EFFECTS  adds Card c to Player's hand
    void add_card(const Card& c) override {
        hand.push_back(c);
    }
    //REQUIRES round is 1 or 2
 //MODIFIES order_up_suit
 //EFFECTS If Player wishes to order up a trump suit then return true and
 //  change order_up_suit to desired suit.  If Player wishes to pass, then do
 //  not modify order_up_suit and return false.
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, std::string& order_up_suit) const override {

        std::vector<Card> tempv = hand;
        std::sort(tempv.begin(), tempv.end());

        for (size_t i = 0; i < hand.size(); i++) {
            std::cout << "Human player " << get_name() << "'s hand: " 
                << "[" << i << "] " << tempv[i] << std::endl;
        }
        std::cout << "Human player " << get_name() <<
            ", please enter a suit, or \"pass\":" << std::endl;
        std::cin >> order_up_suit;

        if (order_up_suit == "pass") {
            std::cout << get_name() << " passes" << std::endl;
            return false;
        }
        else {
            std::cout << get_name() << " orders up " << order_up_suit
            << std::endl;
            return true;
        }
        return false;
    }

    //REQUIRES Player has at least one card
 //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card& upcard) override {
        for (size_t i = 0; i < hand.size(); i++) {
            std::cout << "Human player " << get_name() << "'s hand: "
                << "[" << i << "] " << hand[i] << std::endl;
        }

        std::cout << "Discard upcard: [-1]" << std::endl;
        std::cout << "Select a card to discard" << std::endl;
        int discard;
        std::cin >> discard;

        if (!(discard == -1)) {
            hand[discard] = upcard;
        }
    }

    //REQUIRES Player has at least one card, trump is a valid suit
 //EFFECTS  Leads one Card from Player's hand according to their strategy
 //  "Lead" means to play the first Card in a trick.  The card
 //  is removed the player's hand.
    Card lead_card(const std::string& trump) override {
        std::sort(hand.begin(), hand.end());
        for (size_t i = 0; i < hand.size(); i++) {
            std::cout << "Human player " << get_name() << "'s hand: "
                << "[" << i << "] " << hand[i] << std::endl;
        }
        std::cout << "Human player " << get_name()
        << ", please select a card :" << std::endl;
        int select;
        std::cin >> select;
        std::cout << hand[select] << " led by " << get_name() << std::endl;

        Card temp;
        temp = hand[select];
        hand.erase(hand.begin() + select);
        return temp;
    }
    //REQUIRES Player has at least one card, trump is a valid suit
 //EFFECTS  Plays one Card from Player's hand according to their strategy.
 //  The card is removed from the player's hand.
    Card play_card(const Card& led_card, const std::string& trump) override {
        std::sort(hand.begin(), hand.end());
        for (size_t i = 0; i < hand.size(); i++) {
            std::cout << "Human player " << get_name() << "'s hand: "
                << "[" << i << "] " << hand[i] << std::endl;
        }
        std::cout << "Human player " << get_name()
        << ", please select a card :" << std::endl;
        int select;
        std::cin >> select;
        std::cout << hand[select] << " played by " << get_name() << std::endl;

        Card temp;
        temp = hand[select];
        hand.erase(hand.begin() + select);
        return temp;
    }

private:
    static const int HAND_SIZE = 5;
    std::vector<Card> hand;
    std::string const name;
};

Player* Player_factory(const std::string& name, const std::string& strategy) {
    if (strategy == "Simple") {
        return new Simple(name);
    }
    else if (strategy == "Human") {
        return new Human(name);
    }
    assert(false);
    return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}

