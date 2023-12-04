#!/usr/bin/env python3

import requests
from sys import argv 
import datetime
import os

#SECRET COOKIE... yummy...

year = 2023

session_path = os.getenv('HOME') + "/projects/AOC/.config"

year = datetime.date.today().year
day = datetime.date.today().day

print("Fetching input for day/year {}/{}".format(day, year))

if len(argv) < 2:
    print("No day specified. Using current date.")
else:
    day = argv[1]

cookie = {}

try:
    cookie["session"] = open(session_path, 'r').readline().strip()
except Exception as e:
    print(e)
    exit(1)

try:
    r = requests.get("https://adventofcode.com/{}/day/{}/input".format(year, day), cookies=cookie)
    data = r.content.decode('utf-8')
    with open("input", 'w') as f:
        f.write(data)
        print("Input successfully written")
    os.system("cat input")

except Exception as e:
    print(e)
    exit(2)
