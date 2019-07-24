#!/usr/bin/env python
# -*- coding:utf-8 -*-

import vlc
import re
import time
import sys
import random

f_mp3 = "003涿鹿大战.mp3"#sys.argv[1]
f_lrc = "003涿鹿大战.lrc"#sys.argv[2]


def lrc2dict(lrc):
    lrc_dict = {}
    remove = lambda x: x.strip('[|]')
    for line in lrc.split('\n'):
        time_stamps = re.findall(r'\[[^\]]+\]', line)
        if time_stamps:
            # 截取歌词
            lyric = line
            for tplus in time_stamps:
                lyric = lyric.replace(tplus, '')
            # 解析时间
            # tplus: [02:31.79]
            # t 02:31.79
            for tplus in time_stamps:
                t = remove(tplus)
                tag_flag = t.split(':')[0]
                # 跳过: [ar: 逃跑计划]
                if not tag_flag.isdigit():
                    continue
                time_lrc = int(tag_flag) * 60000
                time_lrc += int(t.split(':')[1].split('.')[0]) * 1000
                # ms也许没有
                try:
                    time_lrc += int(t.split('.')[1])
                except:
                    pass
                # 截取到0.1s精度,降低cpu占用
                time_lrc = time_lrc / 1000 * 1000
                lrc_dict[time_lrc] = lyric
    return lrc_dict


def print_lrc(player, lrc_d, color):
    player.play()
    player.pause()
    # 防止无法获取整个音频时长
    # 音频时长必须加载才能读取
    time.sleep(0.1)
    player.play()
    wholetime = mediaObject.get_duration() / 1000 * 1000
    while 1:
        # 截取到0.1s精度,降低cpu占用, notwork fine for vlc
        # FIXME: get_time NOT WORK WELL, 只能精确到0.3s
        # t = player.get_position() * wholetime
        t = player.get_time() / 1000 * 1000
        # sys.stdout.write(str(t) + '\r')
        sys.stdout.write('[' +
                         time.strftime("%M:%S", time.localtime(t / 1000)) +
                         '/' +
                         time.strftime("%M:%S",
                                       time.localtime(wholetime / 1000)) +
                         '] ')
        if t not in lrc_d:
            sys.stdout.flush()
            # 向后清除
            # sys.stdout.write("\033[K")
        else:
            sys.stdout.write(color + lrc_d[t] + '\033[0m')
            sys.stdout.flush()
            # 向后清除
            sys.stdout.write("\033[K")
        sys.stdout.write('\r')
        # 播放停止时退出
        if t == wholetime:
            sys.exit(0)
        # 0.05s循环
        time.sleep(0.05)

with open(f_lrc) as f:
    lrc = f.read()

lrc_d = lrc2dict(lrc)

vlcInstance = vlc.Instance()
player = vlcInstance.media_player_new()
mediaObject = vlcInstance.media_new(f_mp3)
player.set_media(mediaObject)

colors = [
    '\x1B[31m',  # 红色
    '\x1B[32m',  # 绿色
    '\x1B[33m',  # 黄色
    '\x1B[34m',  # 蓝色
    '\x1B[35m',  # 紫色
    '\x1B[36m',  # 青色
    '\x1B[37m'  # 灰白
]
color = random.choice(colors)
print_lrc(player, lrc_d, color)