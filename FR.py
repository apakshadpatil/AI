from pyDatalog import pyDatalog

pyDatalog.clear()

# Define predicates
pyDatalog.create_terms('male, female, parent, father, mother, child, sibling, grandparent, grandfather, grandmother, uncle, aunt, X, Y, Z')

# ----- Facts -----
+male('john')
+male('peter')
+male('mike')
+male('sam')
+male('rahul')

+female('mary')
+female('linda')
+female('susan')
+female('anna')

+parent('john', 'peter')
+parent('john', 'linda')
+parent('mary', 'peter')
+parent('mary', 'linda')
+parent('peter', 'mike')
+parent('susan', 'mike')
+parent('linda', 'anna')
+parent('sam', 'anna')

# ----- Rules -----
father(X,Y) <= male(X) & parent(X,Y)
mother(X,Y) <= female(X) & parent(X,Y)
child(X,Y) <= parent(Y,X)
sibling(X,Y) <= parent(Z,X) & parent(Z,Y) & (X != Y)
grandparent(X,Y) <= parent(X,Z) & parent(Z,Y)
grandfather(X,Y) <= male(X) & grandparent(X,Y)
grandmother(X,Y) <= female(X) & grandparent(X,Y)
uncle(X,Y) <= male(X) & sibling(X,Z) & parent(Z,Y)
aunt(X,Y) <= female(X) & sibling(X,Z) & parent(Z,Y)

# Example Queries
print(father(X,'linda'))      # Who is father of Linda?
print(sibling('peter', Y))    # Peter's siblings
print(grandparent(X,'mike'))  # Mike's grandparents
