PROVIDE(pc_base_255 = . );
*(".text.caml.255")
*(".text.caml.ocaml_runtime")
PROVIDE(pc_ocaml_end_255 = . );
*(".text.caml.c_runtime")
*(".text.c.255")
*(".text.trap_vector")
*(.text*)
PROVIDE(pc_bound_255 = . );
