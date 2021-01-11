from operator import add, neg
import linalg


__all__ = ["Matrix"]


class MatrixError(Exception):
    pass


class Matrix:
    """Implements Matrices.
    """

    def __init__(self, mat, valid=False):
        if not valid:
            try:
                self._is_valid(mat)
            except Exception as e:
                raise e

        self.shape = (len(mat), len(mat[0]))
        self.matrix = mat

    def _is_valid(self, mat):
        """checks if given matrix is valid

        :param mat: Matrix to test
        :type mat: Matrix
        :raises MatrixError: raises MatrixError
        """
        matlen = len(mat[0])
        for row in mat:
            if len(row) != matlen:
                raise MatrixError("Malformed matrix")
            for i in row:
                assert isinstance(i, (int, float, complex))

    def _is_square(self) -> bool:
        return self.shape[0] == self.shape[1]

    def inverse(self) -> "Matrix":
        """
        returns the inverse matrix of mat
        implemented as an alias of linalg.unary.inverse

        :param mat: the matrix to invert
        :type mat: Matrix
        :return: the inverse matrix of mat
        :rtype: Matrix
        """
        return linalg.unary.inverse(self)

    def transpose(self) -> "Matrix":
        """
        computes the transpose of self
        implemented as an alias of linalg.unary.transpose    

        :return: transposed matrix
        :rtype: Matrix
        """
        return linalg.unary.transpose(self)

    inv = inverse  # Alias for inverse
    T = transpose  # Alias for transpose

    def det(self) -> float:
        """
        computes the determinant for self.
        implemented as an alias of linalg.unary.det

        :return: the determinant for mat
        :rtype: float
        """

        return linalg.unary.det(self)

    def __str__(self):
        r = ""
        for i in range(self.shape[0]):
            r += "|"
            for j in range(self.shape[1]):
                r += "{:^6.5}".format(str(self[i][j]))
            r += "|"
            r += "\n"

        return r

    def __add__(self, x):
        return Matrix(
            list([list(map(add, self[i], x[i])) for i in range(self.shape[0])]),
            valid=True,
        )

    def __neg__(self):
        return Matrix(
            list([list(map(neg, self[i])) for i in range(self.shape[0])]), valid=True
        )

    def __sub__(self, x):
        return self.__add__(-x)

    def __matmul__(self, x: "Matrix"):
        result = Matrix(
            [
                [sum(a * b for a, b in zip(self_row, x_col)) for x_col in zip(*x)]
                for self_row in self
            ]
        )

        return result

    def __mul__(self, x: float):
        return Matrix([[a * x for a in row] for row in self])

    def __rmul__(self, x: float):
        return self.__mul__(x)

    def __getitem__(self, i):
        return self.matrix[i]

    def __setitem__(self, key, item):
        self.matrix[key] = item
