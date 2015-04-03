"""
    Task 2.II.11 Get all out-connected vertices for the vertice
    Graph: directed, not weighted
"""

from graphfau.GraphGenerator import GraphGenerator as gg
from graphfau.Tasks import Tasks as ts
from graphfau.Algo import Algo
params = {'directed': True, 'weigthed': False}
adj_list = {1: [2, 3, 4], 2:[3], 3: [1]}
g = gg.create(params=params, adj_list=adj_list)

print g
print ts.circuit_rank(g)
