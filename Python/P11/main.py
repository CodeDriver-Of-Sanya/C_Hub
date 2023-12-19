def isRun(y):
    if (y % 4 == 0 and y%100!=0) or y%400==0:
        return True
    else:
        return False

cnt=0

for i in range(1800, 2000):
    if isRun(i):
        print(i)
        cnt += 1

print(cnt)