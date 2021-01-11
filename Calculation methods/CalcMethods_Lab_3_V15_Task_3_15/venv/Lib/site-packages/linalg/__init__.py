"""Main functions and classes"""


from . import create
from . import decompose
from . import solve
from . import unary
from . import data

from .types import Matrix
from .create import *
from .decompose import *
from .solve import *
from .unary import *
from .data import *

__all__ = ["Matrix"]
__all__.extend(create.__all__)
__all__.extend(decompose.__all__)
__all__.extend(solve.__all__)
__all__.extend(unary.__all__)
__all__.extend(data.__all__)