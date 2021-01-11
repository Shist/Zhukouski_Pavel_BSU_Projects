from linalg.types import Matrix
from linalg.create import zeroes
from linalg.decompose import lu

__all__ = ["linsolve"]


def linsolve(mat: Matrix, b: Matrix) -> Matrix:
    """solve a system of linear equations using LU decomposition
    
    :param mat: system of linear equations
    :type mat: Matrix
    :param b: column vector to solve for
    :type b: Matrix
    :return: the solution
    :rtype: Matrix
    """
    L, U, P, S = lu(mat)
    x, y = zeroes(*b.shape), zeroes(*b.shape)
    b = P @ b

    n = y.shape[0]

    for i in range(y.shape[1]):
        for j in range(n):  # solve Ly = Pb for y (forward substitution)
            y[j][i] = b[j][i]
            for k in range(j):
                y[j][i] -= L[j][k] * y[k][i]

        for j in range(n - 1, -1, -1):  # solve Ux = y for x (backward substitution)
            x[j][i] = y[j][i]
            for k in range(j + 1, n):
                x[j][i] -= U[j][k] * x[k][i]
            x[j][i] /= U[j][j]

    return x
