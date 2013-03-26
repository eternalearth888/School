'''
Module myPlayerBrain: the sample Python AI.  Start with this project but write 
your own code as this is a very simplistic implementation of the AI.

Created on Dec 7, 2011

@author: malcolmm
'''

import random
import utilities, playerTurn, debug
from api import board, player

NUM_CARDS = 1

class MyPlayerBrain(object):
    '''The Python AI class.  This class must have the methods setup and turn.'''
    
    def __init__(self, password="Donald Knuth", name="Donald Knuth"):
        self.password = password #The password for joining the game.
        self.name = name #The name of the player.
        
        #The player's avatar (looks in the same directory that this module is in).
        #Must be a 32 x 32 PNG file.
        try:
            avatar = open("MyAvatar.png", "rb") #TODO: test
            avatar_str = b''
            for line in avatar:
                avatar_str += line
            avatar = avatar_str
        except IOError:
            avatar = None # avatar is optional
        self.avatar = avatar
    
    def setup(self, gMap, you, allPlayers, startPoints, isGameStart):
        '''
        Return your AI's requested starting point (a BoardLocation).
        
        Called when your robot must be placed on the board.  This is called at 
        the start of the game and each time your robot dies.  Return the 
        BoardLocation on which to place your unit (location and direction).
        
        gMap -- The current GameMap.  There will be no units on this map.
        you -- Your Player object.
        allPlayers -- List of all Player objects (including you).
        startPoints -- List of all (x, y) position(s) on the map where you can 
            place your robot. This will be a single point unless another 
            robot is on your archive point.
        isGameStart -- True if start of game.  False if re-entering the game.
        
        '''
        return board.BoardLocation(startPoints[0], "NORTH")
    
    def turn(self, gMap, you, allPlayers, cards):
        '''
        Return your AI's requested PlayerTurn.
        
        Called each time the system needs another turn.  If you do not return a 
        valid turn, the game will randomly move one of your units.  **This call 
        must return in under 1 second.**  If it has not returned in 1 second the 
        call will be aborted and a random move will be assigned.
        
        gMap -- The current GameMap with all units on it.
        you -- Your Player object.  This is created for each call.
        allPlayers -- List of all Player objects including you.  This is 
            created for each call.
        cards -- List of all Card objects you can pick from.  This does not 
            include locked cards.
        
        '''
        # if hurt bad, consider power down
        powerDown = False
        if you.damage > 5 and random.randrange(3) == 0:
            powerDown = True
        
        # get 40 sets, pick the one that's closest to the flag
        # (middle of the board if got all flags)
        bestCards = None
        bestDiff = float('infinity')
        okDiff = random.randint(0, 3)
        flagStates = [fs for fs in you.flagStates if not fs.touched]
        flagPoint = (flagStates[0].position if len(flagStates) > 0 else 
                     (gMap.width / 2, gMap.height / 2))
        for _ in range(40):
            # pick NUM_CARDS (or fewer if locked) random cards
            moveCards = [None for i in range(NUM_CARDS)]
            cardUsed  = [False for i in range(len(cards))]
            for i in range(NUM_CARDS - you.numLockedCards):
                while True:
                    index = random.randrange(len(cards))
                    if cardUsed[index]:
                        continue
                    moveCards[i] = cards[index]
                    cardUsed[index] = True
                    break
            # add in the locked cards
            for i in range(NUM_CARDS - you.numLockedCards, NUM_CARDS):
                moveCards[i] = you.cards[i]
            # if all we have are rotates, we add in a move forward 1 (since 
            # this AI is too dumb to plan even one move ahead, it would 
            # never choose to make a turn otherwise) 
            if len([c for c in moveCards if not c.isRotate()]) == 0:
                moveCards.append(player.Card('''<card move="FORWARD_ONE" 
                                                priority="500" />'''))
            # run it
            moveTo = utilities.cardDestination(gMap, you.robot.location, moveCards)
            if moveTo.dead:
                continue
            # if better than before, use it
            diff = ( abs(flagPoint[0] - moveTo.location.mapPosition[0]) + 
                     abs(flagPoint[1] - moveTo.location.mapPosition[1]) )
            if diff <= okDiff:
                return playerTurn.PlayerTurn(moveCards, powerDown)
            if diff < bestDiff:
                bestDiff = diff
                bestCards = moveCards
            
        return playerTurn.PlayerTurn( 
                bestCards if bestCards is not None else list(), powerDown)
    # end method: turn
# end class: MyPlayerBrain