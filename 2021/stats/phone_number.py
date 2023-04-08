import requests
from tqdm import tqdm
from bs4 import BeautifulSoup
import re

PLACES = []
PHONES = []

def find_places(radius):
    parms = {'key': 'AIzaSyApZIzfuIWCGDUfiMsHPbAuhl2InxKfwP8', 'location' : "40.2400,-77.0620", 'radius' : '2000'}
    PATH = f"https://maps.googleapis.com/maps/api/place/nearbysearch/json?location={parms['location']}&radius={radius}&key={parms['key']}"

    r = requests.get(PATH).json()
    for places in r['results']:
        if places['name'] not in PLACES:
            PLACES.append(places['name'])

def find_phone(place):
    try:
        sName = place.replace(' ', '+')
        page = requests.get(f"https://www.google.com/search?q={sName}&near=harrisburg")
        soup = BeautifulSoup(page.text, 'html.parser')
        tag_name = soup.find_all("span", "BNeawe tAd8D AP7Wnd")
        phone = re.sub('<[^>]+>', '', str(tag_name[-1]))
        PHONES.append([place, phone])
    except Exception as inst:
        print(inst)

for x in tqdm(range(50, 50000, 50)):
    find_places(x)

for place in tqdm(PLACES):
    find_phone(place)

print(PHONES)

with open('buz_phones.csv', 'w') as f:
    for name, phone in PHONES:
        try:
            f.write(f"{name}, {phone}\n")
        except:
            pass
    f.close()
