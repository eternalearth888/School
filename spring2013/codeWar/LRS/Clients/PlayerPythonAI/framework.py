'''
Created on Dec 4, 2011

@author: malcolmm
'''

from __future__ import print_function
from __future__ import division

import sys, time, base64, traceback
from xml.etree import ElementTree as ET

import tcpClient, myPlayerBrain, api
from debug import trap, printrap, bugprint

DEFAULT_ADDRESS = "127.0.0.1" # local machine


class Framework(object):
    def __init__(self, args):
        if   len(args) >= 3:
            self._brain = myPlayerBrain.MyPlayerBrain(args[1], args[2])
        elif len(args) >= 2:
            self._brain = myPlayerBrain.MyPlayerBrain(args[1])
        else:
            self._brain = myPlayerBrain.MyPlayerBrain()
        self.ipAddress = args[0] if len(args) >= 1 else DEFAULT_ADDRESS
        print("Connecting to server '%s' for user: %r, password: %r" %
              (self.ipAddress, self._brain.name, self._brain.password))
    
    def _run(self):
        print("starting...")
        
        self.client = tcpClient.TcpClient(self.ipAddress, self)
        self.client.start()
        self._connectToServer()
        
        #It's all messages to us now.
        print('enter "exit" to exit program')
        try:
            while True:
                line = raw_input()
                if line == 'exit':
                    break
        except EOFError:
            self.client.close() # exit on EOF
        finally:
            self.client.close()
    
    def statusMessage(self, message):
        trap()
        print(message)
    
    def incomingMessage(self, message):
        try:
            startTime = time.clock()            
            # get the XML - we assume we always get a valid message from the server.
            xml = ET.XML(message)
            name = xml.tag
            if name == 'start-position':
                players = api.player.playersFromXML(xml.find("players"))
                guid = xml.find("players").get("your-guid")
                start = self._brain.setup( api.board.GameMap(xml.find("map")), 
                                           [p for p in players if p.guid == guid][0], 
                                           players, _getPoints(xml.find("points")), 
                                           xml.get("game-start").lower() == "true" )
                print("Starting robot at: %s" % start)
                doc = ET.Element('start-position', start.getAttributes())
                self.client.sendMessage(ET.tostring(doc))
            elif name == 'turn':
                turnOn = int(xml.get('turn'))
                print("turn %i request starting" % turnOn)
                allPlayers = api.player.playersFromXML(xml.find('players'))
                guid = xml.find('players').get('your-guid')
                turn = self._brain.turn( api.board.GameMap(xml.find("map")), 
                                         [p for p in allPlayers if p.guid == guid][0], 
                                         allPlayers, 
                                         api.player.cardsFromXML(xml.find('cards')) )
                print("Turn: %i - %s" % (turnOn, turn))
                docTurn = turn.getXML()
                docTurn.set("turn", str(turnOn))
                print("turn %i replying" % turnOn)
                self.client.sendMessage(ET.tostring(docTurn))
            else:
                printrap("ERROR: bad message (XML) from server - root node %r" % name)
            turnTime = time.clock() - startTime
            prefix = '' if turnTime < .8 else "WARNING - "
            prefix = "!DANGER! - " if turnTime >= 1 else prefix
            print(prefix + "turn took %r seconds" % turnTime)
        except Exception as e:
            traceback.print_exc()
            printrap("Error on incoming message.  Exception: %r" % e)
    
    def connectionLost(self, exception):
        print("Lost our connection! Exception: %r" % exception)
        client = self.client
        
        delay = .5
        while True:
            try:
                if client is not None:
                    client.close()
                client = self.client = tcpClient.TcpClient(self.ipAddress, self)
                client.start()
                
                self._connectToServer()
                print("Re-connected")
                return
            except Exception as e:
                print("Re-connection failed! Exception: %r" % e) # fix this
                time.sleep(delay)
                delay += .5
    
    def _connectToServer(self):
        root = ET.Element('join', {'password': self._brain.password, 
                                   'name': self._brain.name})
        avatar = self._brain.avatar
        if avatar is not None:
            av_el = ET.Element('avatar')
            av_el.text = base64.b64encode(avatar)
            root.append(av_el)
        self.client.sendMessage(ET.tostring(root))
    

def _getPoints(element):
    return [ (int(elemOn.get('x')), int(elemOn.get('y'))) 
             for elemOn in element.findall('position') ]

if __name__ == '__main__':
    printrap(sys.argv[0], breakOn=not sys.argv[0].endswith("framework.py"))
    framework = Framework(sys.argv[1:])
    framework._run()
