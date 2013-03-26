'''
Module playerTurn: contains the PlayerTurn class, which represents a requested 
move for a player's turn.

Created on Dec 8, 2011

@author: malcolmm
'''

from xml.etree import ElementTree as ET

class PlayerTurn(object):
    '''A requested move for a player's turn.'''
    
    def __init__(self, cards, isPowerDown):
        '''Return a PlayerTurn object from the given (ordered) list of cards.
        
        cards -- List of the Card objects that will be used in your next turn.  
            If you have locked cards, only the first N (unlocked) cards 
            returned will be used.  If you do not return enough cards, random 
            cards will be assigned.  Locked cards are the last N cards from 
            the previous turn.
        isPowerDown -- True if you've decided to power down at the end of this 
            turn.  Remember that you still need to return cards, because the 
            power down does not occur until the start of the NEXT turn!
        
        '''
        self.cards = cards if cards is not None else list()
        self.isPowerDown = isPowerDown
    
    def getXML(self):
        '''Return an XML Element object representing the turn.'''
        xmlTurn = ET.Element('turn', {'power-down': str(self.isPowerDown)})
        xmlCards = ET.Element('cards')
        for card in self.cards:
            xmlCards.append(card.getXML())
        xmlTurn.append(xmlCards)
        return xmlTurn
    
    def __repr__(self):
        buff = ["PlayerTurn( ["]
        for card in self.cards:
            buff.append(repr(card) + ', ')
        if len(self.cards) > 0:
            buff[-1] = buff[-1][:-2]
        buff.append('], isPowerDown=' + str(self.isPowerDown) + ' )')
        return ''.join(buff)
    
    def __str__(self):
        buff = ["Turn: Cards["]
        for card in self.cards:
            buff.append(str(card) + ', ')
        if len(self.cards) > 0:
            buff[-1] = buff[-1][:-2]
        buff.append(']')
        if self.isPowerDown:
            buff.append(', PowerDown')
        return ''.join(buff)
    
