#ifndef GSTATEFLAGS_H
#define GSTATEFLAGS_H

#include "card.h"

class GStateFlags {
private:
    //Game state flags
    short currentPlayer;
    bool changedDirection;
    bool colorWished;
    Card::cardSuit wishedSuit;
    bool draw2x;
    short draw2xCount;
    bool skipNextPlayer;

public:
    GStateFlags(short currentPlayer = 0,
                bool changedDirection = false,
                bool colorWished = false,
                Card::cardSuit wishedSuit = 0,
                bool draw2x = false,
                short draw2xCount = 0,
                bool skipNextPlayer = false);
    short getCurrentPlayer() const;
    void setCurrentPlayer(short value);
    bool getChangedDirection() const;
    void setChangedDirection(bool value);
    bool getColorWished() const;
    void setColorWished(bool value);
    Card::cardSuit getWishedSuit() const;
    void setWishedSuit(const Card::cardSuit &value);
    bool getDraw2x() const;
    void setDraw2x(bool value);
    short getDraw2xCount() const;
    void setDraw2xCount(short value);
    bool getSkipNextPlayer() const;
    void setSkipNextPlayer(bool value);
};

#endif // GSTATEFLAGS_H
