#ifdef TEST
#include "gcproxy_mockup.h"

GCProxy_mockup::GCProxy_mockup()
    : GameControllerProxy(nullptr, PLAYER::NONE)
{
}

void GCProxy_mockup::playCard(const Card& card, Card::cardSuit whishedSuit)
{
    UNUSED(card);
    UNUSED(whishedSuit);
}

void GCProxy_mockup::drawCard()
{
}
#endif
