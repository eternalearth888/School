'''
Module utilities: contains utilities that can be of use to an AI.

MovePoint(location, damage, dead) -- the result of the following 'move' 
    functions.
cardDestination(gameMap, startLocation, cards) -- return the result of applying 
    cards in order, starting at startLocation.
cardPath(gameMap, startLocation, cards) -- like cardDestination, but returns a 
    list of every step along the way.
move(gameMap, location, movement) -- return the result of applying a single 
    movement at location.
moveDirection(start, end) -- calculate the direction of movement from start 
    to end.
calcLaserDamage(gameMap, location) -- calculate the damage a robot will 
    receive from lasers (not other robots!) at location.

Created on Dec 4, 2011

@author: malcolmm
'''

import api.player
from debug import trap
from api.board import BoardLocation, SIDE, TYPE
from api.board import DIRECTIONS as DIRS


class MovePoint(object):
    '''The result of one of the utilities module's "move" functions.'''
    
    def __init__(self, location, damage=0, dead=False):
        '''Create a MovePoint object where location is the result of the move.
        
        damage -- the amount of damage the move incurred on the robot. 
            Defaults to 0.
        dead -- whether the robot was killed (moved off the board).  Defaults 
            to False.
        
        '''
        self.location = location
        self.damage = damage
        self.dead = dead
    

def cardDestination(gameMap, startLocation, cards):
    '''Return the MovePoint resulting from applying cards at startLocation.
    
    Ignores all robots on the map but does take into account walls, conveyor 
    belts and gears.  Returns the final location of the move.
    
    gameMap -- the current state of the game map.
    startLocation -- the starting BoardLocation of the move.
    cards -- list of robot Card moves, to be applied in order.
    
    '''
    points = cardPath(gameMap, startLocation, cards)
    if points is None or len(points) == 0:
        trap()
        return None
    else:
        return points[-1]
    
def cardPath(gameMap, startLocation, cards):
    '''Return a list of MovePoints containing every step resulting from 
    applying cards at startLocation.
    
    Ignores all robots on the map but does take into account walls, 
    conveyor belts and gears.
    
    gameMap -- the current state of the game map.
    startLocation -- the starting BoardLocation of the move.
    cards -- list of robot Card moves, to be applied in order.
    
    '''
    #if we can't move, we end up where we started
    points = [MovePoint(startLocation)]
    
    for card in cards:
        #move robot
        endPoint = move(gameMap, startLocation, card.move)
        if endPoint.dead:
            points.append(endPoint)
            return points
        if endPoint.location != startLocation:
            startLocation = endPoint.location
            points.append(MovePoint(startLocation))
        
        sq = gameMap.getSquare(startLocation.mapPosition)
        
        #conveyor belt - may cause a 1/4 turn.
        speed = 1
        while sq.conveyor is not None and speed <= sq.conveyor.speed:
            endPoint = move(gameMap, startLocation.mapPosition, 
                            sq.conveyor.direction)
            locMove = BoardLocation(endPoint.location.mapPosition, 
                                    startLocation.direction)
            sq = gameMap.getSquare(endPoint.location.mapPosition)
            if sq.conveyor is not None:
                dirEnter = moveDirection(startLocation.mapPosition, 
                                         endPoint.location.mapPosition)
                if dirEnter is None:
                    dirEnter = startLocation.direction
                locMove = locMove.rotate(DIRS[sq.conveyor.direction] - DIRS[dirEnter])
            startLocation = locMove
            points.append(MovePoint(startLocation))
            speed += 1
        
        #gears
        if   sq.type == "ROTATE_CLOCKWISE":
            startLocation = startLocation.rotate(1)
        elif sq.type == "ROTATE_COUNTERCLOCKWISE":
            startLocation = startLocation.rotate(-1)
        else:
            assert sq.type in TYPE
        
        points.append(MovePoint(startLocation))
        
        #damage
        damage = calcLaserDamage(gameMap, startLocation)
        if damage != 0:
            points[-1].damage = damage
    return points

def calcLaserDamage(gameMap, location):
    '''Calculate the damage a unit will receive from lasers at location.'''
    damage = 0
    damage += _calcLaserDamage(gameMap, location.mapPosition, 0, -1, 
                               "SOUTH", SIDE["NORTH"], SIDE["SOUTH"])
    damage += _calcLaserDamage(gameMap, location.mapPosition, 0, 1, 
                               "NORTH", SIDE["SOUTH"], SIDE["NORTH"])
    damage += _calcLaserDamage(gameMap, location.mapPosition, -1, 0, 
                               "EAST", SIDE["WEST"], SIDE["EAST"])
    damage += _calcLaserDamage(gameMap, location.mapPosition, 1, 0, 
                               "WEST", SIDE["EAST"], SIDE["WEST"])
    return damage

def _calcLaserDamage(gameMap, position, xAdd, yAdd, laserDirection, wallExit, wallEnter):
    '''Return the damage a unit at position will take from lasers firing 
    from laserDirection.
    '''
    damage = 0
    x = position[0]
    y = position[1]
    startSquare = True
    
    while 0 <= x < gameMap.width and 0 <= y < gameMap.height:
        sq = gameMap.squares[x][y]
        #can we move into this square?
        if not startSquare and (sq.walls & wallEnter) != 0:
            break
        startSquare = False
        
        if sq.laser is not None and sq.laser.location.direction == laserDirection:
            damage += 1
            break #lasers cannot shoot through each other
        
        #can we move out of this square?
        if (sq.walls & wallExit) != 0:
            break
        
        x += xAdd
        y += yAdd
    return damage

def move(gameMap, location, movement):
    '''Return the MovePoint resulting from applying movement at location.
    
    Ignores all robots on the map but does take into account walls, conveyor 
    belts and gears.
    
    location -- Either a BoardLocation or (x, y) point.  If a BoardLocation, 
        'movement' will be considered a player.ROBOT_MOVE index.  If  a 
        tuple, 'movement' will be considered a board.DIRECTION index.
    movement -- A string indicating either the direction in which to move 
        (by one square), or the move card to apply.
    
    '''
    if   type(location) is type(tuple()):
        return _moveByDirection(gameMap, location, movement)
    elif location.__class__.__name__ == "BoardLocation":
        return _moveByCard(gameMap, location, movement)
    else:
        raise TypeError("Unexpected type for parameter 'location': %r" % location)

def _moveByCard(gameMap, startLocation, move):
    '''Move a unit one card move.

    Ignores all robots on the map but does take into account walls, 
    conveyor belts and gears.  Returns the final location of the move.
    '''
    steps = 0
    moves = api.player.ROBOT_MOVE
    assert len(moves) == 7
    if   move == "BACKWARD_ONE":
        steps = -1
    elif move == "FORWARD_ONE":
        steps = 1
    elif move == "FORWARD_TWO":
        steps = 2
    elif move == "FORWARD_THREE":
        steps = 3
    elif move == "ROTATE_LEFT":
        return MovePoint(startLocation.rotate(-1))
    elif move == "ROTATE_RIGHT":
        return MovePoint(startLocation.rotate(1))
    elif move == "ROTATE_UTURN":
        return MovePoint(startLocation.rotate(2))
    else:
        raise TypeError("Unrecognized move type %r" % move)
    
    moveDir = (startLocation.direction if steps >= 0 
               else startLocation.rotate(2).direction)
    position = startLocation.mapPosition
    while steps != 0:
        mp = _moveByDirection(gameMap, position, moveDir)
        if mp.dead:
            return MovePoint(BoardLocation(mp.location.mapPosition, 
                                           mp.location.direction), dead=True)
        position = mp.location.mapPosition
        singleStep = max(-1, min(1, steps))
        steps -= singleStep
    return MovePoint(BoardLocation(position, startLocation.direction))

#NESW
_sideMoveOut = ('NORTH', 'EAST', 'SOUTH', 'WEST')
_sideMoveIn  = ('SOUTH', 'WEST', 'NORTH', 'EAST')

def _moveByDirection(gameMap, position, direction):
    '''Move a unit one square in the given direction.
    
    Ignores all robots on the map but does take into account walls, conveyor 
    belts and gears.  Returns the final location of the move.
    '''
    #watch for wall in this direction
    sideExit  = SIDE[_sideMoveOut[DIRS[direction]]]
    sideEnter = SIDE[_sideMoveIn [DIRS[direction]]]
    location  = BoardLocation(position, direction)
    
    #can we exit this square?
    sq = gameMap.getSquare(position)
    if (sq.walls & sideExit) != 0:
        return MovePoint(location)
    moveTo = location.move(1)
    
    #did we go off the board?
    if (    moveTo.mapPosition[0] < 0 or gameMap.width  <= moveTo.mapPosition[0] or
            moveTo.mapPosition[1] < 0 or gameMap.height <= moveTo.mapPosition[1] or 
            gameMap.getSquare(moveTo.mapPosition).type == "PIT" ):
        return MovePoint(location, dead=True)
    
    #can we enter the new square?
    sq = gameMap.getSquare(moveTo.mapPosition)
    if (sq.walls & sideEnter) != 0:
        return MovePoint(location)
    
    return MovePoint(moveTo)

def moveDirection(start, end):
    '''Calculate the direction of movement from start to end.'''
    
    if   start[1] > end[1]:
        return "NORTH"
    elif start[1] < end[1]:
        return "SOUTH"
    elif start[0] > end[0]:
        return "WEST"
    elif start[0] < end[0]:
        return "EAST"
    else:
        raise TypeError("Start cannot equal end point (start: %r end: %r)" % 
                        (start, end))
        return None
    
