from igraph import Graph
from igraph import VertexSeq
from igraph import Vertex

if __name__ == "__main__":
    u2t = {
        'A': 'ALA', 'R': 'ARG', 'N': 'ASN', 'D': 'ASP', 'C': 'CYS', 'E': 'GLU',
        'Q': 'GLN', 'G': 'GLY', 'H': 'HIS', 'I': 'ILE', 'L': 'LEU', 'K': 'LYS',
        'M': 'MET', 'F': 'PHE', 'P': 'PRO', 'S': 'SER', 'T': 'THR', 'W': 'TRP',
        'Y': 'TYR', 'V': 'VAL'
    }

    # Residuos em que ocorreram as mutacoes
    residues = ['T45', 'F115', 'K155', 'T113', 'G118', 'S71', 'K89', 'D105', 'K135', 'N214',
    'Q119', 'V80', 'S216', 'E153', 'L68', 'Y49', 'V51', 'L140', 'L175', 'K107', 'K200', 'T159',
    'K56', 'Q18', 'K224', 'N78', 'D181', 'N148', 'E204', 'C41', 'F108', 'D111', 'H103', 'K196',
    'G215', 'S188', 'K114', 'S52', 'K69', 'G122', 'Q58', 'S50', 'L147', 'G198', 'Q82', 'S203',
    'T60', 'E144', 'S195', 'A66']

    import sys
    args = sys.argv

    if len(args) == 1:
        print "Uso: python analysis.py <cutoff>"
        sys.exit(1)

    cutoff = args[1]

    if cutoff not in ['5', '7', '9']:
        print "Erro. Escolha 5, 7 ou 9 para o cutoff"
        sys.exit(1)

    print "cutoff = " + cutoff
    print "residuo,grau,betweenness,closeness"

    f = open("graphs/2YPIA_" + cutoff + ".net")
    graph = Graph.Read_Pajek(f)
    v = VertexSeq(graph)

    for r in residues:
        u = r[0]
        n = int(r[1:])

        if (n > 156): n -= 1
        if (n > 225): n -= 3
        id = "%s%d" % (u2t[u], n)

        vx = v.find(id=id)
        #print id, vx.degree(), vx.betweenness(), vx.closeness()
        print "%s,%d,%.5f,%.5f" % (id, vx.degree(), vx.betweenness(), vx.closeness())

    f.close()
