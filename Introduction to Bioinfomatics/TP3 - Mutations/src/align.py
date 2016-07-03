from Bio import SeqIO, pairwise2
from Bio.SubsMat import MatrixInfo
from Bio.Alphabet import generic_protein
from Bio.Seq import Seq
from Bio.SeqRecord import SeqRecord
from Bio.Align import MultipleSeqAlignment
from Mutation import Mutation
from Bio import SeqIO
from collections import Counter
import os

def exists_aligns():
    return os.path.exists("aligns")

def read_sequences():
    seq = []
    seq.append(SeqIO.read("2YPIA.fasta", "fasta"))
    seq.append(SeqIO.read("dTIM.fasta", "fasta"))
    for rec in SeqIO.parse("family.fasta", "fasta"): seq.append(rec)

    return seq

def read_aligns():
    (twoypi, dtim) = list(SeqIO.parse("aligns/dTIM.phy", "phylip"))
    alns = [MultipleSeqAlignment([twoypi, dtim])]
    files = os.listdir("aligns")
    files.remove("dTIM.phy")

    for f in files:
        (twoypi, p) = list(SeqIO.parse("aligns/" + f, "phylip"))
        alns.append(MultipleSeqAlignment([twoypi, p]))

    return alns

def get_align(seq1, seq2):
    matrix = MatrixInfo.pam60
    gap_open = -10
    gap_extend = -0.5

    #alns = pairwise2.align.globaldx(seq1.seq.tostring(), seq2.seq.tostring(), matrix)
    alns = pairwise2.align.globalds(seq1.seq.tostring(), seq2.seq.tostring(), matrix, gap_open, gap_extend)
    return alns[0]

def calc_aligns(sequences):
    twoypi = sequences[0]
    dtim = sequences[1]
    a = get_align(twoypi, dtim)
    t = SeqRecord(Seq(a[0], generic_protein), id=twoypi.id)
    r = SeqRecord(Seq(a[1], generic_protein), id=dtim.id)
    alns = [MultipleSeqAlignment([t, r])]

    for i in xrange(2, len(sequences)):
        s = sequences[i]
        a = get_align(twoypi, s)
        t = SeqRecord(Seq(a[0], generic_protein), id=twoypi.id)
        r = SeqRecord(Seq(a[1], generic_protein), id=s.id[:4])
        alns.append(MultipleSeqAlignment([t, r]))

    return alns

def write_aligns(aligns):
    if not os.path.exists("aligns"): os.makedirs("aligns")
    for a in aligns:
        f = open("aligns/" + a[1].id + ".phy", "w")
        f.write(a.format("phylip"))
        f.close()

def get_aligns():
    if not exists_aligns(): 
        sequences = read_sequences()
        alns = calc_aligns(sequences)
        write_aligns(alns)
    
    return read_aligns()

def get_mutations(align):
    pairs = [(i + 1, align[:, i]) for i in range(align.get_alignment_length())]
    diff = filter(lambda x: x[1][0] != x[1][1], pairs)
    return [Mutation(i[0], i[1][0], i[1][1]) for i in diff]

def get_possible_mutations(aligns):
    muts = get_mutations(aligns[0])
    muts = frozenset(muts)
    inter = []

    for a in aligns[1:]:
        m = get_mutations(a)
        inter += list(muts & frozenset(m))
        #print inter

    return (inter, list(muts - frozenset(inter)))

if __name__ == "__main__":
    aligns = get_aligns()
    (inter, muts) = get_possible_mutations(aligns)
    muts = filter(lambda x: not x.is_conservative() and x.is_change(), muts)
    print muts
