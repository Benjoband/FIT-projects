#IPP 2. Projekt 2022/23
#Autor: Alexej Beňuš xbenus01

import sys

class Arg:
    def __init__(self, argType, value, number):
        self.__type = argType
        self.__value = value
        self.__number = number
    
    def getType(self):
        return self.__type
    
    def getValue(self):
        return self.__value
    
    def getNumber(self):
        return self.__number
    
    def setType(self, argType):
        self.__type = argType

    def setValue(self, value):
        self.__value = value

    def setNumber(self, number):
        self.__number = number

class Label:
    def __init__(self, name, number):
        self.__name = name
        self.__number = number
    
    def getName(self):
        return self.__name
    
    def getNumber(self):
        return self.__number
    
    def setName(self, name):
        self.__name = name

    def setNumber(self, number):
        self.__number = number

    def printLabel(self):
        print(self.__name, self.__number)

class LabelList:
    def __init__(self):
        self.__labels: Label= []
    
    def getLabels(self):
        return self.__labels
    
    def setLabels(self, labels):
        self.__labels = labels
    
    def appendLabels(self, label):
        self.__labels.append(label)

    def clearLabels(self):
        self.__labels.clear()

    def printLabels(self):
        for label in self.__labels:
            label.printLabel()
    
    def findLabel(self, name):
        for label in self.__labels:
            if label.getName() == name:
                return label.getNumber()
        return -1

class Var:
    def __init__(self):
        self.__name = ""
        self.__type = ""
        self.__value = ""
    
    def __init__(self, name, value, type):
        self.__name = name
        self.__type = type
        self.__value = value
    
    def getName(self):
        return self.__name
    
    def getType(self):
        return self.__type
    
    def getValue(self):
        return self.__value
    
    def setName(self, name):
        self.__name = name

    def setType(self, type):
        self.__type = type

    def setValue(self, value):
        self.__value = value

    def printVar(self):
        print(self.__name, self.__value, self.__type)
    

class Frame:
    def __init__(self):
        self.__variables: Var = []
        self.__defined = False

    def getVariables(self):
        return self.__variables
    
    def getDefined(self):
        return self.__defined
    
    def setDefined(self, defined):
        self.__defined = defined
    
    def setVariables(self, variables):
        if self.__defined == True:
            self.__variables = variables
        else:
            exit(55)
    
    def appendVariables(self, variable, value, type):
        if self.__defined == True:
            self.__variables.append(Var(variable, value, type))
        else:
            exit(55)

    def clearVariables(self):
        self.__variables.clear()
    
    def printFrame(self):
        for variable in self.__variables:
            variable.printVar()

class FrameList:
    def __init__(self):
        self.__frames: Frame = []
    
    def getFrames(self):
        return self.__frames
    
    def setFrames(self, frames):
        self.__frames = frames
    
    def appendFrames(self, frame):
        self.__frames.insert(0, frame)

    def popFrames(self):
        self.__frames.pop()

    def printFrames(self):
        for frame in self.__frames:
            frame.printFrame()

class StackData:
    def __init__(self):
        self.__value = ""
        self.__type = ""
    
    def __init__(self, value, type):
        self.__value = value
        self.__type = type
    
    def getValue(self):
        return self.__value
    
    def getType(self):
        return self.__type
    
    def setValue(self, value):
        self.__value = value

    def setType(self, type):
        self.__type = type

class Instruction:
    GF: Frame = Frame()
    TF: Frame = Frame()
    frameStack: FrameList = FrameList()

    stack: StackData = []

    def __init__(self, name, number):
        self.__name = name
        self.__number = number
        self.__args: Arg = []
        Instruction.GF.setDefined(True)

    def getName(self):
        return self.__name
    
    def getNumber(self):
        return self.__number
    
    def getArgs(self):
        return self.__args
     
    def setName(self, name):
        self.__name = name

    def setNumber(self, number):
        self.__number = number
    
    def appendArgs(self, argType, value, number):
        self.__args.append(Arg(argType, value, number))
    
    def pushToStack(self, value, type):
        Instruction.stack.append(StackData(value, type))
    
    def popFromStack(self):
        if Instruction.stack == []:
            exit(56)
        return Instruction.stack.pop()

    def setVariable(self, var, value, type):
        var = var.split("@", 1)
        if var[0] == "GF":
            for i in Instruction.GF.getVariables():
                if i.getName() == var[1]:
                    i.setValue(value)
                    i.setType(type)
                    return
            Instruction.GF.appendVariables(var[1], value, type)
        elif var[0] == "TF":
            if Instruction.TF.getDefined() == False:
                exit(55)
            for i in Instruction.TF.getVariables():
                if i.getName() == var[1]:
                    i.setValue(value)
                    i.setType(type)
                    return
            Instruction.TF.appendVariables(var[1], value, type)
        elif var[0] == "LF":
            if Instruction.frameStack.getFrames() == []:
                exit(55)
            for i in Instruction.frameStack.getFrames()[0].getVariables():
                if i.getName() == var[1]:
                    i.setValue(value)
                    i.setType(type)
                    return
            Instruction.frameStack.getFrames()[0].appendVariables(var[1], value, type)

    def findVariable(self, var):
        var = var.split("@", 1)
        if var[0] == "GF":
            for i in Instruction.GF.getVariables():
                if i.getName() == var[1]:
                    return i
            exit(54)
        elif var[0] == "TF":
            if Instruction.TF.getDefined() == False:
                exit(55)
            for i in Instruction.TF.getVariables():
                if i.getName() == var[1]:
                    return i
            exit(54)
        elif var[0] == "LF":
            if Instruction.frameStack.getFrames() == []:
                exit(55)
            for i in Instruction.frameStack.getFrames()[0].getVariables():
                if i.getName() == var[1]:
                    return i
            exit(54)
    
    def checkVariable(self, var):
        var = var.split("@", 1)
        if var[0] == "GF":
            for i in Instruction.GF.getVariables():
                if i.getName() == var[1]:
                    return True
            return False
        elif var[0] == "TF":
            if Instruction.TF.getDefined() == False:
                return False
            for i in Instruction.TF.getVariables():
                if i.getName() == var[1]:
                    return True
            return False
        elif var[0] == "LF":
            if Instruction.frameStack.getFrames() == []:
                exit(55)
            for i in Instruction.frameStack.getFrames()[0].getVariables():
                if i.getName() == var[1]:
                    return True
            return False
    
    def findVariableValue(self, var):
        var = var.split("@", 1)
        if var[0] == "GF":
            for i in Instruction.GF.getVariables():
                if i.getName() == var[1]:
                    return i.getValue()
        elif var[0] == "TF":
            if Instruction.TF.getDefined() == False:
                exit(55)
            for i in Instruction.TF.getVariables():
                if i.getName() == var[1]:
                    return i.getValue()
        elif var[0] == "LF":
            if Instruction.frameStack.getFrames() == []:
                exit(55)
            for i in Instruction.frameStack.getFrames()[0].getVariables():
                if i.getName() == var[1]:
                    return i.getValue()

    def findVariableType(self, var):
        var = var.split("@", 1)
        if var[0] == "GF":
            for i in Instruction.GF.getVariables():
                if i.getName() == var[1]:
                    return i.getType()
        elif var[0] == "TF":
            if Instruction.TF.getDefined() == False:
                exit(55)
            for i in Instruction.TF.getVariables():
                if i.getName() == var[1]:
                    return i.getType()
        elif var[0] == "LF":
            if Instruction.frameStack.getFrames() == []:
                exit(55)
            for i in Instruction.frameStack.getFrames()[0].getVariables():
                if i.getName() == var[1]:
                    return i.getType()

    def printVars(self):
        print("\nGF: ")
        for i in Instruction.GF.getVariables():
            print(i.getName(), i.getValue(), i.getType(), "|")
        print("\nLF: ")
        for i in Instruction.frameStack.getFrames():
            for j in i.getVariables():
                print(j.getName(), j.getValue(), j.getType(), "|")
        print("\nTF: ")
        for i in Instruction.TF.getVariables():
            print(i.getName(), i.getValue(), i.getType(), "|")
    
    def isInt(self, var):
        try:
            int(var)
            return True
        except ValueError:
            return False
        
    def returnBool(self, var):
        if var == "true":
            return True
        elif var == "false":
            return False
        else:
            exit(53)

    def returnFrame(self, var):
        if var == "GF":
            return Instruction.GF
        elif var == "TF":
            return Instruction.TF
        elif var == "LF":
            return Instruction.frameStack.getFrames()[0]

    def execute(self, inputFile, labels, instructionCount):
        match self.getName():
            case "MOVE": 
                return self.move()
            case "CREATEFRAME":
                return self.createFrame()
            case "PUSHFRAME":
                return self.pushFrame()
            case "POPFRAME":
                return self.popFrame()
            case "DEFVAR":
                return self.defVar()
            case "CALL": 
                return self.call(instructionCount, labels)
            case "RETURN":
                return self.return_()
            case "PUSHS":
                return self.pushs()
            case "POPS":
                return self.pops()
            case "ADD":
                return self.add()
            case "SUB":
                return self.sub()
            case "MUL":
                return self.mul()
            case "IDIV":
                return self.idiv()
            case "LT":
                return self.lt()
            case "GT":
                return self.gt()
            case "EQ":
                return self.eq()
            case "AND":
                return self.and_()
            case "OR":
                return self.or_()
            case "NOT":
                return self.not_()
            case "INT2CHAR":
                return self.int2char()
            case "STRI2INT":
                return self.stri2int()
            case "READ":
                return self.read(inputFile)
            case "WRITE":
                return self.write()
            case "CONCAT":
                return self.concat()
            case "STRLEN":
                return self.strlen()
            case "GETCHAR":
                return self.getchar()
            case "SETCHAR":
                return self.setchar()
            case "TYPE":
                return self.type()
            case "LABEL":
                return self.label()
            case "JUMP":
                return self.jump(labels)
            case "JUMPIFEQ":
                return self.jumpifeq(labels)
            case "JUMPIFNEQ":
                return self.jumpifneq(labels)
            case "EXIT":
                return self.exit()
            case "DPRINT": 
                return self.dprint()
            case "BREAK":
                return self.break_()
            case _:
                exit(32)

    def move(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            var = self.getArgs()[1].getValue().split("@", 1)
            if(var[0] == "GF"):
                for i in Instruction.GF.getVariables():
                    if i.getName() == var[1]:
                        value = i.getValue()
                        type = i.getType()
            elif(var[0] == "TF"):
                for i in Instruction.TF.getVariables():
                    if i.getName() == var[1]:
                        value = i.getValue()
                        type = i.getType()
            elif(var[0] == "LF"):
                for i in Instruction.frameStack.getFrames()[0].getVariables():
                    if i.getName() == var[1]:
                        value = i.getValue()
                        type = i.getType()
            self.setVariable(self.getArgs()[0].getValue(), value, type)
        else:
            self.setVariable(self.getArgs()[0].getValue(), self.getArgs()[1].getValue(), self.getArgs()[1].getType())

    def createFrame(self):
        Instruction.TF.clearVariables()
        Instruction.TF.setDefined(True)
    
    def pushFrame(self):
        if(Instruction.TF.getDefined() == False):
            exit(55)
        Instruction.frameStack.appendFrames(Instruction.TF)
        Instruction.TF = Frame()
    
    def popFrame(self):
        if Instruction.frameStack.getFrames() == []:
            exit(55)
        else:
            Instruction.TF = Instruction.frameStack.getFrames().pop()
    

    def defVar(self):
        if(self.checkVariable(self.getArgs()[0].getValue()) == True):
            exit(52)
        var = self.getArgs()[0].getValue().split("@")
        if var[0] == "GF":
            if var[1] in Instruction.GF.getVariables():
                exit(52)
            Instruction.GF.appendVariables(var[1], None, None)
        elif var[0] == "TF":
            if Instruction.TF.getDefined() == False:
                exit(55)
            if var[1] in Instruction.TF.getVariables():
                exit(52)
            Instruction.TF.appendVariables(var[1], None, None)
            
        elif var[0] == "LF":
            if Instruction.frameStack.getFrames() == []:
                exit(55)
            if var[1] in Instruction.frameStack.getFrames()[0].getVariables():
                exit(52)
            Instruction.frameStack.getFrames()[0].appendVariables(var[1], None, None)

    
    def call(self, number, labels):
        self.pushToStack(number + 1, "int")
        if labels.findLabel(self.getArgs()[0].getValue()) == -1:
            exit(52)
        else:
            return labels.findLabel(self.getArgs()[0].getValue())
        
    
    def return_(self):
        tmp = self.popFromStack()
        return tmp.getValue()
    
    def pushs(self):
        if(self.getArgs()[0].getType() == "var"):
            self.findVariable(self.getArgs()[0].getValue())
            self.pushToStack(self.findVariableValue(self.getArgs()[0].getValue()), self.findVariableType(self.getArgs()[0].getValue()))
        else:
            self.pushToStack(self.getArgs()[0].getValue(), self.getArgs()[0].getType())

    def pops(self):
        self.findVariable(self.getArgs()[0].getValue())
        tmp = self.popFromStack()
        self.setVariable(self.getArgs()[0].getValue(), tmp.getValue(), tmp.getType())
    
    def add(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.findVariableValue(self.getArgs()[1].getValue())) + int(self.findVariableValue(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.findVariableValue(self.getArgs()[1].getValue())) + int(self.getArgs()[2].getValue()), "int")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.getArgs()[1].getValue()) + int(self.findVariableValue(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.getArgs()[1].getValue()) + int(self.getArgs()[2].getValue()), "int")
                else:
                    exit(53)

    def sub(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.findVariableValue(self.getArgs()[1].getValue())) - int(self.findVariableValue(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.findVariableValue(self.getArgs()[1].getValue())) - int(self.getArgs()[2].getValue()), "int")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.getArgs()[1].getValue()) - int(self.findVariableValue(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.getArgs()[1].getValue()) - int(self.getArgs()[2].getValue()), "int")
                else:
                    exit(53)
    
    def mul(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.findVariableValue(self.getArgs()[1].getValue())) * int(self.findVariableValue(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.findVariableValue(self.getArgs()[1].getValue())) * int(self.getArgs()[2].getValue()), "int")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.getArgs()[1].getValue()) * int(self.findVariableValue(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int"):
                    self.setVariable(self.getArgs()[0].getValue(), int(self.getArgs()[1].getValue()) * int(self.getArgs()[2].getValue()), "int")
                else:
                    exit(53)
    
    def idiv(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    if(int(self.findVariableValue(self.getArgs()[2].getValue())) == 0):
                        exit(57)
                    self.setVariable(self.getArgs()[0].getValue(), int(int(self.findVariableValue(self.getArgs()[1].getValue())) / int(self.findVariableValue(self.getArgs()[2].getValue()))), "int")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.getArgs()[2].getValue()) == 0):
                        exit(57)
                    self.setVariable(self.getArgs()[0].getValue(), int(int(self.findVariableValue(self.getArgs()[1].getValue())) / int(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    if(int(self.findVariableValue(self.getArgs()[2].getValue())) == 0):
                        exit(57)
                    self.setVariable(self.getArgs()[0].getValue(), int(int(self.getArgs()[1].getValue()) / int(self.findVariableValue(self.getArgs()[2].getValue()))), "int")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.getArgs()[2].getValue()) == 0):
                        exit(57)
                    self.setVariable(self.getArgs()[0].getValue(), int(int(self.getArgs()[1].getValue()) / int(self.getArgs()[2].getValue())), "int")
                else:
                    exit(53)
    
    def lt(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int" ):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) < int(self.findVariableValue(self.getArgs()[2].getValue()))):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) < self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.findVariableValue(self.getArgs()[1].getValue())
                    b = self.findVariableValue(self.getArgs()[2].getValue())
                    if(self.returnBool(a) < self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) < int(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.getArgs()[2].getType() == "string"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) < self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.findVariableValue(self.getArgs()[1].getValue())
                    b = self.getArgs()[2].getValue()
                    if(self.returnBool(a) < self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    if(int(self.getArgs()[1].getValue()) < int(self.findVariableValue(self.getArgs()[2].getValue()))):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    if(self.getArgs()[1].getValue() < self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.getArgs()[1].getValue()
                    b = self.findVariableValue(self.getArgs()[2].getValue())
                    if(self.returnBool(a) < self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.getArgs()[1].getValue()) < int(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "string" and self.getArgs()[2].getType() == "string"):
                    if(self.getArgs()[1].getValue() < self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.getArgs()[1].getValue()
                    b = self.getArgs()[2].getValue()
                    if(self.returnBool(a) < self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
    
    def gt(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int" ):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) > int(self.findVariableValue(self.getArgs()[2].getValue()))):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) > self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.findVariableValue(self.getArgs()[1].getValue())
                    b = self.findVariableValue(self.getArgs()[2].getValue())
                    if(self.returnBool(a) > self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) > int(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.getArgs()[2].getType() == "string"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) > self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.findVariableValue(self.getArgs()[1].getValue())
                    b = self.getArgs()[2].getValue()
                    if(self.returnBool(a) > self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    if(int(self.getArgs()[1].getValue()) > int(self.findVariableValue(self.getArgs()[2].getValue()))):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    if(self.getArgs()[1].getValue() > self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.getArgs()[1].getValue()
                    b = self.findVariableValue(self.getArgs()[2].getValue())
                    if(self.returnBool(a) > self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.getArgs()[1].getValue()) > int(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "string" and self.getArgs()[2].getType() == "string"):
                    if(self.getArgs()[1].getValue() > self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.getArgs()[1].getValue()
                    b = self.getArgs()[2].getValue()
                    if(self.returnBool(a) > self.returnBool(b)):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
    
    def eq(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) == int(self.findVariableValue(self.getArgs()[2].getValue()))):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif((self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string") or self.findVariableType(self.getArgs()[1].getValue()) == "nil" or self.findVariableType(self.getArgs()[2].getValue()) == "nil"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) == self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) == self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "int"):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) == int(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif((self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.getArgs()[2].getType() == "string") or self.findVariableType(self.getArgs()[1].getValue()) == "nil" or self.getArgs()[2].getType() == "nil"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) == self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.getArgs()[2].getType() == "bool"):
                    if(self.findVariableValue(self.getArgs()[1].getValue()) == self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    if(int(self.getArgs()[1].getValue()) == int(self.findVariableValue(self.getArgs()[2].getValue()))):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                if((self.getArgs()[1].getType() == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string") or self.getArgs()[1].getType() == "nil" or self.findVariableType(self.getArgs()[2].getValue()) == "nil"):
                    if(self.getArgs()[1].getValue() == self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif(self.getArgs()[1].getType() == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    if(self.getArgs()[1].getValue() == self.findVariableValue(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if((self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "int")):
                    if(int(self.getArgs()[1].getValue()) == int(self.getArgs()[2].getValue())):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif((self.getArgs()[1].getType() == "string" and self.getArgs()[2].getType() == "string") or self.getArgs()[1].getType() == "nil" or self.getArgs()[2].getType() == "nil"):
                    if(self.getArgs()[1].getValue() == self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                elif((self.getArgs()[1].getType() == "bool" and self.getArgs()[2].getType() == "bool")):
                    if(self.getArgs()[1].getValue() == self.getArgs()[2].getValue()):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
    
    def and_(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.returnBool(self.findVariableValue(self.getArgs()[1].getValue()))
                    b = self.returnBool(self.findVariableValue(self.getArgs()[2].getValue()))
                    if(a and b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.returnBool(self.findVariableValue(self.getArgs()[1].getValue()))
                    b = self.returnBool(self.getArgs()[2].getValue())
                    if(a and b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.returnBool(self.getArgs()[1].getValue())
                    b = self.returnBool(self.findVariableValue(self.getArgs()[2].getValue()))
                    if(a and b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.returnBool(self.getArgs()[1].getValue())
                    b = self.returnBool(self.getArgs()[2].getValue())
                    if(a and b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
    
    def or_(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.returnBool(self.findVariableValue(self.getArgs()[1].getValue()))
                    b = self.returnBool(self.findVariableValue(self.getArgs()[2].getValue()))
                    if(a or b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.returnBool(self.findVariableValue(self.getArgs()[1].getValue()))
                    b = self.returnBool(self.getArgs()[2].getValue())
                    if(a or b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "bool" and self.findVariableType(self.getArgs()[2].getValue()) == "bool"):
                    a = self.returnBool(self.getArgs()[1].getValue())
                    b = self.returnBool(self.findVariableValue(self.getArgs()[2].getValue()))
                    if(a or b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "bool" and self.getArgs()[2].getType() == "bool"):
                    a = self.returnBool(self.getArgs()[1].getValue())
                    b = self.returnBool(self.getArgs()[2].getValue())
                    if(a or b):
                        self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
                else:
                    exit(53)
    
    def not_(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.findVariableType(self.getArgs()[1].getValue()) == "bool"):
                a = self.returnBool(self.findVariableValue(self.getArgs()[1].getValue()))
                if(not a):
                    self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                else:
                    self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
            else:
                exit(53)
        else:
            if(self.getArgs()[1].getType() == "bool"):
                a = self.returnBool(self.getArgs()[1].getValue())
                if(not a):
                    self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
                else:
                    self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
            else:
                exit(53)
    
    def int2char(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.findVariableType(self.getArgs()[1].getValue()) == "int"):
                try:
                    self.setVariable(self.getArgs()[0].getValue(), chr(int(self.findVariableValue(self.getArgs()[1].getValue()))), "string")
                except:
                    exit(58)
            else:
                exit(53)
        else:
            if(self.getArgs()[1].getType() == "int"):
                try:
                    self.setVariable(self.getArgs()[0].getValue(), chr(int(self.getArgs()[1].getValue())), "string")
                except:
                    exit(58)
            else:
                exit(53)
    
    def stri2int(self): # TODO
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), ord(self.findVariableValue(self.getArgs()[1].getValue())[int(self.findVariableValue(self.getArgs()[2].getValue()))]), "int")
                    except:
                        exit(58)
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.getArgs()[2].getType() == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), ord(self.findVariableValue(self.getArgs()[1].getValue())[int(self.getArgs()[2].getValue())]), "int")
                    except:
                        exit(58)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), ord(self.getArgs()[1].getValue()[int(self.findVariableValue(self.getArgs()[2].getValue()))]), "int")
                    except:
                        exit(58)
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "string" and self.getArgs()[2].getType() == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), ord(self.getArgs()[1].getValue()[int(self.getArgs()[2].getValue())]), "int")
                    except:
                        exit(58)
                else:
                    exit(53)

    def read(self, inputFile):
        self.findVariable(self.getArgs()[0].getValue())
        if(inputFile == ""):
            var = input()
        else:
            file1 = open(str(inputFile), 'r')
            var = file1.readline()
        if(var == ""):
            self.setVariable(self.getArgs()[0].getValue(), "", "nil")
        elif(self.getArgs()[1].getType() != "type"):
            exit(52)
        elif(self.getArgs()[1].getValue() == "int"):
            self.setVariable(self.getArgs()[0].getValue(), int(var), "int")
        elif(self.getArgs()[1].getValue() == "string"):
            self.setVariable(self.getArgs()[0].getValue(), var, "string")
        elif(self.getArgs()[1].getValue() == "bool"):
            var.capitalize()
            if(var == "TRUE\n"):
                self.setVariable(self.getArgs()[0].getValue(), "true", "bool")
            elif(var == "FALSE\n"):
                self.setVariable(self.getArgs()[0].getValue(), "false", "bool")
            else:
                exit(53)
        else:
            exit(1) # TODO

    def write(self):
        if(self.getArgs()[0].getType() == "var"):
            self.findVariable(self.getArgs()[0].getValue())
            if(self.findVariableType(self.getArgs()[0].getValue()) == "int"):
                print(self.findVariableValue(self.getArgs()[0].getValue()), end="")
            elif(self.findVariableType(self.getArgs()[0].getValue()) == "string"):
                print(self.findVariableValue(self.getArgs()[0].getValue()), end="")
            elif(self.findVariableType(self.getArgs()[0].getValue()) == "bool"):
                if(self.returnBool(self.findVariableValue(self.getArgs()[0].getValue()))):
                    print("true", end="")
                else:
                    print("false", end="")
            else:
                print("")
        else:
            if(self.getArgs()[0].getType() == "int"):
                print(self.getArgs()[0].getValue(), end="")
            elif(self.getArgs()[0].getType() == "string"):
                print(self.getArgs()[0].getValue(), end="")
            elif(self.getArgs()[0].getType() == "bool"):
                if(self.returnBool(self.getArgs()[0].getValue())):
                    print("true", end="")
                else:
                    print("false", end="")
            else:
                print("")

    def concat(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[1].getValue()) + self.findVariableValue(self.getArgs()[2].getValue()), "string")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.getArgs()[2].getType() == "string"):
                    self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[1].getValue()) + self.getArgs()[2].getValue(), "string")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    self.setVariable(self.getArgs()[0].getValue(), self.getArgs()[1].getValue() + self.findVariableValue(self.getArgs()[2].getValue()), "string")
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "string" and self.getArgs()[2].getType() == "string"):
                    self.setVariable(self.getArgs()[0].getValue(), self.getArgs()[1].getValue() + self.getArgs()[2].getValue(), "string")
                else:
                    exit(53)
    
    def strlen(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.findVariableType(self.getArgs()[1].getValue()) == "string"):
                self.setVariable(self.getArgs()[0].getValue(), len(self.findVariableValue(self.getArgs()[1].getValue())), "int")
            else:
                exit(53)
        else:
            if(self.getArgs()[1].getType() == "string"):
                self.setVariable(self.getArgs()[0].getValue(), len(self.getArgs()[1].getValue()), "int")
            else:
                exit(53)
    
    def getchar(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[1].getValue())[int(self.findVariableValue(self.getArgs()[2].getValue()))], "string")
                    except:
                        exit(58)
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "string" and self.getArgs()[2].getType() == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[1].getValue())[int(self.getArgs()[2].getValue())], "string")
                    except:
                        exit(58)
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "string" and self.findVariableType(self.getArgs()[2].getValue()) == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), self.getArgs()[1].getValue()[int(self.findVariableValue(self.getArgs()[2].getValue()))], "string")
                    except:
                        exit(58)
                else:
                    exit(53)
            else:
                if(self.getArgs()[1].getType() == "string" and self.getArgs()[2].getType() == "int"):
                    try:
                        self.setVariable(self.getArgs()[0].getValue(), self.getArgs()[1].getValue()[int(self.getArgs()[2].getValue())], "string")
                    except:
                        exit(58)
                else:
                    exit(53)

    def setchar(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[0].getValue()) == "string" and self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) >= len(self.findVariableValue(self.getArgs()[0].getValue())) or (int(self.findVariableValue(self.getArgs()[1].getValue())) >= len(self.findVariableValue(self.getArgs()[0].getValue())))):
                        exit(58)
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[0].getValue())[:int(self.findVariableValue(self.getArgs()[1].getValue()))] + self.findVariableValue(self.getArgs()[2].getValue()) + self.findVariableValue(self.getArgs()[0].getValue())[int(self.findVariableValue(self.getArgs()[1].getValue()))+1:], "string")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[0].getValue()) == "string" and self.findVariableType(self.getArgs()[1].getValue()) == "int" and self.getArgs()[2].getType() == "string"):
                    if(int(self.findVariableValue(self.getArgs()[1].getValue())) >= len(self.findVariableValue(self.getArgs()[0].getValue())) or (int(self.findVariableValue(self.getArgs()[1].getValue())) >= len(self.findVariableValue(self.getArgs()[0].getValue())))):
                        exit(58)
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[0].getValue())[:int(self.findVariableValue(self.getArgs()[1].getValue()))] + self.getArgs()[2].getValue() + self.findVariableValue(self.getArgs()[0].getValue())[int(self.findVariableValue(self.getArgs()[1].getValue()))+1:], "string")
                else:
                    exit(53)
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[0].getValue()) == "string" and self.getArgs()[1].getType() == "int" and self.findVariableType(self.getArgs()[2].getValue()) == "string"):
                    if(int(self.getArgs()[1].getValue()) >= len(self.findVariableValue(self.getArgs()[0].getValue())) or (int(self.getArgs()[1].getValue()) >= len(self.findVariableValue(self.getArgs()[0].getValue())))):
                        exit(58)
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[0].getValue())[:int(self.getArgs()[1].getValue())] + self.findVariableValue(self.getArgs()[2].getValue()) + self.findVariableValue(self.getArgs()[0].getValue())[int(self.getArgs()[1].getValue())+1:], "string")
                else:
                    exit(53)
            else:
                if(self.findVariableType(self.getArgs()[0].getValue()) == "string" and self.getArgs()[1].getType() == "int" and self.getArgs()[2].getType() == "string"):
                    if(int(self.getArgs()[1].getValue()) >= len(self.findVariableValue(self.getArgs()[0].getValue())) or (int(self.getArgs()[1].getValue()) >= len(self.findVariableValue(self.getArgs()[0].getValue())))):
                        exit(58)
                    else:
                        self.setVariable(self.getArgs()[0].getValue(), self.findVariableValue(self.getArgs()[0].getValue())[:int(self.getArgs()[1].getValue())] + self.getArgs()[2].getValue() + self.findVariableValue(self.getArgs()[0].getValue())[int(self.getArgs()[1].getValue())+1:], "string")
                else:
                    exit(53)
    
    def type(self):
        self.findVariable(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.findVariableType(self.getArgs()[1].getValue()) == "None"):
                self.setVariable(self.getArgs()[0].getValue(), "", "string")
                return
            self.setVariable(self.getArgs()[0].getValue(), self.findVariableType(self.getArgs()[1].getValue()), "string")
        else:
            self.setVariable(self.getArgs()[0].getValue(), self.getArgs()[1].getType(), "string")
    
    def label(self):
        pass
    
    def jump(self, labels):
        return labels.findLabel(self.getArgs()[0].getValue())
    
    def jumpifeq(self, labels):
        ret = labels.findLabel(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[1].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "nil" or self.findVariableType(self.getArgs()[2].getValue()) == "nil"):
                    return ret
                if(self.findVariableType(self.getArgs()[1].getValue()) != self.findVariableType(self.getArgs()[2].getValue())):
                    exit(53)
                if(self.findVariableValue(self.getArgs()[1].getValue()) == self.findVariableValue(self.getArgs()[2].getValue())):
                    return ret
                else:
                    return None
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "nil" or self.getArgs()[2].getType() == "nil"):
                    return ret
                if(self.findVariableType(self.getArgs()[1].getValue()) != self.getArgs()[2].getType()):
                    exit(53)
                if(self.findVariableValue(self.getArgs()[1].getValue()) == self.getArgs()[2].getValue()):
                    return ret
                else:
                    return None
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "nil" or self.findVariableType(self.getArgs()[2].getValue()) == "nil"):
                    return ret
                if(self.getArgs()[1].getType() != self.findVariableType(self.getArgs()[2].getValue())):
                    exit(53)
                if(self.getArgs()[1].getValue() == self.findVariableValue(self.getArgs()[2].getValue())):
                    return ret
                else:
                    return None
            else:
                if(self.getArgs()[1].getType() == "nil" or self.getArgs()[2].getType() == "nil"):
                    return ret
                if(self.getArgs()[1].getType() != self.getArgs()[2].getType()):
                    exit(53)
                if(self.getArgs()[1].getValue() == self.getArgs()[2].getValue()):
                    return ret
                else:
                    return None

    def jumpifneq(self, labels):
        ret = labels.findLabel(self.getArgs()[0].getValue())
        if(self.getArgs()[1].getType() == "var"):
            self.findVariable(self.getArgs()[1].getValue())
            if(self.getArgs()[1].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.findVariableType(self.getArgs()[1].getValue()) == "nil" or self.findVariableType(self.getArgs()[2].getValue()) == "nil"):
                    return ret
                if(self.findVariableType(self.getArgs()[1].getValue()) != self.findVariableType(self.getArgs()[2].getValue())):
                    exit(53)
                if(self.findVariableValue(self.getArgs()[1].getValue()) != self.findVariableValue(self.getArgs()[2].getValue())):
                    return ret
            else:
                if(self.findVariableType(self.getArgs()[1].getValue()) == "nil" or self.getArgs()[2].getType() == "nil"):
                    return ret
                if(self.findVariableType(self.getArgs()[1].getValue()) != self.getArgs()[2].getType()):
                    exit(53)
                if(self.findVariableValue(self.getArgs()[1].getValue()) != self.getArgs()[2].getValue()):
                    return ret
                else:
                    return None
        else:
            if(self.getArgs()[2].getType() == "var"):
                self.findVariable(self.getArgs()[2].getValue())
                if(self.getArgs()[1].getType() == "nil" or self.findVariableType(self.getArgs()[2].getValue()) == "nil"):
                    return ret
                if(self.getArgs()[1].getType() != self.findVariableType(self.getArgs()[2].getValue())):
                    exit(53)
                else:
                    return None
            else:
                if(self.getArgs()[1].getType() == "nil" or self.getArgs()[2].getType() == "nil"):
                    return ret
                if(self.getArgs()[1].getType() != self.getArgs()[2].getType()):
                    exit(53)
                if(self.getArgs()[1].getValue() != self.getArgs()[2].getValue()):
                    return ret
                else:
                    return None
    
    def exit(self):
        if(self.getArgs()[0].getType() == "var"):
            self.findVariable(self.getArgs()[0].getValue())
            if(self.findVariableType(self.getArgs()[0].getValue()) == "int"):
                if(int(self.findVariableValue(self.getArgs()[0].getValue())) < 0 or int(self.findVariableValue(self.getArgs()[0].getValue())) > 49):
                    exit(57)
                exit(int(self.findVariableValue(self.getArgs()[0].getValue())))
            else:
                exit(53)
        else:
            if(self.getArgs()[0].getType() != "int"):
                exit(53)
            if(int(self.getArgs()[0].getValue()) < 0 or int(self.getArgs()[0].getValue()) > 49):
                exit(57)
            exit(int(self.getArgs()[0].getValue()))

    def dprint(self):
        if(self.getArgs()[0].getType() == "var"):
            self.findVariable(self.getArgs()[0].getValue())
            sys.stderr.write(self.findVariableValue(self.getArgs()[0].getValue()))
        else:
            sys.stderr.write(self.getArgs()[0].getValue())
    
    def break_(self):
        sys.stderr.write("GF:")
        for i in Instruction.GF:
            sys.stderr.write(i + "(" + Instruction.GF[i][0] + ")" + ":" + Instruction.GF[i][1] + ", ")
        sys.stderr.write("LF:")
        for i in self.LF:
            sys.stderr.write(i + "(" + self.LF[i][0] + ")" + ":" + self.LF[i][1] + ", ")
        sys.stderr.write("TF:")
        for i in Instruction.TF:
            sys.stderr.write(i + "(" + Instruction.TF[i][0] + ")" + ":" + Instruction.TF[i][1] + ", ")
