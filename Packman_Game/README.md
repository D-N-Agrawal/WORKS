This is a game programmed in PYTHON. 
Using PYGAME module

In this we have an arina rendered over a grid of square nodes (rows,collumns)  which contains some walls and ways made by placements of blocks. (Take a look to arina.png image)

Game have two other bolcks (YOU, ENEMY).
You have a control on YOU (green) block and can make it up, down, left, right.
the ENEMY (red) block will approach to YOU block in each next step. It approachs by calculating shortest path using DIJ'KASTRAS algorithm.

If ENEMY managed to reach to YOU, the game will over.
  