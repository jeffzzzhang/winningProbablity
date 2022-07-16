// ConsoleApplication1.cpp : Defines the entry point for the console application.
// This application implements the maths models in Chap 4, the theoretical model of winning probability for the vehicles with and without movement,
// both original scheme and my proposal are conducted, namely, the CW is randomly selected or restrictly selected, ended up on 2016.09.19, since 09.0x or 1x
#include "stdafx.h"
#include<iostream>
// 2 header files for random generatoin
#include<cstdlib>
#include<ctime>
//
#include<vector>
// header file for SORTing
#include<algorithm>
// header file for type transfer
#include<cmath>
// global setup
#include"configuration.h"
// file output
//#include<fstream>
using namespace std;

void main()
{
	// 1. location initialisation, randomly-selected location, stored in the vector LOC_VEC
	srand((unsigned int)time(NULL));// moment as seed
    int cntr = 0;
	float tot_wp[rr + 1] = { 0.00000 };
	int vel_sd; //standard deviation of velocity
	switch (veh_den) {
	case 5: vel_sd = 6;
	case 15: vel_sd = 6;
	case 25: vel_sd = 5;
	default:;
	}
	while (iter_num > cntr) {
		int loc_array[veh_num];
		float rela_vel[veh_num];
		for (int i = 0; i < sizeof(loc_array) / sizeof(loc_array[0]); i++){
			loc_array[i] = rand() % (rr + 1);
			rela_vel[i] = static_cast<float>(rand() % (20 * vel_sd + 1)) / 10 - vel_sd;
		}
		vector<float> loc_vec(loc_array, loc_array + sizeof(loc_array) / sizeof(loc_array[0]));
		//------------------------------------------------------------------------------------
		// 2. sort the location in the same vec, in ascending order
		sort(loc_array, loc_array + veh_num, less<int>());//sort(loc_vec.begin(), loc_vec.end(),less<int>()); // or greater<int> for descending order
		//------------------------------------------------------------------------------------
		// 3. load function to get CW
		int veh_cw[veh_num];
		for (int j = 0; j < veh_num; j++) {
			if(rela_vel_in==0)
				veh_cw[j] = (1 - static_cast<float>(loc_array[j]) / rr)*(CW_max - CW_min) + CW_min;// keep in mind the type transfer
			else
				veh_cw[j] = (1 - (static_cast<float>(loc_array[j])- rela_vel[j]*mph2mps*updating_period)/ rr)*(CW_max - CW_min) + CW_min;
		}
		//------------------------------------------------------------------------------------
		// 4. the winning probability for each vehicle, and normalised since the sum is likely less than one
		// 1st: original scheme
		float wp[veh_num]; // 0: winning probability, 1: normalised winning probability
		for (int i = 0; i < veh_num; i++) {
			float tot_sum = 0;
			if (veh_cw[i] > CW_max || veh_cw[i] < CW_min){
				wp[i] = 0;
				continue;
			}
			//
			int min_posi_cw=15;
			if(veh_cw[veh_num - 1] >= CW_min)
				min_posi_cw = veh_cw[veh_num - 1];
			else
			{
				int tmp_cntr = veh_num-1;
				while (veh_cw[tmp_cntr - 1] < CW_min)
				{
					tmp_cntr--;
				}
				min_posi_cw = veh_cw[tmp_cntr - 1];
			}
			if (proposal_or_not == 1 && min_posi_cw + leng_limit - 1 <= veh_cw[i]){
				wp[i] = 0; 
				continue;
			}
			//
			int countdown_starting = 0;
			if (proposal_or_not == 1)
				countdown_starting = veh_cw[i]- leng_limit + 1;
			else
				countdown_starting = 0;
			for (int j = countdown_starting; j < min_posi_cw; j++) {
				float tot_prod = 1;
				for (int k = 0; k < veh_num; k++) {
					if (i == k) {
						continue;// avoid comparing with the veh itself
					}
					if (veh_cw[k] <= CW_max && veh_cw[k] >= CW_min){
						if(proposal_or_not==0)
							tot_prod *= (static_cast<float>(veh_cw[k]) - j - 1) / static_cast<float>(veh_cw[k]);// 
						else
							tot_prod *= (static_cast<float>(veh_cw[k]) - j - 1) / static_cast<float>(leng_limit);
					}
					else{
						continue;// compared with an excluded veh, then nothing done
					}
				}
				tot_sum += tot_prod / veh_cw[i];
			}
			wp[i] = tot_sum;
		}
		float tmp_sum = 0;
		float wp_normal[veh_num] = { 0 };
		for (int i = 0; i < veh_num; i++)
			tmp_sum += wp[i];
		for (int j = 0; j < veh_num; j++)
			wp_normal[j] = wp[j] / tmp_sum;
		for (int k = 0; k < veh_num; k++) {
			int tmp_k = k;
			tot_wp[loc_array[tmp_k]] = tot_wp[loc_array[tmp_k]] + wp_normal[tmp_k];
		}
		cntr++;
	}
	float tot_wp_pdf[rr + 1], tot_wp_cdf[rr + 1], tot_wp_sum[rr + 1] = { 0 };
	float tmp_sum = 0;
	for (int i = 0; i < rr + 1; i++) {
		tmp_sum += tot_wp[i];
		tot_wp_sum[i] = tmp_sum;
	}
	for (int j = 0; j < rr + 1; j++) {
		tot_wp_pdf[j] = tot_wp[j] / tot_wp_sum[rr];
		tot_wp_cdf[j] = tot_wp_sum[j] / tot_wp_sum[rr];
	}

	//ofstream ofs("C:\\C++ practice\WinningProbability\ConsoleApplication1\ConsoleApplication1\data.txt");
	//ofs << tot_wp<<endl;
	cout << "pause here";
}

