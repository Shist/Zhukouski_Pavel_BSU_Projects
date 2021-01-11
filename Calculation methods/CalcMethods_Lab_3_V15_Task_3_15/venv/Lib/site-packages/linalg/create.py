from linalg.types import Matrix
import random

__all__ = ["zeroes", "identity", "random_matrix"]


def zeroes(i: int, j: int) -> Matrix:
    """creates an i by j zero matrix
    
    :param i: number of columns
    :type i: int
    :param j: number of rows
    :type j: int
    :return: an i by j matrix filled with zeroes
    :rtype: Matrix
    """
    return Matrix([[0] * j for _ in range(i)], valid=True)


def identity(n: int) -> Matrix:
    """generates an n by n identity matrix
    
    :param n: number of rows/columns
    :type n: int
    :return: n by b indentity matrix
    :rtype: Matrix
    """
    id = [[int(i == j) for j in range(n)] for i in range(n)]
    return Matrix(id)


def random_matrix(dim: tuple, rng: tuple, use_float: bool = False) -> Matrix:
    """generates a random matrix

    :param dim: dimensions of matrix
    :type dim: tuple
    :param rng: range of randomized elements
    :type rng: tuple
    :param float: whether to use floats for elements (default False)
    :type float: bool
    :return: randomized matrix of specified size and range
    :rtype: Matrix
    """
    ls = [[random.uniform(*rng) for _ in range(dim[1])] for _ in range(dim[0])]

    if not use_float:
        ls = [[round(x) for x in row] for row in ls]

    return Matrix(ls)
