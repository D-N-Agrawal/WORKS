import pygame
import time

#initialization of pygame
pygame.init()

rd = (height,width) = (600,600)   
gd = pygame.display.set_mode(rd)  # set height and width of window
pygame.display.set_caption("PACKMAN") # set caption/name of window
clock = pygame.time.Clock()

rows = 20        # number of rows 
size = height/rows  # size of each square

arina = tuple(range(20)) + tuple(range(380,400)) + tuple(range(20,361,20)) + tuple(range(39,380,20)) + tuple(range(67,77)) +tuple(range(153,157)) + tuple(range(230,237)) + tuple(range(303,313)) + (256,276,296,316) +(184,185,186) +(150,170,190,210) + tuple(range(83,224,20))  # cubes which are wall 
nodes = [i for i in range(rows*rows) if i not in arina]  #cubes which are ways

#color codes
black = (0,0,0)
white = (255,255,255)
red = (255,0,0)
green = (0,255,0)
blue = (0,0,255)

        
def block_number(px,py):
    return (py//size)*rows + px//size
    
def draw_maze():
    for i in range(rows):
        pygame.draw.line(gd, red, (0,i*size),(width,i*size))
        pygame.draw.line(gd, red, (i*size,0),(i*size,height))
    pygame.display.update()

def draw_arina(blocks):
    for i in blocks:
        py = (i//rows)*size
        px = (i%rows)*size
        pygame.draw.rect(gd, blue, (px, py, size, size))

    pygame.display.update()    



########################### path computing by dij kastras ALGORITHM   ##################################################

# methods to graph of nodes     
def graph_matrix(nodes):
    wtmg = {}
    for i in nodes:
        l = []
        for j in nodes:
            if (j == i+1) or (j == i-1) or (j == i-rows) or (j == i+rows):
                l = l + [(j,1)]
            elif(j == i):
                l = l + [(j,0)]
            else:
                l = l + [(j,-1)]

        wtmg[i] = l

    return wtmg	


#### DIJ KASTRAS ALGORITHM ################

# inutialization of graph_matrix, distance list, parent list and vertex queue        
wtmg = graph_matrix(nodes)

# computing next step through optimal path
def comp_step(youx, youy, enmx, enmy):
    srs = int(block_number(youx,youy))   #source as YOU cube
    print(srs)
    des = int(block_number(enmx,enmy))  # destination as ENEMY cude
    print(des)

    if(srs == des):   # when reached to destination ie YOU CAUGHT
        crash()
        
    dist = {}
    parent = {}
    
    for i in nodes:
        dist[i] = float("Inf")# distance list contain inf values for all nodes
        
    for i in nodes:
        parent[i] = None         # parent list contain None values for all nodes

    que = nodes.copy()       # queue of all nodes
    
    dist[srs] = 0    # source distance is 0 at start

    # required methods for algorithm
    def minimum_dist(fd):
        d = {}
        for i in que:
            d[i] = fd[i]
        
        v=list(d.values())
        k=list(d.keys())
        return k[v.index(min(v))]

    def relax(u,v):
        for i in wtmg[u]:
            if (i[0] == v):
                w = i[1]
                break
            
        if( dist[v] > dist[u] + w):
            dist[v] = dist[u] + w
            parent[v] = u
    
    
    while(que):      # till all nodes are not traversed run dij kastras 
        u = minimum_dist(dist)        #
        que.remove(u)                 #
                                      #
        for i in wtmg[u]:             #
            if i[1] > 0:              #
                relax(u,i[0])         #
         
    nb = parent[des]       # parent of enemy(destination) ie next step for enemy
    print(nb)
    py = (nb//rows)*size
    px = (nb%rows)*size

    return px,py      #return co ordinates of next step
   

##################################################################################################################



# method to draw YOU block
def draw_you(youx, youy):
    pygame.draw.rect(gd, green, (youx, youy, size, size))
    pygame.display.update()

#method to draw ENEMY block
def draw_enemy(enmx,enmy):
     pygame.draw.rect(gd, red, (enmx, enmy, size, size))
     pygame.display.update()


### methods for text display ###    
def textObjects(txt, font, color):
    textSurface = font.render(txt, True, color)
    return textSurface, textSurface.get_rect()

def message_display(txt,color,sizee,pos):
    txt_type = pygame.font.Font('freesansbold.ttf', sizee)
    textSurf, textRect = textObjects(txt, txt_type, color)
    textRect.center = pos
    gd.blit(textSurf, textRect)
    pygame.display.update()

# game over method    
def crash():
    message_display("GAME OVER",white,100, (height/2, width/2))
    time.sleep(3)
    game_loop()


########################  THE MAIN GAME LOOP ########################
def game_loop():
    gameExit = False
    youx, youy = 13*30 , 10*30     # you block start point
    enmx, enmy = 60,270            # enemy block start point  
    x_change = 0
    y_change = 0
        
    while not gameExit:              

        for event in pygame.event.get():
            if event.type == pygame.QUIT:       # QUIT clicked
                pygame.quit()                   # quit
                quit()
                    
            if event.type == pygame.KEYDOWN:      #key pressed down                
                if event.key == pygame.K_LEFT:    #left arrow key
                    y_change = 0
                    x_change = -size

                if event.key == pygame.K_RIGHT:   #right arrow key
                    y_change = 0
                    x_change = size

                if event.key == pygame.K_UP:      # up arrow key
                    x_change = 0
                    y_change = -size

                if event.key == pygame.K_DOWN:    # down arrow key
                    x_change = 0
                    y_change = size

##            if event.type == pygame.KEYUP:
##                if event.key in (pygame.K_LEFT,pygame.K_RIGHT,pygame.K_UP,pygame.K_DOWN):
##                    x_change, y_change = 0,0

        # change in position
        youx += x_change
        youy += y_change

        if block_number(youx,youy) in arina:  ### logic for 'not to overlap with walls' if block is part of wall then undo change in position
            youx -= x_change
            youy -= y_change

        #### drawing all the window    
        gd.fill(black)
        draw_maze()            # draw lines
        draw_arina(arina)      # draw walls
        draw_you(youx, youy)   # draw you 
        enmx, enmy = comp_step(youx, youy,enmx,enmy)  # enemy position as per you position (calculated by dij kastras algo) 
        print(enmx,enmy)             
        draw_enemy(enmx, enmy) #draw enemy
          
        pygame.display.update()
        clock.tick(5)

### game intro ####
gd.fill(white)
message_display(r"LET'S PLAY : PACKMAN",red,35,(350,150))
message_display("use arrow keys for",blue,25,(350,250))
message_display(" UP DOWN LEFT RIGHT",blue,25,(350,310))
pygame.display.update()
time.sleep(3)

game_loop()   # call GAME LOOP
pygame.quit()
quit()
