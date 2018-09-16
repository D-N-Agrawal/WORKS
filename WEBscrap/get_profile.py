import bs4 as bs
import urllib.request as rq



s = """
                  {
                   "name" : "%s" ,
                   
                   "ticker" : "%s" ,

                   "address" : [ "%s","%s","%s","%s"],

                   "contact" : {
                                 "tel" : "%s" ,
                                 "website" : "%s"
                               },

                   "sector" : "%s",
                   "industry" : "%s",
                   "full time employee" : "%s",
                   
                   "discription" : "%s"

                   },  

"""
#WARNING:
#### DO NOT FORGET TO REMOVE THE LAST 'COMMMA' FROM THE END OF YOUR JSON FILE ###


def writetojson(ticker):
    url = "https://in.finance.yahoo.com/quote/{}.BO/profile?p={}.BO".format(ticker,ticker) #url to yahoo finance webpage of company
    print(url)
    source = rq.urlopen(url).read() # read the source of webpage
    bsource = bs.BeautifulSoup(source,'html.parser') #parse sourse with beautifulsoup

    all_data = bsource.findAll("p")  # all the data in pragraphs

    lol = all_data[0].contents #list of locations value at position 1,5,9,13

    # data [2,3,4,5] # location lines
    for i in range(1,14,4):
        data.append(lol[i])

    # data[6,7]  # telephone and website
    for i in all_data[0].findAll('a'):
        data.append(i.text)

    # data [8,9,10] sector ,industry ,full time employee
    for i in all_data[1].findAll('strong'):
        data.append(i.text)


    data.append(all_data[2].text)    




        


file = open(r'C:\Users\HP\Desktop\p_python\web_scrap\largedata.json','a')
file.write(" { \"companies\" : [" )

f = open(r'C:\Users\HP\Desktop\p_python\web_scrap\ListOfScrips.csv') # file has list of companies downloaded from BSE INDIA website

comp = []
for i in range(500):
    splist = f.readline().split(",",3)
    compi = (splist[1], splist[2]) # only ticker and name is needed
    comp.append(compi)
    print(len(comp))

    

not_found_comp = [] # list for those companies for which error occured and data is not fetched

for i in range(40):
    data = []
    ticker = comp[i][0]
    name = comp[i][1]
    try:
        data.append(name) # name 
        data.append(ticker) # ticker
        writetojson(ticker)
        file.write(s%tuple(data))
    except:
        print("some error occured find the data manually for %s" %name)
        not_found_comp.append((ticker,name)) # list out name and ticker for not found companies to fetch data mannually 
        




file.write("]  \n }")

file.close()

notfoundlist = open(r'C:\Users\HP\Desktop\p_python\web_scrap\notfound.txt','w')
for i in not_found_comp:
    notfoundlist.write("\n" + i)

notfoundlist.close()

