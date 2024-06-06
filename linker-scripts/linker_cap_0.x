PROVIDE(pc_base_0 = . );
*(".text.caml.0")
PROVIDE(pc_ocaml_end_0 = . );
KEEP(*(.text.init))
*(".text.c.0")
PROVIDE(pc_bound_0 = . );
