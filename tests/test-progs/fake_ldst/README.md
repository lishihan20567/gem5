# fake_load/fake_store test

Build:

```bash
cd tests/test-progs/fake_ldst/src
make -f Makefile.riscv
# uses clang --target=riscv64-linux-gnu in this environment
```

Run example (SE mode):

```bash
build/RISCV/gem5.opt --debug-flags=LSQUnit \
  configs/example/se.py -c tests/test-progs/fake_ldst/src/fake_ldst
```

Expected log snippets include:

- `fake_store_buffer push ...`
- `fake_load inflight match ...`
- `fake_load matched fake_store_buffer ...`


If `riscv64-linux-gnu-gcc` is available, you may also switch CC in Makefile.
