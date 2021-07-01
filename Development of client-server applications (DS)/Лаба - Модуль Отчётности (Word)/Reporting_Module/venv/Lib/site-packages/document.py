""" Document

Simple document wrapper
"""

from __future__ import unicode_literals, print_function

__all__ = ['set_recursive', 'get_recursive', 'del_recursive',
           'encode_dict_keys', 'Document']

__version__ = '1.0'
__author__ = 'Branko Vukelic <branko@brankovukelic.com>'


def set_recursive(d, names, v):
    """ Recursively set dictionary keys so that final leaf is ``v``

    The ``names`` argument should be a list of keys from top level to bottom.

    Example::

        >>> d = {}
        >>> set_recursive(d, ['foo', 'bar', 'baz'], 12)
        >>> d
        {u'foo': {u'bar': {u'baz': 12}}}

    """
    n = names.pop(0)
    if not names:
        d[n] = v
        return d
    if not n in d:
        d[n] = {}
    set_recursive(d[n], names, v)


def get_recursive(d, names):
    """ Recursively get dictionary keys

    The ``names`` argument should be a list of keys from top level to bottom.

    Example::

        >>> get_recursive({'foo': 'bar', 'baz': {'fam': 12}}, ['baz', 'fam'])
        12

    """
    n = names.pop(0)
    if not names:
        return d[n]
    return get_recursive(d[n], names)


def del_recursive(d, names):
    """ Recursively find the leaf in nested dicts and delete it

    The ``names`` argument should be a list of keys from top level to bottom.

    Example::

        >>> d = {'foo': {'bar': 'baz', 'baz': 12}}
        >>> del_recursive(d, ['foo', 'baz'])
        >>> d
        {u'foo': {u'bar': u'baz'}}

    If any of the keys involved in the deletion is missing a ``KeyError`` is
    raised. This applies equally to leaf keys and intermediate keys. For
    instance::

        >>> d = {'foo': {'bar': {'baz': 12}}}
        >>> del_recursive(d, ['foo', 'fam', 'baz'])
        Traceback (most recent call last):
        ....
        KeyError: u'fam'
        >>> del_recursive(d, ['bar', 'baz'])
        Traceback (most recent call last):
        ....
        KeyError: u'bar'

    """
    n = names.pop(0)
    if not names:
        del d[n]
        return
    del_recursive(d[n], names)


def encode_dict_keys(d, encoding='utf-8'):
    """ Recursively encode all dictionary keys to specified encoding

    This function will go through all keys in the specified dict, as well as
    any nested dicts, and replace unicode keys with bytestring version encoded
    with the given encoding (default is UTF8).

    The function creates a copy of any dicts, so they are not modified
    directly. Lists and any other container types or mutable objects passed by
    reference are not copied but not touched either.

    Example::

        >>> d1 = {u'foo': 12, u'bar': 10}
        >>> for key in d1.iterkeys():
        ...    print(type(key))
        <type 'unicode'>
        <type 'unicode'>
        >>> d2 = encode_dict_keys(d1)
        >>> for key in d2.iterkeys():
        ...    print(type(key))
        <type 'str'>
        <type 'str'>

    """
    if type(d) != dict:
        raise ValueError('First argument must be a dict, got %s' % type(d))
    d = d.copy()
    for key, value in d.iteritems():
        if type(value) == dict:
            value = encode_dict_keys(value, encoding)
        if type(key) == unicode:
            key = key.encode(encoding, 'replace')
        del d[key]
        d[key] = value
    return d


class Document(object):
    """ Very lightweight document wrapper

    Working with dicts and PyMongo is pretty awesome. But then again, dicts are
    a bit underpowered in some scenarios. Full ORM has a steep learning curve,
    and, besides, we haven't given up on the idea that working with dicts is
    pretty awesome. Therefore, we've invented this little wrapper that makes
    our pains go away, and lets us keep working with dicts... sort of.

    Before we go on to discuss the fun part (the API), let me point out briefly
    what this class is **not**. This class is not a model or ORM or anything of
    the sort. For most part it behaves like a plain dict, with a hint of
    ``object``. It doesn't do data validation, saving and retrieving documents
    from the collections, and similar operations. In fact, it can be used
    without a PyMongo. Now that that's out of the way, let's move on to fun
    bits.

    The constructor takes key-value pairs and keeps them stored in a dict
    internally. You can access all dictionary keys as object attributes::

        >>> d = Document(foo='bar')
        >>> d.foo
        u'bar'

    If you wish to create a document from a dict, you can simply create it with
    no arguments, and use the familiar ``update()`` method::

        >>> d = Document()
        >>> d.update({'foo': 'bar'})

    A shortcut for this is the ``from_dict()`` class method.
    ::
        >>> d = Document.from_dict({'foo': 'bar'})

    You can also resort to ``**`` magic if you wish.
    ::
        >>> d = Document(**{'foo': 'bar'})

    You can also assign directly to properties::

        >>> d.bar = 'foo'
        >>> d.bar
        u'foo'

    To retrieve the underlying dict, call the ``to_dict()`` method::

        >>> d.to_dict()
        {u'foo': u'bar', 'bar': u'foo'}

    When converting the document to a plain dict, it may sometimes be useful to
    encode the unicode keys to bytestring versions. For instance, Memcache may
    require this. The ``to_dict()`` method takes an optional ``encode_keys``
    argument (defaults ``None``: no encoding) which you can use to specify the
    desired encoding.

        >>> d.to_dict(encode_keys='utf-8')
        {'foo': u'bar', 'bar': u'foo'}

    Notice that the key 'foo' is now a bytestring unlike in the previous
    example.

    The document object iself has a neat string representation useful for
    debugging purposes.

        >>> d
        Document <{u'foo': u'bar', 'bar': u'foo'}>

    The reason we use this type of wrapper is that it allows us to separate the
    data from attributes defined directly on the classes. For example::

        >>> class FooDoc(Document):
        ...     foo = 12

        >>> f = FooDoc(bar='foo')
        >>> f.foo
        12
        >>> f.bar
        u'foo'
        >>> f
        FooDoc <{'bar': u'foo'}>

    Because of the duality of attributes and document keys, the ``hasattr()``
    call will return ``True`` for both attributes and document keys::

        >>> hasattr(f, 'foo')
        True
        >>> hasattr(f, 'bar')
        True

    As you can see from the last line in the example, only the ``bar`` key is
    considered part of the document.

    Apart from attribute access, you can also use the dict-like indexing.
    ::
        >>> d = Document(foo='bar')
        >>> d['foo']
        u'bar'

    Unlike normal dicts, however, it is possible to get nested dictionaries
    using dot-separated key names::

        >>> d = Document(foo={'bar': 'baz'})
        >>> d['foo.bar']
        u'baz'

    This also works with the ``get()`` method::

        >>> d.get('foo.bar')
        u'baz'
        >>> d.get('foo.baz', 'not there')
        u'not there'

    The dot-separated key names also work when setting values, and any missing
    intermediate keys are created automatically::

        >>> d['foo.baz'] = 12
        >>> 'baz' in d.to_dict()['foo']
        True
        >>> d['foo']
        {u'baz': 12, u'bar': u'baz'}

    Testing if the document contains a key is as straightforward as with
    regular dicts:

        >>> 'foo' in d
        True

    Furthermore, this test also works with nested structures.

        >>> d = Document(foo={'bar': 'baz', 'baz': 12}, bar=12)
        >>> 'foo.baz' in d
        True
        >>> 'foo.bogus' in d
        False


    When deleting keys from the document, you can use the ``del`` keyword as
    usual with both dot-separated and normal keys::

        >>> d = Document(foo={'bar': 'baz', 'baz': 12}, bar=12)
        >>> del d['foo.bar']
        >>> d
        Document <{'foo': {u'baz': 12}, 'bar': 12}>
        >>> del d['bar']
        >>> d
        Document <{'foo': {u'baz': 12}}>

    For removing top-level keys, you can use attribute access as well::

        >>> del d.foo
        >>> d
        Document <{}>

    It should be noted here that deleting using attribute access will raise a
    ``KeyError`` instead of ``AttributeError`` if the attribute is missing,
    since we are essentially deleting a key rather than a proper attribute.

        >>> del d.bar
        Traceback (most recent call last):
        ....
        KeyError: 'bar'

    Also note that you cannot delete non-document attribute defined elsewhere
    in the class. Using the previously defined ``FooDoc`` class which has
    custom ``foo`` attribute, we get a key error trying to delete it::

        >>> f = FooDoc(bar='foo')
        >>> del f.foo
        Traceback (most recent call last):
        ....
        KeyError: 'foo'

    Finally, a note about attribute precedence. When using attribute access,
    getting an attribute value always returns the attributes defined on the
    class and falls back on the document keys. The same applies to setting
    attribute values. When using key access instead, only the document keys are
    taken into consideration.
    ::
        >>> f = FooDoc(foo=2)
        >>> f.foo
        12
        >>> f['foo']
        2
        >>> f.foo = None
        >>> f['foo']
        2

    You can think of extra attributes as of something like meta data for the
    document (which is the original motivation for developing this wrapper).

    When two documents are compared, only the document part are compared, and
    not the other attribute. As mentioned before, the extra attributes are
    treated as metadata, so they are not considered when testing for equality.
    Here is an example::

        >>> f1 = FooDoc(bar=2)
        >>> f2 = FooDoc(bar=2)
        >>> f1.foo = True
        >>> f2.foo = False
        >>> f1 == f2
        True

    Now if we modify one of the documents, equality will fail::

        >>> f2.bar = 3
        >>> f1 == f2
        False

    You can update the document values with a dict by using the ``update()``
    method just like in regular Python dicts::

        >>> d = Document(foo=1, bar=2)
        >>> d.update({'foo': 2, 'bar': 1})
        >>> d
        Document <{'foo': 2, 'bar': 1}>

    Popping values from the document works just like the dict's ``pop()``
    method::

        >>> d = Document(foo=1, bar=2)
        >>> d.pop('foo')
        1
        >>> d
        Document <{'bar': 2}>

    To get a subset of keys there is a `slice()` method. Since this class is
    meant to be used with MongoDB and PyMongo (although it doesn't have to be),
    slicing can be very useful in building subsets for use in querying.

    The ``slice()`` method accepts one or more keys as its arguments. Each key
    must be a top-level key (for now). It returns a dictionary containing the
    key-value mappings.
    ::
        >>> d = Document(foo=1, bar=2, baz=3)
        >>> d.slice('foo')
        {u'foo': 1}
        >>> d.slice('foo', 'baz')
        {u'foo': 1, u'baz': 3}

    Keys that do not exist in the document will be mapped to ``None``::

        >>> d.slice('bogus')
        {u'bogus': None}

    Calling it with no arguments will return an empty dict.

        >>> d.slice()
        {}

    """


    _document = {}

    def __init__(self, **kwargs):
        self._document = kwargs

    def __getattr__(self, name):
        """ Falling back on document keys """
        if name in ['iter', 'has_key', 'items', 'iteritems', 'iterkeys',
                    'itervalues', 'keys', 'pop', 'popitem', 'setdefault',
                    'update', 'values', 'viewitems', 'viewkeys', 'viewvalues']:
            return getattr(self._document, name)
        return self._document[name]

    def __setattr__(self, name, value):
        try:
            object.__getattribute__(self, name)
            object.__setattr__(self, name, value)
        except AttributeError:
            self._document[name] = value

    def __delattr__(self, name):
        del self._document[name]

    def __getitem__(self, key):
        return get_recursive(self._document, key.split('.'))

    def __setitem__(self, key, value):
        set_recursive(self._document, key.split('.'), value)

    def __delitem__(self, key):
        del_recursive(self._document, key.split('.'))

    def __contains__(self, key):
        try:
            get_recursive(self._document, key.split('.'))
            return True
        except KeyError:
            return False

    def __eq__(self, other):
        return self._document == other._document

    def __repr__(self):
        return '%s <%s>' % (self.__class__.__name__, self._document)

    def get(self, key, default=None):
        """ Return the value of specified key falling back on default value """
        try:
            return get_recursive(self._document, key.split('.'))
        except KeyError:
            return default

    def slice(self, *keys):
        """ Return portions of the document that match the specified keys """
        return {key: self._document.get(key) for key in keys}

    def to_dict(self, encode_keys=None):
        """ Return a copy of the document """
        document = self._document.copy()
        if encode_keys is None:
            return document
        return encode_dict_keys(document, encoding=encode_keys)

    @classmethod
    def from_dict(cls, other):
        document = cls()
        document.update(other)
        return document


if __name__ == "__main__":
    import doctest
    doctest.testmod()
