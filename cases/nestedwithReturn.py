def f():
    return 7 * 2


def g():
    print 15
    x = 12

    def h():
        return x
    print h()
    return x * 2


print f()
print g()
