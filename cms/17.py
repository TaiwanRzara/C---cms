file=open("cms/17.c","w")
count=1
prime=[2]
is_pr=True
string="const int prime[]={2"
for i in range(3,int(1e4+1)):
    is_pr=True
    for p in prime:
        if(p*p>i): break
        if(i%p==0):
            is_pr=False
            break
    if(is_pr):
        prime.append(i)
        count+=1
        string+=f",{i}"
string+="};"
file.write(string)
print(count)