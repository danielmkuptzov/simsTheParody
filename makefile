CC=gcc
OBJS=body.o list.o set.o
EXEC=danielCity
DEBUG=#for debugging delete the line from the = to here -g
CFLAGS=-std=c99 Wall- Werror- $(DEBUG)
$(EXEC) : $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $@

set(COREPROJ Kernel/outerCore/core/AmountSet.c
             Kernel/outerCore/core/List.h
             Kernel/outerCore/core/List.c
             Kernel/outerCore/core/set.h
             Kernel/outerCore/core/set.c)

set(OUTERCORE Kernel/outerCore/outerCore.c
              Kernel/outerCore/AmountSet.h
              Kernel/outerCore/Date.c
              Kernel/outerCore/Date.h
              Kernel/outerCore/Product.c
              ${COREPROJ})
body.o: main_test_block.c Person.h Kernel.h kernel.o
kernel.o:person.o kernelUnit.o orderProduct.o rational.o
person.o: Person.h Kernel/Person.c kernel.o Kernel/OrderProduct.h Kernel/Rational.h Kernel/outerCore.h
kernelUnit.o: Kernel.h Kernel/Kernel.c Kernel/OrderProduct.h Kernel/Rational.h Kernel/outerCore.h Kernel/Product.h
orderProduct.o: Kernel/OrderProduct.h Kernel/OrderProduct.c
rational.o: Kernel/Rational.h Kernel/Rational.c
