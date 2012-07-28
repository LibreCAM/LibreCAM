#!/usr/bin/env python2.5
#
#  emc2.py
#  QCad
#
#  Created by Ries van Twisk on 7/25/10.
#  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
#
# Class to test the emc2 class
#
#

from emc2 import emc2
		
test = emc2(True)
test.init("Ries.tap")
test.preCode()
test.setFeedRate(2000)
test.setCutterCompensation('DLEFT',6.2)
test.setCutterCompensation('LEFT',6.2)
test.rapidMove(0,0)
test.turnSpindleOn('CW')
test.linearMove(10)
test.linearMove(10,10)
test.linearMove(0,10)
test.linearMove(0,0)
test.linearMove(5,5)
test.postCode()
test.teardown()
