from linalg.types import Matrix
from linalg.create import identity
from linalg.solve import linsolve
from linalg.decompose import lu

__all__ = ["pivotize", "inverse", "det", "transpose", "T", "inv"]


def pivotize(mat: Matrix) -> (Matrix, int):
    """creates the pivoting matrix for mat

    :param mat: the matrix to perform the operation on
    :type mat: Matrix
    :return: the pivoting matrix for self and the number of permutations
    :rtype: Matrix, int
    """
    assert mat._is_square()
    n = mat.shape[0]
    S = 0
    a = identity(n)
    for j in range(n):
        row = max(range(j, n), key=lambda i: abs(mat[i][j]))
        if j != row:
            S += 1
            a[j], a[row] = a[row], a[j]

    return a, S


def inverse(mat: Matrix) -> Matrix:
    """returns the inverse matrix of mat
    
    :param mat: the matrix to invert
    :type mat: Matrix
    :return: the inverse matrix of mat
    :rtype: Matrix
    """
    assert mat._is_square()
    return linsolve(mat, identity(mat.shape[0]))


def det(mat: Matrix) -> float:
    """computes the determinant for a given matrix
    
    :param mat: matrix to compute the determinant for
    :type mat: Matrix
    :return: the determinant for mat
    :rtype: float
    """
    assert mat._is_square()

    L, U, P, S = lu(mat)
    n = mat.shape[0]
    l_pd, u_pd = 1, 1
    for i in range(n):
        l_pd *= L[i][i]
        u_pd *= U[i][i]
    return (-1) ** S * l_pd * u_pd


def transpose(mat: Matrix) -> Matrix:
    """
    computes the transpose of a given matrix
    
    :param mat: matrix to perform the operation on
    :type mat: Matrix
    :return: transposed matrix
    :rtype: Matrix
    """
    x, y = mat.shape
    return Matrix([[mat[a][b] for a in range(y)] for b in range(x)])


T = transpose  # Function alias
inv = inverse  # Function alias
