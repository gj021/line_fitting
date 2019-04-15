/**
 * @file line_fitting.cpp
 * @author Anshuman Padhi
 * @brief 
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <bits/stdc++.h>
#include "Points.h"

/**
 * @brief Class for calculating the optimal best lines for given input of points
 * 
 */
class lineFitting
{
    public:
    //Vector for storing optimal(j)
    vector<double> M;
    //Vector to store the point i for j till the best line fits
    vector<int> iforj;
    //Vectore to store position of best fit lines
    vector<pair<int,int>> fit_points;

    /**
     * @brief function to find the optimum pair of lines using Dynamic Programming.
     * 
     * @param c cost variable to keep in check the number of segments.
     * @param err error vector to store errors for best fit lines.
     */
    void find_optimum(double c, vector<vector<double>> err) 
    {
        M.push_back(0);
        iforj.push_back(0);

        for(int j=1; j<err.size(); j++)
        {
            double min_err = INT_MAX;
            double min_i = 0;
            for(int i=1; i<=j; i++)
            {
                double temp_err = err[i][j]+c+M[i-1];
                if(temp_err<=min_err)
                {
                    min_err = temp_err;
                    min_i=i;
                }
            }
            M.push_back(min_err);
            iforj.push_back(min_i);
        }
    }

    /**
     * @brief function to calculate the best fit lines from the calculated errors.
     * 
     * @param slope vector to store slopes for all possible pairs of lines.
     * @param intercept vector to store intercepts for all possible pairs of lines.
     */
    void fit_lines(vector<vector<double>> slope, vector<vector<double>> intercept) 
    {
        int j = M.size()-1;
        int i = iforj[j];

        while(j>0)
        {
            cout<<slope[i][j]<<","<<intercept[i][j]<<endl;
            fit_points.push_back(make_pair(i,j));
            j = i-1;
            i = iforj[j];
        }
    }
};

int main()
{
    Points p;
    p.takeInput("p3.txt");
    
    p.sortByx();
    int n=p.points.size();
   
    for(int i=0;i<p.points.size();i++)
    {
        vector<double> temp(n, INT_MAX);
        p.err.push_back(temp);
        p.slope.push_back(temp);
        p.intercept.push_back(temp);
    }

   

    p.calc_error();

    lineFitting lf[5];
    int c[5]={2,10,50,1000,8000};

    for(int i=0; i<5; i++)
    {
        lf[i].find_optimum(c[i],p.err);
        lf[i].fit_lines(p.slope,p.intercept);
        cout<<"***\n";
    }

    return 0;
}