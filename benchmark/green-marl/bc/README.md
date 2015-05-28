# without
run

```
bin/bc data/graphName.bin 8
```

explain

```
<program name> <graph name> <# of threads>
```

# Notice

When trying to run on large graph like 2^21 from the generator, you might see

```
graph loading time=749.682000
reverse edge creation time=0.000000
*** Error in `bin/bc': free(): invalid pointer: 0x00007f21c67205c0 ***
Aborted (core dumped)
```

This could be a bug in the current version of Green Marl [commit: 4c0d62e67d431d535ca27140df60b25c234a808b]
