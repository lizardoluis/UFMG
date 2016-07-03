class Mutation:
    def __init__(self, seq, amino1, amino2):
        self.s = seq
        self.a1 = amino1
        self.a2 = amino2
        if self.a1 == '-': self.t = 'ADD'
        elif self.a2 == '-': self.t = 'DEL'
        else: self.t = 'MUT'

    def __str__(self):
        if self.t == "MUT": return "(%d) %s: %s -> %s" % (self.s, self.t, self.a1, self.a2)
        if self.a1 == '-': amino = self.a2
        else: amino = self.a1
        return "(%d) %s: %s" % (self.s, self.t, amino)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, other):
        return self.s == other.s and self.t == other.t and self.a1 == other.a1 and self.a2 == other.a2

    def __hash__(self):
        return hash("%s%s%s%s" % (self.s, self.t, self.a1, self.a2))

    def is_conservative(self):
        if self.t == 'ADD' or self.t == 'DEL': return False

        groups = [['H', 'K', 'R'], ['D', 'E'], ['N', 'Q', 'S', 'T'], ['A', 'G', 'I', 'L', 'M', 'V'], ['F', 'P', 'W', 'Y'], ['C']]
        m = {}

        for g in groups:
            for r in g:
                m[r] = g

        return self.a2 in m[self.a1]

    def is_change(self):
        return self.t == "MUT"
