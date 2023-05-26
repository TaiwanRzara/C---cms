import requests
a0=requests.get(f"https://iscoj.fg.tp.edu.tw/cms/0")
for i in range(0,100):
    
    a=requests.get(f"https://iscoj.fg.tp.edu.tw/cms/{i}")
    if(a.content!=a0.content):
        print(i)
