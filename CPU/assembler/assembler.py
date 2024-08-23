# In the future the assembler will be written in my assembly language then transformed 
# into machine language that runs on my simulated cpu via this program. Then it will 
# be able to run in my operating system’s environment 

import sys

func_table = {
    "add": 0,
    "sub": 1,
    "mul": 2,
    "div": 3,
    "mov": 4,
    "and": 5,
    "or": 6,
    "xor": 7,
    "not": 8,
    "compb": 9,
    "compl": 10,
    "jeq": 11,
    "jlt": 12,
    "jgt": 13,
    "jne": 14,
    "jmp": 15,
    "load": 16,
    "save": 17,
    "lea": 18,
    "push": 19,
    "pop": 20}

reg_names = {
    "R0": 1,
    "R1": 2,
    "R2": 3,
    "R3": 4,
    "R4": 5,
    "R5": 6,
    "R6": 7,
    "R7": 8,
    "R8": 9,
    "R9": 10,
    "RPC": 11,
    "RSP": 12,
    "RSB": 13,
    "RFG": 14,
    "RA1": 15,
    "RA2": 16
}



def main ():

    if(len(sys.argv) != 3):
        print("Usage: python3 assembler.py {file} {out}")

    assembled = ''
    
    #convert_labels(sys.argv[1]) # converts labels to numbers
    assemble_no_labels() # assembles

    #open(sys.argv[2], 'w').write(assembled)

def assemble_no_labels():
    f = open(sys.argv[1], 'r')
    bits = []

    for i in f.readlines():
        curstr = ""

        space = i.find(" ")

        instruction = i[0:space]
        curstr += str(bin(func_table[instruction]))[2:].zfill(5) # convert instruction to binary of 5 bits

        comma = i.find(",")

        arg1 = i[space+1:comma]
        
        if(arg1 in reg_names.keys()):
            curstr += '0'
            curstr += str(bin(reg_names[arg1])[2:].zfill(16))
        else:
            curstr += '1'
            curstr += str(bin(int(arg1)))[2:].zfill(16)
        
        arg2 = i[comma+1: len(i.rstrip())]
        curstr += str(bin(reg_names[arg2]))[2:].zfill(5)
        curstr += "00000"

        bits.append(curstr)
    f.close()

    f = open(sys.argv[2],'w')
    for i in bits:
        f.write(i + "\n")
    f.close()
        


def convert_labels(file):
    pass


if __name__ == "__main__":
    main()