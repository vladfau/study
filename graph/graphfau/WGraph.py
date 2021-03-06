"""
    Undirected weighted graph
"""

import copy


class WGraph:
    def __init__(self, vertices, adj_list):
        self.vertices = vertices  # set
        self.adj = adj_list
        self.gen_connections()  # list of tuples
        self.gen_adj_list_undir()  # map int-set of ints

    def __str__(self):
        return 'Graph:\nnot directed\nweighted\nVertices: %s\n' \
               'Adjcency map:\n%s\n' \
               'All connections:\n%s\n' % \
               (' '.join([str(x) for x in self.vertices]),
                '\n'.join(['%s: %s' % (v,
                                       ' '.join([str(x) for x in self.adj[v]]))
                          for v in self.adj]), self.connections)

    def __deepcopy__(self, memo):
        dup = WGraph(copy.deepcopy(self.vertices),
                     copy.deepcopy(self.adj))
        dup.gen_connections()
        return dup

    def type_check(self, v):
        return v if type(v) is int else int(v)

    def add_vertex(self, vertex):
        vertex = self.type_check(vertex)
        if vertex in self.vertices:
            raise Exception('Vertex %d already exists' % vertex)
        self.vertices.add(vertex)
        self.adj[vertex] = set()

    def add_edge(self, vfrom, vto, weight):
        vfrom = self.type_check(vfrom)
        vto = self.type_check(vto)

        if vfrom not in self.vertices:
            raise Exception('Vertex to add arc FROM is not in graph')

        if vto not in self.vertices:
            raise Exception('Vertex to add arc TO is not in graph')

        self.adj[vfrom].add(vto)
        self.adj[vto].add(vfrom)
        self.connections.append([vto, vfrom, weight])
        self.connections.append([vfrom, vto, weight])

    def remove_vertex(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        for conn in self.get_connections(vertex):
            self.adj[conn[0]].remove(conn[1])
        self.vertices.remove(vertex)
        del self.adj[vertex]
        self.connections = [c for c in self.connections
                            if not (c[0] == vertex or c[1] == vertex)]

    def gen_connections(self):
        res = []
        for v in self.adj:
            for vv in self.adj[v]:
                res.append([v, vv[0], vv[1]])
                res.append([vv[0], v, vv[1]])
        self.connections = res

    def gen_adj_list_undir(self):
        self.adj = {}
        for v in self.vertices:
            self.adj[v] = set()
        for v in self.connections:
            self.adj[v[0]].add(v[1])

    def get_connections(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        return [v for v in self.connections if v[0] == vertex
                or v[1] == vertex]

    def get_unique_connections_from_vertex(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        unique_conns = []
        res = []
        for conn in self.connections:
            pair = (conn[0], conn[1])
            if pair not in unique_conns and \
               pair[::-1] not in unique_conns and \
               (pair[0] == vertex or pair[1] == vertex):
                unique_conns.append(pair)
                res.append(conn)
        return res

    def get_unique_connections(self):
        unq = []
        localunq = []
        for conn in self.connections:
            pair = (conn[0], conn[1])
            if pair not in localunq and pair[::-1] not in localunq:
                unq.append(conn)
                localunq.append(pair)
        return unq

    def get_connection_weight(self, vfrom, vto):
        vs = self.get_connections(vfrom)
        for v in vs:
            if v[1] == vto:
                return v[2]
        return -1

    def get_connected_vertices(self, vertex):
        vertex = self.type_check(vertex)
        if vertex not in self.vertices:
            raise Exception('Vertex %d not found' % vertex)
        res = set()
        for v in self.get_connections(vertex):
            res.add(v[0])
            res.add(v[1])
        if vertex in res and \
           (vertex, vertex) not in self.get_connections(vertex):
            res.remove(vertex)
        return res

    def degree(self, vertex):
        return len(self.adj[vertex])

    def get_edges(self):
        unique_conns = []
        for conn in self.connections:
            conn = (conn[0], conn[1])
            if conn not in unique_conns and \
               conn[::-1] not in unique_conns:
                unique_conns.append(conn)
        return unique_conns

    def get_w_edges(self):
        unique_conns = []
        ucw = []
        for conn in self.connections:
            pair = (conn[0], conn[1])
            if pair not in unique_conns and \
               pair[::-1] not in unique_conns:
                unique_conns.append(pair)
                ucw.append(conn)
        return ucw

    def count_edges(self):
        return len(self.get_edges())

    def count_vertices(self):
        return len(self.vertices)

    def count_arcs(self):
        return len(self.connections)

    def has_edge(self, vfrom, vto):
        conns = []
        for c in self.connections:
            conns.append((c[0], c[1]))
        return (vfrom, vto) in conns or (vto, vfrom) in conns
