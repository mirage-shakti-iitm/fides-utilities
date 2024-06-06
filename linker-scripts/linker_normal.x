/* taken (and modified) from riscv-pk. See LICENSE.riscv-pk */

OUTPUT_ARCH( "riscv" )

ENTRY( reset_vector )

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text.caml.caml_hot__code_begin)
        KEEP(*(.text.init))
        *(.text*)
        *(.text.caml.caml_hot__code_end)
        *(.gnu.linkonce.t.*)
       
    }

  . = ALIGN(16);
/* rodata: Read-only data */
  .rodata :
  {
    PROVIDE( _srodata = . );
    *(.rdata)
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    PROVIDE( _erodata = . );
  }

  /*--------------------------------------------------------------------*/
  /* HTIF, isolated onto separate page                                  */
  /*--------------------------------------------------------------------*/
  . = ALIGN(0x1000);
  .htif :
  {
    PROVIDE( __htif_base = . );
    *(.htif)
  }
  . = ALIGN(0x1000);


  /*--------------------------------------------------------------------*/
  /* Initialized data segment                                           */
  /*--------------------------------------------------------------------*/

  /* Start of initialized data segment */
  . = ALIGN(16);
   _fdata = .;

  /* data: Writable data */
  .data :
  {
  *(.data)
  *(.data.*)
  *(.srodata*)
  *(.gnu.linkonce.d.*)
  *(.comment)
  }

  /* End of initialized data segment */
  PROVIDE( edata = . );
  _edata = .;

  /* Have _gp point to middle of sdata/sbss to maximize displacement range */
  . = ALIGN(16);
  _gp = . + 0x800;

    PROVIDE( start_sdata = . );
  /* Writable small data segment */
  .sdata :
  {
    *(.sdata)
    PROVIDE( _impure_ptr = . );
    _impure_ptr = .;
    *(.sdata.*)
    *(.srodata.*)
    *(.gnu.linkonce.s.*)
  }
  PROVIDE( end_sdata = . );


  /*--------------------------------------------------------------------*/
  /* Uninitialized data segment                                         */
  /*--------------------------------------------------------------------*/
    
  PROVIDE( start_uninitialized_data = . );

  /* Start of uninitialized data segment */
  . = ALIGN(8);
  _fbss = .;

  /* Writable uninitialized small data segment */
  .sbss :
  {
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
  }

  /* bss: Uninitialized writeable data section */
  . = .;
  _bss_start = .;
  .bss :
  {
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
  }
  _bss_end = .;
  _ebss = .;

  PROVIDE( end_uninitialized_data = . );

  PROVIDE( start_stack = .);
  . = ALIGN(16);
  .stack-reserved :
  { 
  }
  PROVIDE( end_stack = .);

  _end = ALIGN(8);
  /* End of uninitialized data segment
   * used for heap allocation
   */ 
  PROVIDE( __KERNEL_END = . );
  __KERNEL_END = .;
}
