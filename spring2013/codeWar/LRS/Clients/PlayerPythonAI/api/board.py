'''
Module board: classes, functions and constants for working with the game 
board and its properties.
Created on Dec 16, 2011

@author: malcolmm
'''

DIRECTIONS = {"NORTH":0, "EAST":1, "SOUTH":2, "WEST":3}
"""The direction a robot or laser is facing. Also used for the direction a 
conveyor is running."""
DIRNUMS = {0:"NORTH", 1:"EAST", 2:"SOUTH", 3:"WEST"}

SIDE = {"NONE": 0, "NORTH": 0x01, "EAST": 0x02, "SOUTH": 0x04, "WEST": 0x08}
"""Which side(s) of a square has a wall. A square can have multiple walls."""

TYPE = ("NORMAL", "CONVEYOR_BELT", "ROTATE_CLOCKWISE", "ROTATE_COUNTERCLOCKWISE",
        "REPAIR", "FLAG", "PIT")
"""The different types a MapSquare can be."""


class GameMap(object):
    '''Represents the state of the game map.'''
    
    def __init__(self, element):
        '''Create the map from the given XML Element.'''
        
        self.width = int(element.get('width'))
        self.height = int(element.get('height'))
        xmlsquares = element.findall('square')
        
        #make a list of the locations of all flags, then sort them by order
        flags = [(square.get('flag'), square.get('x'), square.get('y')) 
                 for square in xmlsquares if square.get('flag') != '0']
        flags.sort()
        #then put them into a new list as 2-tuples (points)
        self.flags = [(flag[1], flag[2]) for flag in flags]
        
        #make a list of lists representing the map grid--each (x, y) square on 
        #the map is accessed by: gameMapInstance.squares[x][y]
        mapsquares = []
        for x in range(self.width):
            xrow = [xsq for xsq in xmlsquares if int(xsq.get('x')) == x]
            yrow = []
            for y in range(self.height):
                squares = [ysq for ysq in xrow if int(ysq.get('y')) == y]
                assert len(squares) == 1 #there should be exactly one square at (x, y)
                yrow.append(MapSquare(squares[0]))
            mapsquares.append(yrow)
        self.squares = mapsquares
    
    def getSquare(self, location):
        '''Return the mapSquare at the location (x, y).'''
        return self.squares[location[0]][location[1]]
    

def makeFlags(sides):
    '''Returns a numeric flag including walls at every side in the list given.'''
    ret = 0
    for side in sides:
        ret |= SIDE[side]
    return ret

class MapSquare(object):
    '''A class representing an individual square on the map.'''
        
    def __init__(self, element):
        '''Construct a new MapSquare instance from the given XML Element.'''
        
        self.type = element.get('type')
        self.walls = makeFlags(element.get('walls').split(', '))
        self.flag = int(element.get('flag'))
        
        conveyorElement = element.find('conveyor')
        self.conveyor = (None if conveyorElement is None 
                         else MapSquare.Conveyor(conveyorElement))
        
        laserElement = element.find('laser')
        self.laser = (None if laserElement is None
                      else MapSquare.Laser(laserElement))
    
    class Laser(object):
        '''A laser on the board. This sits on a specific map square.'''
        
        def __init__(self, element):
            '''Laser(xml.etree.ElementTree.Element) -> Initialize with the values in 
            the given XML.'''
            
            self.location = BoardLocation(element)
            self.numSquares = int(element.get('num-squares'))
        
    class Conveyor(object):
        '''A conveyor belt.  This is a subelement of a map square and 
        represents the conveyor belt on that single square.'''
    
        def __init__(self, element):
            '''Conveyor(xml.etree.ElementTree.Element) -> Constructs a new 
            Conveyor object from the given XML.'''
            
            #The speed of the belt. Values are 1 or 2.
            self.speed = int(element.get('speed'))
            #The direction the belt exits to.
            self.direction = element.get('direction')
            #The direction(s) the belt enters from.
            self.entry = makeFlags(element.get('entry').split(', '))
        
    
class BoardLocation(object):
    '''
    Represents a position and direction on the game board.
    
    BoardLocation(Element) -> construct a new BoardLocation from XML.
    BoardLocation(BoardLocation) -> return a new copy of the given BoardLocation.
    BoardLocation(point, direction) -> construct a new BoardLocation, where 
        point is an (x, y) 2-tuple representing a location on the board and 
        direction is a string in DIRECTIONS.keys().
    
    In general, a BoardLocation's position is (-1, -1) if the unit is dead.
    
    '''
    def __init__(self, arg1, arg2=None):
        '''Construct a new BoardLocation from the given arguments.
        See class documentation for more information.'''
        
        if arg2 is None:
            if   arg1.__class__.__name__ == 'BoardLocation': #copy constructor
                self.mapPosition = arg1.mapPosition
                self.direction = arg1.direction
            elif arg1.__class__.__name__ == 'Element': #from XML
                self.mapPosition = (int(arg1.get('x')), int(arg1.get('y')))
                self.direction = arg1.get('direction')
            else:
                raise TypeError("Unrecognized constructor argument: %r" % arg1)
        else:
            self.mapPosition = arg1
            self.direction = arg2
        assert self.direction in DIRECTIONS
    
    def getAttributes(self):
        '''Return this BoardLocation's attributes as a dictionary.'''
        
        return {"direction": self.direction,
                "x": str(self.mapPosition[0]),
                "y": str(self.mapPosition[1])}
        
    def move(self, numtimes):
        '''Return a new BoardLocation object moved the requested number of squares 
        in the location's direction. This can move off the board and is not blocked 
        by units or walls.'''
        
        if   self.direction == "NORTH":
            return BoardLocation( (self.mapPosition[0], self.mapPosition[1]-numtimes),
                                   self.direction )
        elif self.direction == "EAST":
            return BoardLocation( (self.mapPosition[0]+numtimes, self.mapPosition[1]),
                                   self.direction )
        elif self.direction == "SOUTH":
            return BoardLocation( (self.mapPosition[0], self.mapPosition[1]+numtimes),
                                   self.direction )
        elif self.direction == "WEST":
            return BoardLocation( (self.mapPosition[0]-numtimes, self.mapPosition[1]),
                                   self.direction )
        else:
            raise TypeError("Unrecognized direction %r" % self.direction)
        
    def rotate(self, numtimes):
        '''Return a new BoardLocation rotated clockwise (NESW) the given number 
        of times (can be positive or negative). A value of 4 results in a full circle.'''
        
        dirnum = (DIRECTIONS[self.direction] + numtimes) % 4
        return BoardLocation(self.mapPosition, DIRNUMS[dirnum])
    
    def __eq__(self, other):
        if other.__class__.__name__ == "BoardLocation":
            return (self.direction == other.direction and 
                    self.mapPosition == other.mapPosition)
        return False
    
    def __hash__(self):
        return hash(self.mapPosition) ^ hash(self.direction)
    
    def __repr__(self):
        return "BoardLocation( %r, %r )" % (self.mapPosition, self.direction)
    
