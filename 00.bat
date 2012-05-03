for %%c in (makefile*) do nmake -f %%c %1

del test.bin

rename *.mod test.bin
copy test.bin H:\apple\test\
