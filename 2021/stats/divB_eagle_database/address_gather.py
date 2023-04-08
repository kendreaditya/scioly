import numpy as np
import requests
from bs4 import BeautifulSoup
from tqdm import tqdm

school_names = np.genfromtxt("divB_eagle_database\Eagle Invy Addresses - Sheet2.csv", delimiter='\n', dtype=str)
URL1 = "https://www.google.com/search?q="
URL2 = "&near=harrisburg"
filename = "divB_eagle_database\school_address.csv"

with open(filename, "a") as f:
    for school_name in tqdm(school_names):
        sName = school_name.replace(' ', '+')
        page = requests.get(URL1+sName)
        soup = BeautifulSoup(page.text, 'html.parser')
        rAddress = str(soup.find("span", "BNeawe tAd8D AP7Wnd"))
        address = rAddress[str(rAddress).find(">")+1:-7]
        if address is not None and address!="":
            f.write(f'{school_name},{address}\n')
f.close()