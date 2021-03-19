#include "Pack.h"

Pack::Pack() {
    int index = 0;
    for (int suitVal = 0; suitVal < 4; ++suitVal) {
        for (int rankVal = 7; rankVal < 13; ++rankVal) {
            cards[index] = Card(RANK_NAMES_BY_WEIGHT[rankVal],
                                SUIT_NAMES_BY_WEIGHT[suitVal]);
            ++index;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    std::string rank = "";
    std::string of = "";
    std::string suit = "";
    for (int i = 0; i < 24; ++i) {
        pack_input >> rank >> of >> suit;
        cards[i] = Card(rank, suit);
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    ++next;
    return cards[next - 1];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    std::array<Card, 24> cards1;
    std::array<Card, 24> cards2;
    for (int counter = 0; counter < 7; ++counter) {
        for (int i = 0; i < 12 ; ++i) {
            cards1[i] = cards[i];
        }
    
        for (int i = 12; i < 24 ; ++i) {
            cards2[i - 12] = cards[i];
        }
        int j = 0;
        int k = 0;
        for (int i = 0; i < 24; ++i) {
            if (i % 2 == 0) {
                cards[i] = cards2[j];
                ++j;
            }
            else {
                cards[i] = cards1[k];
                ++k;
            }
        }
    }
    reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next == 24) {
        return true;
    }
    else {
        return false;
    }
}

