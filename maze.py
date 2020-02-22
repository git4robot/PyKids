import tkinter as tk
import threading
import time
import random
import sys

class Cell():
    def __init__(self, row, col):
        self.row, self.col = row, col 
        self.top, self.right, self.bottom, self.left = True, True, True, True
        self.visited = False
    def __str__(self):
        return 'row:{} col:{}--{} {} {} {}'.format( \
                self.row, self.col, self.top, self.right, \
                self.bottom, self.left)
    def setVisited(self):
        self.visited = True
    def isVisited(self):
        return self.visited

class Maze(threading.Thread):
    colCount = 15
    rowCount = 15
    winWidth = 700
    winHeight = 600
    beginOf = (0, 0)
    endOf = (colCount - 1, rowCount - 1)
    def __init__(self):
        threading.Thread.__init__(self)
        self.initData()
        self.initUi()
    def initUi(self):
        self.ui = tk.Tk()
        self.centeredDisplay()
        self.cs = tk.Canvas(self.ui, bg = '#121a2a')
        self.cs.pack(fill = tk.BOTH, expand = 1)
        self.ui.bind('<Key-h>', self.hideCell)
        self.ui.bind('<Key-Up>', self.up)
        self.start()
    def hideCell(self, event):
        self.cs.delete('currend')
    def up(self, event):
        pass
    def updateUi(self):
        w = float(self.winWidth / self.colCount)
        h = float(self.winHeight / self.rowCount)
        for row in range(self.rowCount):
            for col in range(self.colCount):
                cell = self.cells[row][col]
                tagtmp = 'wall%02d%02d' % (row, col)
                if cell.top:
                    self.cs.create_line(\
                            (w * col, h * row), \
                            (w * (col + 1), h * row), \
                            width = 3, fill = 'yellow', tag = 'top' + tagtmp) 
                else:
                    self.cs.delete('top' + tagtmp)
                if cell.right:
                    self.cs.create_line(\
                            (w * (col + 1), h * row), \
                            (w * (col + 1), h * (row + 1)), \
                            width = 3, fill = 'yellow', tag = 'right' + tagtmp)
                else:
                    self.cs.delete('right' + tagtmp)
                if cell.bottom:
                    self.cs.create_line(\
                            (w * (col + 1), h * (row + 1)), \
                            (w * col, h * (row + 1)), \
                            width = 3, fill = 'yellow', tag = 'bottom' + tagtmp)
                else:
                    self.cs.delete('bottom' + tagtmp)
                if cell.left:
                    self.cs.create_line(\
                            (w * col, h * (row + 1), \
                            (w * col, h * row)), \
                            width = 3, fill = 'yellow', tag = 'left' + tagtmp)
                else:
                    self.cs.delete('left' + tagtmp)

        self.cs.create_rectangle((self.beginOf[0] * w + 3, self.beginOf[1] * h + 3), \
                (self.beginOf[0] + 1) * w - 3, (self.beginOf[1] + 1) * h - 3, \
                fill = '#b4532a', tag = 'begin')
        self.cs.create_rectangle((self.endOf[0] * w + 3, self.endOf[1] * h + 3), \
                (self.endOf[0] + 1) * w - 3, (self.endOf[1] + 1) * h - 3, \
                fill = '#ff0000', tag = 'end')
        self.cs.delete('currend')
        self.cs.create_rectangle((self.currentCell.col * w + 10, self.currentCell.row * h + 10), \
                (self.currentCell.col + 1) * w - 10, (self.currentCell.row + 1) * h - 10, \
                fill = '#00ff00', tag = 'currend')
        
        self.cs.update()    

    def centeredDisplay(self):
        w = self.ui.winfo_screenwidth()
        h = self.ui.winfo_screenheight()
        self.ui.geometry('{}x{}+{}+{}'.format(\
                self.winWidth, self.winHeight, \
                int((w - self.winWidth)/2), \
                int((h - self.winHeight)/2)))
        self.ui.resizable(False, False)
        self.ui.title('Maze')
    def initData(self):
        self.cells = [[Cell(row, col) for col in range(self.colCount)] \
                for row in range(self.rowCount)]
        self.cellStack = []

        self.currentCell = self.cells[self.beginOf[0]][self.beginOf[1]]
    def delWall(self, cell, cell2):
        if 1 == cell.row - cell2.row:
            cell.top, cell2.bottom = False, False
        elif -1 == cell.row - cell2.row:
            cell.bottom, cell2.top = False, False
        if 1 == cell.col - cell2.col:
            cell.left, cell2.right = False, False
        elif -1 == cell.col - cell2.col:
            cell.right, cell2.left = False, False
    def topCell(self, cell):
        if 0 == cell.row:
            return None
        ret = self.cells[cell.row - 1][cell.col]
        if ret.isVisited():
            return None
        return ret
    def rightCell(self, cell):
        if self.colCount - 1 == cell.col:
            return None
        ret = self.cells[cell.row][cell.col + 1]
        if ret.isVisited():
            return None
        return ret 
    def bottomCell(self, cell):
        if self.rowCount - 1 == cell.row:
            return None
        ret = self.cells[cell.row + 1][cell.col]
        if ret.isVisited():
            return None
        return ret 
    def leftCell(self, cell):
        if 0 == cell.col:
            return None
        ret = self.cells[cell.row][cell.col - 1]
        if ret.isVisited():
            return None
        return ret 

    def checkNeighbor(self):
        curCell = self.currentCell
        curCell.setVisited()
        neighbor = [self.topCell(curCell), self.rightCell(curCell), \
                self.bottomCell(curCell), self.leftCell(curCell)]
        while None in neighbor:
            neighbor.remove(None)
        n = len(neighbor)
        if 0 == n:
            try:
                self.currentCell = self.cellStack.pop()
                if None == curCell:
                    return
                self.checkNeighbor()
                return
            except:
                return
        self.cellStack.append(self.currentCell)
        self.currentCell = neighbor[random.randint(0, n - 1)]  
        self.delWall(curCell, self.currentCell)
        self.checkNeighbor()
    def run(self):
        self.checkNeighbor()
        self.updateUi()
        print('finish')
sys.setrecursionlimit(100000)
maze = Maze()
tk.mainloop()
