#!/usr/bin/env python2.5
#
#  emc2.py
#  LibreCAD
##
# This class generates RS274D comaptible GCode for use in EMC
#
# Implemented are
# preCode()
# postCode()
#
# ! means required
# setFeedRate(number units)
# setSpindleRPM(number rpm)
# setUnit(MM or INCH)
# setCutterCompensation(LEFT(D) or RIGHT(D) or OFF or DLEFT(!D,L) or DRIGHT(!D,L), number D, number L)
# setPathControlMode(EXACTPATH or EXACTSTOP or BESTSPEED or MOTIONBLEND(P,Q), number P, number Q)
# turnSpindleOn(CCW or CW or OFF)
# linearMove(number X, number Y, number Z)
# RapidMove(number X, number Y, number Z)
# arc(CW or CCW, number X, number Y, number Z, number I, number J, number F)

def enum(**enums):
    return type('Enum', (), enums)

MOTION=enum(RAPID=0, LINEAR=1)

class emc2:
	showComments=True
	
	def __init__(self, showComments=True):
		self.showComments=showComments

# Initialize the class and 		
	def init(self, filename):
		self.FILE = open(filename,"w")

# Use this function to write a line to the file
	def writeToFile(self, line, comment=None):
		if comment==None or self.showComments==False:
			comment=''
		else:
			comment=' ('+comment+')'
		self.FILE.writelines(line + comment + "\n");

# Teardown function will get called when it's time to close to file, and any cleanup has to be done
	def teardown(self):
		self.FILE.close()

# Example function that can raize an exception
	def foobar(self):
		raise NotImplementedError

# preCode get's called on the empty file and will be the very start of the generated G-Code file,
# nothing comes before these lines (except additional comments)
	def preCode(self):
		self.writeToFile('G90', 'Absolute distance mode')
		self.writeToFile('G17', 'xy plane selection')
		self.writeToFile('G40', 'Cancel diameter comp.')
		self.writeToFile('G49', 'Cancel length comp.')
		self.writeToFile('M8', 'Coolant flood on')

# postCode get's called when we are done generating all gCode, no code get's added after this code
# exceot may be some comments
	def postCode(self):
		self.writeToFile('M9', 'Coolant off')
		self.writeToFile('M5', 'Spindle off')
		self.writeToFile('M2', 'Program end')

# Set the feedrate for linear motions
	def setFeedRate(self, units):
		if units<0.1 or units==None:
			raise ValueError			
		self.writeToFile('F%1.6f' % (units), 'Feed rate')

# Set the RPM for the spindle
	def setSpindleRPM(self, rpm):
		if rpm<1 or rpm==None:
			raise ValueError
		self.writeToFile('S%1.6f' % (feedRate), 'Spindle')

# Turn teh spindle on in a specific direction
	def turnSpindleOn(self, direction):
		if direction=='CW':
			self.writeToFile('M03', 'Spindle on CW')
		elif direction=='CCW':
			self.writeToFile('M04', 'Spindle on CCW')
		elif direction=='OFF':
			self.writeToFile('M05', 'Spindle on OFF')
		else:
			raise ValueError

# Set the measuring units to MM or INCHES
	def setUnit(self, unit):
		if unit=='MM':
			self.writeToFile('G21', 'Units in mm')
		elif unit=='INCH':
			self.writeToFile('G20', 'Units in Inch')
		else:
			raise ValueError
			
# Turn off compersation
	def setCutterCompensation(self, mode=None, D=None, L=None):
		_D=_L=''
		if (D!=None and D<0):
			raise ValueError
		if (L!=None and (L<0 or L>9)):
			raise ValueError

		if mode=='LEFT':					
			if D!=None: _D=' D%d' % int(D)
			self.writeToFile('G41%s' % _D, 'Cutter comp. left')
		elif mode=='RIGHT':
			if D!=None: _D=' D%d' % int(D)
			self.writeToFile('G42%s' % _D, 'Cutter comp. right')
		elif mode=='OFF':
			self.writeToFile('G40', 'Cutter comp. off')
		elif mode=='DLEFT':
			if D!=None: _D=' D%1.6f' % D
			if L!=None: _L=' L%d' % int(L)
			self.writeToFile('G41.1%s%s' % (_D,_L), 'Dynamic Cutter comp. left')
		elif mode=='DRIGHT':
			if D!=None: _D=' D%1.6f' % D
			if L!=None: _L=' L%d' % int(L)
			self.writeToFile('G42.1%s%s' % (_D,_L), 'Dynamic Cutter comp. right')
		else:
			raise ValueError

# Path control mode
	def setPathControlMode(self, mode, P, Q):
		if mode=='EXACTPATH':					
			self.writeToFile('G61', 'Exact Path mode')
		elif mode=='EXACTSTOP':
			self.writeToFile('G61.1', 'Exact Stop mode')
		elif mode=='BESTSPEED':
			self.writeToFile('G64', 'Best possible speed')
		elif mode=='MOTIONBLEND':
			_P=''
			_Q=''
			if P!=None: _P=' P%1.6f' % P
			if Q!=None: _Q=' Q%1.6f' % Q
			self.writeToFile('G64%s%s' % (_P,_Q), 'Motion blending tolerance')
		else:
			raise ValueError
		

# Linear move to position
	def linearMove(self,x=None,y=None,z=None):
		if x==None and y==None and z==None:
		    raise ValueError
		line='G1'			
		if x!=None: 
		    line=line+' X%1.6f' % (x)
		if y!=None: 
		    line=line+' Y%1.6f' % (y)
		if z!=None:
		    line=line+' Z%1.6f' % (z)
		self.writeToFile(line, 'Linear Line')

# Rapid move to a position		
	def rapidMove(self,x=None,y=None,z=None):
		if x==None and y==None and z==None:
		    raise ValueError
		line='G0'
		if x!=None: 
		    line=line+' X%1.6f' % (x)
		if y!=None: 
		    line=line+' Y%1.6f' % (y)
		if z!=None:
		    line=line+' Z%1.6f' % (z)
		self.writeToFile(line, 'Rapid Line')
		
# center Arc 
# TODO solve when other planes are selected then XY (IJ), XZ(IK), YZ(JK)
	def arc(self, direction, X, Y, Z, I, J, F):
		if (X==None and Y==none):
			raise ValueError			
		if (I==None and J==none):
			raise ValueError			
	
		if direction=='CW':
			line='G2'
		if direction=='CCW':
			line='G3'
		if I!=None: _I=' I%1.6f' % I
		if J!=None: _J=' J%1.6f' % J
		if F!=None: _F=' F%1.6f' % G
		self.writeToFile(line+'%s%s%s' % (_I,_J,_F), 'Arc')

