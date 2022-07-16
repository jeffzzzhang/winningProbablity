#pragma once
const int CW_max = 1023;
const int CW_min = 15;
//-----------------------------------------------------------
const int veh_den = 15;
const bool proposal_or_not = 1;
const bool rela_vel_in = 0; 
//adjustable parameters, whether relative velocity is incoporated, 1: incorporated, 0: excluded;
const int leng_limit = 4; // 
const int veh_num = veh_den;
const int rr = 240;
const int iter_num = 100000; // iteration times
const int updating_period = 5;
const float mph2mps = 0.44704;