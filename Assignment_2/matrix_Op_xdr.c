/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "matrix_Op.h"

bool_t
xdr_matrix (XDR *xdrs, matrix *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->row))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->col))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->mat.mat_val, (u_int *) &objp->mat.mat_len, sz,
		sizeof (double), (xdrproc_t) xdr_double))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_data1 (XDR *xdrs, data1 *objp)
{
	register int32_t *buf;

	 if (!xdr_matrix (xdrs, &objp->A))
		 return FALSE;
	 if (!xdr_matrix (xdrs, &objp->B))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->operator))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_data2 (XDR *xdrs, data2 *objp)
{
	register int32_t *buf;

	 if (!xdr_matrix (xdrs, &objp->A))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->operator))
		 return FALSE;
	return TRUE;
}