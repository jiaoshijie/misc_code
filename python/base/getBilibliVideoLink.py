import requests
import json
import os
import re


def get_bilibili_video_url(url):
    rmap = {}  # return value
    html = requests.get(url)
    matchs = re.search(r"window.__INITIAL_STATE__=(.+);\(function", html.text).group(1)
    print(matchs)
    exit(0)
    js = json.loads(matchs)

    for key in js['epMap'].keys():
        # print(key, js['epMap'][str(key)])
        temp = js['epMap'][str(key)]
        if temp['sectionType'] == 0:
            rmap[temp['i']] = {'titleFormat': temp['titleFormat'],
                               'title': temp['longTitle'], 'link': temp['link']}

    return rmap


def downloader(videoinfo, command='annie', com_args='-f 80'):
    # using annie
    for i in range(len(videoinfo)):
        args = videoinfo[i]['link']
        while os.system('{} {} {}'.format(command, com_args, args)):
            pass


def print_info(videoinfo):
    for i in range(len(videoinfo)):
        print("{} {}: {}".format(
            videoinfo[i]['titleFormat'], videoinfo[i]['title'], videoinfo[i]['link']))


if __name__ == '__main__':
    url = "https://www.bilibili.com/bangumi/play/ep172119"
    info = get_bilibili_video_url(url)
    # downloader('annie', '-f 80', info)
    print_info(info)
