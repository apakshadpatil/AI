from pyDatalog import pyDatalog

pyDatalog.clear()

pyDatalog.create_terms('bike, price, cheaper, is_cheaper, cheaper_than, costliest, cheapest, X, Y, P1, P2')

# Facts: bike(model, brand, price)
+bike('shine','honda',80000)
+bike('splendor','hero',75000)
+bike('pulsar','bajaj',95000)
+bike('fz','yamaha',110000)
+bike('royal_enfield','bullet',180000)

# Rules
price(X,P) <= bike(X,_,P)
cheaper(X,Y,X) <= price(X,P1) & price(Y,P2) & (P1<P2)
cheaper(X,Y,Y) <= price(X,P1) & price(Y,P2) & (P2=<P1)
is_cheaper(X,Y) <= price(X,P1) & price(Y,P2) & (P1<P2)
cheaper_than(A,X) <= price(X,P) & (P<A)
costliest(X) <= price(X,P) & ~(price(_,P2) & (P2>P))
cheapest(X) <= price(X,P) & ~(price(_,P2) & (P2<P))

# Example Queries
print(cheaper('pulsar','fz',X))
print(is_cheaper('splendor','shine'))
print(cheaper_than(100000,X))
print(costliest(X))
print(cheapest(X))
