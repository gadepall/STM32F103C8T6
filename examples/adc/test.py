V_SENSE = 3.3*1766/4095
V_25 = 1.43
AvgSlope = 4.3
temp = (V_25-V_SENSE)/AvgSlope + 25
print(temp)
