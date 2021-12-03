import os
import base64
import requests
import json

lockfilePath = os.path.join(os.getenv('LOCALAPPDATA'), R'Riot Games\Riot Client\Config\lockfile')

lockfileF = open(lockfilePath)
data = lockfileF.read().split(':')
keys = ['name', 'PID', 'port', 'password', 'protocol']
lockfile = dict(zip(keys, data))

headers = {}
headers['Authorization'] = 'Basic ' + base64.b64encode(('riot:' + lockfile['password']).encode()).decode()
response = requests.get("https://127.0.0.1:{port}/chat/v1/session".format(port=lockfile['port']), headers=headers, verify=False)
puuid = response.json()['puuid']

response = requests.get("https://127.0.0.1:{port}/chat/v4/presences".format(port=lockfile['port']), headers=headers, verify=False)
presences = response.json()

for presence in presences['presences']:
    if presence['puuid'] == puuid:    # compares to the PUUID we got in the previous response to aviod setting someone else's state as our status
        party_id = json.loads(base64.b64decode(presence['private']))['partyId']
        
print(partyId)
print(puuid)
print("https://jloh02.github.io/valorant-discord-presence?puuid={puuid}&party={party}&region={region}".format(party=party_id, puuid=puuid, region='ap'))