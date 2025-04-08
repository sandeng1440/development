import sympy

R, x = sympy.symbols('R x')
equation = sympy.Eq(27*R, x**2 - 2*x + 1)
solutions = sympy.solve(equation, x)
print(solutions)
