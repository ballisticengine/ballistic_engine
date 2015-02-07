class aimingManipulator(manipulatorClass):
    def onEntityCollision(self,entitya,entityb,ci):
        if entitya.subtype=="bullet":
            
            print "ambullet"