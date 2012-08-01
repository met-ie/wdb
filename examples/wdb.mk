#-----------------------------------------------------------------------------
# WDB example programs
#-----------------------------------------------------------------------------

INSTALLTESTS += test_examples

examples/setupExamples.sh: examples/setupExamples.in.sh

test_examples: examples/setupExamples.sh examples wdbConfiguration
	@echo '#!/bin/sh' > $@.tmp
	@echo 'set -e' > $@.tmp
	@echo "./examples/setupExamples.sh" >> $@.tmp
	@for T in $(CPP_EXAMPLES); do echo "echo $$T && ./$$T \"\`./wdbConfiguration --pqxxArgs\`\" >> /dev/null" >> $@.tmp; done
	@for T in $(SQL_EXAMPLES); do echo "echo $$T && psql $(DATABASE_NAME) < $(top_srcdir)/$$T >> /dev/null" >> $@.tmp; done
	@echo "psql $(DATABASE_NAME) -c \"SELECT wci.begin('cleantest',999,999,999); SELECT cleanupdb()\" >> /dev/null" >> $@.tmp
	@mv $@.tmp $@
	@chmod 774 $@

examples:   			all_cpp_examples

EXTRA_DIST +=   		examples/setupExamples.in.sh \
						examples/wdb.mk \
		                examples/Makefile.am \
		                examples/Makefile.in

CLEANFILES += test_examples examples/setupExamples.sh
 

DISTCLEANFILES +=       examples/Makefile
                