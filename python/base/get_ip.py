#! /usr/bin/python3

from urllib.request import urlopen, Request
import re
import sys
import os


def openurl(website, query_string):
    if query_string == "":
        get_localIP()
    url = website + query_string
    open_url = Request(url, headers={"User-Agent": "Mozilla/5.0 (X11; Linux \
            x86_64) AppleWebKit/537.36 (KHTML, like Gecko) \
            Chrome/74.0.3729.108 Safari/537.36"})
    html = urlopen(open_url).read().decode("utf-8")
    #  print(html)
    ip_compile = re.compile(r"<code>(.+?)</code>")
    ip_informations = ip_compile.findall(html)
    print("公网IP: ", ip_informations[0])
    print("地区: ", ip_informations[1])
    print("Geo IP: ", ip_informations[2])


def get_localIP():
    ip_info = os.popen("ip addr").read()
    ip_local = re.compile(r"inet (.+?)/")
    ip_local_info = ip_local.findall(ip_info)
    print("本机IP: ", end="")
    for i in ip_local_info:
        print(i, end="  ")
    print()


if __name__ == "__main__":
    # https://ip.cn/?ip=8.8.8.8
    website = "https://ip.cn"
    query_string = ""
    if len(sys.argv) > 1:
        ipaddr = str(sys.argv[1])
        query_string = "?ip=" + ipaddr
    openurl(website, query_string)
