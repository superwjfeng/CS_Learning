
;; Function main (main, funcdef_no=23, decl_uid=2952, cgraph_uid=24, symbol_order=23)

int main ()
{
  int two;
  int data;
  int D.2958;
  struct .omp_data_s.0 .omp_data_o.1;

  data = 100;
  two = -100;
  printf ("start\n");
  .omp_data_o.1.two = two;
  .omp_data_o.1.data = data;
  #pragma omp parallel firstprivate(two) firstprivate(data) default(none) num_threads(4) [child fn: main._omp_fn.0 (.omp_data_o.1)]
  .omp_data_i = (struct .omp_data_s.0 & restrict) &.omp_data_o.1;
  two = .omp_data_i->two;
  data = .omp_data_i->data;
  D.2957 = omp_get_thread_num ();
  printf ("tid = %d data = %d two = %d\n", D.2957, data, two);
  #pragma omp return
  .omp_data_o.1 = {CLOBBER};
  printf ("finished\n");
  D.2958 = 0;
  goto <D.2968>;
  D.2958 = 0;
  goto <D.2968>;
  <D.2968>:
  return D.2958;
}



;; Function printf (<unset-asm-name>, funcdef_no=15, decl_uid=964, cgraph_uid=16, symbol_order=15)

__attribute__((artificial, gnu_inline, always_inline))
__attribute__((nonnull (1), format (printf, 1, 2)))
int printf (const char * restrict __fmt)
{
  int D.2972;

  D.2972 = __printf_chk (1, __fmt, __builtin_va_arg_pack ());
  goto <D.2973>;
  <D.2973>:
  return D.2972;
}


