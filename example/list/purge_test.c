#include <cure/cure_list.h>

zListClass(int_list_t, int_list_cell_t, int);

int main(void)
{
  register int i;
  int_list_t list;
  int_list_cell_t *cp;

  printf( "+++ list test +++\n\n" );
  zListInit( &list );
  for( i=0; i<10; i++ ){
    if( !( cp = zAlloc( int_list_cell_t, 1 ) ) ){
      ZALLOCERROR( "int_list_cell" );
      exit( 1 );
    }
    cp->data = i;
    zListInsertTail( &list, cp );
  }

  while( !zListIsEmpty(&list) ){
    cp = zListHead( &list );
    zListPurge( &list, cp );
    printf( "value = %d\n", cp->data );
    zFree( cp );
  }
  zListWrite( (zList*)&list );
  zListDestroy( int_list_cell_t, &list );
  printf( "list test terminated.\n\n" );
  return 0;
}
