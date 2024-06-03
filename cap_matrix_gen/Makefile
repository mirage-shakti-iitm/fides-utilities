.phony: install_cap_matrix_generator clean

cap_matrix_generator::
	g++ cap_matrix_generator.cc -o cap_matrix_generator

install_cap_matrix_generator: cap_matrix_generator
	mkdir -p $(FIDES_UTILITIES)
	mkdir -p $(FIDES_UTILITIES)/bin
	cp cap_matrix_generator $(FIDES_UTILITIES)/bin

clean:
	rm $(FIDES_UTILITIES)/bin/cap_matrix_generator