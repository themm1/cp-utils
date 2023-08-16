import random
from pprint import pprint
from typing import Dict, List, Set, Tuple


def rand_tree(N: int, directed: bool = False) -> Dict[int, Set[int]]:
    """
    Generates random tree with N nodes.

    :param N: Number of nodes in the tree.
    :param directed: Whether the tree should have directed edges (note that
        tree with directed edges is just DAG with N nodes and N - 1 edges),
        defaults to False.
    :return: Generated tree represented as graph adjacency list.
    """
    prufer_sequence = [random.randint(1, N) for _ in  range(N - 2)]
    degrees_needed = {v: 1 for v in range(1, N + 1)}
    for v in prufer_sequence:
        degrees_needed[v] += 1
    g = {v: set() for v in range(1, N + 1)}
    
    # creates tree according to generated prufer sequence
    ones = [v for v in range(1, N + 1) if degrees_needed[v] == 1]
    for v in prufer_sequence:
        u = ones.pop()
        _add_edge(g, u, v, directed)
        degrees_needed[u] -= 1
        degrees_needed[v] -= 1
        if degrees_needed[v] == 1:
            ones.append(v)
            
    # adds last edge
    _add_edge(g, ones[0], ones[1], directed)
    return g
    
def rand_simple_graph(N: int, M: int, directed: bool = False) -> Dict[int, Set[int]]:
    """
    Generates radnom simple (no self loops and no double edges) connected graph.

    :param N: Number of nodes in the graph.
    :param M: Number of edges in the graph.
    :param directed: Whether the graph should be directed, default to False.
    :return: Generated graph represented as adjacency list.
    """
    max_edges = (N * (N - 1)) // 2 if not directed else N * (N - 1)
    if M > max_edges or M < N - 1:
        raise ValueError(f"Invalid number of edges. Choose M from {N - 1} to" +
            f" {max_edges} for N = {N} for this graph.")

    # create an MST for our graph
    g = rand_tree(N, directed)
    edges_to_add = M - (N - 1)
    edges_to_ban = max_edges - (edges_to_add + N - 1)

    # it's faster to ban edges randomly and create dense graph then from the
    # ones that weren't banned
    if edges_to_add > edges_to_ban:
        banned_edges = set()
        while (directed and len(banned_edges) < edges_to_ban) or \
                (not directed and len(banned_edges) // 2 < edges_to_ban):
            u = random.randint(1, N)
            v = random.randint(1, N)
            if u != v and v not in g[u] and (directed or u not in g[v]):
                banned_edges.add((u, v))
                if not directed:
                    banned_edges.add((v, u))
        for v in range(1, N + 1):
            for u in range(1, N + 1):
                if u != v and (u, v) not in banned_edges and v not in g[u]:
                    _add_edge(g, u, v, directed)
    # it's faster to create the wanted graph by trying to randomly add edges
    else:
        edges_cnt = N - 1
        while edges_cnt < M:
            u = random.randint(1, N)
            v = random.randint(1, N)
            if u != v and v not in g[u]:
                _add_edge(g, u, v, directed)
                edges_cnt += 1
    return g

def rand_array(N: int, min_a: int, max_a: int, repetitions: bool = True) -> List[int]:
    """
    Generates an array of random integers.

    :param N: Length of the array.
    :param min_a: Minimum element value.
    :param max_a: Maximum element value.
    :param repetitions: Whether element repetitions are allowed, defaults to True.
    :return: Generated random array.
    """
    if not repetitions and max_a - min_a + 1 < N:
        raise ValueError(f"Can't generate array without repetitions of length" +
            f" N = {N}, min_a = {min_a} and max_a = {max_a}.")
    elements_to_ban = max_a - min_a + 1 - N
    l = []
    # it's faster to ban some elements and create list without repetitions randomly
    # by shuffling the rest
    if not repetitions and elements_to_ban < N:
        banned_elements = set()
        while len(banned_elements) < elements_to_ban:
            a = random.randint(min_a, max_a)
            if a not in banned_elements:
                banned_elements.add(a)
        for a in range(min_a, max_a + 1):
            if a not in banned_elements:
                l.append(a)
        random.shuffle(l)
    # create random array by adding elements randomly
    else:
        used = set()
        while len(l) < N:
            a = random.randint(min_a, max_a)
            if repetitions:
                l.append(a)
            elif a not in used:
                l.append(a)
                used.add(a)
    return l
    
def rand_permutation(N: int) -> List[int]:
    """
    Generates random permutation (array of length N with every element from 1
    to N occuring exactly once).

    :param N: Length of the permutation.
    :return: Generated permutation.
    """
    l = list(range(1, N + 1))
    random.shuffle(l)
    return l

def rand_array_of_pairs(N: int, min_x: int, max_x, min_y: int, max_y: int,
        distinct: bool = True, second_greater: bool = False) -> List[Tuple[int, int]]:
    """
    Generates N random pairs of integers.

    :param N: Number of pairs.
    :param min_x: Minimum first value of a pair.
    :param max_x: Maximum first value of a pair.
    :param min_y: Minimum second value of a pair.
    :param max_y: Maximum second value of a pair.
    :param distinct: Whether the pairs have to be be pairwise distinct, default to True.
    :param second_greater: Whether second element in the pair should be greater than first.
    :return: Generated pairs.
    """
    if second_greater and max_y < min_x:
        raise ValueError("Can't satisfy second_greater, when max_y < min_x.")
    pairs = []
    used = set()
    while len(pairs) < N:
        x = random.randint(min_x, max_x)
        if second_greater and x + 1 > max_y:
            continue
        if second_greater:
            y = random.randint(max(x + 1, min_y), max_y)
        else:
            y = random.randint(min_y, max_y)
        pair = (x, y)
        if not distinct or pair not in used:
            pairs.append(pair)
            used.add(pair)
    return pairs

def rand_string(N: int, min_char: str = "a", max_char: str = "z",
        alphabet: str = None) -> str:
    """
    Generates random string using ASCII characters in range [min_char, max_char].

    :param N: Length of the string.
    :param min_char: First allowed character, defaults to "a"
    :param max_char: Last allowed character, defaults to "z"
    :param alphabet: Alphabet to choose characters from, given as a string.
        When set, min_char and max_char are ignored, defaults to None.
    :return: Generated string.
    """
    alph_list = [c for c in alphabet] if alphabet else []
    l = []
    for _ in range(N):
        if alph_list:
            rand_char_code = ord(random.choice(alph_list))
        else:
            rand_char_code = random.randint(ord(min_char), ord(max_char))
        l.append(chr(rand_char_code))
    return "".join(l)

def print_graph_edges(g: Dict[int, Set[int]], directed: bool = False,
        add_weights: bool = False, min_weight: int = 1, max_weight: int = 10,
        shuffle: bool = False):
    """
    Prints edges of given graph.

    :param g: Graph to print edges from.
    :param directed: Whether the graph is directed, defaults to False.
    :param add_weights: Whether to print random weight for every edge, defaults to False.
    :param min_weight: Minimum weight, defaults to 1.
    :param max_weight: Maximum weight, defaults to 10.
    :param shuffle: Whether edges should be printed in random order, defaults to False.
    """
    edges = []
    for v in g:
        for u in g[v]:
            if directed or u <= v:
                edges.append((u, v))
    if shuffle:
        random.shuffle(edges)
    for edge in edges:
        print(edge[0], edge[1], end = "")
        if add_weights:
            print(" " + str(random.randint(min_weight, max_weight)))
        else:
            print()
                    
def _add_edge(g: Dict[int, Set[int]], u: int, v: int, directed: bool = False):
    """
    Add edge to g.

    :param g: Graph to add edge to.
    :param u: First node.
    :param v: Second node.
    :param directed: If True, creates edge only from u to v, defaults to False. 
    """
    g[u].add(v)
    if not directed:
        g[v].add(u)
        