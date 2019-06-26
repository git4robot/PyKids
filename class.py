# -*- coding: utf-8 -*-
"""
Created on Wed Jun 19 16:09:06 2019

@author: Robin
"""
class Yh:
    def cryh(many, much):
        return round(many * much * 0.85)
    def yh(many, much):
        return many * much * 0.85

class Cy:
    def hcy(many, much):
        return many * much * 0.85
    def dcy(many, much):
        return many * much * 0.85

class Em:
    def sf(many, much):
        return many * much * 0.85
    def dm(many, much):
        return many * much * 0.85

class Sf:
    def yb(many, much):
        return round(many * much * 0.85)
    def rb(many, much):
        return round(many * much * 0.85)

class Tb:
    def rt(many, much):
        return many * much * 0.85
    def wt(what):
        if what == 'xq':
            return round(4.5 * 1650)
        elif what == 'y':
            return 1650
        elif what == 't':
            return 80
    def hs_rt(many, much):
        return many * much * 0.85

xx = Yh.yh(48, 138)
xxx = Yh.cryh(24, 145)
yy = Cy.hcy(24, 168)
yyy = Cy.dcy(24, 188)
zz = Em.sf(24, 158)
zzz = Em.dm(24, 148)
aa = Sf.yb(48, 100)
aaa = Sf.rb(24, 100)
bb = Tb.wt('xq')
bbb = Tb.rt(125, 175)
bbbb = Tb.hs_rt(55, 175)
men = (xx, xxx, yy, yyy, zz, zzz, aa, aaa, bb, bbb, bbbb)
print(men)