/* CURE - Commonly-Used Routine Elements
 * Copyright (C) 1998 Tomomichi Sugihara (Zhidao)
 *
 * cure_string - string manipulations.
 */

#include <cure/cure_strlist.h>
#include <stdarg.h>

/* zStrListInsert
 * - insert a string to a list of strings.
 */
zStrListCell *zStrListInsert(zStrList *list, char str[])
{
  zStrListCell *cell;

  if( !( cell = zAlloc( zStrListCell, 1 ) ) ){
    ZALLOCERROR();
    return NULL;
  }
  if( !( cell->data = zStrClone( str ) ) ){
    ZALLOCERROR();
    free( cell );
    return NULL;
  }
  zListInsertHead( list, cell );
  return cell;
}

/* zStrListCellFree
 * - free a cell of a list of strings.
 */
void zStrListCellFree(zStrListCell *cell)
{
  free( cell->data );
  free( cell );
}

/* zStrListDestroy
 * - destroy a list of strings.
 */
void zStrListDestroy(zStrList *list)
{
  zStrListCell *cell;

  while( !zListIsEmpty( list ) ){
    zListDeleteTail( list, &cell );
    zStrListCellFree( cell );
  }
}

/* zStrListGetPtr
 * - get pointers to strings of a list.
 */
void zStrListGetPtr(zStrList *strlist, int n, ...)
{
  zStrListCell *cell;
  va_list args;
  char **ptr;

  cell = zListTail(strlist);
  va_start( args, n );
  while( --n >= 0 ){
    ptr = va_arg( args, char** );
    if( cell == zListRoot(strlist) )
      *ptr = NULL;
    else{
      *ptr = cell->data;
      cell = zListCellNext(cell);
    }
  }
  va_end( args );
}

/* zStrListFWrite
 * - output a list of strings to a file.
 */
void zStrListFWrite(FILE *fp, zStrList *list)
{
  zStrListCell *cell;

  zListForEach( list, cell )
    fprintf( fp, "%s\n", cell->data );
}
