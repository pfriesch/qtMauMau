#ifdef TEST
#ifndef GCPROXY_MOCKUP_H
#define GCPROXY_MOCKUP_H
#include "gameLogic/gamecontrollerproxy.h"

class GCProxy_mockup : public GameControllerProxy {
public:
    GCProxy_mockup();
    void playCard(const Card& card, Card::cardSuit whishedSuit);
    void drawCard();
};

#endif // GCPROXY_MOCKUP_H
#endif //TEST
