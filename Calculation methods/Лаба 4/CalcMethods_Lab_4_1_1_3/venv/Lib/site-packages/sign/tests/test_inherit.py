from sign import inherit
import inspect


def foo(a=1, b=2):
    pass


@inherit(foo)
def bar(*args, **kwargs):
    return foo(*args, **kwargs)



def test_inherit():
    assert inspect.signature(foo) == inspect.signature(bar)
