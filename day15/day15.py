import re


def calc_manhattan_distance(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

# read the file input.txt into a list of strings

with open('day15/input.txt', 'r') as f:
    data = f.readlines()

sensors = []
beacons = []

for line in data:
    # find first occurence of a number
    x_sensor = re.search(r'\d+', line).group()
    # find second occurence of a number
    y_sensor = re.search(r'\d+', line[line.find(x_sensor) + len(str(x_sensor)):]).group()
    # find third occurence of a number
    x_beacon = re.search(r'\d+', line[line.find(y_sensor)+ len(str(y_sensor)):]).group()
    # find fourth occurence of a number
    y_beacon = re.search(r'\d+', line[line.find(x_beacon)+ len(str(x_beacon)):]).group()
    # find the name of the sensor

    sensor = {'x': int(x_sensor), 'y': int(y_sensor)}
    beacon = {'x': int(x_beacon), 'y': int(y_beacon)}
    sensors.append(sensor)
    beacons.append(beacon)

