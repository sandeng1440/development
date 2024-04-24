
# *
# **
# ***
# ****
# *****

def LRUTriangle():
    print("\n")
    for i in range(5):
        j = 0
        while j <= i:
            print("*",end = "")
            j += 1
        print("\r")

#     *
#    **
#   ***
#  ****
# *****

def RRUTriangle():
    print("\n")
    for i in range(1,6):
        j = 5 - i
        for n in range(j):
            print(" ",end = "")
        for p in range(i):
            print("*",end = "")
        print("\r")

# *****
#  ****
#   ***
#    **
#     *

def RRDTriangle():
    print("\n")
    for i in range(5):
        j = 5 - i
        for n in range(i,0,-1):
            print(" ",end = "")
        for k in range(j):
            print("*",end = "")
        print("\r")
            

# *****
# **** 
# ***  
# **   
# *    

def LRDTriangle():
    print("\n")
    for i in range(5):
        j = 5 - i
        for k in range(j,0,-1):
            print("*",end = "")
        for n in range(i,0,-1):
            print(" ",end = "")
        print("\r")

LRUTriangle()
RRUTriangle()
RRDTriangle()
LRDTriangle()



