"""
inherit **kwargs from another fucntion in the signature. 
"""


__version__ = '0.0.2'

import inspect


def inherit(target):

    def decorate(function):
        sig =  inspect.signature(target)
        parameters = sig.parameters
        
        current_sig = inspect.signature(function)
        current_params = [(k,v) for k,v in current_sig.parameters.items()]
        if current_params[-1][1].kind == inspect.Parameter.VAR_KEYWORD:
            del current_params[-1]
            current_params.extend([(k,v) for k,v in parameters.items()])
        new_sig = inspect.Signature([v for k,v in current_params])
        function.__signature__ = new_sig
        return function

    return decorate
