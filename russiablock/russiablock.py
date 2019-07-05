from tkinter import *
from tkinter import messagebox
from time import *
from random import *

class Game:
    def __init__(self):
        self.next = randrange(1,8)
        self.slen = 25
        self.x0 = 340 + 55
        self.y0 = 200 + 65
        #方块颜色列表
        self.color = ['red','orange','yellow','purple','blue','green','pink']
        # Set a core squre and any shape can be drawn by the relative location.
        #字典 存储形状对应7种形状 元组存储坐标
        self.shapeDict = {1:[(0,0),(0,-1),(0,-2),(0,1)], # shape I
                           2:[(0,0),(0,-1),(1,-1),(1,0)], # shape O 
                           3:[(0,0),(-1,0),(0,-1),(1,0)], # shape T T型
                           4:[(0,0),(0,-1),(1,0),(2,0)], # shape J 右长倒L盖子
                           5:[(0,0),(0,-1),(-1,0),(-2,0)], # shape L
                           6:[(0,0),(0,-1),(-1,-1),(1,0)], # shape Z
                           7:[(0,0),(-1,0),(0,-1),(1,-1)]} # shape S
        #旋转坐标控制
        self.rotateDict = {(0,0):(0,0),(0,1):(-1,0),(0,2):(-2,0),(0,-1):(1,0),
                           (0,-2):(2,0),(1,0):(0,1),(2,0):(0,2),(-1,0):(0,-1),
                           (-2,0):(0,-2),(1,1):(-1,1),(-1,1):(-1,-1),
                           (-1,-1):(1,-1),(1,-1):(1,1)}
        # 初始高度，宽度 核心块位置
        self.coreLocation = [4,-2]
        self.height,self.width = 20,10
        self.size = 32
        # Map can record the location of every square.i宽  j高
        self.map = {}
        #全部置0
        for i in range(self.width):
            for j in range(-4,self.height):
                self.map[(i,j)] = 0
        #添加边界
        for i in range(-4,self.width+4):
            self.map[(i,self.height)] = 1
        for j in range(-4,self.height+4):
            for i in range(-4,0):
                self.map[(i,j)] = 1
        for j in range(-4,self.height+4):
            for i in range(self.width,self.width+4):
                self.map[(i,j)] = 1

        # 初始化分数0  默认不加快  按下时加快
        self.score = 0
        self.isFaster = False
        # 创建GUI界面
        self.root = Tk()
        self.root.title("俄罗斯♦️")
        self.root.geometry("500x645")
        #self.area = Canvas(self.root,width=320,height=640,bg='white')
        self.area = Canvas(self.root,width=500,height=645,bg='white')
        self.area.configure(highlightthickness = 0)
        # 游戏方块区域
        self.area.create_rectangle(0, 0, 320, 640, fill='white')
        # 下一个图像提示区域
        #self.area.create_rectangle(340, 200, 490, 350, fill='white')
        self.area.grid(row=2)
        self.startBut = Button(self.root,text="Start",height=2,width=13,font=(18),command=self.play)
        self.startBut.place(x=350,y=20)
        self.quitBut = Button(self.root,text="Quit",height=2,width=13,font=(18),command=self.isQuit)
        self.quitBut.place(x=350,y=75)
        self.restartBut = Button(self.root,text="Restart",height=2,width=13,font=(18),command=self.isRestart)
        self.restartBut.place(x=350,y=130)
        self.scoreLabel1 = Label(self.root,text="Score:",font=(24))
        self.scoreLabel1.place(x=350,y=600)
        self.scoreLabel2 = Label(self.root,text="0",fg='red',font=(24))
        self.scoreLabel2.place(x=410,y=600)
        #按键交互 
        self.area.bind("<Up>",self.rotate)
        self.area.bind("<Left>",self.moveLeft)
        self.area.bind("<Right>",self.moveRight)
        self.area.bind("<Down>",self.moveFaster)
        self.area.bind("<Key-w>",self.rotate)
        self.area.bind("<Key-a>",self.moveLeft)
        self.area.bind("<Key-d>",self.moveRight)
        self.area.bind("<Key-s>",self.moveFaster)
        self.area.focus_set()
        
    def play(self):
        self.next = randrange(1,8)
        self.startBut.config(state=DISABLED)
        global isPause
        isPause = True
        global map
        map = self.map
        while True:
            if self.isOver():
                self.run()
            else:
                break
        self.over()

    def restart(self):
        self.core = [4,-2]
        self.map = {}
        for i in range(self.width):
            for j in range(-4,self.height):
                self.map[(i,j)] = 0
        for i in range(-1,self.width):
            self.map[(i,self.height)] = 1
        for j in range(-4,self.height+1):
            self.map[(-1,j)] = 1
            self.map[(self.width,j)] = 1       
        self.score = 0
        self.t = 0.07
        for j in range(self.height):
            self.area.delete('bottom'+str(j))
        self.play()
    def getLocation(self):
        map[(core[0],core[1])] = 1
        for i in range(4):
            map[((core[0]+getNew[i][0]),
                 (core[1]+getNew[i][1]))]=1

    #判断方块下移一格后对应位置map中的元素是否为一，是，则不可移动，返回False；否，可以移动，返回True。
    def canMove(self):
        for i in range(4):
            if map[(core[0]+getNew[i][0]),(core[1]+1+getNew[i][1])] == 1:
                return False
        return True

    def canRotate(self):
        for i in range(4):
            map[((core[0]+getNew[i][0]),
                (core[1]+getNew[i][1]))] = 0
        for i in range(4):
            if map[((core[0]+self.rotateDict[getNew[i]][0]),
                    (core[1]+self.rotateDict[getNew[i]][1]))] == 1:
                return False
        return True

    def drawNew(self):
        global getNew
        global core      
        #next = randrange(1,8)
        #形状
        self.getNew = self.shapeDict[self.next]
        getNew = self.getNew
        core = [4,-2]
        time = 0.2
        isDrawSmall = True
        
        while self.canMove():
            if isDrawSmall:
                # 把下次的图像在提示区域提前画出来
                self.next = randrange(1,8)
                self.drawSmallNext(self.next - 1)
                isDrawSmall = False
                
            if isPause:
                core[1] += 1
                self.drawSquare()
                if self.isFaster:
                    sleep(0)
                else:
                    sleep(time+0.12)
                self.isFaster = False    
            else:
                self.drawSquare()
                sleep(time)
        self.getLocation()        
        
        
    def drawSmallNext(self, colorNo):
        self.area.delete("newsmall")
        if self.next == 1:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0, self.y0 + self.slen, self.x0 + self.slen, self.y0 + self.slen * 2, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0, self.y0 + self.slen * 2, self.x0 + self.slen, self.y0 + self.slen * 3, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")
        if self.next == 2:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0 + self.slen, self.y0 - self.slen, self.x0 + self.slen * 2, self.y0, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 + self.slen, self.y0, self.x0 + self.slen * 2, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
        if self.next == 3:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 - self.slen, self.y0, self.x0, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 + self.slen, self.y0, self.x0 + self.slen * 2, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
        if self.next == 5:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0 - self.slen, self.y0, self.x0, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 - self.slen * 2, self.y0, self.x0 - self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
        if self.next == 4:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0 + self.slen, self.y0, self.x0 + self.slen * 2, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 + self.slen * 2, self.y0, self.x0 + self.slen * 3, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
        if self.next == 6:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0 - self.slen, self.y0 - self.slen, self.x0, self.y0, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 + self.slen, self.y0, self.x0 + self.slen * 2, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
        if self.next == 7:
            self.area.create_rectangle(self.x0, self.y0, self.x0 + self.slen, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 - self.slen, self.y0, self.x0, self.y0 + self.slen, fill=self.color[colorNo],tags="newsmall")        
            self.area.create_rectangle(self.x0, self.y0 - self.slen, self.x0 + self.slen, self.y0, fill=self.color[colorNo],tags="newsmall")
            self.area.create_rectangle(self.x0 + self.slen, self.y0 - self.slen, self.x0 + self.slen * 2, self.y0, fill=self.color[colorNo],tags="newsmall")
        self.area.update()
        
    def drawSquare(self):
        self.area.delete("new")
        for i in range(4):
            self.area.create_rectangle((core[0]+self.getNew[i][0])*self.size,
                                       (core[1]+self.getNew[i][1])*self.size,
                                       (core[0]+self.getNew[i][0]+1)*self.size,
                                       (core[1]+self.getNew[i][1]+1)*self.size,
                                       fill=self.color[self.next-1],tags="new")
        self.area.update()
        

    # 给底部每行中方块都加上标签：bottom + str(j), j代表该块所在行数，每次遍历map，建立对于range（self. height）的for循环，删去每一行，
    # 若map什么地方的元素为1，画出这一位置的方块，不断更新。这样可以画出底部方块。
    def drawBottom(self):
        for j in range(self.height):
            self.area.delete('bottom'+str(j))
            for i in range(self.width):
                if map[(i,j)] == 1:
                    self.area.create_rectangle(self.size*i,self.size*j,self.size*(i+1),
                                               self.size*(j+1),fill='grey',tags='bottom'+str(j))        
            self.area.update()
                
    # 判断填满遍历map每一行的各个元素，若所有元素为1，则标签中score值+10，将
    # 此行所有元素改为0，行数map（i,j)=map(i-1,j)（即所有之上的行下移）
    # ，那么后续画底部方块时，可实现消行。
    def isFill(self):
        for j in range(self.height):
            t = 0
            for i in range(self.width):
                if map[(i,j)] == 1:
                    t = t + 1
            if t == self.width:
                self.getScore()
                self.deleteLine(j)

    # 加分
    def getScore(self):
        scoreValue = eval(self.scoreLabel2['text'])
        scoreValue += 10
        self.scoreLabel2.config(text=str(scoreValue))

    # 消行
    def deleteLine(self,j):
        for t in range(j,2,-1):
            for i in range(self.width):
                map[(i,t)] = map[(i,t-1)]
        for i in range(self.width):
            map[(i,0)] = 0
        self.drawBottom()
        
    def isQuit(self):
        askQuit = messagebox.askquestion("Quit","Are you sure to quit?")
        if askQuit == 'yes':
            self.root.destroy()
            exit()

    def isRestart(self):
        askRestart = messagebox.askquestion("Restart","Are you sure to restart?")
        if askRestart == 'yes':
            self.restart()
        else:
            return
    
    def isOver(self):
        t = 0
        for j in range(self.height):
            for i in range(self.width):
                if self.map[(i,j)] == 1:
                    t += 1
                    break
        if t >= self.height:
            return False
        else:
            return True

    #旋转
    def rotate(self,event):
        if self.next != 2:
            if self.canRotate():
                for i in range(4):
                    getNew[i] = self.rotateDict[getNew[i]]
                self.drawSquare()        
        if not self.canMove():
            for i in range(4):
                map[((core[0]+getNew[i][0]),(core[1]+getNew[i][1]))] = 1

    # 先判断是否左移/右移，同样，将方块现在所处位置的map中元素设为0，看其移动后的位置上map的元素是否有1，
    # 若有，说明这一位置已被占据或已到边界，不可移动，返回False。若可移动，返回True。按下左键，若可
    # 以移动，核心块的横坐标减1，由于我们只讨论其他小块对于核心块的相对位置，所以其他小块的位置自动随
    # 核心块的位置移动而移动。将移动过后的位置对应map中的元素设为1。
    def canLeft(self):
        coreNow = core
        for i in range(4):
            map[((coreNow[0]+getNew[i][0]),(coreNow[1]+getNew[i][1]))] = 0
        for i in range(4):
            if map[((coreNow[0]+getNew[i][0]-1),(coreNow[1]+getNew[i][1]))] == 1:
                return False
        return True

    #左移
    def moveLeft(self,event):
        if self.canLeft():
            core[0] -= 1
            self.drawSquare()
            self.drawBottom()
        if not self.canMove():
            for i in range(4):
                map[((core[0]+getNew[i][0]),(core[1]+getNew[i][1]))] = 1

             
    # 判断右移
    def canRight(self):
        for i in range(4):
            map[((core[0]+getNew[i][0]),(core[1]+getNew[i][1]))] = 0
        for i in range(4):
            if map[((core[0]+getNew[i][0]+1),(core[1]+getNew[i][1]))] == 1:
                return False
        return True

    # 右移
    def moveRight(self,event):
        if self.canRight():
            core[0] += 1
            self.drawSquare()
            self.drawBottom()
        if not self.canMove():
            for i in range(4):
                map[((core[0]+getNew[i][0]),(core[1]+getNew[i][1]))] = 1

            
    # 初始化中有一self. isFaster 的变量被设为False，当其为False时，
    # 程序中的sleep(time)中time的值为0.35，而按下下键，self. isFaster变为True，
    # time变成0.05，通过调整sleep()中变量的大小可以调节方块运动的速度。
    # 此功能通过if语句实现。
    def moveFaster(self,event):
        self.isFaster = True
        if not self.canMove():
            for i in range(4):
                map[((core[0]+getNew[i][0]),(core[1]+getNew[i][1]))] = 1
        
    # run the programe
    def run(self):
        self.isFill()
        self.drawNew()
        self.drawBottom()

    def over(self):
        feedback = messagebox.askquestion("You Lose!","You Lose!")
        self.root.destroy()
    
    def mainloop(self):
        self.root.mainloop()

class Coords:
    def __init__(self, x1 = 0, y1 = 0, x2 = 0, y2 = 0):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.leftTop = (x1, y1)
        self.rightBottom = (x2, y2)

g = Game()
g.mainloop()



