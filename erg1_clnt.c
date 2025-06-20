/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "erg1.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

int *
eswt_ginom_1(pin_args *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ESWT_GINOM,
		(xdrproc_t) xdr_pin_args, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

averages_ret *
averages_1(pin_args *argp, CLIENT *clnt)
{
	static averages_ret clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, AVERAGES,
		(xdrproc_t) xdr_pin_args, (caddr_t) argp,
		(xdrproc_t) xdr_averages_ret, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

ginom_r_ret *
ginom_r_1(ginom_r_args *argp, CLIENT *clnt)
{
	static ginom_r_ret clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, GINOM_R,
		(xdrproc_t) xdr_ginom_r_args, (caddr_t) argp,
		(xdrproc_t) xdr_ginom_r_ret, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
