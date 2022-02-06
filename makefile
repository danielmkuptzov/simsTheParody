CC=gcc
OBJS=body.o
EXEC=danielCity
DEBUG=#for debugging delete the line from the = to here -g
CFLAGS=-std=c99 Wall- Werror- $(DEBUG)
$(EXEC) : $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $@

body.o: main_test_block.c Person.h Kernel.h kernel.o
kernel.o:person.o kernelUnit.o orderProduct.o rational.o outerCore.o
person.o: Person.h Kernel/Person.c kernel.o Kernel/OrderProduct.h Kernel/Rational.h Kernel/outerCore.h
kernelUnit.o: Kernel.h Kernel/Kernel.c Kernel/OrderProduct.h Kernel/Rational.h Kernel/outerCore.h Kernel/Product.h kernelBase.o
kernelBase.o: orderProduct.o rational.o product.o outerCore.o
orderProduct.o: Kernel/OrderProduct.h Kernel/OrderProduct.c
rational.o: Kernel/Rational.h Kernel/Rational.c
product.o: Kernel/Product.h Kernel/outerCore/Product.c Kernel/outerCore.h
outerCore.o: Kernel/outerCore/outerCore.c Kernel/outerCore/Date.h date.o Kernel/outerCore/AmountSet.h core.o
date.o: Kernel/outerCore/Date.h Kernel/outerCore/Date.c
core.o:Kernel/outerCore/AmountSet.h Kernel/outerCore/core/AmountSet.c Kernel/outerCore/core/set.h set.o
set.o: Kernel/outerCore/core/set.h Kernel/outerCore/core/set.c Kernel/outerCore/core/List.h list.o
list.o: Kernel/outerCore/core/List.h Kernel/outerCore/core/List.c