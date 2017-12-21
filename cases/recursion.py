def f(x):
    if x > 10:
        return
    else:
        f(x + 1)
    print x


f(1)
