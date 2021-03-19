// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
//default card constructor. sets card to Two of Spades
Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

//card constructor with rank and suit name as argument. may have to use ASSERT.
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//returns the rank. I think const is placed correctly.
std::string Card::get_rank() const {
    return rank;
}

//returns the suit. I think const is placed correctly.
std::string Card::get_suit() const {
    return suit;
}

//get suit with trump
std::string Card::get_suit(const std::string &trump) const {
    if (is_left_bower(trump)) {
        return trump;
    }
    else {
        return suit;
    }
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
    if (rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING
        || rank == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    if (suit == trump && rank == RANK_JACK) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    if (rank != RANK_JACK) {
        return false;
    }
    //might not need this one.
    if (suit == trump) {
        return false;
    }
    if (trump == SUIT_SPADES && suit == SUIT_CLUBS) {
        return true;
    }
    if (trump == SUIT_CLUBS && suit == SUIT_SPADES) {
        return true;
    }
    if (trump == SUIT_HEARTS && suit == SUIT_DIAMONDS) {
        return true;
    }
    if (trump == SUIT_DIAMONDS && suit == SUIT_HEARTS) {
        return true;
    }
    else {
        return false;
    }
}
 
//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    if (suit == trump || is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
// need to fix this to consider suit dominance
bool operator<(const Card& lhs, const Card& rhs) {
    if (lhs.get_rank() == rhs.get_rank()) {
        int left = 0;
        int right = 0;
        for (int i = 0; i < NUM_SUITS; ++i) {
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
                left = i;
            }
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
                right = i;
            }
        }
        if (left < right) {
            return true;
        }
        else {
            return false;
        }
    }
    int left1 = 0;
    int right1 = 0;
    for (int i = 0; i < NUM_RANKS; ++i) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            left1 = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            right1 = i;
        }
    }
    if (left1 < right1) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
//also need to fix. same reason
bool operator>(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank()) {
        int left = 0;
        int right = 0;
        for (int i = 0; i < NUM_SUITS; ++i) {
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
                left = i;
            }
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
                right = i;
            }
        }
        if (left > right) {
            return true;
        }
        else {
            return false;
        }
    }
    int left1 = 0;
    int right1 = 0;
    for (int i = 0; i < NUM_RANKS; ++i) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
            left1 = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
            right1 = i;
        }
    }
    if (left1 > right1) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()) {
        return false;
    }
    else {
        return true;
    }
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    if (suit == SUIT_NAMES_BY_WEIGHT[0]) {
        return SUIT_NAMES_BY_WEIGHT[2];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[1]) {
        return SUIT_NAMES_BY_WEIGHT[3];
    }
    else if (suit == SUIT_NAMES_BY_WEIGHT[2]) {
        return SUIT_NAMES_BY_WEIGHT[0];
    }
    else {
        return SUIT_NAMES_BY_WEIGHT[1];
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    if (a.is_right_bower(trump)) {
        return false;
    }
    if (b.is_right_bower(trump)) {
        return true;
    }
    if (a.is_left_bower(trump)) {
        if (b.is_right_bower(trump)) {
            return true;
        }
        else {
            return false;
        }
    }
    if (b.is_left_bower(trump)) {
        if (a.is_right_bower(trump)) {
            return false;
        }
        else {
            return true;
        }
    }
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    if (a.is_trump(trump) && !(b.is_trump(trump))) {
        return false;
    }
    if (!(a.is_trump(trump)) && b.is_trump(trump)) {
        return true;
    }
    if (!(a.is_trump(trump)) && !(b.is_trump(trump))) {
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    if (a.is_right_bower(trump)) {
        return false;
    }
    if (b.is_right_bower(trump)) {
        return true;
    }
    if (a.is_left_bower(trump)) {
        if (b.is_right_bower(trump)) {
            return true;
        }
        else {
            return false;
        }
    }
    if (b.is_left_bower(trump)) {
        if (a.is_right_bower(trump)) {
            return false;
        }
        else {
            return true;
        }
    }
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (operator<(a, b)) {
            return true;
        }
        else {
            return false;
        }
    }
    if (a.is_trump(trump) && !(b.is_trump(trump))) {
        return false;
    }
    if (!(a.is_trump(trump)) && b.is_trump(trump)) {
        return true;
    }
    if (!(a.is_trump(trump)) && !(b.is_trump(trump))) {
        if (a.get_suit() == led_card.get_suit() &&
            b.get_suit() == led_card.get_suit()) {
            if (operator<(a, b)) {
                return true;
            }
            else {
                return false;
            }
        }
        if (a.get_suit() == led_card.get_suit() &&
            b.get_suit() != led_card.get_suit()) {
            return false;
        }
        if (a.get_suit() != led_card.get_suit() &&
            b.get_suit() == led_card.get_suit()) {
            return true;
        }
        if (a.get_suit() != led_card.get_suit() &&
            b.get_suit() != led_card.get_suit()) {
            if (operator<(a, b)) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false; 
}
