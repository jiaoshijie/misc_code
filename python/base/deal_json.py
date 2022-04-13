#! /usr/bin/python3

import json

json_file = open(
        "dynamicPort_config.json", "r", encoding="utf-8")

movie = json.load(json_file)

json_file.close()
print(movie)
