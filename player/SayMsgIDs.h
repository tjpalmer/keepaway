/*
Copyright (c) 2004, Gregory Kuhlmann, Peter Stone
University of Texas at Austin
All right reserved

Based On:

    Coachable Agent communication encoding and decoding library
    Copyright (C) 2004, John Davin, Carnegie Mellon University

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/*
 * SayMsgIDs.h - defines numeric codes that identify the say message types
 *  These codes are defined in the standardized coachable agent communication specification. 
 *
 * Creation Date: 11/18/03
 * Author: John Davin
 *
 * If any message types are added to the specification, their ID code must be added here, 
 *  and a message type class must be implemented in SayMsgTypes.h
 *
 *
 */

#ifndef SAY_MSG_IDS_H
#define SAY_MSG_IDS_H



#define OUR_POS_ID        0
//#define BALL_POS_ID       1
//#define BALL_VEL_ID       2
#define BALL_INFO_ID      1
#define WE_HAVE_BALL_ID   3
#define OPP_HAS_BALL_ID   4
#define PASS_TO_PLAYER_ID 5
#define PASS_TO_COORD_ID  6
#define WANT_PASS_ID      7
#define OPP_POS_ID        8
#define TEAMMATE_POS_ID  19




#endif



