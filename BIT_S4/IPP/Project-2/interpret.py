#IPP 2. Projekt 2022/23
#Autor: Alexej Beňuš xbenus01

import re
import argparse
import xml.etree.ElementTree as ET
import sys
from src.instruction import *

class Interpret:
    instructions: Instruction = []
    numofInstructions = 0
    labels = LabelList()
    def __init__(self):
        self.__instruction_counter = 0
        self.__xmlCode = ""
        self.__inputs = ""

    def setXmlCode(self, xmlCode):
        self.__xmlCode = xmlCode
    def setInputs(self, inputs):
        self.__inputs = inputs
    def setInstructionCounter(self, instructionCounter):
        self.__instruction_counter = instructionCounter

    def appendXmlCode(self, xmlCode):
        self.__xmlCode += xmlCode

    def getXmlCode(self):
        return self.__xmlCode
    def getInputs(self):
        return self.__inputs
    def getInstructionCounter(self):
        return self.__instruction_counter

    @classmethod
    def getInstructions(cls):
        return cls.instructions

    @classmethod
    def appendInstructions(cls, instruction):
        for(inst) in cls.instructions:
            if inst.getNumber() == instruction.getNumber():
                exit(32)
        cls.instructions.append(instruction)

    @classmethod
    def printInstructions(cls):
        for instruction in cls.instructions:
            print(instruction.getName(), instruction.getNumber())
            for arg in instruction.getArgs():
                print(arg.getType(), arg.getValue(), arg.getNumber())

    def argumentParse(self):     # argparse
        parser = argparse.ArgumentParser()
        parser.add_argument("--source", nargs=1, default=None, help="source file")
        parser.add_argument("--input", nargs=1, default=None, help="input file")
        # parser.add_argument("--help", help="ahojda") #TODO

        # Parse the arguments
        args = parser.parse_args()
        if (args.source is None) and (args.input[0] is None):
            # print("Nedostatečný počet argumentů", file=sys.stderr)
            exit(10)
        if (args.source is None):
            for line in sys.stdin:
                if 'Exit' == line.rstrip():
                    break
                self.appendXmlCode(line)
        else:
            try:
                with open(args.source[0], "r") as sourceFile:
                    self.setXmlCode(sourceFile.read())
            except FileNotFoundError:
                # print("Soubor neexistuje", file=sys.stderr)
                exit(11)
        if (args.input is None):
            self.setInputs("")
        else:
            self.setInputs(args.input[0])
        
    def escapeSequence(self, string):
        value = string
        value = value.replace("&amp;","&")
        value = value.replace("&lt;","<")
        value = value.replace("&gt;",">")
        # escape sequences
        matches = re.findall(r'\\[0-9]{3}', value)
        # remove duplicates
        matches = list(set(matches))
        for match in matches:
            replace = chr(int(match.replace("\\","")))
            value = value.replace(match, replace)
        return value
    
    def replaceEscapeSequence(self):
        for instruction in self.instructions:
            for arg in instruction.getArgs():
                if arg.getType() == "string":
                    arg.setValue(self.escapeSequence(arg.getValue()))

    def xmlCheck(self):
        root = ET.fromstring(self.getXmlCode())
        if root.tag != "program":
            exit(31)
        for child in root:
            # control of instruction
            if child.tag != "instruction":
                exit(32)
            childAttrib = list(child.attrib.keys())
            if not ("order" in childAttrib) or not ("opcode" in childAttrib):
                exit(32)
            if int(child.attrib.get("order")) < 1:
                exit(32)

            for subelem in child:
                #control of arguments
                if not(subelem.tag.strip() == "arg1" or subelem.tag.strip() == "arg2" or subelem.tag.strip() == "arg3"):
                    exit(32)
                subelemAttrib = list(subelem.attrib.keys())
                if not ("type" in subelemAttrib):
                    exit(32)
                if not (subelem.attrib["type"] == "var" or subelem.attrib["type"] == "string" or subelem.attrib["type"] == "label" or subelem.attrib["type"] == "type" or subelem.attrib["type"] == "int" or subelem.attrib["type"] == "bool" or subelem.attrib["type"] == "nil"):
                    exit(32)
                if subelem.attrib["type"] == "var":
                    if not(re.match(r"^(G|L|T)F@([a-zA-Z]|_|-|\$|&|%|\*|!|\?)([a-zA-Z0-9]|_|-|\$|&|%|\*|!|\?)*$|^(nil|LF|TF|GF)$", subelem.text.strip())):
                        exit(52)
                if subelem.attrib["type"] == "label":
                    if not(re.match(r"^([a-zA-Z]|_|-|\$|&|%|\*|!|\?)([a-zA-Z0-9]|_|-|\$|&|%|\*|!|\?)*$", subelem.text)):
                        exit(52)
                if subelem.attrib["type"] == "type":
                    if not(re.match(r"^(int|string|bool)$", subelem.text.strip())):
                        exit(52)
                if subelem.attrib["type"] == "string":
                    subelem.text = self.escapeSequence(subelem.text.strip())
                    
        
    def loadInstructions(self):
        root = ET.fromstring(self.getXmlCode())
        for child in root:
            self.numofInstructions += 1
            self.appendInstructions(Instruction(child.attrib["opcode"], child.attrib["order"]))
            counter = 0
            for sub in child:
                counter += 1
                self.instructions[self.numofInstructions-1].appendArgs(sub.attrib["type"], sub.text.strip(), counter)
    
    def checkLabels(self, string):
        for lab in self.labels.getLabels():
            if lab.getName() == string:
                exit(52)

    def loadLabels(self):
        for instruction in self.instructions:
            if instruction.getName() == "LABEL":
                self.checkLabels(instruction.getArgs()[0].getValue())
                self.labels.appendLabels(Label(instruction.getArgs()[0].getValue(), instruction.getNumber()))
        
    def processOrder(self):
        for i in range(len(self.instructions)):
            # bubble sort
            for j in range(len(self.instructions)-1):
                if self.instructions[j].getNumber() > self.instructions[j+1].getNumber():
                    self.instructions[j], self.instructions[j+1] = self.instructions[j+1], self.instructions[j]
    
    def executeProgram(self):
        # print("executeProgram")
        counter = 0
        while (counter in range(len(self.instructions))):
            tmp = self.instructions[counter].execute(self.getInputs(), self.labels, counter)
            # print("execute: ", counter)
            # print("stack: ", Instruction.stack)
            # self.instructions[counter].printVars()
            if(tmp == -1):
                exit(52)
            if(tmp != None):
                counter = tmp
            else:
                counter+=1

new = Interpret() 
new.argumentParse()
new.xmlCheck()
new.loadInstructions()
new.processOrder()
new.replaceEscapeSequence()
new.loadLabels()
new.executeProgram()
exit(0)
