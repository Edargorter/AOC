#!/usr/bin/env python3

import requests
import argparse 
from sys import argv 
import datetime
import os

#MMMMMMMmmmmmmmmm SECRET COOKIE...yummmmmy
session_path = os.getenv('HOME') + "/CP/AOC2020/.config"

parser = argparse.ArgumentParser(description="Get input from AOC site")
parser.add_argument("-p", metavar="path", type=str, help="Path to session cookie")
parser.add_argument("-d", metavar="day", type=int, help="Day of the month")
args = parser.parse_args()

day = datetime.date.today().day

if not args.d:
    print("No day specified. Using current date.")
else:
    day = args.d

cookie = {}

if args.p:
    session_path = args.p

try:
    cookie["session"] = open(session_path, 'r').readline().strip()
except Exception as e:
    print(e)
    exit(1)

try:
    r = requests.get("https://adventofcode.com/2020/day/{}/input".format(day), cookies=cookie)
    data = r.content.decode('utf-8')
    with open("input", 'w') as f:
        f.write(data)
        print("Input successfully written")
    os.system("cat input")

except Exception as e:
    print(e)
    exit(2)
