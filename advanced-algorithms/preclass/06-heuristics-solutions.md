# Heuristics

## Question 1a

The Euclidian Distance is the distance between two points calculated with: $\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}$ for points $(x_1, y_1)$ and $(x_2, y_2)$. Usually used when the movement is unrestricted (up, down, left, right, diagonal).

## Question 1b

The Manhattan Distance is the distance between two points calculated with: $|x_2-x_1|+|y_2-y_1|$ for points $(x_1, y_1)$ and $(x_2, y_2)$. Usually used when the movement is restricted to a grid (up, down, left, right).

## Question 2a

- Visited = []; Unvisited = [A, B, C, D, E, F, Z]
- initial state

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | ∞        | -        |
| C       | ∞        | -        |
| D       | ∞        | -        |
| E       | ∞        | -        |
| F       | ∞        | -        |
| Z       | ∞        | -        |

---

- Visited = [A]; Unvisited = [B, C, D, E, F, Z]
- from A to B: 0+4=4
- from A to C: 0+3=3

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | ∞        | -        |
| E       | ∞        | -        |
| F       | ∞        | -        |
| Z       | ∞        | -        |

---

- Visited = [A, C]; Unvisited = [B, D, E, F, Z]
- from C to D: 3+7=10
- from C to E: 3+10=13

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | 10       | C        |
| E       | 13       | C        |
| F       | ∞        | -        |
| Z       | ∞        | -        |

---

- Visited = [A, C, B]; Unvisited = [D, E, F, Z]
- from B to E: 4+12=16
- from B to F: 4+5=9

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | 10       | C        |
| E       | 13       | C        |
| F       | 9        | B        |
| Z       | ∞        | -        |

---

- Visited = [A, C, B, F]; Unvisited = [D, E, Z]
- from F to Z: 9+16=25

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | 10       | C        |
| E       | 13       | C        |
| F       | 9        | B        |
| Z       | 25       | F        |

---

- Visited = [A, C, B, F, D]; Unvisited = [E, Z]
- from D to E: 10+2=12

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | 10       | C        |
| E       | 12       | D        |
| F       | 9        | B        |
| Z       | 25       | F        |

---

- Visited = [A, C, B, F, D, E]; Unvisited = [Z]
- from E to Z: 12+5=17

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | 10       | C        |
| E       | 12       | D        |
| F       | 9        | B        |
| Z       | 17       | E        |

---

- Visited = [A, C, B, F, D, E, Z]; Unvisited = []
- No more vertices to visit

| Vertex | Distance | Previous |
| ------- | -------- | -------- |
| A       | 0        | -        |
| B       | 4        | A        |
| C       | 3        | A        |
| D       | 10       | C        |
| E       | 12       | D        |
| F       | 9        | B        |
| Z       | 17       | E        |

---

- Shortest path: A -> C -> D -> E -> Z; Cost: 17

## Question 2b

- Initial state: G=0, H=14, F=14
- open = [A]; closed = []

---

- Expand A (F=14)
- Examine B, C
- open = [B, C]; closed = [A]

| Node | G    | H    | F    | Previous |
| ---- | ---- | ---- | ---- | -------- |
| B    | 4    | 12   | 16   | A        |
| C    | 3    | 11   | 14   | A        |

---

- Expand C (F=14)
- Examine D, E
- open = [B, D, E]; closed = [A, C]

| Node | G    | H    | F    | Previous |
| ---- | ---- | ---- | ---- | -------- |
| B    | 4    | 12   | 16   | A        |
| C    | 3    | 11   | 14   | A        |
| D    | 10   | 6    | 16   | C        |
| E    | 13   | 4    | 17   | C        |

---

- Expand B (F=16)
- Examine E, F
- open = [D, E, F]; closed = [A, C, B]

| Node | G    | H    | F    | Previous |
| ---- | ---- | ---- | ---- | -------- |
| B    | 4    | 12   | 16   | A        |
| C    | 3    | 11   | 14   | A        |
| D    | 10   | 6    | 16   | C        |
| E    | 13   | 4    | 17   | C        |
| F    | 9    | 11   | 20   | B        |

---

- Expand D (F=16)
- Examine E
- open = [E, F]; closed = [A, C, B, D]

| Node | G    | H    | F    | Previous |
| ---- | ---- | ---- | ---- | -------- |
| B    | 4    | 12   | 16   | A        |
| C    | 3    | 11   | 14   | A        |
| D    | 10   | 6    | 16   | C        |
| E    | 12   | 4    | 16   | D        |
| F    | 9    | 11   | 20   | B        |

---

- Expand E (F=16)
- Examine Z
- open = [F, Z]; closed = [A, C, B, D, E]

| Node | G    | H    | F    | Previous |
| ---- | ---- | ---- | ---- | -------- |
| B    | 4    | 12   | 16   | A        |
| C    | 3    | 11   | 14   | A        |
| D    | 10   | 6    | 16   | C        |
| E    | 12   | 4    | 16   | D        |
| F    | 9    | 11   | 20   | B        |
| Z    | 17   | 0    | 17   | E        |

---

- Shortest path: A -> C -> D -> E -> Z; Cost: 17
