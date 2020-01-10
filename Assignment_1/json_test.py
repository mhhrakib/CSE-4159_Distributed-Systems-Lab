import json

with open('jokes.json') as f:
    data = json.load(f)


def get_jokes_by_no(id):
    return data['jokes'][id - 1]['joke']


def get_jokes_id_by_no(id):
    return data['jokes'][id - 1]['id']


def get_jokes_by_id(id):
    for jokes in data['jokes']:
        if jokes['id'] == id:
            return jokes['joke']


