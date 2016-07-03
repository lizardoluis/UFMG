from tempfile import TemporaryFile
from Bio.PDB import PDBParser
from Bio.Alphabet import ThreeLetterProtein
from Point import Point
import gzip
import os

def create_file(name, tmp):
    gz = gzip.open(name, "rb")
    tmp.write(gz.read())
    tmp.seek(0)
    gz.close()

def get_structure(parser, tmp, id):
    s = parser.get_structure(id, tmp)
    tmp.truncate(0)
    return s

def get_chain(id, structure):
    return filter(lambda x: x.id.lower() == id[-1:].lower(), structure.get_chains())[0]

def read_proteins():
    parser = PDBParser(QUIET=True)
    tmp = TemporaryFile()
    f = open("idsFamily.txt", "r")
    ids = f.read().split()
    chains = []
    print "Lendo arquivos PDB..."

    for id in ids:
        create_file("pdb/" + id.lower() + ".gz", tmp)
        chain = get_chain(id, get_structure(parser, tmp, id.lower()))
        chains.append(chain)
        print "Proteina %s lida com sucesso!" % (id)

    f.close()
    tmp.close()
    return chains

def calc_distance(res1, res2):
    try:
        ca1 = filter(lambda x: x.get_id() == 'CA', list(res1.get_list()))[0]
        ca2 = filter(lambda x: x.get_id() == 'CA', list(res2.get_list()))[0]
    except IndexError: return 100.
    #print ca1.get_coord(), ca2.get_coord()
    p1 = Point(ca1.get_coord())
    p2 = Point(ca2.get_coord())
    return p1.distance(p2)

def get_contacts(protein, cutoff):
    letters = map(lambda x: x.upper(), ThreeLetterProtein.letters)
    residues = filter(lambda x: x.get_resname().upper() in letters, list(protein.get_residues()))
    i = 0
    contacts = []
    protein_id = protein.get_full_id()[0].upper()
    print "Iniciando calculo dos contatos para %s..." % (protein_id)

    while i < len(residues) - 1:
        j = i + 1
        while j < len(residues):
            d = calc_distance(residues[i], residues[j])
            if d <= cutoff:
                #print residues[i].get_resname(), residues[j].get_resname(), d
                contacts.append((residues[i], residues[j], d))
            j += 1
        i += 1

    print "Contatos da proteina %s calculados com sucesso!" % (protein_id)
    return contacts

def get_residue_id(residue):
    return "%s%d" % (residue.get_resname(), residue.get_id()[1])

def make_vertices(contacts):
    v1 = frozenset([get_residue_id(i[0]) for i in contacts])
    v2 = frozenset([get_residue_id(i[1]) for i in contacts])
    v = list(v1 | v2)
    return [(i + 1, v[i]) for i in range(len(v))]

def write_vertices(handle, vertices):
    handle.write("*Vertices %d\n" % len(vertices))
    for v in vertices: handle.write('%d "%s"\n' % (v[0], v[1]))

def write_edges(handle, contacts, vertices):
    m = {}
    for v in vertices: m[v[1]] = v[0]
    handle.write("*Edges\n")

    for c in contacts: 
        id1 = get_residue_id(c[0])
        id2 = get_residue_id(c[1])
        handle.write("%d %d %.3f\n" % (m[id1], m[id2], c[2]))

def write_contacts(contacts, cutoff):
    if not os.path.exists("graphs"):
        os.makedirs("graphs")

    name = "%s_%d" % (contacts[0][0].get_full_id()[0], int(cutoff))
    name = name.upper() + ".net"
    f = open("graphs/" + name, "w")
    v = make_vertices(contacts)
    write_vertices(f, v)
    write_edges(f, contacts, v)
    f.close()
    print "Arquivo %s gerado com sucesso!" % (name)

if __name__ == "__main__":
    proteins = read_proteins()
    print

    for cutoff in [5., 7., 9.]:
        print "Gerando contatos com cutoff %d..." % (int(cutoff))
        for p in proteins:
            contacts = get_contacts(p, cutoff)
            write_contacts(contacts, cutoff)
        print
