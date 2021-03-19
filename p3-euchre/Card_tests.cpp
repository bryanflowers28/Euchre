// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    //tests card constructor with arguments
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
    
    //tests default card constructor
    Card d;
    ASSERT_EQUAL(Card::RANK_TWO, d.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, d.get_suit());
}

TEST(test_card_get_rank) {
    Card a(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::RANK_KING, a.get_rank());
}

TEST(test_card_get_suit) {
    Card a(Card::RANK_KING, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::SUIT_CLUBS, a.get_suit());
}

TEST(test_card_get_suit_trump) {
    //tests non left bower card
    Card a(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    const string trump1 = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(Card::SUIT_HEARTS, a.get_suit(trump1));
    
    //tests left bower card
    Card b(Card::RANK_JACK, Card::SUIT_HEARTS);
    const string trump2 = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit(trump2));
}

TEST(test_is_left_bower) {
    //test non left bower
    Card a(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    const string trump1 = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(false, a.is_left_bower(trump1));
    
    //test left bower
    Card b(Card::RANK_JACK, Card::SUIT_HEARTS);
    const string trump2 = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(true, b.is_left_bower(trump1));
}

TEST(is_face) {
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(king_hearts.is_face());

    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_TRUE(king_spades.is_face());

    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(queen_hearts.is_face());

    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_FALSE(nine_hearts.is_face());
}

TEST(test_less_than_operator) {
    //test cards of same suit
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(a < b);
    
    //test cards of different suits
    Card c(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_FALSE(c < d);
    
    //test cards of different suits, yet rank that is higher is lower value
    Card e(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card f(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(e < f);
}

TEST(is_right_bower) {
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    string trump = king_hearts.get_suit();

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades.is_right_bower(trump));

    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_FALSE(queen_hearts.is_right_bower(trump));

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(jack_spades.is_right_bower(trump));

    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(jack_hearts.is_right_bower(trump));
}

TEST(is_trump) {
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    string trump = king_hearts.get_suit();

    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(three_spades.is_trump(trump));

    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_TRUE(queen_hearts.is_trump(trump));

    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_FALSE(king_spades.is_trump(trump));

    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_TRUE(jack_hearts.is_trump(trump));
}

TEST(operator_less) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_TRUE(operator<(two_spades, three_spades));

    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(operator<(nine_spades, jack_spades));

    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(operator<(king_spades, ace_spades));

    ASSERT_FALSE(operator<(ace_spades, two_spades));

    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(operator<(ace_spades, ace_clubs));

    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(operator<(ace_diamonds, ace_diamonds));
}

TEST(operator_greater) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_TRUE(operator>(three_spades, two_spades));

    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(operator>(jack_spades, nine_spades));

    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(operator>(ace_spades, king_spades));

    ASSERT_FALSE(operator>(two_spades, ace_spades));

    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(operator>(ace_clubs, ace_spades));

    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_diamonds2 = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(operator>(ace_diamonds, ace_diamonds2));
}

TEST(operator_equal) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card three_spades2 = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_TRUE(operator==(three_spades, three_spades2));

    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(operator==(nine_spades, jack_spades));

    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator==(king_spades, king_hearts));

    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_FALSE(operator==(two_spades, ace_spades));
}

TEST(operator_notequal) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card three_spades2 = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_FALSE(operator!=(three_spades, three_spades2));

    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(operator!=(nine_spades, jack_spades));

    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator!=(king_spades, king_hearts));

    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    ASSERT_TRUE(operator!=(two_spades, ace_spades));
}
//TEST(suit_next) {
    //ASSERT_TRUE(suit_next(Card::SUIT_SPADES) == "Clubs");
    //ASSERT_TRUE(suit_next(Card::SUIT_CLUBS) == "Spades");
    //ASSERT_TRUE(suit_next(Card::SUIT_DIAMONDS) == "Hearts");
    //ASSERT_TRUE(suit_next(Card::SUIT_HEARTS) == "Diamonds");

//}

//TEST(operator_print) {
    //Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    //string output_c = "Ace of Spades";

    //ostringstream output;
    //output << operator<<(output, ace_spades);
    //ASSERT_EQUAL(output, output_c);
//}

TEST(Card_less_first) {
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(ace_diamonds, ace_spades, Card::SUIT_SPADES));

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ace_spades, jack_spades, Card::SUIT_SPADES));

    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, Card::SUIT_SPADES));

    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, Card::SUIT_SPADES));

    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(ace_clubs, ace_diamonds, Card::SUIT_SPADES));

    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Card_less(king_diamonds, ace_diamonds, Card::SUIT_SPADES));
}

TEST(Card_less_second) {
    //string trump = Card::SUIT_SPADES;
    //string lead1 = Card::SUIT_HEARTS;
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_clubs = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card king_diamonds = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card king_clubs = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card nine_clubs = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card queen_diamonds = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card queen_clubs = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);

   
    //                     this card < this card    
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, jack_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, nine_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(nine_diamonds, nine_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, ace_spades, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_clubs, ace_hearts, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_clubs, nine_hearts, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_clubs, king_hearts, queen_hearts, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_clubs, ace_diamonds, queen_hearts, Card::SUIT_SPADES));

    //string lead2 = Card::SUIT_CLUBS;
    //                     this card < this card    
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, jack_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, nine_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(nine_diamonds, nine_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, ace_spades, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, ace_clubs, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_clubs, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_hearts, jack_diamonds, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_diamonds, king_clubs, queen_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_hearts, ace_diamonds, queen_clubs, Card::SUIT_SPADES));

    //string lead3 = Card::SUIT_SPADES;
    ASSERT_TRUE(Card_less(ace_diamonds, ace_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(jack_clubs, jack_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_clubs, ace_diamonds, queen_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(king_diamonds, ace_diamonds, queen_spades, Card::SUIT_SPADES));
}


TEST_MAIN()
