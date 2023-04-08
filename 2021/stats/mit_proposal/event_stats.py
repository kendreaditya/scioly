import yaml
import os
import sys

PATH = "mit_proposal\data"

comps = dict()

def commonElements(arr): 
      
    # initialize result with first array as a set 
    result = set(arr[0]) 
  
    # now iterate through list of arrays starting from 
    # second array and take intersection_update() of  
    # each array with result. Every operation will  
    # update value of result with common values in 
    # result set and intersected set 
    for currSet in arr[1:]: 
        result.intersection_update(currSet) 
  
    return list(result) 


for file_name in os.listdir(PATH):
    with open(f"{PATH}\{file_name}", 'r') as f:
        data = yaml.load(f)
        try:
            name = data['Tournament']['short name']
        except:
            name = data['Tournament']['name']
        #events = [i['name'] for i in data['Events']]
        teams = [i['school'] for i in data['Teams']]
        comps[name] = teams

teams = []

for name in comps:
    torno = []
    for team in comps[name]: 
        torno.append(team)
    teams.append(torno)

#print(teams)
nats_teams = commonElements(teams)

for team in nats_teams:
    print(team)