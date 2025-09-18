from pyDatalog import pyDatalog

pyDatalog.clear()

pyDatalog.create_terms('calculate, Op, X, Y, R')

# Rules
calculate('add', X, Y, R) <= (R == X + Y)
calculate('sub', X, Y, R) <= (R == X - Y)
calculate('mul', X, Y, R) <= (R == X * Y)
calculate('div', X, Y, R) <= (Y != 0) & (R == X / Y)

# Example Queries
print(calculate('add', 10, 5, R))
print(calculate('sub', 20, 7, R))
print(calculate('mul', 6, 4, R))
print(calculate('div', 15, 3, R))
