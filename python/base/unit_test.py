#! /usr/bin/python3

from math import pi

def circle_area(r):
    if type(r) not in [int, float]:
        raise TypeError("int or float")
    if r < 0:
        raise ValueError("不能是负数")
    return pi * (r ** 2)

if __name__ == "__main__":
    #  Test function
    radii = [2, 0, -3, 2 + 5j, True, "radius"]

    for r in radii:
        A = circle_area(r)
        print("Area of circles with r = {radius} is {area}.".format(radius=r, area=A))
