# preprocess.py
# python preprocessor for Amiga BlitzBasic 2.
# Written to combine all the "XIncludes" from Smite to make debugging less painful.

import sys
import re
quoted = re.compile('"[^"]*"')

mainbb2 = sys.argv[2]
xincludses = []
  
def processLines(lines):
    global count
    global xincludses
    global outputfile
    for line in lines:
        count += 1
        if ("XINCLUDE" in line):
            
            for value in quoted.findall(line):
                #print (value)
                if value not in xincludses:
                    xincludses.append(value)
                    withoutQuotes = value.replace('"', '')

                    inputfile = open(withoutQuotes, 'r')
                    Lines = inputfile.readlines()
                    #outputfile.write("; --------------------------------------------------------------\n")
                    outputfile.write("; XINCLUDE " + value + "\n")
                    outputfile.write("; --------------------------------------------------------------\n")
                    outputfile.write("\n")
                    processLines(Lines)
                    outputfile.write("\n")
                    #outputfile.write("; " + value + "\n")
                    outputfile.write("; --------------------------------------------------------------\n")
                    outputfile.write("\n")

            print("Line {}: {}".format(count, line.strip()))
        else:
            outputfile.write(line)
    

# Using readlines()
inputfile = open(mainbb2, 'r')
Lines = inputfile.readlines()
outputfile = open(sys.argv[1], 'w')
count = 0
# Strips the newline character

processLines(Lines)

