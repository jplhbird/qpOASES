/*
 *	This file is part of qpOASES.
 *
 *	qpOASES -- An Implementation of the Online Active Set Strategy.
 *	Copyright (C) 2007-2015 by Hans Joachim Ferreau, Andreas Potschka,
 *	Christian Kirches et al. All rights reserved.
 *
 *	qpOASES is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	qpOASES is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *	See the GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with qpOASES; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


/**
 *	\file examples/example1a.cpp
 *	\author Hans Joachim Ferreau
 *	\version 3.1
 *	\date 2007-2015
 *
 *	Very simple example for testing qpOASES using the SQProblem class.
 */



#include <qpOASES.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"


/** Example for qpOASES main function using the SQProblem class. */
int main( )
{
	USING_NAMESPACE_QPOASES

	/* Setup data of first QP. */
	real_t H[3*3] = { 5.0, 0.0, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 1.0};
	real_t A[1*3] =  { 0, 0, -19 };
	real_t g[3] = { 0.0, 0.0, 0.0 };
	real_t lb[3] =  { -100.0, -100.0, -100.0 };
	real_t ub[3] = { 500.0, 500.0, 500.0};
	real_t lbA[1] = {  -1000.0};
	real_t ubA[1] = { -1185 };

	/* Setup data of second QP. */
	real_t H_new[3*3] = { 5.0, 0.0, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 1.0};
	real_t A_new[1*3] = { 0, 0, -19 };
	real_t g_new[3] = { 0.0, 0.0, 0.0 };
	real_t lb_new[3] = { -100.0, -100.0, -100.0 };
	real_t ub_new[3] = { 500.0, 500.0, 500.0};
	real_t lbA_new[1] = {  -1000.0};
	real_t ubA_new[1] = { -1185 };


	/* Setting up SQProblem object. */
	SQProblem example( 3,1 );

	/* Solve first QP. */
	int nWSR = 10;
	example.init( H,g,A,lb,ub,lbA,ubA, nWSR,0 );

	/* Solve second QP. */
	nWSR = 10;
	//example.hotstart( H_new,g_new,A_new,lb_new,ub_new,lbA_new,ubA_new, nWSR,0 );


	long int ts_usec;
	long int time0;
	double ts_sec;
	double time_body;

	time0 = (uint64_t)(ros::WallTime::now().toSec() * 1.0e6);

	example.hotstart( H_new,g_new,A_new,lb_new,ub_new,lbA_new,ubA_new, nWSR,0);

 	ts_usec = (long int)(ros::WallTime::now().toSec() * 1.0e6);
	time_body =(double)(ts_usec-time0)/1.0e6;  //actual time used in calculation

	printf( "wasting time: %e \n", time_body);


	/* Get and print solution of second QP. */
	real_t xOpt[3];
	example.getPrimalSolution( xOpt );
	printf( "\nxOpt = [ %e, %e, %e ];  objVal = %e\n\n", xOpt[0],xOpt[1],xOpt[2],example.getObjVal() );

	printf( "\nwww\n\n" );

	return 0;
}


/*
 *	end of file
 */
