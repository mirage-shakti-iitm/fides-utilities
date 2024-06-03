.phony: install_cap_matrix_generator clean

cap_matrix_generator::
	g++ cap_matrix_generator.cc -o cap_matrix_generator

install_cap_matrix_generator: cap_matrix_generator
	cp cap_matrix_generator $(SHAKTI_TEE_UTILITIES)/bin

clean:
	rm $(SHAKTI_TEE_UTILITIES)/bin/cap_matrix_generator