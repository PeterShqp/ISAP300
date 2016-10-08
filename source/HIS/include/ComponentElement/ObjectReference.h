/*
 * ObjectReference.h
 *
 *  Created on: 2013-12-10
 *      Author: Administrator
 */

#ifndef OBJECTREFERENCE_H_
#define OBJECTREFERENCE_H_

class CardXC;
class Card24E1;
class CardVF;
class CardPCMXC;
class Card16FE1;
class CardDXC;
class CardFAN;

class ObjectReference {
public:
    ObjectReference();
    virtual ~ObjectReference();

    static CardXC* getPXCCard(int sn);
    static CardDXC* getDXCCard(int sn);
    static CardDXC* getWorkingDXC(void);
    static CardPCMXC* getPCMXCCard(int sn);
    static Card24E1* get24E1Card(int sn);
    static CardVF* getVFCard(int sn);
    static int getOPTMode(void); //return 0 622 ,return 1 155
    static Card16FE1* get16FE1Card(int sn);

    static CardFAN* getFANCard(void);

};

#endif /* OBJECTREFERENCE_H_ */
