// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;



TEST(test_simple_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_simple_player_add_card) {
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(king_hearts);
    ASSERT_EQUAL(alice->play_card(jack_hearts, jack_hearts.get_suit()),
                 king_hearts);
    delete alice;
}

TEST(test_simple_player_make_trump) {
    //ROUND 1 NOT DEALER
    //ALICE HAS NO CARDS THAT MATCH
    Player * alice = Player_factory("Alice", "Simple");
    Card trumpCard = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    string orderUpSuit = SUIT_NAMES_BY_WEIGHT[3];
    
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card king_hearts = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card nine_hearts = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card ten_hearts = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    
    alice->add_card(ace_hearts);
    alice->add_card(king_hearts);
    alice->add_card(queen_hearts);
    alice->add_card(nine_hearts);
    alice->add_card(ten_hearts);
    
    ASSERT_EQUAL(false, alice->make_trump(trumpCard, false, 1, orderUpSuit));
    delete alice;
    
    ASSERT_EQUAL(SUIT_NAMES_BY_WEIGHT[3], orderUpSuit);
    
    //ROUND 1 NOT DEALER
    //JOSE HAS ONE CARD THAT MATCHES
    Player * jose = Player_factory("Jose", "Simple");
    
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    
    jose->add_card(ace_diamonds);
    jose->add_card(king_hearts);
    jose->add_card(queen_hearts);
    jose->add_card(nine_hearts);
    jose->add_card(ten_hearts);
    
    ASSERT_EQUAL(false, jose->make_trump(trumpCard, false, 1, orderUpSuit));
    delete jose;
    
    //ROUND 1 NOT DEALER
    //MIKA HAS TWO CARDS THAT MATCH
    Player * mika = Player_factory("Mika", "Simple");
    
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    
    mika->add_card(ace_diamonds);
    mika->add_card(jack_diamonds);
    mika->add_card(queen_hearts);
    mika->add_card(nine_hearts);
    mika->add_card(ten_hearts);
    
    ASSERT_EQUAL(true, mika->make_trump(trumpCard, false, 1, orderUpSuit));
    delete mika;
    
    //ROUND 1 NOT DEALER
    //EDELGARD HAS THREE CARDS THAT MATCH
    Player * edelgard = Player_factory("Edelgard", "Simple");
    
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    
    edelgard->add_card(ace_diamonds);
    edelgard->add_card(jack_diamonds);
    edelgard->add_card(jack_hearts);
    edelgard->add_card(nine_hearts);
    edelgard->add_card(ten_hearts);
    
    ASSERT_EQUAL(true, edelgard->make_trump(trumpCard, false, 1, orderUpSuit));
    delete edelgard;
    
    //ROUND 2 NOT DEALER
    //NO CARDS THAT MATCH
    Player * dimitri = Player_factory("Dimitri", "Simple");
    Card trumpCard2 = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    
    dimitri->add_card(ace_hearts);
    dimitri->add_card(king_hearts);
    dimitri->add_card(queen_hearts);
    dimitri->add_card(nine_hearts);
    dimitri->add_card(ten_hearts);
    
    ASSERT_EQUAL(false, dimitri->make_trump(trumpCard2, false, 2, orderUpSuit));
    delete dimitri;
    
    //ROUND 2 NOT DEALER
    //ONE CARD THAT MATCHES
    Player * claude = Player_factory("Claude", "Simple");
    
    Card king_spades = Card(Card::RANK_KING, Card::SUIT_SPADES);
    
    claude->add_card(king_spades);
    claude->add_card(king_hearts);
    claude->add_card(queen_hearts);
    claude->add_card(nine_hearts);
    claude->add_card(ten_hearts);
    
    ASSERT_EQUAL(true, claude->make_trump(trumpCard2, false, 2, orderUpSuit));
    delete claude;
    
    //ROUND 2 NOT DEALER
    //TWO CARD THAT MATCHES
    Player * hilda = Player_factory("Hilda", "Simple");
    
    Card queen_spades = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    
    hilda->add_card(king_spades);
    hilda->add_card(queen_spades);
    hilda->add_card(queen_hearts);
    hilda->add_card(nine_hearts);
    hilda->add_card(ten_hearts);
    
    ASSERT_EQUAL(true, hilda->make_trump(trumpCard2, false, 2, orderUpSuit));
    delete hilda;
    
    //ROUND 2, IS DEALER!!!!!!!!!
    //NO CARD THAT MATCHES
    Player *bernadetta = Player_factory("Bernadetta", "Simple");
    
    bernadetta->add_card(ace_hearts);
    bernadetta->add_card(king_hearts);
    bernadetta->add_card(queen_hearts);
    bernadetta->add_card(nine_hearts);
    bernadetta->add_card(ten_hearts);
    
    ASSERT_EQUAL(true, bernadetta->make_trump(trumpCard2, true, 2,
                                              orderUpSuit));
    delete bernadetta;
    
    ASSERT_EQUAL(SUIT_NAMES_BY_WEIGHT[0], orderUpSuit);
}

TEST(test_add_and_discard_simple) {
    //five cards, card is added
    Player * dimitri = Player_factory("Dimitri", "Simple");
    Card upCard = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ledCard = Card(Card::RANK_NINE, Card::SUIT_CLUBS);

       Card c1 = Card(Card::RANK_ACE, Card::SUIT_SPADES);
       Card c2 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
       Card c3 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
       Card c4 = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
       Card c5 = Card(Card::RANK_KING, Card::SUIT_SPADES);
       
       dimitri->add_card(c1);
       dimitri->add_card(c2);
       dimitri->add_card(c3);
       dimitri->add_card(c4);
       dimitri->add_card(c5);
    
    dimitri->add_and_discard(upCard);
       
       ASSERT_EQUAL(upCard, dimitri->play_card(ledCard, upCard.get_suit()));
       delete dimitri;
    //five cards, card not added
    Player * edelgard = Player_factory("Edelgard", "Simple");

       Card c6 = Card(Card::RANK_TEN, Card::SUIT_SPADES);
       
       edelgard->add_card(c1);
       edelgard->add_card(c2);
       edelgard->add_card(c3);
       edelgard->add_card(c6);
       edelgard->add_card(c5);
    
    edelgard->add_and_discard(upCard);
       
       ASSERT_EQUAL(c6, edelgard->play_card(ledCard, upCard.get_suit()));
       delete edelgard;
    
    //four cards, card is added
    Player * claude = Player_factory("Claude", "Simple");
       
       claude->add_card(c1);
       claude->add_card(c3);
       claude->add_card(c4);
       claude->add_card(c5);
    
    claude->add_and_discard(upCard);
       
       ASSERT_EQUAL(upCard, claude->play_card(ledCard, upCard.get_suit()));
       delete claude;
    
    //four cards, card not added
    Player * bernie = Player_factory("Bernie", "Simple");
    
       bernie->add_card(c1);
       bernie->add_card(c3);
       bernie->add_card(c6);
       bernie->add_card(c5);
    
    bernie->add_and_discard(upCard);
       
       ASSERT_EQUAL(c6, bernie->play_card(ledCard, upCard.get_suit()));
       delete bernie;
    
    //three cards, card is added
    Player * ashe = Player_factory("Ashe", "Simple");
       
       ashe->add_card(c1);
       ashe->add_card(c4);
       ashe->add_card(c5);
    
    ashe->add_and_discard(upCard);
       
       ASSERT_EQUAL(upCard, ashe->play_card(ledCard, upCard.get_suit()));
       delete ashe;
    
    //three cards, card not added
    Player * leonie = Player_factory("Leonie", "Simple");
    
       leonie->add_card(c1);
       leonie->add_card(c6);
       leonie->add_card(c5);
    
    leonie->add_and_discard(upCard);
       
       ASSERT_EQUAL(c6, leonie->play_card(ledCard, upCard.get_suit()));
       delete leonie;
    
    //two cards, card is added
    Player * manuela = Player_factory("Manuela", "Simple");
       
       manuela->add_card(c1);
       manuela->add_card(c4);
    
    manuela->add_and_discard(upCard);
       
       ASSERT_EQUAL(upCard, manuela->play_card(ledCard, upCard.get_suit()));
       delete manuela;
    
    //two cards, card not added
    Player * rhea = Player_factory("Rhea", "Simple");
    
       rhea->add_card(c1);
       rhea->add_card(c6);
    
    rhea->add_and_discard(upCard);
       
       ASSERT_EQUAL(c6, rhea->play_card(ledCard, upCard.get_suit()));
       delete rhea;
    
    //one card, card is added
    Player * seteth = Player_factory("Seteth", "Simple");
       
       seteth->add_card(c4);
    
    seteth->add_and_discard(upCard);
       
       ASSERT_EQUAL(upCard, seteth->play_card(ledCard, upCard.get_suit()));
       delete seteth;
    
    //one card, card not added
    Player * flayn = Player_factory("Flayn", "Simple");
    
       flayn->add_card(c6);
    
    flayn->add_and_discard(upCard);
       
       ASSERT_EQUAL(c6, flayn->play_card(ledCard, upCard.get_suit()));
       delete flayn;
}

TEST(test_lead_card_simple) {
    //five mix trump cards with left bower
    Player * hilda = Player_factory("Hilda", "Simple");
    string trumpCard = Card::SUIT_SPADES;
    
    Card c1 = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c2 = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c3 = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card c4 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c5 = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    
    hilda->add_card(c1);
    hilda->add_card(c2);
    hilda->add_card(c3);
    hilda->add_card(c4);
    hilda->add_card(c5);
    
    ASSERT_EQUAL(c2, hilda->lead_card(trumpCard));
    delete hilda;
    
    //five all trump cards with left bower
    Player * lysithea = Player_factory("Lysithea", "Simple");
    
    Card c6 = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    
    lysithea->add_card(c1);
    lysithea->add_card(c6);
    lysithea->add_card(c3);
    lysithea->add_card(c4);
    lysithea->add_card(c5);
    
    ASSERT_EQUAL(c1, lysithea->lead_card(trumpCard));
    delete lysithea;
    
    //five all trump cards without left bower
    Player * sylvain = Player_factory("Sylvain", "Simple");
       
    Card c7 = Card(Card::RANK_ACE, Card::SUIT_SPADES);
       
    sylvain->add_card(c7);
    sylvain->add_card(c6);
    sylvain->add_card(c3);
    sylvain->add_card(c4);
    sylvain->add_card(c5);
       
    ASSERT_EQUAL(c7, sylvain->lead_card(trumpCard));
    delete sylvain;
}

TEST(test_play_card_simple) {
    //mix of normal cards
    Player * gustavo = Player_factory("Gustavo", "Simple");
    Card ledCard = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    string trumpCard = Card::SUIT_SPADES;
    
    Card c1 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c2 = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c3 = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card c4 = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c5 = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    
    gustavo->add_card(c1);
    gustavo->add_card(c2);
    gustavo->add_card(c3);
    gustavo->add_card(c4);
    gustavo->add_card(c5);
    
    ASSERT_EQUAL(gustavo->play_card(ledCard, trumpCard), c2)
    delete gustavo;
    
    //mix of cards left bower
    Player * constantine = Player_factory("Constantine", "Simple");
    
    Card c6 = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    
    constantine->add_card(c1);
    constantine->add_card(c2);
    constantine->add_card(c6);
    constantine->add_card(c4);
    constantine->add_card(c5);
    
    ASSERT_EQUAL(constantine->play_card(ledCard, trumpCard), c2)
    delete constantine;
    
    //mix of cards right bower
    Player * vik = Player_factory("Vivek", "Simple");
    
    Card c7 = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    
    vik->add_card(c1);
    vik->add_card(c2);
    vik->add_card(c7);
    vik->add_card(c4);
    vik->add_card(c5);
    
    ASSERT_EQUAL(vik->play_card(ledCard, trumpCard), c2)
    delete vik;
    
    //can't follow suit
    Player * joey = Player_factory("Joey", "Simple");
    
    joey->add_card(c3);
    joey->add_card(c6);
    joey->add_card(c7);
    joey->add_card(c4);
    joey->add_card(c5);
    
    ASSERT_EQUAL(joey->play_card(ledCard, trumpCard), c6)
    delete joey;
    
}

// Add more tests here

TEST_MAIN()
