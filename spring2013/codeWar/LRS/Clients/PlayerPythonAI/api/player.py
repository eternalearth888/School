'''
Module player: classes, functions and constants for working with players and 
their tokens.
Created on Dec 4, 2011

@author: malcolmm
'''

import board
from xml.etree import ElementTree as ET

MODE = ('ACTIVE', 'POWER_DOWN', 'DESTROYED', 'DEAD')
"""
What mode the player/robot is in:
ACTIVE: Normal mode, it is moving around the board
POWER_DOWN: It is powered down - static on the board
DESTROYED: It is destroyed - it will return next turn
DEAD: Lost all three life tokens - it is no longer in the game.

"""
POWER_MODE = ('UP', 'ANNOUNCED', 'DOWN')
"""
The power down mode for this player/robot:
UP: Running (not down, not announced)
ANNOUNCED: Announced, will power down at the end of the turn
DOWN: Powered down.

"""

class Player(object):
    '''Class for representing a player in the game.'''
    
    def __init__(self, element):
        '''Create a player instance from the given XML Element.'''
        
        #guid: a unique string identifier for this player. This string will remain 
        #constant throughout the game (while the Player objects passed will change 
        #on every call).
        self.guid = element.get('guid')
        
        #lives: starts at 3, at 0 the player is removed from the board
        self.lives = int(element.get('lives'))
        
        #damage: starts at 0, cards start locking at 5, and the player loses a life 
        #when damage reaches 10.
        self.damage = int(element.get('damage'))
        
        #score: the score for this player.
        self.score = int(element.get('score'))
        
        #numLockedCards: the number of the player's cards that are locked. 
        #Locked cards are the last N cards from the previous turn.
        self.numLockedCards = int(element.find('cards').get('num-locked'))
        
        #repairOn: True if repair squares are working this turn
        self.repairOn = bool(element.get('repair-on'))
        
        #powerMode: which POWER_MODE this player is in.
        self.powerMode = element.get('power-mode')
        
        #The location the player's robot will re-enter on if it loses a life.
        self.archive = ( int(element.get('archive-x')), int(element.get('archive-y')) )
        
        #robot: the player's robot object.
        self.robot = Robot(element.find('robot'))
        
        #flagStates: where the flags are and if they've been touched by this player.
        self.flagStates = flagStatesFromXML(element.find('flags'))
        
        #cards: the player's cards.
        self.cards = cardsFromXML(element.find('cards'))
    
    def getScore(self):
        '''The score for this player.'''
        return self.score
    
    def getNumFlagsTouched(self):
        '''The number of flags the player has touched. If it is 3 the player has won.'''
        return len([fs for fs in self.flagStates if fs.touched])
    
    def hasWon(self):
        '''True if the player has touched all three flags in the correct order.'''
        return self.numFlagsTouched() == len(self.flagStates)
    
    def isVisible(self):
        '''True if the player's robot is on the map, false if it is dead or destroyed.'''
        return (self.getMode() != "DEAD" and 
                self.getMode() != "DESTROYED")
    
    def getMode(self):
        '''The mode this player is in.'''
        if   self.lives <= 0:
            return "DEAD"
        elif self.damage >= 10:
            return "DESTROYED"
        elif self.powerMode == "DOWN":
            return "POWER_DOWN"
        else:
            return "ACTIVE"
    
    def getNumLockedCards(self):
        '''The number of the player's cards that are locked. Locked cards are the 
        last N cards from the previous turn.'''
        return self.numLockedCards
    
    def __eq__(self, other):
        if isinstance(other, Player) and self.guid == other.guid:
            return True
        else:
            return False
    

class FlagState(object):
    '''Class representing the state of a specific flag for a particular player.'''
    
    def __init__(self, element):
        '''Build the flag from the given XML Element.'''
        self.position = ( int(element.get('x')), int(element.get('y')) )
        self.touched = element.get('touched').lower() == 'true'
     

class Robot(object):
    '''A player's robot.'''
    
    def __init__(self, element):
        '''Create a robot object from the given XML Element or string.
        
        If element is of type str, it will be parsed as XML to create an 
        instance of the xml.etree.ElementTree.Element class.  Otherwise, it 
        is assumed to be an Element already.
        
        '''
        if type(element) == type(str()):
            element = ET.XML(element)
        self.location = board.BoardLocation(element)
    
    def __repr__(self):
        return ("Robot('<robot direction=\"" + 
                self.location.direction + 
                '" x="' + self.location[0] + '" y="' + self.location[1] + 
                "\" />')")
    

ROBOT_MOVE = {'BACKWARD_ONE':0, 'FORWARD_ONE':1, 'FORWARD_TWO':2, 
              'FORWARD_THREE':3, 'ROTATE_LEFT':4, 'ROTATE_RIGHT':5, 
              'ROTATE_UTURN':6}
"""The different types of moves possible for a move card."""

class Card(object):
    '''A card (move) for a robot.'''
    
    def __init__(self, element):
        '''Create a Card object from an XML Element or string.
        
        If element is of type str, it will be parsed as XML to create an 
        instance of the xml.etree.ElementTree.Element class.  Otherwise, it 
        is assumed to be an Element already.
        
        '''
        if type(element) == type(str()):
            element = ET.XML(element)
        self.move = element.get('move')
        self.priority = int(element.get('priority'))
    
    def isRotate(self):
        return (self.move == "ROTATE_LEFT" or
                self.move == "ROTATE_RIGHT" or
                self.move == "ROTATE_UTURN")
    
    def getXML(self):
        return ET.Element('card', {'priority':str(self.priority), 'move':self.move})
    
    def __repr__(self):
        return ("Card('<card move=" + repr(self.move) + " priority=" + 
                 repr(self.priority) + " />')")
    
    def __str__(self):
        return (self.move + ': ' + str(self.priority))
    

def playersFromXML(element):
    '''Return a list of Player objects from the given XML Element.'''
    return [Player(p) for p in element.findall('player')]

def cardsFromXML(element):
    '''Return a list of Card objects from the given XML Element.'''
    return [Card(c) for c in element.findall('card')]

def flagStatesFromXML(element):
    '''Return a list of FlagState objects from the given XML ELement.'''
    return [FlagState(f) for f in element.findall('flag-state')]
