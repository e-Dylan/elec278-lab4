# Makefile for ELEC278 Lab 4
# Meant to be used with MSVC nmake command; may not work with Linux or
# other make commands.

all:	avl.exe

clean:
		del *.obj
		del *.exe
		del *.bak
		del *.map


avl.exe:	main.obj avl.obj
		cl /nologo /Feavl avl.obj main.obj

makerandom.exe:	makerandom.c

main.obj:	main.c avl.h

avl.obj:	avl.c. avl.h
