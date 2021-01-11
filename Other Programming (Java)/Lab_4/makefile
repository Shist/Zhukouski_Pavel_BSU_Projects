# makefile Lab_4

.SUFFIXES: .class .java

TARG=test
JC=javac -g -encoding utf8
JM=java -ea -jar
JR=jar -cfe

OBJ=Polynom.class \
    PolynomialParser.class \
    test.class

.java.class:
	$(JC) $<

run: build
	$(JM) $(TARG).jar

build: 	$(OBJ)
	$(JR) $(TARG).jar test $(OBJ)

clean:
	for %%f in ($(OBJ)) do del %%f
	del $(TARG).jar

Polynom.class: Polynom.java makefile

PolynomialParser.class: PolynomialParser.java makefile

test.class: test.java makefile

# eof makefile Lab_4