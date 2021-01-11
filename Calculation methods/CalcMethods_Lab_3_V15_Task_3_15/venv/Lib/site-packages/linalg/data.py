from linalg.types import Matrix

__all__ = ["as_matrix", "as_list"]


def as_matrix(ls: list) -> Matrix:
    """
    Parses the input 2D list into a Matrix.
    Convenience top-level function for linalg.matrix.Matrix()

    :param ls: list to convert into matrix
    :type ls: list
    :return: Matrix represtation of ls
    :rtype: Matrix
    """
    return Matrix(ls)


def as_list(mat: Matrix) -> list:
    """
    Returns the matrix as a vanilla 2D list.
    
    :param mat: matrix to convert
    :type mat: Matrix
    :return: matrix as a 2d list
    :rtype: list
    """
    return mat.matrix
