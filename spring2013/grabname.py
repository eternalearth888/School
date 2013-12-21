import os
someDir = "./pokemon"
someFile = open("pokemon.txt", "w")
for poke in os.listdir(someDir):
	someFile.write(poke[:-4] + "\n")
